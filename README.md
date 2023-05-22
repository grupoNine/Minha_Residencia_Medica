# ⚕️ Minha Residência Médica - MRM ⚕️

{{breve descrição do projeto}}


  - [👣 Instalação](#-setup)
  - [🖥️ Programa](#-arquitetura)
  - [📐 Arquitetura](#-arquitetura)
  - [🔎 Testes](#-testes)
  - [🛠️ Ferramentas](#-ferramentas)
  - [♾️ Projeto](#-opcao-04)
  - [👨‍💻 Team](#-team)

---

### 👣 Instalação

- Sugerimos utilizar o **VS Code** e **MinGW**[🔗](https://www.mingw-w64.org/) para este projeto:

    Instruções:[https://code.visualstudio.com/docs/cpp/config-mingw](https://code.visualstudio.com/docs/cpp/config-mingw)

- Sugerimos também a utilização do **Git Bash** no terminal VSCode:

    [https://git-scm.com/](https://git-scm.com/)

    Para torná-lo default no VS Code: `Ctrl+Shift+P` -> `Terminal: Select Default Profile`

    _Obs. Não esquecer de adicionar ambos às variáveis do sistema._

- Instalar **Make** [🔗](https://www.gnu.org/software/make/manual/make.html):
    
    1 Na pasta `bin` do diretório de instalação do MinGW, renomear `mingw32-make` para `make`

    2 Adicionar make as variáveis do sistema. 

    3 Testar no terminal com `make --version`

    No diretório raiz deste projeto, o arquivo makefile permite executar o programa e os testes de maneira automatizada.

- **Lista de comandos**

// Compila e executa o programa principal.
  `make run` 
  ou
   `gcc -g -I./src src/presentation.c src/application.c src/data.c main.c -o build/main && ./build/main`

//Compila e executa o programa principal no modo debug
 `make run-debug`
 ou
 `gcc -g -I./src src/presentation.c src/application.c src/data.c main.c -o build/main && gdb build/main`


// Compila e executa os testes.
 `make test` 
 ou
 `gcc -g -I./src src/presentation.c src/application.c src/data.c tests/tests.c -o build/Tests && ./build/Tests > tests/tests.txt`

// Compila e executa os testes no modo debug
 `make test-debug`
 ou
`gcc -g -I./src src/presentation.c src/application.c src/data.c tests/tests.c -o build/Tests && gdb build/Tests`

// Limpa os arquivos temporários e o executável
 `make clean` 

---

### 🖥️ Programa



---

### 📐 Arquitetura

<img width="820" alt="arquitetura_" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/005a8c29-7edb-435a-a480-d8e4a0f26faa">

<img width="1668" alt="Arquitetura (3)" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/7a6ea8dc-3201-40e9-a5e1-b71dd750c4f8">

<img width="3517" alt="Arquitetura (2)" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/4d626814-fe42-41d8-8b48-7894adf0f9cd">

<img width="2885" alt="Arquitetura" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/86b109a9-1454-401e-acf2-92c61cbd2e89">

<img width="2885" alt="Arquitetura (1)" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/219c8456-5945-4a08-a0a6-c6de5983df23">


---

### 🔎 Testes

---

### 🛠️ Ferramentas

-   **[C](https://www.open-std.org/jtc1/sc22/wg14/)**
-   **[MinGW-w64](https://www.mingw-w64.org/)**
-   **[Make](https://www.gnu.org/software/make/)**
-   **[Figma](https://www.figma.com/)**
-   **[Github](https://github.com/)**
-   **[Visual Studio Code](https://code.visualstudio.com/)**

---

### ♾️ Projeto



---

### 👨‍💻 Team

<table>
  <tr>
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/116602650?v=4" width="100px;" alt=""/><br /><sub><b>Gislaine Reis</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/116669790?v=4" width="100px;" alt=""/><br /><sub><b>Lucas Cortez</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/111138996?v=4" width="100px;" alt=""/><br /><sub><b>Pedro Coelho</b></sub></a><br /></a></td>
   <td align="center"><img style="border-radius: 50%;" src="https://media.licdn.com/dms/image/D4D03AQEWkpGgAcLo1g/profile-displayphoto-shrink_800_800/0/1681732287722?e=1689811200&v=beta&t=vVd3v_YpV9SKdRb5PsvHOVR-iCTeRcIttLRth9ARC-Q" width="100px;" alt=""/><br /><sub><b>Letícia Pinheiro</b></sub></a><br /></a></td>   
    <td align="center"><img style="border-radius: 50%;" src="https://media.licdn.com/dms/image/D4D03AQGwFWKSKKaDUA/profile-displayphoto-shrink_800_800/0/1679698808237?e=1689811200&v=beta&t=0x_3B1zlS50soHbgrMand6jJHPZQZy49NfavBw95Fxc" width="100px;" alt=""/><br /><sub><b>Bruna Carvalho</b></sub></a><br /></a></td>
     <td align="center"><img style="border-radius: 50%;" src="https://media.licdn.com/dms/image/D4D35AQEbX5ogC2YVRg/profile-framedphoto-shrink_800_800/0/1642452377945?e=1685106000&v=beta&t=4dC0vixL13cvxCBPV3TXB-GEYBrB3m7R6Aa3AohXQco" width="100px;" alt=""/><br /><sub><b>Guilherme Lopes</b></sub></a><br /></a></td>   
   
   

    
  </tr>
