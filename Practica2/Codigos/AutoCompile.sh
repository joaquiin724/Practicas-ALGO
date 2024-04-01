#!/bin/bash

# Obtener la ruta completa del script actual
script_directory=$(dirname "$0")

gcc -Og SumaMax.cpp -o Ejecutables/SumaMax -lstdc++
gcc -Og Losetas.cpp -o Ejecutables/Losetas -lstdc++
gcc -Og Viajante.cpp -o Ejecutables/Viajante -lstdc++