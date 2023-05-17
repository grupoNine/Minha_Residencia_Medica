# Minha Residência Médica - M.R.M

{{descrição do projeto}}


  - [🖥️ Setup](#-setup)
  - [📐 Arquitetura](#-arquitetura)
  - [🔲 OPCAO 02](#-opcao-02)
  - [🔲 OPCAO 03](#-opcao-03)
  - [🔲 OPCAO 04](#-opcao-04)
  - [🛠 Ferramentas](#-ferramentas)
  - [👨‍💻 Team](#-team)

---

### 🖥️ Setup

- Sugerimos utilizar o **VS Code** e **MinGW**[🔗](https://www.mingw-w64.org/) para este projeto:

    Instruções:[https://code.visualstudio.com/docs/cpp/config-mingw](https://code.visualstudio.com/docs/cpp/config-mingw)

- Sugerimos também a utilização do Git Bash no terminal VSCode:

    [https://git-scm.com/](https://git-scm.com/)

    Para torná-lo default no VS Code: `Ctrl+Shift+P` -> `Terminal: Select Default Profile`

    _Obs. Não esquecer de adicionar ambos às variáveis do sistema._

- Instalar Make [🔗](https://www.gnu.org/software/make/manual/make.html):
    
    1 Na pasta `bin` do diretório de instalação do MinGW, renomear `mingw32-make` para `make`

    2 Adicionar make as variáveis do sistema. 

    3 Testar no terminal com `make --version`

    No diretório raiz deste projeto, o arquivo makefile permite executar o programa e os testes de maneira automatizada.

  Lista de comandos:

    make build: Compila o programa principal.

    make run: Compila e executa o programa principal.

    make test: Executa todos os testes.

    make clean: Limpa o projeto, removendo arquivos objeto, executáveis e resultados de testes.

    make nomedoteste_test: Executa um teste específico, onde 'nome_do_teste' é o nome do teste.
    

- Para rodar o programa, digite no terminal:

  `make run` 
 
  ou
 
  `gcc -o build/main.exe src/01_presentation/presentation.c src/02_application/application.c src/03_data/data.c main.c` 
  
  e depois 
  
  `./build/main.exe`

---

### 📐 Arquitetura

<img width="1668" alt="Arquitetura (3)" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/7a6ea8dc-3201-40e9-a5e1-b71dd750c4f8">

<img width="3517" alt="Arquitetura (2)" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/4d626814-fe42-41d8-8b48-7894adf0f9cd">

<img width="2885" alt="Arquitetura" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/86b109a9-1454-401e-acf2-92c61cbd2e89">

<img width="2885" alt="Arquitetura (1)" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/219c8456-5945-4a08-a0a6-c6de5983df23">

---

### 🔲 OPCAO 02

---

### 🔲 OPCAO 03


---

### 🔲 OPCAO 04


---

### 🛠 Ferramentas

-   **[C](https://www.open-std.org/jtc1/sc22/wg14/)**
-   **[MinGW-w64](https://www.mingw-w64.org/)**
-   **[Unity](http://www.throwtheswitch.org/unity)**
-   **[Make](https://www.gnu.org/software/make/)**
-   **[Figma](https://www.figma.com/)**
-   **[Github](https://github.com/)**
-   **[Visual Studio Code](https://code.visualstudio.com/)**

---

### 👨‍💻 Team

<table>
  <tr>
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/116602650?v=4" width="100px;" alt=""/><br /><sub><b>Gislaine Reis</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/116669790?v=4" width="100px;" alt=""/><br /><sub><b>Lucas Cortez</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/111138996?v=4" width="100px;" alt=""/><br /><sub><b>Pedro Coelho</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="" width="100px;" alt=""/><br /><sub><b>nome</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="" width="100px;" alt=""/><br /><sub><b>nome</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="" width="100px;" alt=""/><br /><sub><b>nome</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="" width="100px;" alt=""/><br /><sub><b>nome</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="" width="100px;" alt=""/><br /><sub><b>nome</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="" width="100px;" alt=""/><br /><sub><b>nome</b></sub></a><br /></a></td>


    
  </tr>
  
