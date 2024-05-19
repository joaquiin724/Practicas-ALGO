import matplotlib.pyplot as plt
import sys

def leer_puntos(nombre_archivo):
    puntos = []
    with open(nombre_archivo, 'r') as archivo:
        for linea in archivo:
            x, y = map(float, linea.strip().split())
            puntos.append((x, y))
    return puntos

def leer_resultado(nombre_archivo):
    with open(nombre_archivo, 'r') as archivo:
        orden = list(map(int, archivo.readline().strip().split()))
    return orden

def graficar(puntos, orden, nombre_salida):
    x = [puntos[i][0] for i in orden]
    y = [puntos[i][1] for i in orden]
    plt.figure()
    plt.plot(x, y, marker='o', linestyle='-')
    plt.scatter(x, y, color='red')
    for i, (px, py) in enumerate(zip(x, y)):
        plt.text(px, py, f'{orden[i]}', fontsize=12, ha='right')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Camino del Viajante')
    plt.grid(True)
    plt.savefig(nombre_salida)
    plt.close()

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("Uso: python graph.py <archivo_puntos> <archivo_resultado> <archivo_salida>")
        sys.exit(1)
    
    archivo_puntos = sys.argv[1]
    archivo_resultado = sys.argv[2]
    archivo_salida = sys.argv[3]
    
    puntos = leer_puntos(archivo_puntos)
    orden = leer_resultado(archivo_resultado)
    graficar(puntos, orden, archivo_salida)
