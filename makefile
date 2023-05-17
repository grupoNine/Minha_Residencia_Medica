# Lista de comandos:
# make build: Compila o programa principal.
# make run: Compila e executa o programa principal.
# make test: Executa todos os testes.
# make clean: Limpa o projeto, removendo arquivos objeto, executáveis e resultados de testes.
# make nome_do_teste_test: Executa um teste específico, onde 'nome_do_teste' é o nome do teste.

# Se a variável OSTYPE for igual a 'cygwin', as variáveis CLEANUP, MKDIR e TARGET_EXTENSION serão definidas como abaixo.
# Essa seção é usada para configurar comandos dependendo do sistema operacional onde o código é compilado.
#ifeq ($(OSTYPE),cygwin)
#	CLEANUP=rm -f  # Comando para remover arquivos.
#	MKDIR=mkdir -p  # Comando para criar diretórios.
#	TARGET_EXTENSION=out  # Extensão do arquivo de saída.
#else ifeq ($(OS),Windows_NT)
#	CLEANUP=del /F /Q
#	MKDIR=mkdir
#	TARGET_EXTENSION=exe
#else
CLEANUP=rm -f
MKDIR=mkdir -p
TARGET_EXTENSION=exe
#endif

# Definição dos caminhos usados no projeto.
PATHU = unity/
PATHS = src/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

# Agrupando todos os caminhos de build em uma única variável.
BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

# Identificando todos os arquivos de teste.
SRCT = $(wildcard $(PATHT)*/*.c)

# Definindo os comandos de compilação e linkagem.
COMPILE=gcc -c
LINK=gcc
DEPEND=gcc -MM -MG -MF
CFLAGS=-I. -I$(PATHU) -I$(PATHS) -DTEST

# Regra para construir o programa principal.
build: $(BUILD_PATHS) $(PATHB)main.$(TARGET_EXTENSION)
	@echo "Construção do programa principal concluída."

# Regra para compilar o arquivo main.c e todos os arquivos .c na pasta src.
$(PATHB)main.$(TARGET_EXTENSION): $(wildcard $(PATHS)*/*.c) main.c
	$(LINK) -o $@ $^


# Regra para construir e executar o programa.
run: $(BUILD_PATHS) $(PATHB)main.$(TARGET_EXTENSION)
	./$(PATHB)main.$(TARGET_EXTENSION)

# Definindo a regra para executar todos os testes.
test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo `grep -s IGNORE $(PATHR)*.txt`
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo `grep -s FAIL $(PATHR)*.txt`
	@echo "\nDONE"

# Regra para executar um teste específico.
# Uso: make test_name_test, onde 'name' é o nome do teste.
%_test: $(BUILD_PATHS) $(PATHR)Test%.txt
	@echo `grep -s IGNORE $(PATHR)Test$*.txt`
	@echo `grep -s FAIL $(PATHR)Test$*.txt`

# Definição dos arquivos de resultados dos testes.
RESULTS = $(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt,$(SRCT))

# Regra para gerar um arquivo de texto com os resultados de cada teste.
$(PATHR)%.txt: $(PATHB)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

# Regra para linkar os objetos dos testes e gerar o executável do teste.
$(PATHB)Test%.$(TARGET_EXTENSION): $(PATHO)Test%.o $(PATHO)%.o $(PATHO)unity.o $(PATHD)Test%.d
	$(LINK) -o $@ $^

# Regras para compilar os arquivos fonte dos testes e gerar os respectivos arquivos objeto.
$(PATHO)%.o:: $(PATHT)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

# Regras para compilar os arquivos fonte do código principal e gerar os respectivos arquivos objeto.
$(PATHO)%.o:: $(PATHS)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

# Regras para compilar os arquivos fonte da Unity e gerar os respectivos arquivos objeto.
$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

# Regra para gerar as dependências dos testes.
$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

# Regras para criar os diretórios necessários se eles ainda não existirem.
$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)

# Regra para limpar o projeto, removendo arquivos objeto, executáveis e resultados de testes.
clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt

# Indica que os arquivos e diretórios listados são preciosos, ou seja, não devem ser automaticamente removidos pelo make.
.PRECIOUS: $(PATHB)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

# Indica que 'clean' e 'test' são nomes de regras, não de arquivos.
.PHONY: clean
.PHONY: test
.PHONY: run
.PHONY: build