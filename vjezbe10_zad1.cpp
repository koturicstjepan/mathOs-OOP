#include <iostream>
#include<list>
using namespace std;

template <typename K, typename V>
struct MinPriorityQueue {
    list<pair<K, V>> container;
    void insert(const pair<K, V>& el);
    V extractMin();

    void decreaseKey(const K& key, const K& newKey);

    void print() const;
};

template<typename K, typename V>
void MinPriorityQueue<K, V>::insert(const pair<K, V> &el) {
    auto it{container.begin()};

    while(it!=container.end() && el.first > it->first)
        it++;

    container.insert(it,el);

}

template<typename K, typename V>
V MinPriorityQueue<K, V>::extractMin() {

    V value = container.front().second;
    container.pop_front();

    return value;
}

template<typename K, typename V>
void MinPriorityQueue<K, V>::decreaseKey(const K &key, const K &newKey) {
    auto it{container.rbegin()};

    while(it!=container.rend() && it->first != key)
        it++;

    if(it == container.rend()) return;

    pair<K,V> el{*it};
    el.first = newKey;

    container.erase(next(it).base());

    while(it!=container.rend() && it->first > newKey) it++;

    container.insert(it.base(),el);

}

template<typename K, typename V>
void MinPriorityQueue<K, V>::print() const {

    for(auto it = container.begin(); it!=container.end(); ++it)
         cout << "K: " << it->first << "; V: " << it->second << ";\t";;
    cout << "\n\n";
}

int main()
{

    MinPriorityQueue<int, string> mpq{};
    mpq.insert({1,"osoba4"});
    mpq.insert({2,"osoba7"});
    mpq.insert({7,"osoba5"});
    mpq.insert({8,"osoba1"});
    mpq.insert({5,"osoba6"});

    mpq.print();

    mpq.insert({6,"osoba9"});
    mpq.print();

    cout << mpq.extractMin() << "\n";

    mpq.decreaseKey(6,4);
    mpq.print();

    return 0;
}
