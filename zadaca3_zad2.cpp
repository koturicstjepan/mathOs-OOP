#include <iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<numeric>


using namespace std;

struct Student {
    int scores[5];
    Student();
    void fillScores(int(& arr)[5]);
    int calculateTotalScore() const;
    void print() const;
};

Student::Student() {}

void Student::fillScores(int (&arr)[5]) {
    for(int i=0; i<5; i++)
        scores[i] = arr[i];
}

int Student::calculateTotalScore() const {
    return accumulate(scores, scores+5, 0);
}

void Student::print() const {
    for(auto score:scores)
        cout << score << "\t";
    cout << endl;
}
int grade;

bool gradeGraterThan(const Student& s){
    return s.calculateTotalScore()>=grade;
}

int main(){

    ifstream infile("C:\\Users\\Korisnik\\Desktop\\data.txt");
    string line;

    int n;
    getline(infile,line);

    istringstream iss(line);
    iss >> n;
    cout << n << endl << endl;

    Student *students = new Student[n];

    int i= 0;
    while(getline(infile,line)){
        istringstream iss(line);

        int arr[5];
        for(int j=0; j<5; j++)
            iss >> arr[j];

        students[i].fillScores(arr);
        i++;
    }
    for(int i=0; i<n; i++)
        students[i].print();

    grade = students[0].calculateTotalScore();
    cout << grade << endl;

    cout << count_if(students+1, students+n, gradeGraterThan)  << endl;

    infile.close();

    delete[] students;

    return 0;
}