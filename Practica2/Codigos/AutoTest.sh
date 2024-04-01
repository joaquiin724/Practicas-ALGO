#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")

# Cambiar al directorio del archivo
cd $script_directory

# ----------------------|Ejecución de SumaMax|---------------------- #
rm -f Salidas/SumaMax.txt
size=10000
opcion=2 # [1] Time Test || [2] Correctness Test

#---------------Tamaño|DyV|Alg. Iterativo-----------------#
for ((i=100; i <= $size; i+=100)); do
    if [ $opcion -eq 1 ]; then
        printf "$i " >> Salidas/SumaMax.txt
    fi
    ./Ejecutables/SumaMax $i $opcion >> Salidas/SumaMax.txt
done
