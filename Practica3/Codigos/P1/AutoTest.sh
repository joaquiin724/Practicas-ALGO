#!/bin/bash

num_bienes=100000
rm -r Salidas/Resultados/
rm -r Salidas/Tiempos/

for ((i=1000; i < $num_bienes; i+=1000)); do

    # Nombre del archivo de salida
    salida="Salidas/Resultados/Herencia_$i.txt"
    ./Ejecutables/Herencia $i $salida

    printf "$i " >> Salidas/Tiempos/Herencia.txt
    ./Ejecutables/Herencia $i $salida  >> Salidas/Tiempos/Herencia.txt

    
done