#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

const string MAIN_FOLDER = "C:\\Pasta C++\\gestorficheiro\\";

//Função que garante que a pasta existe
void ensure_folder_exists() {
    // Tenta criar a pasta principal
    if (CreateDirectoryA("C:\\Pasta C++", NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
        // Depois tenta criar a subpasta gestorficheiro
        if (CreateDirectoryA(MAIN_FOLDER.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
            // Tudo OK
        } else {
            cerr << "Erro ao criar a subpasta 'gestorficheiro'!" << endl;
            exit(1);
        }
    } else {
        cerr << "Erro ao criar a pasta 'C:\\Pasta C++'!" << endl;
        exit(1);
    }
}

void saudation() {
    cout << "Bem-Vindo ao Gestor de ficheiros 2.0" << endl;
    cout << "------------------------------------" << endl << endl;
}

void menu() {
    cout << "[1] - Escrever ficheiros" << endl;
    cout << "[2] - Criar ficheiros" << endl;
    cout << "[0] - Sair" << endl;
}

// Função que mostra todos os ficheiros .txt
int show_files() {
    string search_pattern = MAIN_FOLDER + "*.txt";

    WIN32_FIND_DATAA fileData;
    HANDLE hFind = FindFirstFileA(search_pattern.c_str(), &fileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "Nenhum arquivo .txt encontrado ou caminho invalido!\n";
        return 0;
    }

    int counter = 0;
    do {
        if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            cout << "[" << counter << "] - " << fileData.cFileName << '\n';
            counter++;
        }
    } while (FindNextFileA(hFind, &fileData) != 0);

    FindClose(hFind);
    return counter;
}

// Função que retorna o caminho completo do ficheiro escolhido
string search_file(int index) {
    string search_pattern = MAIN_FOLDER + "*.txt";
    string reward_file;

    WIN32_FIND_DATAA fileData;
    HANDLE hFind = FindFirstFileA(search_pattern.c_str(), &fileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cerr << "Nenhum arquivo .txt encontrado ou caminho invalido!\n";
        exit(1);
    }

    int counter = 0;
    do {
        if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            if (counter == index) {
                reward_file = MAIN_FOLDER + fileData.cFileName;
                break;
            }
            counter++;
        }
    } while(FindNextFileA(hFind, &fileData) != 0);

    FindClose(hFind);
    return reward_file;
}

// Função que abre e reescreve o ficheiro
void rewrite_file(int index) {
    string file_path = search_file(index);

    if (file_path.empty()) {
        cout << "Ficheiro não encontrado!" << endl;
        return;
    }

    system("cls");
    cout << "Ficheiro escolhido: " << file_path << endl;

    // Mostrar conteúdo atual
    ifstream inside_file(file_path);
    if (inside_file.is_open()) {
        cout << "\n--- Conteudo escrito ---\n";
        string line;
        while (getline(inside_file, line)) {
            cout << line << endl;
        }
        inside_file.close();
    } else {
        cout << "Nao foi possivel abrir o ficheiro!" << endl;
        return;
    }

    
    // Escrever novo conteúdo
    cout << "\n--- Escreva o novo conteudo (use apenas uma linha): ---\n";
    cin.ignore();
    string new_text;
    getline(cin, new_text);

    ofstream outside_file(file_path, ios::trunc); // apaga e reescreve
    if (outside_file.is_open()) {
        outside_file << new_text << endl;
        outside_file.close();
        cout << "\nFicheiro atualizado com sucesso!\n";
    } else {
        cout << "Erro ao reescrever o ficheiro!" << endl;
    }

    system("pause");
    system("cls");
}

// Função que permite escolher um ficheiro e editá-lo
void write_files() {
    int choice;
    int archives_qtd;

    do {
        system("cls");
        archives_qtd = show_files();
        cout << "\nTemos " << archives_qtd << " ficheiros .txt!\n";

        cout << "-> Escolha o ficheiro a ser escrito (-1 para encerrar): ";
        cin >> choice;

        if (choice >= 0 && choice < archives_qtd) {
            rewrite_file(choice);
        } else if (choice != -1) {
            cout << "Opção inválida!" << endl;
            system("pause");
        }
    } while (choice != -1);

    system("cls");
}

//Função para criar ficheiros
void create_file() {
    system("cls");
    string name; 
    string content;

    cout << "Digite o nome do novo ficheiro (sem extensao): ";
    cin.ignore();
    getline(cin, name);

    string full_path = MAIN_FOLDER + name + ".txt";

    ofstream new_file(full_path);
    if (!new_file.is_open()) {
        cout << "Erro ao criar o ficheiro!" << endl;
        system("pause");
        return;
    }

    cout << "Escreva o conteudo inicial do ficheiro:\n";
    getline(cin, content);

    new_file << content << endl;
    new_file.close();

    cout << "\nFicheiro '" << name << ".txt' criado com sucesso em:\n" << full_path << endl;
    system("pause");
    system("cls");
}

int main() {
    ensure_folder_exists(); //Cria as pastas necessárias automaticamente

    int option;
    do {
        saudation();
        menu();

        cout << "-> Escolha sua opcao: ";
        cin >> option;

        switch (option) {
            case 1:
                write_files();
                break;
            case 2:
                create_file();
                break;
            case 0:
                continue;
            default:
                system("cls");
        }
    } while (option != 0);

    system("cls");
    return 0;
}
