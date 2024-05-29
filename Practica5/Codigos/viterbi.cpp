/* The basic Viterbi decoder operation, called a "butterfly"
 * operation because of the way it looks on a trellis diagram. Each
 * butterfly involves an Add-Compare-Select (ACS) operation on the two nodes
 * where the 0 and 1 paths from the current node merge at the next step of
 * the trellis.
 *
 * The code polynomials are assumed to have 1's on both ends. Given a
 * function encode_state() that returns the two symbols for a given
 * encoder state in the low two bits, such a code will have the following
 * identities for even 'n' < 64:
 *
 * 	encode_state(n) = encode_state(n+65)
 *	encode_state(n+1) = encode_state(n+64) = (3 ^ encode_state(n))
 *
 * Any convolutional code you would actually want to use will have
 * these properties, so these assumptions aren't too limiting.
 *
 * Doing this as a macro lets the compiler evaluate at compile time the
 * many expressions that depend on the loop index and encoder state and
 * emit them as immediate arguments.
 * This makes an enormous difference on register-starved machines such
 * as the Intel x86 family where evaluating these expressions at runtime
 * would spill over into memory.
 */
#include "viterbi.h"
#include "common.h"
#include <math.h>
using namespace SPUC;
#define	BUTTERFLY(i,sym) { \
	int m0,m1;\
\
	/* ACS for 0 branch */\
	m0 = state[i].metric + euclid[sym];	/* 2*i */\
	m1 = state[i+32].metric + euclid[3^sym];	/* 2*i + 64 */\
	if(m0 > m1){\
		next[2*i].metric = m0;\
		next[2*i].path = state[i].path << 1;\
	} else {\
		next[2*i].metric = m1;\
		next[2*i].path = (state[i+32].path << 1)|1;\
	}\
	/* ACS for 1 branch */\
	m0 = state[i].metric + euclid[3^sym];	/* 2*i + 1 */\
	m1 = state[i+32].metric + euclid[sym];	/* 2*i + 65 */\
	if(m0 > m1){\
		next[2*i+1].metric = m0;\
		next[2*i+1].path = state[i].path << 1;\
	} else {\
		next[2*i+1].metric = m1;\
		next[2*i+1].path = (state[i+32].path << 1)|1;\
	}\
}
/* Viterbi decoder */
bool viterbi::decode(
					 long symbol0,	/* Raw deinterleaved input symbols */
					 long symbol1	/* Raw deinterleaved input symbols */
				   )
{
  long euclid[4];
  bool current_decoded_bit;
  long bestmetric;
  int i;
  
  // Read input symbol pair and compute all possible branch metrics
  euclid[0] = (symbol0+symbol1);
  euclid[1] = (symbol0-symbol1);
  euclid[2] = -euclid[1];
  euclid[3] = -euclid[0];

  // These macro calls were generated by genbut.c 
  BUTTERFLY(0,0);  BUTTERFLY(1,1);  BUTTERFLY(2,3);  BUTTERFLY(3,2);
  BUTTERFLY(4,3);  BUTTERFLY(5,2);  BUTTERFLY(6,0);  BUTTERFLY(7,1);
  BUTTERFLY(8,0);  BUTTERFLY(9,1);  BUTTERFLY(10,3); BUTTERFLY(11,2);
  BUTTERFLY(12,3); BUTTERFLY(13,2); BUTTERFLY(14,0); BUTTERFLY(15,1);
  BUTTERFLY(16,2); BUTTERFLY(17,3); BUTTERFLY(18,1); BUTTERFLY(19,0);
  BUTTERFLY(20,1); BUTTERFLY(21,0); BUTTERFLY(22,2); BUTTERFLY(23,3);
  BUTTERFLY(24,2); BUTTERFLY(25,3); BUTTERFLY(26,1); BUTTERFLY(27,0);
  BUTTERFLY(28,1); BUTTERFLY(29,0); BUTTERFLY(30,2); BUTTERFLY(31,3);

  // Swap current and next states
  if (bitcnt & 1){
	state = state0;
	next = state1;
  } else {
	state = state1;
	next = state0;
  }
  // Delay by 32 + 5 bits
  if (bitcnt == 37)	enable_output = 1;
  // Find current best path
  bestmetric = state[0].metric;
  beststate = 0;
  for(i=1;i<64;i++){
	if(state[i].metric > bestmetric){
	  bestmetric = state[i].metric;
	  beststate = i;
	}
  }
  current_decoded_bit = (state[beststate].path & 0x80000000) ? 1 : 0;
  bitcnt++;
  return current_decoded_bit;
}
bool viterbi::depuncture(const long steal, long soft_in)
{
  bool viterbi_data;
  if (steal>1) { // ! rate 1/2
	if (steal < 4) {
	  switch (depuncture_bit_number) {
	  case 0: 
		viterbi_data = clock(soft_in);
		if (phase) depuncture_bit_number++;
		break;
	  case 1: 
		viterbi_data = clock(soft_in);
		viterbi_data = clock(0);
		depuncture_bit_number++;
		break;
	  case 2:
		viterbi_data = clock(0);
		viterbi_data = clock(soft_in);
		depuncture_bit_number++;
		break;
	  }
	} else if (steal == 5) {
	  switch (depuncture_bit_number) {
	  case 0: 
		viterbi_data = clock(soft_in);
		if (phase) depuncture_bit_number++;
		break;
	  case 1: 
		viterbi_data = clock(soft_in);
		viterbi_data = clock(0);
		depuncture_bit_number++;
		break;
	  case 2:
		viterbi_data = clock(0);
		viterbi_data = clock(soft_in);
		depuncture_bit_number++;
		break;
	  case 3: 
		viterbi_data = clock(soft_in);
		viterbi_data = clock(0);
		depuncture_bit_number++;
		break;
	  case 4:
		viterbi_data = clock(0);
		viterbi_data = clock(soft_in);
		depuncture_bit_number++;
		break;
	  }
	}
  } else {
	viterbi_data = clock(soft_in);
  }
  phase = !phase;
  if (depuncture_bit_number == steal) {
	depuncture_bit_number = 0;
	phase = 0;
  }
  return(viterbi_data);
}