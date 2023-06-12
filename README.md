# ⚕️ Minha Residência Médica - MRM ⚕️

O MRM é um aplicativo desenvolvido em C para a disciplina de Projetos II dos cursos de Ciência da Computação e Design da [CESAR School](https://www.cesar.school/).
Tivemos como cliente o Hospital das Clínicas da Universidade Federal de Pernambuco.

Para mais informações sobre o projeto, acesse: https://sites.google.com/cesar.school/infinity


  - [👣 Instalação](#instalação)
  - [🖥️ Aplicativo](#aplicativo)
  - [📐 Arquitetura](#arquitetura)
  - [🔎 Testes](#testes)
  - [🛠️ Ferramentas](#ferramentas)
  - [📖 Referências](#referências)
  - [👨‍💻 Team](#team)

---

👣 
### Instalação

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

  -> Compila e executa o programa principal.
    `make run` 
    ou
     `gcc -g -I./src src/presentation.c src/application.c src/data.c main.c -o build/main && ./build/main`

  -> Compila e executa o programa principal no modo debug
   `make run-debug`
   ou
   `gcc -g -I./src src/presentation.c src/application.c src/data.c main.c -o build/main && gdb build/main`


  -> Compila e executa os testes.
   `make test` 
   ou
   `gcc -g -I./src src/presentation.c src/application.c src/data.c tests/tests.c -o build/Tests && ./build/Tests > tests/tests.txt`

  -> Compila e executa os testes no modo debug
   `make test-debug`
   ou
  `gcc -g -I./src src/presentation.c src/application.c src/data.c tests/tests.c -o build/Tests && gdb build/Tests`

  -> Limpa os arquivos temporários e o executável
   `make clean` 

---

🖥️
###  Aplicativo

  O MRM tem como objetivo gerenciar as atividades da Residência do HC:

  O residente pode visualizar avisos e suas atividades dárias, além de marcar presença, solicitar avaliação e selecionar seu ambiente de aprendizagem atual.

  O preceptor pode avaliar o residente, escrever no quadro de avisos e criar seu ambiente de aprendizagem e suas atividades.

  O gestor pode exportar avaliações e frequências mensais de todos os residentes, assim como escrever no quadro de avisos e cadastrar novos usários.

  <img width="2205" alt="residente" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/4dcd6c0d-6146-418f-adf3-6f3d0acf7f74">

  <img width="2905" alt="preceptor" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/4543de81-70f9-4918-8ab9-063127fcd31d">

  <img width="2885" alt="gestor" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/6494de31-faa0-4a5c-b18a-4b77f31b84f3">


---

📐 
### Arquitetura

  <img width="5176" alt="Arquitetura" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/8cdf600f-dfbc-4145-abdc-d7eb4bafe4eb">

  <img width="1464" alt="datalayer" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/a7a500df-0745-4053-b4d1-61417cf05c97">

  <img width="346" alt="folder" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/71b6d5ed-bbd0-4730-8860-04839d488d60">

---

🔎
### Testes

Nosso maior aliado nos testes foi o debugger GNU gdb, por meio do makefile podemos utilizar o comando `make test` nos permitiu observar o comportamento do programa e facilitou a busca mais precisão por bugs no código.

Foram recorrentes falhas de 'segfault' pela dificuldade de gestão da alocação de memória típica de C, o comando do gdb `backtrace` nos ajudou bastante apontando as falhas.

O início do desenvolvimento, na construção dos menus, login, signup e avaliação utilizamos testes enquanto produziamos o código, próximo a uma metodologia test-driven.
Como esses códigos iniciais funcionaram como protótipos para o restante do código, o número de bugs e falhas mais imediatas se reduziram, e passamos a testar apenas ao fim.

Para isso além de constantes testes exploratórios, fizemos um arquivo tests.c com funções para testes unitários e de integração, que geram um arquivo tests.txt como relatório.

---

🛠️ 
### Ferramentas

  -   **[C](https://www.open-std.org/jtc1/sc22/wg14/)**
  -   **[MinGW-w64](https://www.mingw-w64.org/)**
  -   **[Make](https://www.gnu.org/software/make/)**
  -   **[Figma](https://www.figma.com/)**
  -   **[Github](https://github.com/)**
  -   **[Visual Studio Code](https://code.visualstudio.com/)**

---

📖 
### Referências

- **[21st Century C](https://www.oreilly.com/library/view/21st-century-c/9781491904428/)** "Part I.The Environment" 
- **[Engenharia de Software](https://engsoftmoderna.info/)** 
- **[C: the complete reference](https://www.amazon.com.br/C-Complete-Reference-Herbert-Schildt/dp/0072121246)** 
- **[GeeksForGeeks.org](https://www.geeksforgeeks.org/c-programming-language/)**

---

👨‍💻
### Team

<table>
  <tr>
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/116602650?v=4" width="100px;" alt=""/><br /><sub><b>Gislaine Reis</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/116669790?v=4" width="100px;" alt=""/><br /><sub><b>Lucas Cortez</b></sub></a><br /></a></td>
    <td align="center"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/111138996?v=4" width="100px;" alt=""/><br /><sub><b>Pedro Coelho</b></sub></a><br /></a></td>
   <td align="center"><img style="border-radius: 50%;" src="https://media.licdn.com/dms/image/D4D03AQEWkpGgAcLo1g/profile-displayphoto-shrink_800_800/0/1681732287722?e=1689811200&v=beta&t=vVd3v_YpV9SKdRb5PsvHOVR-iCTeRcIttLRth9ARC-Q" width="100px;" alt=""/><br /><sub><b>Letícia Pinheiro</b></sub></a><br /></a></td>   
    <td align="center"><img style="border-radius: 50%;" src="https://media.licdn.com/dms/image/D4D03AQGwFWKSKKaDUA/profile-displayphoto-shrink_800_800/0/1679698808237?e=1689811200&v=beta&t=0x_3B1zlS50soHbgrMand6jJHPZQZy49NfavBw95Fxc" width="100px;" alt=""/><br /><sub><b>Bruna Carvalho</b></sub></a><br /></a></td>
     <td align="center"><img style="border-radius: 50%;" src="https://media.licdn.com/dms/image/D4D35AQEbX5ogC2YVRg/profile-framedphoto-shrink_800_800/0/1642452377945?e=1685106000&v=beta&t=4dC0vixL13cvxCBPV3TXB-GEYBrB3m7R6Aa3AohXQco" width="100px;" alt=""/><br /><sub><b>Guilherme Lopes</b></sub></a><br /></a></td>   
   
   

    
  </tr>
