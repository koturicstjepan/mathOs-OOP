#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <limits>

using namespace std;

typedef int Elem;
class Node;
typedef list<Node*> NodeList;

class Node{
protected:
    Elem _elt;
    Node* _par;
    list<Node*> _children;

public:
    Node(Elem e): _elt(e), _par(nullptr), _children() {}
    Node(const Node& n) { _par = n.parent(); _elt = n._elt; _children = n._children; }

    list<Node*>& children() { return _children; }
    Node* parent() const { return _par; }
    Elem element() const { return _elt; }

    void setParent(Node* v) { _par = v; }

    void prependChild(Node* v) { _children.push_front(v); v->setParent(this);}
    void appendChild(Node* v) { _children.push_back(v); v->setParent(this); }

    void removeFirstChild() { _children.pop_front(); }
    void removeLastChild() { _children.pop_back(); }

    void setValue(Elem e) { _elt = e; }

    bool isRoot() const { return _par == nullptr; }
    bool isLeaf() const { return _children.empty(); }
};

class NAryTree {
public:
    Node* _root;

public:
    NAryTree(): _root(nullptr) {}
    NAryTree(const NAryTree&);
    ~NAryTree();

    Node* root() const { return _root; }
    void addRoot(Elem e) { _root = new Node(e);}

    void appendChild(Node*, Elem);
    void prependChild(Node*, Elem);

    void copyNode(Node*, Node*);

    void preorderPrint(Node* ) const;
    void postorderPrint(Node* ) const;

    void preorderNodes(Node*, NodeList&);

    NodeList BFS(Node*);

    NAryTree& operator=(const NAryTree&);

};

void NAryTree::copyNode(Node* origNode, Node* newNode) {
    if(origNode != nullptr) {
        for(Node* origChild: origNode->children()) {
            Node* newChild = new Node(origChild->element());
            newNode->appendChild(newChild);
            newChild->setParent(newNode);
            copyNode(origChild, newChild);
        }
    }
}


NAryTree::NAryTree(const NAryTree& copyTree) {
    addRoot(copyTree.root()->element());
    copyNode(copyTree.root(), root());
}

NAryTree::~NAryTree() {
    NodeList L;
    preorderNodes(_root, L);
    for(auto node: L) {
        delete node;
    }
}

void NAryTree::appendChild(Node* v, Elem e){
    Node* c{new Node{e}};
    v->appendChild(c);
	c->setParent(v);
}
void NAryTree::prependChild(Node* v, Elem e){
    Node* c{new Node{e}};
    v->prependChild(c);
	c->setParent(v);
}

void NAryTree::preorderPrint(Node* v) const {
    if(v == nullptr) {
        return;
    }
    cout << v->element() << " ";
    for(Node* child: v->children()) {
        preorderPrint(child);
    }
}


void NAryTree::postorderPrint(Node* v) const {
    if(v == nullptr) {
        return;
    }
    for(Node* child: v->children()) {
        postorderPrint(child);
    }
    cout << v->element() << " ";
}

void NAryTree::preorderNodes(Node* v, NodeList& L) {
    if(v == nullptr) {
        return;
    }
	L.push_back(v);
	
    for(Node* child: v->children()) {
        preorderNodes(child, L);
    }

}

NodeList NAryTree::BFS(Node* s) {
    NodeList nl{};

    queue<Node*> q{};
    q.push(s);

    while(!q.empty()){
        Node* n{q.front()};
        q.pop();

        if(n!= nullptr){
            nl.push_back(n);
            for(auto c: n->children())
                q.push(c);
        }
    }

    return nl;
}

NAryTree& NAryTree::operator=(const NAryTree& copyTree) {
	
	this->~NAryTree();
	_root = nullptr; 
	
    addRoot(copyTree.root()->element());
    copyNode(copyTree.root(), root());
    return *this;
}

int main() {
    NAryTree T{};

    T.addRoot(10);

    T.appendChild(T.root(), 11);
    T.appendChild(T.root(), 12);
    T.appendChild(T.root(), 7);
    T.preorderPrint(T.root());
    cout << endl;

    T.prependChild(T.root()->children().front(),9);
    T.preorderPrint(T.root());
    cout << endl;

    NodeList l{T.BFS(T.root())};

    for(Node* n: l)
        cout << n->element() << " ";
    cout << endl;

    return 0;
}