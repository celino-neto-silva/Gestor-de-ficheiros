#Gestor de Ficheiros
--------------------

->Descrição: O projeto atual consiste na criação de um "editor de ficheiros" em Linguagem C++ que utiliza a API windows.h para criação e manipulação de ficheiros no modelo File I/O.

É um projeto de intuito educacional que visa explorar novas tecnologias e ferramentas.

->Descrição do percurso da aplicação:
------------------------

-O programa utiliza de ferramentas de menu para orientar as decisões do utilizador.

-O programa possui a função ensure_folder_exists(), que garante que o diretório seja criado.

-Ao escolher a função escrever ficheiro, o utilizador verá os ficheiros já criados através da função show_files().

-Ao visualizar os ficheiros criados o utilizador poderá escolher um para editar, se a escolha for válida a função rewrite_file() irá chamar a função search_file(), tal devolverá efetivamente o ficheiro escolhido para ser editado.

-Caso o utilizador recorra a opção de criar ficheiro a função create_file() entará em ação.