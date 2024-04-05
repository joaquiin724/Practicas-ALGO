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

EOF

# Bucle para generar gráficos para cada algoritmo y tipo de dato
for ((i=4; i <= 10; i++)); do
    name="Viajante$i"
    cat << EOF >> script_gnuplot.gp

# Algoritmo $name
# Establece la leyenda, donde 
    # primer "" indica el lugar de donde tomar los datos
    # 1:2 indica que se tomará la primera columna para el eje x y la segunda para el eje y
    # with linespoints indica que se dibujarán líneas uniendo los puntos
    # segundo "" indica el nombre que se le dará a la serie
plot "Salidas/$name.txt" using 1:2 with linespoints title "$name", \\

EOF
done 

# Eliminar la última coma y agregar replot al final
sed -i '$ s/..$//' script_gnuplot.gp
echo "replot" >> script_gnuplot.gp

gnuplot script_gnuplot.gp