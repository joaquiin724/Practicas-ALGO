import matplotlib.pyplot as plt

def leer_camino_desde_archivo(nombre_archivo):
    with open(nombre_archivo, 'r') as archivo:
        lineas = archivo.readlines()
        camino = []
        coordenadas = []
        for linea in lineas:
            nodo, x, y = map(int, linea.strip().split())
            camino.append(nodo)
            coordenadas.append((x, y))
        return camino, coordenadas

def graficar_camino(camino, coordenadas):
    x = [coord[0] for coord in coordenadas]
    y = [coord[1] for coord in coordenadas]

    plt.figure(figsize=(10, 6))
    plt.plot(x, y, marker='o', linestyle='-', color='b')
    plt.scatter(x, y, color='r')
    for i, (x_coord, y_coord) in enumerate(zip(x, y)):
        plt.text(x_coord, y_coord, f'{camino[i]}', fontsize=12, ha='right')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Camino del Viajante')
    plt.grid(True)
    plt.show()

if __name__ == '__main__':
    camino, coordenadas = leer_camino_desde_archivo('Puntos_2.txt')
    graficar_camino(camino, coordenadas)
