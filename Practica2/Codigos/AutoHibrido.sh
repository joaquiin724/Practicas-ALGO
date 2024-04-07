#!/bin/bash
# Script solo para crear gráficas de ajuste híbrido
script_directory=$(dirname "$0")
cd $script_directory
name="Viajante"


# Crear un script de Gnuplot para generar los archivos, todo lo que hay entre EOF y EOF se escribe en un archivo,
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
#Definimos unna función para los métodos factoriales
f(x) = a0*


#Indicamos al gnuplot que haga la regresión
fit f(x) "Salidas/$name.txt" via a0,a1

#Imprimimos las graficas a excepción del tipo string que estará en otra gráfica distinta
plot "Salidas/$name.txt", f(x) title "Curva ajustada $name"  
# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./Graficas/${name}_hib.png"
replot

EOF


# Ejecutar Gnuplot con el script generado
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp

name="SumaMaxDyV"
rm -r Graficas/SumaMax${name}_hib


# Crear un script de Gnuplot para generar los archivos, todo lo que hay entre EOF y EOF se escribe en un archivo,
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
#Definimos unna función para los métodos cuadraticos
f(x) = a0*x+a1


#Indicamos al gnuplot que haga la regresión
fit f(x) "Salidas/$name.txt" via a0,a1

#Imprimimos las graficas a excepción del tipo string que estará en otra gráfica distinta
plot "Salidas/$name.txt", f(x) title "Curva ajustada $name"  
# Guardar la gráfica en un archivo de imagen, definiendo el formato primero y el nombre del archivo después
set term png
set output "./Graficas/${name}_hib.png"
replot

EOF


# Ejecutar Gnuplot con el script generado
gnuplot script_gnuplot.gp

# Eliminar el script de Gnuplot
rm script_gnuplot.gp
