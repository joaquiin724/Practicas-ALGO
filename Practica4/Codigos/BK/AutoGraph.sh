#!/bin/bash
g++ -o Ejecutables/backtracking backtracking.cpp

# Ejecuta el código compilado para cada archivo .txt en la carpeta instancias que comienza con matriz
echo " " > Salidas/salida.txt
for file in Instancias/matriz_*.txt
do
    ./Ejecutables/backtracking $file 0 >> Salidas/salida.txt
done



archivo_tiempos="Salidas/salida.txt"
grafico_salida="Salidas/grafico_tiempos.png"

# Comprobar si el archivo de tiempos existe
if [ ! -f "$archivo_tiempos" ]; then
    echo "El archivo de tiempos '$archivo_tiempos' no existe."
    exit 1
fi

# Generar el gráfico con GNUplot
gnuplot <<- EOF
    set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
    set output '$grafico_salida'
    set title "Tiempos de Ejecución"
    set xlabel "Tamaño de Entrada"
    set ylabel "Tiempo (ns)"
    set grid
    set style data linespoints
    plot '$archivo_tiempos' using 1:2 title 'Tiempo de Ejecución' with linespoints lw 2 pt 7
EOF

echo "Gráfico generado en $grafico_salida"
