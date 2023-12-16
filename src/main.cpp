#include <chrono>
#include "segTree.hpp"

int main() {

    try{
        auto start = std::chrono::high_resolution_clock::now();
        int n, q;
        std::cin >> n >> q;
        if (std::cin.fail()) {
            throw std::invalid_argument("Entrada inválida para n ou q.");
        }

        SegTree segtree(n);

        // Cria uma matriz identidade 2x2
        Matrix id;
        id.mat[0][0] = id.mat[1][1] = 1;
        id.mat[0][1] = id.mat[1][0] = 0;

        // Constrói a Árvore de Segmentação
        segtree.build(1, 0, n-1, id);

        // Itera pela quantidade de operações a serem feitas
        for (int i = 0; i < q; i++) {
            char op;
            std::cin >> op;

            if (op == 'u') { // Atualização
                int idx;
                std::cin >> idx;

                // Cria uma matriz a partir dos valores recebidos na entrada
                Matrix newMatrix;
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 2; k++) {
                        std::cin >> newMatrix.mat[j][k];
                    }
                }
                // Atualiza a árvore a partir dessa nova matriz
                segtree.update(1, 0, n-1, idx, newMatrix);

            } else if (op == 'q') { // Consulta
                int t0, td, x, y;
                std::cin >> t0 >> td >> x >> y;
                if(t0<0 || td>=n){
                    throw std::out_of_range("Valor fora do intervalo.");
                }

                Matrix result = segtree.query(1, 0, n-1, t0, td);

                // Multiplica a matriz retornada da consulta pelas coordenadas recebidas na entrada
                int newX = (result.mat[0][0] * x + result.mat[0][1] * y) % 100000000;
                int newY = (result.mat[1][0] * x + result.mat[1][1] * y) % 100000000;

                std::cout << newX << " " << newY << std::endl;
            } else{
                throw std::invalid_argument("Operação Inexistente.");
            }
        }
                    auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        // Exibindo o tempo de execução em segundos
        std::cout << "Tempo de execução: " << elapsed.count() << " segundos." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
}
