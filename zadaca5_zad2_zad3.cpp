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

    void reverse();

    double avg() ;
    Node* max() ;
    Node* min() ;
    void deleteAboveAverage();
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

void CSLL::reverse(){
    if(!empty()) {
        Node *prev = head;
        while(prev->next!=head)
            prev = prev->next;

        Node *curr = head;

        do {
            Node *next = curr->next;
            curr->next = prev;

            prev = curr;
            curr = next;

        }while (curr != head);

        head = prev;
    }
}

double CSLL::avg() {

    if(!empty()) {
        int br = 0;
        double suma = 0.0;

        Node *iter = head;

        do {
            suma += iter->value;
            br++;
            iter = iter->next;
        } while (iter != head);

        return suma / br;
    }
}

Node *CSLL::max() {

    if(!empty()) {
        Node *iter = head;
        Node *max = head;

        do {
            if (iter->value > max->value)
                max = iter;
            iter = iter->next;
        } while (iter != head);

        return max;
    }

    return nullptr;

}

Node *CSLL::min() {

    if(!empty()) {
        Node *iter = head;
        Node *min = head;

        do {
            if (iter->value < min->value)
                min = iter;
            iter = iter->next;
        } while (iter != head);

        return min;
    }
    return nullptr;
}

void CSLL::deleteAboveAverage() {

    if(!empty()) {
        double avg = this->avg();

        while(head->value > avg)
            removeFromHead();

        Node *prev = head;
        Node *curr = head->next;

        do{
            if(curr->value>avg){
                Node* to_delete = curr;
                prev->next = curr->next;
                curr = curr->next;

                delete to_delete;
            }else{
                prev = curr;
                curr = curr->next;
            }
        }while(curr!=head);

    }


}



int main(){

    CSLL* c = new CSLL{};

    c->print();
    double arr[] ={59.9, 13.7, 10.0, 98.44, 16.7, 20.269, 1.5};

    for(auto el: arr)
        c->append(el);

    c->print();
    c->reverse();
    c->print();


    cout << c->avg() << endl;
    cout << c->max()->value << endl;
    cout << c->min()->value << endl;
    c->deleteAboveAverage();
    c->print();

    delete c;

    return 0;

}
