#!/bin/bash# Este archivo tiene la finalidad de obtener las graficas de 
# la eficiencia hibrida de los metodos de floyd,fibonacci y hanoi

rm -r AjusteHibrido/Hibrido_fibonacci_floyd_hanoi

# Crear un directorio para guardar los archivos
mkdir AjusteHibrido/Hibrido_fibonacci_floyd_hanoi

# Crear un script de Gnuplot para generar los archivos, todo lo que hay entre EOF y EOF se escribe en un archivo,
# en este caso, script_gnuplot.gp
cat << EOF > script_gnuplot.gp
# Configuración del gráfico, se define el nombre de los ejes
set xlabel "Tamaño de entrada"
set ylabel "Tiempo de ejecución"

EOF

# Bucle para generar gráficos para cada algoritmo y tipo de dato
cat << EOF >> script_gnuplot.gp

# Algoritmo Floyd
# Da un nombre a la gráfica
set title "Algoritmo - Floyd"
#Definimos unna función para el metodo Floyd
fl(x) = a0*x*x*x

#Indicamos al gnuplot que haga la regresión
fit fl(x) "Resultados/Salidafloyd.txt" via a0

#Imprimimola gráfica
plot "Resultados/Salidafloyd.txt", fl(x) title "Curva ajustada "  
# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./AjusteHibrido/Hibrido_fibonacci_floyd_hanoi/Floyd.png"
replot

#Algoritmo Fibonacci
# Da un nombre a la gráfica
set title "Algoritmo - Fibonacci"
#Definimos unna función para el metodo Fibonacci
fi(x) = b0*((1+sqrt(5))/2)**x

#Indicamos al gnuplot que haga la regresión
fit fi(x) "Resultados/Salidafibonacci.txt" via b0

#Imprimimola gráfica
plot "Resultados/Salidafibonacci.txt", fi(x) title "Curva ajustada "  
# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./AjusteHibrido/Hibrido_fibonacci_floyd_hanoi/Fibonacci.png"
replot

#Algoritmo Hanoi
# Da un nombre a la gráfica
set title "Algoritmo - Hanoi"
#Definimos unna función para el metodo Hanoi
h(x) = c0*2**x

#Indicamos al gnuplot que haga la regresión
fit h(x) "Resultados/Salidahanoi.txt" via c0

#Imprimimola gráfica
plot "Resultados/Salidahanoi.txt", h(x) title "Curva ajustada "  
# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./AjusteHibrido/Hibrido_fibonacci_floyd_hanoi/Hanoi.png"
replot

EOF


# Ejecutar Gnuplot con el script generado
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp

