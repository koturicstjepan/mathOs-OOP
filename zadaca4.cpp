#include<iostream>

using namespace std;

struct Node {
    double value;
    Node* next;

    Node();
    Node(double value);
    Node(const Node& n);
    ~Node();

    void swap(Node& n);

    void print() const;
};

Node::Node(): next{nullptr}, value{} {}

Node::Node(double value): next{nullptr}, value{value} {}

Node::Node(const Node &n) {
    value = n.value;
    next = n.next;
}

Node::~Node() {}

void Node::swap(Node &n) {
    double temp= value;
    value = n.value;
    n.value = temp;
}

void Node::print() const {
    cout << "Node at " << this <<"; value: " << value << "; next: " << next << endl;
}

class CSLL {
protected:
    Node* head;
public:
    CSLL();
    CSLL(const CSLL& c);
    ~CSLL();

    bool empty() const;

    void prepend(double value);
    void append(double value);

    double removeFromHead();
    double removeFromTail();

    void sort();

    void print() const;
};

CSLL::CSLL(): head{nullptr} {}

CSLL::CSLL(const CSLL &c) {
    head = nullptr;

    Node* it = c.head;
    do{
        append(it->value);
        it = it->next;
    }while(it!=c.head);
}

CSLL::~CSLL() {
    while(!empty())
        removeFromHead();
}

bool CSLL::empty() const {
    return head == nullptr;
}

void CSLL::prepend(double value) {

    Node* n = new Node{value};

    if(empty()){
        head = n;
        n->next = n;
    }else{
        Node* it = head;

        while(it->next!=head)
            it = it->next; 

        n->next = head;
        it->next = n;
        head = n;
    }
}

void CSLL::append(double value) {
    prepend(value);
    head = head->next;
}

double CSLL::removeFromHead() {
    if(!empty()){

        double to_return = head->value;
        Node* toDelete = head;

        Node* it = head;

        while(it->next != head)
            it = it->next;

        if(head->next== head)
            head = nullptr;
        else{
            it->next = head->next;
            head = head->next;
        }

        delete toDelete;
        return to_return;
    }
}

double CSLL::removeFromTail() {

    Node* it = head;
    while(it->next != head)
        it = it->next; 

    head = it;

    return removeFromHead();

}

void CSLL::sort() {
    Node* last = head;
    while(last->next != head)
        last = last->next; 

    while(head!=last)
    {
        Node *j = head;
        Node* prev;

        while(j!=last) {
            if(j->value>j->next->value)
                j->swap(*j->next);

            prev = j;
            j=j->next;
        }
        last = prev;
    }

}

void CSLL::print() const {
    cout << "CSLL at: " << this << "; head at: " << head << endl;

    if(!empty()){
        Node* it = head;
        do{
            it->print();
            it=it->next;
        }while(it!=head);
    }

    cout << endl << endl;
}


class DynamicQueue {
protected:
    CSLL container;
public:
    DynamicQueue();
    DynamicQueue(const DynamicQueue& q);
    ~DynamicQueue();

    bool empty() const;

    void enqueue(double x);
    double dequeue();

    void print() const;
};

DynamicQueue::DynamicQueue(): container{} {}

DynamicQueue::DynamicQueue(const DynamicQueue &q): container{q.container} {}

DynamicQueue::~DynamicQueue() {}

bool DynamicQueue::empty() const {
    return container.empty();
}

void DynamicQueue::enqueue(double x) {
    container.append(x);
}

double DynamicQueue::dequeue() {
    return container.removeFromHead();
}

void DynamicQueue::print() const {
    container.print();
}

int main(){
    CSLL* c = new CSLL{};

    c->print();
    double arr[] ={59.9, 13.7, 10.0, 98.44, 16.7, 20.269, 1.5};

    for(auto el: arr)
        c->append(el);

    c->print();

    CSLL* c2 = new CSLL{*c};
    c2->sort();
    c2->print();

    c2->removeFromTail();
    c2->print();

    DynamicQueue* dq = new DynamicQueue{};
    dq->print();

    for(auto el: arr)
        dq->enqueue(el);

    dq->print();

    DynamicQueue* dq2 = new DynamicQueue{*dq};
    dq2->print();

    while(!dq2->empty())
        cout << dq2->dequeue() << endl;

    dq2->print();
    delete c; delete c2;
    delete dq; delete dq2;

    return 0;

}
