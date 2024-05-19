# Directorios
GEN_DIR = Generador
ALG_DIR = Algoritmo
INST_DIR = Instancias
OUT_DIR = Salidas
GRAPH_DIR = Graficos

# Archivos fuente
GEN_SOURCES = $(wildcard $(GEN_DIR)/*.cpp)
ALG_SOURCES = $(wildcard $(ALG_DIR)/*.cpp)

# Ejecutables
CREA_PUNTOS_EXEC = $(GEN_DIR)/creacion_puntos
CREA_MATRICES_EXEC = $(GEN_DIR)/creacion_matrices
ALG_EXEC = $(ALG_DIR)/viajante_bb

# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++20 -O3

# Variables de cantidad de archivos
TAM = 13
NUM = 1

all: generate run graph

# Regla para compilar CreacionPuntos
$(CREA_PUNTOS_EXEC): $(GEN_DIR)/CreacionPuntos.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar CreacionMatrices
$(CREA_MATRICES_EXEC): $(GEN_DIR)/CreacionMatrices.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar ViajanteBB
$(ALG_EXEC): $(ALG_DIR)/ViajanteBB.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para ejecutar el generador y crear instancias
generate: $(CREA_PUNTOS_EXEC) $(CREA_MATRICES_EXEC)
	@echo "Generando instancias..."
	@mkdir -p $(INST_DIR)
	@for size in $(shell seq 3 $(TAM)); do \
	    for inst in $(shell seq 1 $(NUM)); do \
	        puntos_file=$(INST_DIR)/puntos_$${size}_$${inst}.txt; \
	        matriz_file=$(INST_DIR)/matriz_$${size}_$${inst}.txt; \
	        $(CREA_PUNTOS_EXEC) $${size} $${puntos_file} 50; \
	        $(CREA_MATRICES_EXEC) $${puntos_file} $${matriz_file}; \
	    done \
	done
	@echo "Instancias generadas en $(INST_DIR)"

# Regla para ejecutar el algoritmo con las instancias
run: $(ALG_EXEC)
	@echo "Ejecutando algoritmo..."
	@mkdir -p $(OUT_DIR)
	@for size in $(shell seq 3 $(TAM)); do \
	    for inst in $(shell seq 1 $(NUM)); do \
	        matriz_file=$(INST_DIR)/matriz_$${size}_$${inst}.txt; \
	        resultado_file=$(OUT_DIR)/resultado_$${size}_$${inst}.txt; \
	        $(ALG_EXEC) $${matriz_file} 1 > $${resultado_file}; \
	    done \
	done
	@echo "Resultados guardados en $(OUT_DIR)"

# Regla para graficar los resultados
graph: $(OUT_DIR)/*.txt
	@echo "Generando gráficos..."
	@mkdir -p $(GRAPH_DIR)
	@for size in $(shell seq 3 $(TAM)); do \
	    for inst in $(shell seq 1 $(NUM)); do \
	        puntos_file=$(INST_DIR)/puntos_$${size}_$${inst}.txt; \
	        resultado_file=$(OUT_DIR)/resultado_$${size}_$${inst}.txt; \
	        grafico_file=$(GRAPH_DIR)/grafico_$${size}_$${inst}.png; \
	        ./graph.sh $${puntos_file} $${resultado_file} $${grafico_file}; \
	    done \
	done
	@echo "Gráficos generados en $(GRAPH_DIR)"

clean:
	@echo "Limpiando archivos compilados y resultados..."
	@rm -f $(CREA_PUNTOS_EXEC) $(CREA_MATRICES_EXEC) $(ALG_EXEC)
	@rm -rf $(INST_DIR)/*
	@rm -rf $(OUT_DIR)/*
	@rm -rf $(GRAPH_DIR)/*

.PHONY: all generate run graph clean
