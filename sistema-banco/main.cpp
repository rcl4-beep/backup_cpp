#include <iostream>
#include <string>
#include <limits> // Para limpar o buffer de entrada
#include "ContaCorrente.h"
#include "ContaPoupanca.h"
#include "GerenciadorBD.h"
using namespace std;

/**
 * Esta função contém toda a lógica do banco que já fizemos.
 * Ela só será chamada DEPOIS do login.
 */
void rodarAppPrincipal(GerenciadorBD& gerenciador) {
    // 1. Define os valores iniciais (padrão) das contas
    ContaCorrente c1(101, "Tiago Mattos", 1000.0, 15.0);
    ContaPoupanca p1(202, "Maria Silva", 5000.0, 0.02);

    // 2. Tenta carregar os dados salvos do BD
    cout << "\nCarregando contas do banco de dados..." << endl;
    gerenciador.carregarConta(c1);
    gerenciador.carregarConta(p1);

    // 3. Inicia o Menu (focado na c1, como no seu original)
    int num_op;
    double val_op;

    cout << "\n=== App Principal do Banco ===";
    cout << "\n=== Conta Corrente ===";
    c1.exibir(); // Mostra o saldo atual (carregado do BD)
    cout << "Selecione a operação que deseja realizar:\n";
    cout << "(1) Exibir Saldo\n";
    cout << "(2) Depositar\n";
    cout << "(3) Sacar\n";
    cout << "(4) Sair e Salvar\n";
    cin >> num_op;

    while (num_op != 4) {
        if (num_op == 1) {
            c1.exibir();
        }
        else if (num_op == 2) {
            cout << "Digite o valor que deseja depositar: ";
            cin >> val_op;
            c1.depositar(val_op);
        }
        else if (num_op == 3) {
            cout << "Digite o valor que deseja Sacar: ";
            cin >> val_op;
            c1.sacar(val_op);
        }

        // Limpar buffer de entrada se o usuário digitar algo inválido
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opção inválida." << endl;
        }

        cout << "\n(1) Saldo, (2) Depositar, (3) Sacar, (4) Sair e Salvar" << endl;
        cin >> num_op;
    }

    // 4. Ao sair do loop (opção 4), salva o estado final
    cout << "Salvando dados das contas..." << endl;
    gerenciador.salvarConta(c1);
    gerenciador.salvarConta(p1);

    cout << "Sessão do banco encerrada." << endl;
}


// --- O NOVO PONTO DE ENTRADA (MAIN) ---
int main() {
    // 1. Conecta ao Banco de Dados (Isso cria as tabelas Usuarios e Contas)
    GerenciadorBD gerenciador("banco_contas.db");

    int escolha = 0;
    string usuario, senha;
    bool loginEfetuado = false;

    // 2. Loop de Login/Cadastro
    while (!loginEfetuado) {
        cout << "\n--- BEM-VINDO AO SISTEMA BANCÁRIO ---" << endl;
        cout << "1. Fazer Login" << endl;
        cout << "2. Registrar-se" << endl;
        cout << "3. Sair do Programa" << endl;
        cout << "Escolha uma opção: ";

        cin >> escolha;

        // Limpar buffer de entrada
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opção inválida." << endl;
            continue;
        }

        if (escolha == 1) { // Login
            cout << "Usuário: ";
            cin >> usuario;
            cout << "Senha: ";
            cin >> senha;

            if (gerenciador.verificarLogin(usuario, senha)) {
                loginEfetuado = true; // Quebra o loop 'while'
            }

        } else if (escolha == 2) { // Registrar
            cout << "Novo Usuário: ";
            cin >> usuario;
            cout << "Nova Senha: ";
            cin >> senha;
            gerenciador.registrarUsuario(usuario, senha);

        } else if (escolha == 3) { // Sair
            cout << "Saindo..." << endl;
            return 0; // Termina o programa
        }
    }

    // 3. Se o loop 'while' terminar, o login foi um sucesso.
    // Agora, rodamos a aplicação principal do banco.
    rodarAppPrincipal(gerenciador);

    cout << "Programa encerrado." << endl;
    return 0;
}