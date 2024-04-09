#!/bin/bash

# Script solo para buscar el mejor umbral práctico
script_directory=$(dirname "$0")
cd "$script_directory" || exit

rm -f Salidas/SumaMaxKadane_Umbral*


size=10000000
umbral=6000
opcion=2


for ((i=1000; i <= $umbral; i+=1000)); do
    best_solution=1000000000
    for ((j=10;j<=$size;j*=10)); do

        printf "$j " >> Salidas/SumaMaxKadane_Umbral_$i.txt
        ./Ejecutables/SumaMax $j $opcion $i >> Salidas/SumaMaxKadane_Umbral_$i.txt
        
    done


# Crear un script de Gnuplot para generar la gráfica, todo lo que hay entre EOF y EOF se escribe en un archivo,
# en este caso, script_gnuplot.gp
cat << EOF > script_gnuplot.gp
# Configuración del gráfico, se define el nombre de los ejes
set xlabel "Tamaño de entrada"
set ylabel "Tiempo de ejecución"

EOF

# Bucle para generar gráficos para cada algoritmo y tipo de dato
cat << EOF >> script_gnuplot.gp

# Algoritmo SumaMaxKadane_Umbral_$i
# Da un nombre a la gráfica
set title "Algoritmo - SumaMaxKadaneUmbral$i"
# Establece la leyenda, donde 
    # primer "" indica el lugar de donde tomar los datos
    # 1:2 indica que se tomará la primera columna para el eje x y la segunda para el eje y
    # with linespoints indica que se dibujarán líneas uniendo los puntos
    # segundo "" indica el nombre que se le dará a la serie
plot "Salidas/SumaMaxKadane_Umbral_$i.txt" using 1:2 with linespoints title "SumaMaxKadaneUmbral$i"

# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "Graficas/SumaMaxKadaneUmbral$i.png"
replot
EOF
# Ejecutar Gnuplot con el script generado
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp
done
