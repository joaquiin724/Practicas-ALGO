# Configuración del gráfico, se define el nombre de los ejes
set xlabel "Tamaño de entrada"
set ylabel "Tiempo de ejecución"


# Algoritmo SumaMaxKadane_Umbral_3000
# Da un nombre a la gráfica
set title "Algoritmo - SumaMaxKadaneUmbral3000"
# Establece la leyenda, donde 
    # primer "" indica el lugar de donde tomar los datos
    # 1:2 indica que se tomará la primera columna para el eje x y la segunda para el eje y
    # with linespoints indica que se dibujarán líneas uniendo los puntos
    # segundo "" indica el nombre que se le dará a la serie
plot "Salidas/SumaMaxKadane_Umbral_3000.txt" using 1:2 with linespoints title "SumaMaxKadaneUmbral3000"

# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "Graficas/SumaMaxKadaneUmbral3000.png"
replot
