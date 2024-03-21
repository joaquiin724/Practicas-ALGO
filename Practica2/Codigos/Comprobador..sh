#!/bin/bash

name="sumaMax"
size=1000
echo "" > Codigos/Salida/Prueba.txt;
for ((i=10; i <= $size; i+=10)); do
    ./Codigos/Ejecutables/$name $i >> Codigos/Salida/Prueba.txt
done
