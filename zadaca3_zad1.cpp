#include <iostream>
#include<cmath>
#include<algorithm>

using namespace std;

struct PositionVector {
    double x, y;
    PositionVector();
    PositionVector(double, double);
    PositionVector(const PositionVector&);

    double norm() const;
    void print() const;
};

PositionVector::PositionVector() {
    x = 0.0;
    y = 0.0;
}

PositionVector::PositionVector(double x, double y) {
    this->x = x;
    this->y = y;
}

PositionVector::PositionVector(const PositionVector &pv) {
    x = pv.x;
    y = pv.y;
}

double PositionVector::norm() const {
    return sqrt(pow(x,2)+pow(y,2));
}

void PositionVector::print() const {
    cout << "(x,y) = (" << x << "," << y << ")\tnorm: " << norm() << endl;
}

bool comp(const PositionVector& pv1, const PositionVector& pv2){
    return pv1.norm() > pv2.norm();
}

int main(){

    PositionVector vecs[5] = {{1.5, 2.7}, {3.4, 5.1}, {2.3, 6.3}, {5.0, 0.8}, {0.0, 0.0}};

    for(auto& el: vecs)
        el.print();

    sort(vecs, vecs+5, comp);

    cout << endl << endl;
    for(auto& el: vecs)
        el.print();

    return 0;
}