#include <iostream>
#include <random>
#include<ctime>
#include<unistd.h>

using namespace std;

class IMU{
private:
    double dx, dy, dz;
public:
    IMU(): dx{}, dy{}, dz{} {}

    void measure(){
        dx = (double) (rand() / (RAND_MAX +1.0));
        dy = (double) (rand() / (RAND_MAX +1.0));
        dz = (double) (rand() / (RAND_MAX +1.0));
    }

    friend ostream& operator<<(ostream&, const IMU&);
    friend int main();
    friend class Car;
    friend class Drone;
};

ostream& operator<<(ostream& os, const IMU& imu){
    return os << "dx: " << imu.dx << ", dy: " << imu.dy << ", dz: " << imu.dz;
}

struct Position{
    double x, y, z;
};

class AutonomousVehicle{
protected:
    Position p{};
    IMU imu{};
public:
    AutonomousVehicle(): imu{}, p{}{};
    ~AutonomousVehicle(){};
    virtual ostream& printDrive(ostream &os) const = 0;
    virtual void drive(double dt) = 0;
};

ostream& operator<<(ostream& os, const AutonomousVehicle& av){
    return av.printDrive(os);
}

class Car: public AutonomousVehicle{
public:
    ostream& printDrive(ostream &os) const override;
    void drive(double) override;
};

void Car::drive(double dt) {
    imu.measure();
    p.x += imu.dx *dt;
    p.y += imu.dy *dt;

}

ostream & Car::printDrive(ostream &os) const{
    return os << "Car position: (" << p.x << ", " << p.y <<")";
}

class Drone: public AutonomousVehicle{
public:
    ostream& printDrive(ostream &os) const override;
    void drive(double) override;
};

void Drone::drive(double dt) {
    imu.measure();
    p.x += imu.dx *dt;
    p.y += imu.dy *dt;
    p.z += imu.dz *dt;

}

ostream & Drone::printDrive(ostream &os) const{
    return os << "Drone position: (" << p.x << ", " << p.y << ", " << p.z <<")";
}

int main() {

    Car c{};
    Drone d{};
    c.drive(0.005);
    d.drive(0.005);

    cout << c << "\n" << d << "\n";
	cout << endl << endl;

    AutonomousVehicle* av[2] = {&c, &d};

    for(AutonomousVehicle* vehicle: av){
        vehicle->drive(0.005);
        cout << *vehicle << endl;
    }

    return 0;
}
