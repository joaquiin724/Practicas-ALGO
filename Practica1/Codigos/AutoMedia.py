def convert_file(input_file, output_file):
    # Abre el fichero de entrada en modo lectura y el fichero de salida en modo escritura
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        # Itera sobre cada línea del fichero de entrada
        for line in f_in:
            # Divide la línea en dos partes a partir del caracter ':', el tamaño y los tiempos
            parts = line.split(':') 
             # Se queda con el tamaño de cada ejecución 
            size = parts[0].strip()
            values = list(map(float, parts[1].split())) # Crea el array de valores de tiempos
            avg = sum(values) / len(values) # Crea el array con los valores de los tiempos promedios
            avg_str = '{:.10f}'.format(avg) # Formatea el promedio para evitar la notación científica
            f_out.write(f'{size} {avg_str}\n') # Escribe el tamaño en el fichero y el tiempo promedio de ejecución

# Sirve para poder utilizar los parámetros de entrada
import sys

# Dos argumentos: el archivo de entrada y el archivo de salida
if len(sys.argv) != 3:
    print('Usage: python3 AutoMedia.py input_file output_file')
    sys.exit(1)
else:
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    convert_file(input_file, output_file)




