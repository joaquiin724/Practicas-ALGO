#!/bin/bash

# vector with files to execute
files=("burbuja" )
# files = ("fibonacci" "hanoi" "floyd" "heapsort" "insercion" "mergesort" "quicksort" "seleccion")

# Option 1 to remove previous files if argument provided
if [ "$1" == "clean" ]; then
    rm -r Resultados
fi


for file in "${files[@]}"; do
    # Redireccion a archivo txt con los resultados con salto de linea tras cada archivo
    printf "File: $file.cpp\n" >> $file.txt


    # Bucles principales de ejecucion-> i para el tamaño de los datos y j para el numero de ejecuciones
    for ((i=1; i<=10000 ; i*=10)) do
            printf "\nSize $i:\t" >> $file.txt
        for ((j=1; j<=10 ; j++)) do
            # Ejecucion del programa y redireccion a archivo txt
            ./$file $i >> $file.txt            
            printf " " >> $file.txt
        done
    done
done

mkdir Resultados
mv *.txt ./Resultados
