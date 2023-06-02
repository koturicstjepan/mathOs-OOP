#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Node;

typedef list<Node*> NodeList;
typedef int Elem;

class Node
{
private:
    Elem _elt;
    Node* _left;
    Node* _right;
    Node* _par;
public:
    Node(Elem e): _elt(e), _left(nullptr), _right(nullptr), _par(nullptr){}

    void setLeft(Node *left)  { _left = left; }
    void setRight(Node *right) { _right = right; }
    void setParent(Node *par) { _par = par; }
    void setElement(Elem elt){ _elt = elt;}

    Elem element() const { return _elt; }
    Node * left() const { return _left; }
    Node * right() const { return _right; }
    Node * parent() const  { return _par; }

    bool isRoot() const { return _par == nullptr; } 
    bool isLeaf() const { return (_left == nullptr) && (_right == nullptr); } 

};

class BinaryTree
{
private:
    Node* _root;
    unsigned int _size;
public:
    BinaryTree():_root(nullptr), _size(0){}
    BinaryTree(const BinaryTree&);
    ~BinaryTree(); 

    Node* root() const { return _root; };
    unsigned size() const { return _size ; }

    bool addRoot(Elem e); 
    bool expandLeaves(Node *, Elem, Elem); 

    void postorderPrint(Node*); 
    void preorderPrint(Node*); 

    void preorderTree(Node*, NodeList&); 

    NodeList BFS(Node*);
    void BFSCopy(Node*, Node*);

    BinaryTree& operator=(const BinaryTree&);

};

void BinaryTree::BFSCopy(Node* n1, Node* n2){
    if(n1!=nullptr){
        if(n1->left()!=nullptr){
            Node* n2left = new Node{n1->left()->element()};
            n2->setLeft(n2left);
            n2left->setParent(n2);
            BFSCopy(n1->left(),n2left);
        }

        if(n1->right()!=nullptr){
            Node* n2right = new Node{n1->right()->element()};
            n2->setRight(n2right);
            n2right->setParent(n2);
            BFSCopy(n1->right(),n2right);
        }
    }

}

BinaryTree::BinaryTree(const BinaryTree& bt): BinaryTree{}{
    addRoot(bt.root()->element());
    BFSCopy(bt.root(),_root);
    _size = bt.size();
}

BinaryTree& BinaryTree::operator=(const BinaryTree& bt){
    this->~BinaryTree();
    _root = nullptr;
    _size = 0;

    addRoot(bt.root()->element());
    BFSCopy(bt.root(),_root);
    _size = bt.size();
	
	return *this;
}

NodeList BinaryTree::BFS(Node* n){
    NodeList l{};

    queue<Node*> q{};

    q.push(n);
    
    while(!q.empty()){
        Node* n1 = q.front();
        q.pop();

        if(n1!=nullptr){
            l.push_back(n1);
            q.push(n1->left());
            q.push(n1->right());
        }
    }

    return l;
}

void BinaryTree::preorderTree(Node* n, NodeList& L){

    if (n == nullptr)
        return;
    L.push_back(n);
    preorderTree(n->left(), L);
    preorderTree(n->right(), L);
}

BinaryTree::~BinaryTree()
{

    NodeList L;
    preorderTree(_root, L);

    for (auto n: L)
    {
        delete n;
    }
}
void BinaryTree::postorderPrint(Node *n){
    if (n == nullptr)
        return;

    postorderPrint(n->left());
    postorderPrint(n->right());
    cout << n->element() << "  " ;
}

void BinaryTree::preorderPrint(Node *n)
{
    if (n == nullptr)
        return;
    cout << n->element() << "  " ;
    preorderPrint(n->left());
    preorderPrint(n->right());
}
bool BinaryTree::addRoot(Elem e)
{
    if (_root != nullptr)
        return false;
    else
    {
        _root = new Node(e);
        _size = 1;
        return true;
    }
}

bool BinaryTree::expandLeaves(Node *n, Elem e1, Elem e2)
{
    if (n->left() != nullptr && n->right() != nullptr)
        return false;
    else
    {
        Node* n1 = new Node(e1);
        Node* n2 = new Node (e2);
        n->setLeft(n1);
        n1->setParent(n);
        n->setRight(n2);
        n2->setParent(n);
        _size += 2;
        return true;
    }
}

int main() {
    Elem e = 1;
    Node n(e);

    BinaryTree T;
    T.addRoot(1);
    T.expandLeaves(T.root(), 2, 3);
    T.expandLeaves(T.root()->left(), 4, 5);

    T.preorderPrint(T.root());
    cout << endl;
    T.postorderPrint(T.root());
    cout << endl;

    BinaryTree T2{T};
    T2.postorderPrint(T2.root());
    cout << endl;

    T2.root()->setElement(20);

    T.postorderPrint(T.root());
    cout << endl;
    T2.postorderPrint(T2.root());
    cout << endl;

    NodeList l{T.BFS(T.root())};

    for(Node* n: l)
        cout << n->element() << "  ";
    cout << endl;

    return 0;
}
