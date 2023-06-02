#include <iostream>
#include <vector>
using namespace std;

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node* parent, * left, * right;

    void print() const;
};

template<typename K, typename V>
void Node<K, V>::print() const {
    cout << "Node at: " << this << "; parent at: " << parent;
    cout << "; left at: " << left << "; right at: " << right << endl;
    cout << "Key: " << key << "; value: " << value << endl;
}

template <typename K, typename V>
struct BST {
    Node<K, V>* root;

    BST();
    BST(const BST& bst);
    ~BST();

    Node<K, V>* search(Node<K, V>* x, K key);

    Node<K, V>* minimum(Node<K, V>* x);

    Node<K, V>* maximum(Node<K, V>* x);

    Node<K, V>* successor(Node<K, V>* x);

    Node<K, V>* predecessor(Node<K, V>* x);

    void insert(const K& key, const V& value);

    void transplant(Node<K, V>* u, Node<K, V>* v);

    void remove(Node<K, V>* x);

    void inorderWalk(Node<K, V>* x, vector<Node<K, V>*>& nodes) const;

    BST& operator=(const BST& bst);

    void print() const;
};

template<typename K, typename V>
BST<K, V>::BST(): root{nullptr} {}

template<typename K, typename V>
BST<K, V>::BST(const BST &bst): BST{} {
    vector<Node<K, V>*> nodes{};
    bst.inorderWalk(bst.root, nodes);

    for(Node<K,V>* nodePtr: nodes)
        insert(nodePtr->key, nodePtr->value);

}

template<typename K, typename V>
BST<K, V>::~BST() {
    vector<Node<K, V>*> nodes{};
    inorderWalk(root, nodes);

    for(Node<K,V>* nodePtr: nodes)
        delete nodePtr;
}

template<typename K, typename V>
Node<K, V> *BST<K, V>::search(Node<K, V> *x, K key) {
    if(x==nullptr || x->key == key) return x;

    if(key<x->key)
        search(x->left, key);
    else
        search(x->right, key);

}

template<typename K, typename V>
Node<K, V> *BST<K, V>::minimum(Node<K, V> *x) {
    while(x->left!=nullptr)
        x = x->left;

    return x;
}

template<typename K, typename V>
Node<K, V> *BST<K, V>::maximum(Node<K, V> *x) {
    while(x->right!=nullptr)
        x = x->right;

    return x;
}

template<typename K, typename V>
Node<K, V> *BST<K, V>::successor(Node<K, V> *x) {
    if(x->right!=nullptr)
        return minimum(x->right);

    Node<K,V>* y = x->parent;
    while(y!=nullptr && y->right==x){
        x = y;
        y = y->parent;
    }

    return y;
}

template<typename K, typename V>
Node<K, V> *BST<K, V>::predecessor(Node<K, V> *x) {
    if(x->left!=nullptr)
        return maximum(x->left);

    Node<K,V>* y = x->parent;
    while(y!=nullptr && y->left==x){
        x = y;
        y = y->parent;
    }

    return y;
}

template<typename K, typename V>
void BST<K, V>::insert(const K &key, const V &value) {

    Node<K,V>* z = new Node<K,V>{key,value, nullptr, nullptr, nullptr};
    Node<K,V>* y = nullptr;
    Node<K,V>* x = root;

    while(x!= nullptr){
        y = x;
        if(z->key<x->key)
            x= x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if(y ==nullptr)
        root = z;
    else if(z->key < y->key)
        y->left = z;
    else
        y->right = z;


}

template<typename K, typename V>
void BST<K, V>::transplant(Node<K, V> *u, Node<K, V> *v) {

    if(u->parent == nullptr)
        root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if(v!=nullptr)
        v->parent = u->parent;

}

template<typename K, typename V>
void BST<K, V>::remove(Node<K, V> *x) {
    if(x->left == nullptr)
        transplant(x,x->right);
    else if(x->right ==nullptr) transplant(x,x->left);
    else{
        Node<K,V>* y = minimum(x->right);

        if(y->parent != x){
            transplant(y, y->right);
            y->right = x->right;
            y->right->parent = y;
        }

        transplant(x,y);
        y->left = x->left;
        y->left->parent = y;
    }
    delete x;
}

template<typename K, typename V>
void BST<K, V>::inorderWalk(Node<K, V> *x, vector<Node<K, V> *> &nodes) const {

    if(x!=nullptr){
        inorderWalk(x->left, nodes);
        nodes.push_back(x);
        inorderWalk(x->right, nodes);
    }
}

template<typename K, typename V>
BST<K, V> &BST<K, V>::operator=(const BST &bst) {
    this->~BST();

    root = nullptr;
    vector<Node<K, V>*> nodes{};
    bst.inorderWalk(bst.root, nodes);

    for(Node<K,V>* nodePtr: nodes)
        insert(nodePtr->key, nodePtr->value);


    return *this;
}

template<typename K, typename V>
void BST<K, V>::print() const {

    vector<Node<K,V>*> nodes{};
    inorderWalk(root, nodes);
    cout << "-------------------------------------------------------" << endl;
    cout << "Binary search tree with root at: " << root << endl;
    cout << "Nodes: " << endl;
    for(Node<K, V>* nodePtr: nodes)
        nodePtr->print();
    cout << "-------------------------------------------------------" << endl;
}

int main() {

    BST<int,string> v{};

    v.insert(20, "Korisnik1");
    v.insert(25, "Korisnik2");
    v.insert(15, "Korisnik3");
    v.insert(17, "Korisnik4");

    v.print();
    v.remove(v.root);

    v.print();

    return 0;
}
