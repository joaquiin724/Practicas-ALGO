def convert_file(input_file, output_file):
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        for line in f_in:
            parts = line.split(':') # Divide la línea en dos partes a partir del caracter ':'
            size = parts[0].strip() # Se queda con el tamaño de cada ejecución
            values = list(map(float, parts[1].split())) # Crea el array de valores de tiempos
            avg = sum(values) / len(values) # Crea el array con los valores de los tiempos promedios
            avg_str = '{:.10f}'.format(avg) # Formatea el promedio para evitar la notación científica
            f_out.write(f'{size} {avg_str}\n') # Escribe el tamaño en el fichero y el tiempo promedio de ejecución

import sys

# Dos argumentos: el archivo de entrada y el archivo de salida
if len(sys.argv) != 3:
    print('Usage: python3 AutoMedia.py input_file output_file')
    sys.exit(1)
else:
    input_file = sys.argv[1]
    output_file = sys.argv[2]
    convert_file(input_file, output_file)




