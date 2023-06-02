#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int Node;

template <typename K, typename V>
struct CompleteBinaryTree{

    vector<pair<K, V>> N;
    unsigned int size;

    CompleteBinaryTree(): N{}, size{0u} {}
    CompleteBinaryTree(const vector<pair<K, V>>& L): N{L}, size{L.size()} {}

    Node left(Node i) const { return 2 * i+1 ; }
    Node right(Node i) const { return 2 * (i + 1); }
    Node parent(Node i) const { return (i-1) / 2 ; }
    Node root() {return 1;}

    pair<K, V>& element(Node i) { return N[i]; }
    const pair<K, V>& element(Node i) const { return N[i]; }

    void updateLeft(Node i, const pair<K, V>& e) { N[left(i)] = e; }
    void updateRight(Node i, const pair<K, V>& e) { N[right(i)] = e; }
    void updateParent(Node i, const pair<K, V>& e) { N[parent(i)] = e; }

    bool isLeaf(Node i) const { return size < left(i); }

    unsigned int getSize() { return size; }
    void setSize(unsigned int newSize) { size = newSize; }
    bool empty() { return size == 0; }

    void preorderPrint(Node);
    void postorderPrint(Node);

    void swapNodes(Node i, Node j);

    const pair<K, V>& operator[](int) const;
    pair<K, V>& operator[](int);

};

template <typename K, typename V>
void CompleteBinaryTree<K, V>::preorderPrint(Node i) {
    if (i >= size) {
        return;
    }
    cout << N[i].first << ":" << N[i].second <<  ";\t";
    preorderPrint(left(i));
    preorderPrint(right(i));
}

template <typename K, typename V>
void CompleteBinaryTree<K, V>::postorderPrint(Node i) {
    if (i >= size) {
        return;
    }
    postorderPrint(left(i));
    postorderPrint(right(i));
    cout << N[i].first << ":" << N[i].second <<  ";\t";
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::swapNodes(Node i, Node j) {
    swap(N[i], N[j]);
}

template<typename K, typename V>
const pair<K, V> &CompleteBinaryTree<K, V>::operator[](int i) const {
    return N.at(i);
}

template<typename K, typename V>
pair<K, V> &CompleteBinaryTree<K, V>::operator[](int i) {
    return N.at(i);
}

template <typename K, typename V>
class MinPriorityQueue {
public:
    CompleteBinaryTree<K, V> tree;
    MinPriorityQueue(): tree{}{}
    MinPriorityQueue(const MinPriorityQueue& mpq):tree{mpq.tree.N} {}

    void downHeap(Node i);
    void upHeap(Node i);

    void buildMinHeap(const vector<pair<K, V>>& L);

    V minimum();
    V extractMin();
    void decreaseKey(Node i, K key);
    void insert(const pair<K, V>& v);

    void print() const;
};

template<typename K, typename V>
void MinPriorityQueue<K, V>::downHeap(Node i) {
    Node l = tree.left(i);
    Node r = tree.right(i);

    Node smallest;

    if(l<tree.getSize() && (tree.element(l).first < tree.element(i).first))
        smallest = l;
    else
        smallest = i;

    if(r<tree.getSize() && (tree.element(r).first <tree.element(smallest).first))
        smallest = r;

    if(smallest != i){
        tree.swapNodes(i,smallest);
        downHeap(smallest);
    }

}

template<typename K, typename V>
void MinPriorityQueue<K, V>::upHeap(Node i) {
    while( i>0 && tree[tree.parent(i)].first > tree[i].first){
        tree.swapNodes(i, tree.parent(i));
        i = tree.parent(i);
    }

}

template<typename K, typename V>
void MinPriorityQueue<K, V>::buildMinHeap(const vector<pair<K, V>> &L) {
    tree.N = L;

    tree.setSize(L.size());

    for(int i= L.size()/2-1; i>=0; i--)
        downHeap(i);

}

template<typename K, typename V>
V MinPriorityQueue<K, V>::minimum() {
    return tree.N.front().second;
}

template<typename K, typename V>
V MinPriorityQueue<K, V>::extractMin() {
    if(tree.getSize()<0){

        return nullptr;
    }else{
        V min = minimum();
        tree[0] = tree[tree.getSize()-1];
        tree.setSize(tree.getSize()-1);
        tree.N.pop_back();
        downHeap(0);
        return min;
    }

}

template<typename K, typename V>
void MinPriorityQueue<K, V>::decreaseKey(Node i, K key) {
    if(i>=tree.getSize() && tree[i].first < key){

        return;
    }

    tree[i].first = key;
    upHeap(i);
}

template<typename K, typename V>
void MinPriorityQueue<K, V>::insert(const pair<K, V> &v) {
    tree.setSize(tree.getSize()+1);
    pair<K,V> newNode = v;
    tree.N.push_back(v);
    upHeap(tree.getSize()-1);
}

template<typename K, typename V>
void MinPriorityQueue<K, V>::print() const {

    for(auto it = tree.N.cbegin(); it!= tree.N.cend(); it++)
        cout << "K: " << it->first << ", V: " << it->second << ";\t";

    cout << endl << endl;

}

int main() {

    MinPriorityQueue<int, string> mp{};
    mp.insert({1,"osoba4"});
    mp.insert({2,"osoba7"});
    mp.insert({7, "osoba5"});
    mp.insert({8, "osoba1"});
    mp.insert({5, "osoba6"});

    mp.print();

    mp.insert({6,"osoba9"});
    mp.print();

    mp.extractMin();
    mp.print();

    mp.decreaseKey(2,4);
    mp.print();

    return 0;
}
