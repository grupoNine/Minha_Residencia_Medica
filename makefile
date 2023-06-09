# 'make run' compila e executa o programa principal.
# 'make run-debug'
# 'make clean' limpa os arquivos temporários e o executável.
# 'make test' compila e executa os testes.
# 'make test-debug'

# gcc como o compilador C
CC = gcc

# diretório de inclusão
INCLUDES = -I./src

# diretório de compilação
BUILD_DIR = build

# executável de saída
EXECUTABLE = main

# arquivos de origem
SOURCES = $(wildcard src/*.c)
MAIN_SOURCE = main.c

# arquivos objeto
MAIN_OBJECT = $(BUILD_DIR)/main.o
OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.c=.o)))

# são comandos não são arquivos
.PHONY: run clean test run-debug test-debug

# 'make run' compila e executa o programa principal
run: $(BUILD_DIR)/$(EXECUTABLE)
	./$(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR)/$(EXECUTABLE): $(MAIN_OBJECT) $(OBJECTS)
	$(CC) $^ -o $@

$(MAIN_OBJECT): $(MAIN_SOURCE)
	$(CC) -g $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/%.o: src/%.c
	$(CC) -g $(INCLUDES) -c $< -o $@

# 'make clean' limpa arquivos temporários e o executável
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/$(EXECUTABLE) $(BUILD_DIR)/Tests

# 'make test' compila e executa os testes
test: $(BUILD_DIR)/Tests
	./$(BUILD_DIR)/Tests > tests/tests.txt

$(BUILD_DIR)/Tests: $(BUILD_DIR)/Tests.o $(OBJECTS)
	$(CC) $^ -o $@

$(BUILD_DIR)/Tests.o: tests/tests.c
	$(CC) -g $(INCLUDES) -c $< -o $@

# 'make run-debug'
run-debug: $(BUILD_DIR)/$(EXECUTABLE)
	gdb $(BUILD_DIR)/$(EXECUTABLE)

# 'make test-debug'
test-debug: $(BUILD_DIR)/Tests
	gdb $(BUILD_DIR)/Tests
