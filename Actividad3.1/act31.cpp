#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

class NodeTree {
public:
    int data;
    NodeTree* left;
    NodeTree* right;
    NodeTree* up;
    NodeTree(int value, NodeTree* parent = nullptr)
        : data(value), left(nullptr), right(nullptr), up(parent) {}
};

class BST {
public:
    NodeTree* root;
    BST(int value) { root = new NodeTree(value, nullptr); }

    NodeTree* search(int);
    void insert(int);
    void remove(int);
    void preorder(NodeTree*);
    void inorder(NodeTree*);
    void postorder(NodeTree*);
    void levelorder();
    void dfsStack();
};

//O(n) peor
NodeTree* BST::search(int value) {
    NodeTree* aux = root;
    while (aux != nullptr) {
        if (value < aux->data) {
            aux = aux->left;
        }
        else if (value > aux->data) {
            aux = aux->right;
        }
        else {
            return aux;
        }
    }
    return nullptr;
}

//O(n) 
void BST::insert(int value) {
    if (search(value) != nullptr) {
        return;
    }
    NodeTree* nuevo = new NodeTree(value);
    NodeTree* aux = root;
    while (aux != nullptr) {
        if (value < aux->data) {
            if (aux->left == nullptr) {
                aux->left = nuevo;
                nuevo->up = aux;
                return;
            }
            aux = aux->left;
        }
        else {
            if (aux->right == nullptr) {
                aux->right = nuevo;
                nuevo->up = aux;
                return;
            }
            aux = aux->right;
        }
    }
}

//O(n) 
void BST::remove(int value) {
    NodeTree* node = search(value);
    if (!node) {
        return;
    }

    if (!node->left && !node->right) {
        if (node == root) {
            root = nullptr;
        } else if (node->up->left == node) {
            node->up->left = nullptr;
        } else {
            node->up->right = nullptr;
        }
        delete node;
        return;
    }

    if (node->left == nullptr || node->right == nullptr) {
        NodeTree* child = (node->left) ? node->left : node->right;
        if (node == root) {
            root = child;
            root->up = nullptr;
        } else {
            if (node->up->left == node) {
                node->up->left = child;
            } else {
                node->up->right = child;
            }
            child->up = node->up;
        }
        delete node;
        return;
    }

    NodeTree* succ = node->right;
    while (succ->left != nullptr) {
        succ = succ->left;
    }

    node->data = succ->data;

    NodeTree* succParent = succ->up;
    NodeTree* succChild  = succ->right;

    if (succParent->left == succ) {
        succParent->left = succChild;
    } else {
        succParent->right = succChild;
    }
    if (succChild != nullptr) {
        succChild->up = succParent;
    }

    delete succ;
    return;
}

// O(n)
void BST::preorder(NodeTree* node) {
    if (!node) {
        return;
    }
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

// O(n)
void BST::inorder(NodeTree* node) {
    if (!node) {
        return;
    }
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

// O(n)
void BST::postorder(NodeTree* node) {
    if (!node) {
        return;
    }
    postorder(node->left);
    postorder(node->right);
    cout << node->data << " ";
}


// O(n)
void BST::levelorder() {
    if (!root) {
        return;
    }
    auto valOrNull = [](NodeTree* p)->string {
        if (!p) {
            return "null";
        }
        return to_string(p->data);
    };
    queue<NodeTree*> q;
    q.push(root);
    while (!q.empty()) {
        NodeTree* cur = q.front();
        q.pop();
        cout << cur->data << " {"
             << valOrNull(cur->up) << " "
             << valOrNull(cur->left) << " "
             << valOrNull(cur->right) << "}" << endl;
        if (cur->left) {
            q.push(cur->left);
        }
        if (cur->right) {
            q.push(cur->right);
        }
    }
    return;
}


// O(n)
void BST::dfsStack() {
    if (!root) {
        return;
    }
    stack<NodeTree*> st;
    st.push(root);
    while (!st.empty()) {
        NodeTree* cur = st.top();
        st.pop();
        cout << cur->data << " ";
        if (cur->right) {
            st.push(cur->right);
        }
        if (cur->left) {
            st.push(cur->left);
        }
    }
}

int main() {
    BST* bst = new BST(25);

    bst->search(25);
    bst->search(30);

    int vals[] = {20,34,2,22,30,40,26,31,32,45,39};
    for (int x : vals) {
         bst->insert(x); 
        }

    cout << "LevelOrder:\n"; bst->levelorder(); cout << endl;

    bst->remove(34);
    cout << "Despues de eliminar 34:\n"; bst->levelorder(); cout << endl;

    bst->remove(32);
    cout << "Despues de eliminar 32:\n"; bst->levelorder(); cout << endl;

    bst->remove(39);
    cout << "Despues de eliminar 39:\n"; bst->levelorder(); cout << endl;

    bst->remove(40);
    cout << "Despues de eliminar 40:\n"; bst->levelorder(); cout << endl;

    bst->insert(33);
    bst->insert(48);
    bst->insert(35);
    cout << "Despues de insertar 33, 48 y 35:\n"; bst->levelorder(); cout << endl;

    cout << "Preorder: "; bst->preorder(bst->root); cout << endl;
    cout << "Inorder: "; bst->inorder(bst->root); cout << endl;
    cout << "Postorder: "; bst->postorder(bst->root); cout << endl;
    cout << "DFS (stack): "; bst->dfsStack(); cout << endl;
    cout << "LevelOrder final:\n"; bst->levelorder(); cout << endl;

    return 0;
}