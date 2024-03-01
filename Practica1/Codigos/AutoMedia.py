def convert_file(input_file, output_file):
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        for line in f_in:
            parts = line.split(':')
            size = parts[0].strip()
            values = list(map(float, parts[1].split()))
            avg = sum(values) / len(values)
            f_out.write(f'{size} {avg}\n')

import sys

# Dos argumentos: el archivo de entrada y el archivo de salida
if len(sys.argv) != 3:
    print('Usage: python AutoMedia.py input_file output_file')
    sys.exit(1)
else:
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    convert_file(input_file, output_file)




