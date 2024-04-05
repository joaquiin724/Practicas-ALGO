#!/bin/bash
# Script solo para crear gráficas
script_directory=$(dirname "$0")
cd $script_directory

# Gnuplot para generar la gráfica, todo lo que hay entre EOF y EOF se escribe en un archivo,
# en este caso, script_gnuplot.gp
cat << EOF > script_gnuplot.gp
# Configuración del gráfico, se define el nombre de los ejes
set xlabel "Tamaño de entrada"
set ylabel "Tiempo de ejecución"
set title "Comparación de Algoritmos Viajante"
set term png
set output "Graficas/Comparacion.png"
set key outside

# Algoritmo $name
# Establece la leyenda, donde 
    # primer "" indica el lugar de donde tomar los datos
    # 1:2 indica que se tomará la primera columna para el eje x y la segunda para el eje y
    # with linespoints indica que se dibujarán líneas uniendo los puntos
    # segundo "" indica el nombre que se le dará a la serie
plot "Salidas/Viajante4.txt" using 1:2 with linespoints title "Umbral 4", \\
     "Salidas/Viajante5.txt" using 1:2 with linespoints title "Umbral 5", \\
     "Salidas/Viajante6.txt" using 1:2 with linespoints title "Umbral 6", \\
     "Salidas/Viajante7.txt" using 1:2 with linespoints title "Umbral 7", \\
     "Salidas/Viajante8.txt" using 1:2 with linespoints title "Umbral 8", \\
     "Salidas/Viajante9.txt" using 1:2 with linespoints title "Umbral 9"
EOF

# Ejecuta gnuplot con el script generado
gnuplot script_gnuplot.gp