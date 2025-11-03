#ifndef SISTEMA_BANCO_GERENCIADORBD_H
#define SISTEMA_BANCO_GERENCIADORBD_H

#include <string>
#include "Conta.h"
#include "sqlite3.h"

class GerenciadorBD {
private:
    sqlite3* db;


    void criarTabelaContas();
    void criarTabelaUsuarios();

public:
    GerenciadorBD(const std::string& nomeArquivo);
    ~GerenciadorBD();

   
    bool salvarConta(Conta& conta);
    bool carregarConta(Conta& conta);

    
    bool registrarUsuario(const std::string& usuario, const std::string& senha);
    bool verificarLogin(const std::string& usuario, const std::string& senha);
};


#endif
