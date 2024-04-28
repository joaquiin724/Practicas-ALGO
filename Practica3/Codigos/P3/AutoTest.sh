#!/bin/bash


num_archivos_puntos=5
num_grafos=2 # Número de grafos por archivo de puntos

# Ejecutar CreacionPuntos.cpp varias veces
for ((i=1; i <=$num_archivos_puntos; i++)); do
    # Nombre del archivo de puntos
    puntos_file="Ciudades/puntos_$i.txt"

    # Generar puntos
    ./Ejecutables/CreacionPuntos $num_puntos $rango_max_puntos $puntos_file

    # Ejecutar CreacionGrafos.cpp varias veces para cada archivo de puntos
    for ((j=1; j<=$num_grafos; j++)); do
        # Nombre del archivo de salida de la matriz
        matriz_file="Instancias/matriz_$i-$j.txt"

        # Procesar puntos y generar matriz
        ./Ejecutables/CreacionGrafos $puntos_file $matriz_file
    done
done

