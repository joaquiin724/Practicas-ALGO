#!/bin/bash

name="sumaMax"
size=10000
echo "" > Codigos/Salida/Prueba.txt;
for ((i=100; i <= $size; i+=100)); do
    ./Codigos/Ejecutables/$name $i >> Codigos/Salida/Prueba.txt
done
