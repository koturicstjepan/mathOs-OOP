#include <iostream>
#include <cmath>
using namespace std;

class Point {
private:
    double x, y;
public:
    Point();
    Point(double, double);
    ~Point();

    void setx(double);
    void sety(double);

    double getx();
    double gety();

    void printPoint();

    double euclideanDistance(Point& p);
};

Point::Point(){}

Point::Point(double a, double b){
    x = a;
    y = b;
}

Point::~Point() {}

void Point::setx(double x) {
    this->x = x;
}

void Point::sety(double y) {
    this->y = y;
}

double Point::getx() {
    return x;
}

double Point::gety()  {
    return y;
}

void Point::printPoint() {
    cout << "x: " << x << ";\ty:" << y << ";\n";
}

double Point::euclideanDistance(Point& p)  {
    return sqrt(pow(x - p.getx(), 2.0) + pow(y - p.gety(), 2.0));
}

int main() {
    Point p{5.4, 17.5};
    Point p2{4.88, 1.0};

    Point points[5];
    double x{0.0};
    double y{0.0};
    double m{0.0};

    for(int i=0; i<5; i++){
		m+=2;
        x+=m;
        points[i].setx(x);
        points[i].sety(y++);
    }

    for(int i=0; i<5; i++)
        points[i].printPoint();

    for(int i=1; i<5; i++){
        cout << endl << "Distance between points:" << endl;;
        points[i-1].printPoint();
        points[i].printPoint();
        cout << "iznosi: " << points[i].euclideanDistance(points[i-1]) << endl << endl;
    }


    return 0;
}
