#!/bin/bash

# This Script executes de programs:
# opt variable for is the type of variable to execute (1 -> int , 2 -> float, 3 -> double)
# Then files is the executable files with O(n^2) complexity
# Then files2 is the executable files with O(nlogn) complexity
# If option "clean" is provided, the previous files are removed (CAUTION)
# Each file is executed with different sizes of data 5 times
# Once the files are executed, the python script AutoMedia.py is executed to get the average of the results
# The results are stored in the folder "Resultados"

for ((opt=1; opt <= 3 ; ++opt)); do 

    files=("burbuja" "insercion" "seleccion")
    # files = ("fibonacci" "hanoi" "floyd" "heapsort" "insercion" "mergesort" "quicksort" "seleccion")

    # Option 1 to remove previous files if argument provided
    if [ "$1" == "clean" ]; then
        rm -r Resultados
        rm -r *.txt
    fi

    for file in "${files[@]}"; do
        # Redireccion a archivo txt con los resultados con salto de linea tras cada archivo
        # printf "File: $file.cpp\n" >> $file.txt

        # Bucles principales de ejecucion-> i para el tamaño de los datos y j para el numero de ejecuciones
        for ((i=5000; i<=125000 ; i+=5000)) do
            printf "$i: \t\t" >> $file.txt
            for ((j=1; j<=5 ; j++)) do
                # Ejecucion del programa y redireccion a archivo txt
                ./$file $i $opt >> $file.txt            
                printf " " >> $file.txt
            done
            printf "\n" >> $file.txt
        done
    done

    mkdir Resultados

    for file in "${files[@]}"; do
        python3 AutoMedia.py $file.txt output$file.txt
    done

    # ALGORITMOS DE ORDENACION CON EFICIENCIA O(nlogn)----------------------------------------------

    files2=("mergesort" "quicksort")

    for file in "${files2[@]}"; do
        # Redireccion a archivo txt con los resultados con salto de linea tras cada archivo
        # printf "File: $file.cpp\n" >> $file.txt

        # Bucles principales de ejecucion-> i para el tamaño de los datos y j para el numero de ejecuciones
        for ((i=50000; i<=1250000 ; i+=50000)) do
            printf "$i: \t\t" >> $file.txt
            for ((j=1; j<=5 ; j++)) do
                # Ejecucion del programa y redireccion a archivo txt
                ./$file $i $opt >> $file.txt            
                printf " " >> $file.txt
            done
            printf "\n" >> $file.txt
        done
    done

    for file in "${files2[@]}"; do
        python3 AutoMedia.py $file.txt output$file.txt
    done


    mv *.txt ./Resultados
done


