#include <iostream>
#include <algorithm>
using namespace std;

// Estrutura de um nó da árvore
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Função para obter a altura do nó
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Função para calcular o fator de balanceamento
int getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Função para atualizar a altura do nó
void updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// Rotação à direita
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Rotação à esquerda
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Função para balancear o nó
Node* balance(Node* node) {
    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    // Rotação à direita
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    // Rotação à esquerda-direita
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Rotação à esquerda
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Rotação à direita-esquerda
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Função para inserir um valor na árvore
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Duplicados não são permitidos
    }

    return balance(node);
}

// Função para encontrar o nó com o menor valor
Node* findMin(Node* node) {
    return node->left ? findMin(node->left) : node;
}

// Função para remover um valor da árvore
Node* remove(Node* node, int key) {
    if (!node) return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        if (!node->left) {
            Node* rightChild = node->right;
            delete node;
            return rightChild;
        } else if (!node->right) {
            Node* leftChild = node->left;
            delete node;
            return leftChild;
        } else {
            Node* minLargerNode = findMin(node->right);
            node->key = minLargerNode->key;
            node->right = remove(node->right, minLargerNode->key);
        }
    }

    return balance(node);
}

// Função para realizar a busca na árvore
bool search(Node* node, int key) {
    if (!node) return false;

    if (key < node->key) {
        return search(node->left, key);
    } else if (key > node->key) {
        return search(node->right, key);
    } else {
        return true; // Chave encontrada
    }
}

// Função para imprimir a árvore em ordem
void inorder(Node* node) {
    if (!node) return;

    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
}

int main() {
    Node* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Árvore em ordem: ";
    inorder(root);
    cout << endl;

    root = remove(root, 20);

    cout << "Árvore após remoção de 20: ";
    inorder(root);
    cout << endl;

    cout << "Busca por 25: " << (search(root, 25) ? "Encontrado" : "Não encontrado") << endl;

    return 0;
}
