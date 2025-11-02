cmake_minimum_required(VERSION 3.10)
project(sistema_banco)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Esta é a grande mudança:
# Nós compilamos o SQLite diretamente, em vez de procurá-lo.
# Não precisamos mais de find_package ou target_link_libraries.

add_executable(
        sistema_banco

        # Seus arquivos .cpp
        main.cpp
        Conta.cpp
        ContaCorrente.cpp
        ContaPoupanca.cpp
        GerenciadorBD.cpp
        # (Adicione Banco.cpp aqui se você o criou)

        # O código-fonte do SQLite que você acabou de baixar
        sqlite3.c
)