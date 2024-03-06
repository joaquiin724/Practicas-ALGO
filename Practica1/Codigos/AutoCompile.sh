#!/bin/bash

rm -r Ejecutables
mkdir Ejecutables
gcc -Og seleccion.cpp -o Ejecutables/seleccion -lstdc++
gcc -Og burbuja.cpp -o burbuja -lstdc++
gcc -Og insercion.cpp -o insercion -lstdc++
gcc -Og mergesort.cpp -o mergesort -lstdc++
gcc -Og quicksort.cpp -o quicksort -lstdc++
gcc -Og fibonacci.cpp -o fibonacci -lstdc++
gcc -Og hanoi.cpp -o hanoi -lstdc++
gcc -Og floyd.cpp -o floyd -lstdc++