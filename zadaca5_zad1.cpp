#include <iostream>
#include <list>
#include <limits>

using namespace std;

double sum(const list<double>& li){
    double suma = 0.0;

    for(auto value: li)
        suma+=value;

    return suma;
}

double prod(const list<double>& li){
    double produkt = 1.0;

    for(auto value: li)
        produkt*=value;

    return produkt;
}

double min(const list<double>& li){
    double minValue = numeric_limits<double>::max();

    for(auto value: li)
        if(value<minValue)
            minValue=value;

    return minValue;
}

double max(const list<double>& li){
    double maxValue = numeric_limits<double>::min();

    for(auto value: li)
        if(value>maxValue)
            maxValue=value;

    return maxValue;
}

int main() {

    list<double> li;

    double values[] = {59.9, 13.7, 10.0, 98.44, 16.7, 20.269, 1.5};

    for(double value: values)
        li.push_back(value);

    for(double el: li)
        cout << el << "\t";
    cout << endl;


    cout << sum(li) << endl;
    cout << prod(li) << endl;
    cout << min(li) << endl;
    cout << max(li) << endl;

    return 0;
}
