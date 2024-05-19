import matplotlib.pyplot as plt

def leer_camino_desde_archivo(nombre_archivo):
    with open(nombre_archivo, 'r') as archivo:
        lineas = archivo.readlines()
        camino = list(map(int, lineas[0].strip().split()))
        coordenadas = []
        for linea in lineas[1:]:
            nodo, x, y = map(float, linea.strip().split())
            coordenadas.append((x, y))
        return camino, coordenadas

def graficar_camino(camino, coordenadas):
    x = [coordenadas[i][0] for i in camino]
    y = [coordenadas[i][1] for i in camino]

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
    camino, coordenadas = leer_camino_desde_archivo('camino.txt')
    graficar_camino(camino, coordenadas)
