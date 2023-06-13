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
   
  -> Foram criados usuários padrões para fim de testes, são:
  
  Residente -> usuário: `jtr` senha: `1234`
  
  Preceptora -> usuário: `dtp` senha: `1234`
  
  Gestora -> usuário: `rtg` senha:`1234`
  

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
  
  <img width="307" alt="2" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/f85fb332-41a3-4a87-a62e-1ed50e64a725">

  <img width="293" alt="5" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/065823f7-e57e-4754-abc3-4a788467ff1a">

  <img width="299" alt="8" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/aefdd771-5c7f-4b22-8975-49bf2e76ea01">

---

📐 
### Arquitetura

  [FIGMA](https://www.figma.com/file/N0Fp63qzlDYMZJPfZjzGFT/Arquitetura?type=whiteboard&node-id=0%3A1&t=NLGScytnXbGCC0zG-1)

  <img width="5176" alt="Arquitetura" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/8cdf600f-dfbc-4145-abdc-d7eb4bafe4eb">

  ![datalayer](https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/4c74e281-51aa-4399-bdcc-ee94910afd4f)

  <img width="186" alt="Screenshot 2023-06-12 201516" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/0d26102f-1ff3-4314-b805-6d8eb6af4b9a">


---

🔎
### Testes

Nosso maior aliado nos testes foi o debugger GNU gdb: o comando do makefile `make run-debug` nos permitiu observar o comportamento do programa e encontrar de forma precisa por bugs no código.

Foram recorrentes falhas de 'segfault' por conta gestão da alocação de memória típica de C, o comando do gdb `backtrace` foi útil em apontar essas e outras falhas.

O início do desenvolvimento, na construção dos menus, login e signup realizamos testes enquanto produziamos código e o setup inicial.
Como esses códigos iniciais funcionaram como protótipos para o restante do código, o número de bugs e falhas mais imediatas se reduziram, e passamos a testar mais isoladamente e utilizar mais o gdb.
A criação de prints de verificação ao longo do código também foi uma prática que permitiu rastrear mais rápido os problemas.

Para isso, além de constantes testes exploratórios, automatizamos no makefile `make test` a execução do arquivo tests.c com funções para testes unitários e de integração, que geram um arquivo tests.txt como relatório.

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

<img width="602" alt="image" src="https://github.com/grupoNine/Minha_Residencia_Medica/assets/111138996/bc4b7da8-0977-4505-ad36-0f25971cd3c8">

