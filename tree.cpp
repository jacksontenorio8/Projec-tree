#include <iostream>
#include <algorithm>
using namespace std;

// Estrutura de um n� da �rvore
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Fun��o para obter a altura do n�
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// Fun��o para calcular o fator de balanceamento
int getBalanceFactor(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Fun��o para atualizar a altura do n�
void updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// Rota��o � direita
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Rota��o � esquerda
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Fun��o para balancear o n�
Node* balance(Node* node) {
    updateHeight(node);

    int balanceFactor = getBalanceFactor(node);

    // Rota��o � direita
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    // Rota��o � esquerda-direita
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Rota��o � esquerda
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Rota��o � direita-esquerda
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Fun��o para inserir um valor na �rvore
Node* insert(Node* node, int key) {
    if (!node) return new Node(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Duplicados n�o s�o permitidos
    }

    return balance(node);
}

// Fun��o para encontrar o n� com o menor valor
Node* findMin(Node* node) {
    return node->left ? findMin(node->left) : node;
}

// Fun��o para remover um valor da �rvore
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

// Fun��o para realizar a busca na �rvore
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

// Fun��o para imprimir a �rvore em ordem
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

    cout << "�rvore em ordem: ";
    inorder(root);
    cout << endl;

    root = remove(root, 20);

    cout << "�rvore ap�s remo��o de 20: ";
    inorder(root);
    cout << endl;

    cout << "Busca por 25: " << (search(root, 25) ? "Encontrado" : "N�o encontrado") << endl;

    return 0;
}
