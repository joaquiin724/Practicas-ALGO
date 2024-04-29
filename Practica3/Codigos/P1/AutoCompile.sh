#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")
cd $script_directory

# Compilar los programas
gcc -O2 Herencia.cpp -o Ejecutables/Herencia -lstdc++ -lm