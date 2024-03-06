#!/bin/bash
# Este archivo es como el autorun pero sirve para ejecutar un solo archivo, en este
# caso, el archivo especificado en la siguiente variable:

name="floyd"
rm -r Grafica$name

# Crear un directorio para guardar las gráficas
mkdir Grafica$name

for ((j=1; j<=3 ; j++)) do
    for ((i=50; i<=200 ; i+=50)) do
            printf "$i \t" >> Grafica$name/SalidaTest$j$name.txt
            ./Ejecutables/$name $i $j >> Grafica$name/SalidaTest$j$name.txt            
            printf "\n" >> Grafica$name/SalidaTest$j$name.txt
    done
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

# Algoritmo $name
# Da un nombre a la gráfica
set title "Algoritmo - $name"
# Establece la leyenda, donde 
    # primer "" indica el lugar de donde tomar los datos
    # 1:2 indica que se tomará la primera columna para el eje x y la segunda para el eje y
    # with linespoints indica que se dibujarán líneas uniendo los puntos
    # segundo "" indica el nombre que se le dará a la serie
plot "Grafica$name/SalidaTest1$name.txt" using 1:2 with linespoints title "int", \
     "Grafica$name/SalidaTest2$name.txt" using 1:2 with linespoints title "float", \
     "Grafica$name/SalidaTest3$name.txt" using 1:2 with linespoints title "double"

# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./Grafica$name/${name}.png"
replot
EOF

# Ejecutar Gnuplot con el script generado
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp
