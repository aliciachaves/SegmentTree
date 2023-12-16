#include "segTree.hpp"

// Construtor da matriz, inicia o array que representa a Árvore de Segmentos
SegTree::SegTree(int n){
    if (n <= 0) {
        throw std::invalid_argument("O tamanho da árvore deve ser um número positivo.");
    }
   tree = new Matrix[n << 2]; // Aloca espaço para a árvore com o tamanho 4 vezes o número de instantes de tempo
}

// Função auxiliar para multiplicar matrizes e limitar para seus 8 dígitos menos significativos
Matrix SegTree::multiply(Matrix a, Matrix b) {
    Matrix result;
    result.mat[0][0] = (a.mat[0][0] * b.mat[0][0] + a.mat[0][1] * b.mat[1][0]) % 100000000;
    result.mat[0][1] = (a.mat[0][0] * b.mat[0][1] + a.mat[0][1] * b.mat[1][1]) % 100000000;
    result.mat[1][0] = (a.mat[1][0] * b.mat[0][0] + a.mat[1][1] * b.mat[1][0]) % 100000000;
    result.mat[1][1] = (a.mat[1][0] * b.mat[0][1] + a.mat[1][1] * b.mat[1][1]) % 100000000;
    return result;
}


// Constrói a Árvore de Segmentação
void SegTree::build(int node, int start, int end, Matrix id) {
    if (start == end) { // Nó folha
        tree[node] = id;
    } else {
        int mid = (start + end) >> 1; // Acha a metade do intervalo
        // Constroi recursivamente a árvore
        build((node << 1), start, mid, id);
        build((node << 1) + 1, mid + 1, end, id);
        tree[node] = multiply(tree[(node << 1)], tree[((node << 1)) + 1]);
    }
}

// Atualiza recursivamente as matrizes da Árvore de Segmentação a partir de uma matriz recebida como parâmetro
void SegTree::update(int node, int start, int end, int idx, Matrix newMatrix) {
    if (start == end) {
        tree[node] = newMatrix;
    } else {
        int mid = (start + end) >> 1;
        if (idx <= mid) {
            update((node << 1), start, mid, idx, newMatrix);
        } else {
            update((node << 1) + 1, mid + 1, end, idx, newMatrix);
        }
        tree[node] = multiply(tree[(node << 1)], tree[(node << 1) + 1]);
    }
}

// Realiza a consulta na Árvore de Segmentação
Matrix SegTree::query(int node, int start, int end, int left, int right) {
    if (right < start || left > end) {
        Matrix id;
        id.mat[0][0] = id.mat[1][1] = 1;
        id.mat[0][1] = id.mat[1][0] = 0;
        return id;
    }
    if (left <= start && right >= end) {
        return tree[node]; // Retorna a matriz do nó
    }
    int mid = (start + end) >> 1;
    Matrix p1 = query((node << 1), start, mid, left, right);
    Matrix p2 = query((node << 1) + 1, mid + 1, end, left, right);
    return multiply(p1,p2); // Multiplica as matrizes obtidas nos nós filhos
}

// Destrutor: Libera a memória alocada para a árvore
SegTree::~SegTree() {
    delete[] tree;
}
