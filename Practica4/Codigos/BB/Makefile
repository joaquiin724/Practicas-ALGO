# Directorios
GEN_DIR = Generador
ALG_DIR = Algoritmo
INST_DIR = Instancias
OUT_DIR = Salidas

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

all: $(CREA_PUNTOS_EXEC) $(CREA_MATRICES_EXEC) $(ALG_EXEC)

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
	$(CREA_PUNTOS_EXEC) 5 $(INST_DIR)/puntos_5.txt 50
	$(CREA_MATRICES_EXEC) $(INST_DIR)/puntos_5.txt $(INST_DIR)/matriz_5.txt
	$(CREA_PUNTOS_EXEC) 10 $(INST_DIR)/puntos_10.txt 50
	$(CREA_MATRICES_EXEC) $(INST_DIR)/puntos_10.txt $(INST_DIR)/matriz_10.txt
	$(CREA_PUNTOS_EXEC) 14 $(INST_DIR)/puntos_14.txt 50
	$(CREA_MATRICES_EXEC) $(INST_DIR)/puntos_14.txt $(INST_DIR)/matriz_14.txt
	@echo "Instancias generadas en $(INST_DIR)"

# Regla para ejecutar el algoritmo con las instancias
run: $(ALG_EXEC)
	@echo "Ejecutando algoritmo..."
	@mkdir -p $(OUT_DIR)
	$(ALG_EXEC) $(INST_DIR)/matriz_5.txt 1 > $(OUT_DIR)/resultado_5.txt
	$(ALG_EXEC) $(INST_DIR)/matriz_10.txt 1 > $(OUT_DIR)/resultado_10.txt
	$(ALG_EXEC) $(INST_DIR)/matriz_14.txt 1 > $(OUT_DIR)/resultado_14.txt
	@echo "Resultados guardados en $(OUT_DIR)"

clean:
	@echo "Limpiando archivos compilados y resultados..."
	@rm -f $(CREA_PUNTOS_EXEC) $(CREA_MATRICES_EXEC) $(ALG_EXEC)
	@rm -rf $(INST_DIR)/*
	@rm -rf $(OUT_DIR)/*

.PHONY: all generate run clean
