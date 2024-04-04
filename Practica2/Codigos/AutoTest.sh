#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")

# Cambiar al directorio del archivo
cd $script_directory
chmod +x AutoCompile.sh
./AutoCompile.sh

# --------------------------|Ejecución de SumaMax|-----------------------------#

size=1000000
opcion=3 # [1] Time Test Kadane || [2] Time Test DyV || [3] Correctness Test
if [ $opcion -eq 1 ]; then
    rm -f Salidas/SumaMaxKadane.txt
fi
if [ $opcion -eq 2 ]; then
    rm -f Salidas/SumaMaxDyV.txt
fi


for ((i=2500; i <= $size; i+=2500)); do
    if [ $opcion -eq 1 ]; then
        printf "$i " >> Salidas/SumaMaxKadane.txt
        ./Ejecutables/SumaMax $i $opcion >> Salidas/SumaMaxKadane.txt
    fi
    if [ $opcion -eq 2 ]; then
        printf "$i " >> Salidas/SumaMaxDyV.txt
        ./Ejecutables/SumaMax $i $opcion >> Salidas/SumaMaxDyV.txt
    fi
    if [ $opcion -eq 3 ]; then
        ./Ejecutables/SumaMax $i $opcion >> Salidas/SumaMax.txt
    fi
done

#---------------------------|Ejecucion Viajante|-------------------------------#

rm -f Salidas/Viajante.txt
size2=20 # Para el caso brute force a partir de 12 no se puede ejecutar
opcion2=2 # [1] Random test || [2] Made test 
files=(
    "Paises/Finland.txt" 
    "Paises/Nicaragua.txt" 
    "Paises/Djibouti.txt" 
    "Paises/Egypt.txt" 
    "Paises/Oman.txt"
    "Paises/Vietnam.txt"
    "Paises/Uruguay.txt"
    "Paises/Canada.txt"
    "Paises/Greece.txt"
    "Paises/Japan.txt"
    "Paises/China.txt"
    "Paises/Burma.txt"
    )
#Solucion: Finland = 520527, Djibouti = 6656, Oman = 86891, Nicaragua = 96132, Egypt = 172387
# Vietnam = 569288  Uruguay = 79114 Canada = 1290319 Greece = 300899 Japan = 491924 China = 4566563
# Burma = 959304

if [ $opcion2 -eq 1 ]; then
    for ((i=10; i <= $size2; i+=2)) do
        ./Ejecutables/Viajante $i $opcion2 >> Salidas/Viajante.txt
    done
fi
if [ $opcion2 -eq 2 ]; then
    for ((i=0; i < ${#files[@]}; i++)) do
        ./Ejecutables/Viajante ${files[i]} $opcion2 >> Salidas/Viajante.txt
    done
fi

