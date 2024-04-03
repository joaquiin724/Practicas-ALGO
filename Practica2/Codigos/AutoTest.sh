#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")

# Cambiar al directorio del archivo
cd $script_directory
chmod +x AutoCompile.sh
./AutoCompile.sh

# --------------------------|Ejecución de SumaMax|-----------------------------#
rm -f Salidas/SumaMax.txt
size=10000
opcion=2 # [1] Time Test || [2] Correctness Test

for ((i=100; i <= $size; i+=100)); do
    if [ $opcion -eq 1 ]; then
        printf "$i " >> Salidas/SumaMax.txt
    fi
    ./Ejecutables/SumaMax $i $opcion >> Salidas/SumaMax.txt
done

#---------------------------|Ejecucion Viajante|-------------------------------#

rm -f Salidas/Viajante.txt
size2=200 # Para el caso brute force a partir de 12 no se puede ejecutar
opcion2=2 # [1] Random test || [2] Made test 
files=("finlandTest.txt" "djibouti.txt")
#Soluciones: finlandTest.txt = 520527, djibouti.txt = 6656

if [ $opcion2 -eq 1 ]; then
    for ((i=5; i <= $size2; i+=10)) do
        ./Ejecutables/Viajante $i $opcion2 >> Salidas/Viajante.txt
    done
fi
if [ $opcion2 -eq 2 ]; then
    for ((i=0; i < ${#files[@]}; i++)) do
        filename=${files[$i]} # Arreglar
        ./Ejecutables/Viajante $filename $opcion2 >> Salidas/Viajante.txt
    done
fi


