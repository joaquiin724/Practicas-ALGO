#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")
cd $script_directory

# Compilar los programas
g++ -o Ejecutable/CreacionPuntos CreacionPuntos.cpp
g++ -o Ejecutable/CreacionMatrices CreacionMatrices.cpp
g++ -o Ejecutable/Backtracking Backtracking.cpp