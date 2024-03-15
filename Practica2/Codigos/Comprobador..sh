#!/bin/bash

name="sumaMax"
nveces=25

for ((i=1; i <= $nveces; i++)); do
    ./Codigos/Ejecutables/$name >> Codigos/Salida/Prueba.txt
done
