#include <iostream>

using namespace std;

template <typename T, size_t S>
struct Stack {
    int top;
    T container[S]{};
    Stack();
    Stack(const Stack&);
    ~Stack();

    bool empty() const;
    bool full() const;

    void push(const T&);
    T pop();

    void print() const;
};

template<typename T, size_t S>
Stack<T,S>::Stack(): top{-1}, container{}{};

template<typename T, size_t S>
Stack<T,S>::Stack(const Stack& s): Stack(){
    if(!s.empty()){
        for(const T& el: s.container){
            top++;
            container[top] = el;
        }
    }
}

template<typename T, size_t S>
Stack<T, S>::~Stack() {}

template<typename T, size_t S>
bool Stack<T, S>::empty() const {
    return top==-1;
}

template<typename T, size_t S>
bool Stack<T, S>::full() const {
    return top+1==S;
}

template<typename T, size_t S>
void Stack<T, S>::push(const T &el) {
    if(!full()){
        top++;
        container[top] = el;
    }
}

template<typename T, size_t S>
T Stack<T, S>::pop() {
    if(!empty())
        return container[top--];
}

template<typename T, size_t S>
void Stack<T, S>::print() const {
    for(int i=0; i<=top; i++)
        cout << container[i] << " ";

    cout << endl;
}

int main() {

    Stack<double,5> s{};

    double i = 1.5;
    while(!s.full())
        s.push(i++);

    s.print();

    cout << endl;
    while(!s.empty())
        cout << s.pop() << " ";

    cout << endl;

    s.print();

    return 0;
}