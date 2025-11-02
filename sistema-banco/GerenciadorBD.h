#ifndef SISTEMA_BANCO_GERENCIADORBD_H
#define SISTEMA_BANCO_GERENCIADORBD_H

#include <string>
#include "Conta.h"
#include "sqlite3.h"

class GerenciadorBD {
private:
    sqlite3* db;

    // --- FUNÇÕES DE TABELA ATUALIZADAS ---
    // (O seu 'criarTabela' original foi renomeado e um novo foi adicionado)
    void criarTabelaContas();
    void criarTabelaUsuarios();

public:
    GerenciadorBD(const std::string& nomeArquivo);
    ~GerenciadorBD();

    // --- Métodos de Conta (que já temos) ---
    bool salvarConta(Conta& conta);
    bool carregarConta(Conta& conta);

    // --- NOVOS MÉTODOS DE USUÁRIO ---
    // (Estes são os que estão faltando no seu .h)
    bool registrarUsuario(const std::string& usuario, const std::string& senha);
    bool verificarLogin(const std::string& usuario, const std::string& senha);
};

#endif //SISTEMA_BANCO_GERENCIADORBD_H