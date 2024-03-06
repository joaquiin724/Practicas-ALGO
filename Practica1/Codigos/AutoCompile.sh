#!/bin/bash

rm -r Ejecutables
mkdir Ejecutables
gcc -Og seleccion.cpp -o Ejecutables/seleccion -lstdc++
gcc -Og burbuja.cpp -o Ejecutables/burbuja -lstdc++
gcc -Og insercion.cpp -o Ejecutables/insercion -lstdc++
gcc -Og mergesort.cpp -o Ejecutables/mergesort -lstdc++
gcc -Og quicksort.cpp -o Ejecutables/quicksort -lstdc++
gcc -Og fibonacci.cpp -o Ejecutables/fibonacci -lstdc++
gcc -Og hanoi.cpp -o Ejecutables/hanoi -lstdc++
gcc -Og floyd.cpp -o Ejecutables/floyd -lstdc++