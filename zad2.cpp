#include <iostream>
#include <random>
#include <unistd.h>
#include <ctime>

using namespace std;

class IMU {
private:
    double dx, dy, dz;
public:
    IMU(): dx{}, dy{}, dz{} {};

    void measure() {
        dx = (double) (rand() / (RAND_MAX + 1.0));
        dy = (double) (rand() / (RAND_MAX + 1.0));
        dz = (double) (rand() / (RAND_MAX + 1.0));
    };

    friend int main();
    friend ostream& operator<<(ostream&, const IMU&);
    friend class Car;
    friend class Drone;
};

ostream& operator<<(ostream& os, const IMU& imu){
    return os << "dx: " << imu.dx << "; dy: " << imu.dy << "; dz: " << imu.dz;
}

struct Position{
    double x,y,z;
};

class AutonomousVehicle{
protected:
    Position p{};
    IMU imu{};
public:
    AutonomousVehicle();
    ~AutonomousVehicle();

    void drive(double dt){};
    ostream& printDrive(ostream& os) const{
        return os;
    }
};

AutonomousVehicle::AutonomousVehicle(): imu{}, p{} {}
AutonomousVehicle::~AutonomousVehicle() {}

class Car: public AutonomousVehicle{
public:
    void drive(double dt);
    ostream& printDrive(ostream& os) const;

    friend ostream& operator<<(ostream&, const Car&);
};

void Car::drive(double dt) {
    imu.measure();
    p.x += imu.dx * dt;
    p.y += imu.dy * dt;
}

ostream & Car::printDrive(ostream &os) const {
    return os << "Car position: (" << p.x << ", " << p.y << ")";
}

ostream& operator<<(ostream&os, const Car& c){
    return c.printDrive(os);
}

class Drone: public AutonomousVehicle{
public:
    void drive(double dt);
    ostream& printDrive(ostream& os) const;

    friend ostream& operator<<(ostream&, const Drone&);
};

void Drone::drive(double dt) {
    imu.measure();
    p.x += imu.dx*dt;
    p.y += imu.dy*dt;
    p.z += imu.dz*dt;
}

ostream &Drone::printDrive(ostream &os) const {
    return os << "Drone position: (" << p.x << ", " << p.y << ", " << p.z <<")";
}

ostream& operator<<(ostream& os, const Drone& d){
    return d.printDrive(os);
}


int main() {

    srand(time(nullptr));
    Car car{};


    unsigned long ms= 0;

    while(true){
        if(ms%1000== 0)
            cout << car << endl;

        if(ms == 20000)
            break;

        usleep(5000);
        ms+=5;
        car.drive(0.005);
    }

    Drone drone{};

    ms= 0;

    while(true){
        if(ms%1000== 0)
            cout << drone << endl;

        if(ms == 20000)
            break;

        usleep(5000);
        ms+=5;
        drone.drive(0.005);
    }

    return 0;
}
