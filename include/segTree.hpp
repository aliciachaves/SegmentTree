#include <iostream>
#include <cmath>

// Estrutura da matriz
// Array de arrays com inteiros positivos e maior capacidade de armazenamento [long]
struct Matrix {
    unsigned long int mat[2][2];
};

class SegTree{

public:
SegTree(int n);
Matrix multiply(Matrix a, Matrix b);
void build(int node, int start, int end, Matrix id);
void update(int node, int start, int end, int idx, Matrix newMatrix);
Matrix query(int node, int start, int end, int left, int right);
~SegTree();

private:
Matrix* tree; //Árvore guardada em um array dinâmico
};

