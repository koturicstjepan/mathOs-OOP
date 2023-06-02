#include<iostream>

using namespace std;

class SquareMatrix {
public:
    double** container;
    unsigned int M;

    SquareMatrix(unsigned int);
    SquareMatrix(const SquareMatrix&);
    ~SquareMatrix();

    void print() const;

    double* operator[](unsigned int);
    const double* operator[](unsigned int) const;

    SquareMatrix& operator=(const SquareMatrix&);
    SquareMatrix& operator+=(const SquareMatrix&);
    SquareMatrix& operator-=(const SquareMatrix&);
    SquareMatrix& operator*=(const SquareMatrix&);

    SquareMatrix& operator=(double);
    SquareMatrix& operator+=(double);
    SquareMatrix& operator-=(double);
    SquareMatrix& operator*=(double);
    SquareMatrix& operator/=(double);

    SquareMatrix operator+(const SquareMatrix&) const;
    SquareMatrix operator-(const SquareMatrix&) const;
    SquareMatrix operator*(const SquareMatrix&) const;


    SquareMatrix operator+(double) const;
    SquareMatrix operator-(double) const;
    SquareMatrix operator*(double) const;
    SquareMatrix operator/(double) const;

    bool operator==(const SquareMatrix&) const;
    bool operator!=(const SquareMatrix&) const;
};

SquareMatrix::SquareMatrix(unsigned int M): M{M}, container{new double*[M]} {
    for(int i=0; i<M; i++)
        container[i] = new double[M];

    for(int i=0; i<M; i++)
        for(int j=0; j<M; j++)
            container[i][j] = 0;

}

double *SquareMatrix::operator[](unsigned int i) {
    return container[i];
}

const double *SquareMatrix::operator[](unsigned int i) const {
    return container[i];
}

SquareMatrix::SquareMatrix(const SquareMatrix &m): M{m.M}, container{new double*[m.M]}{

    for(int i=0; i<M; i++)
        container[i] = new double[M];

    for(int i=0; i<M; i++)
        for(int j=0; j<M; j++)
            container[i][j] = m[i][j];
}

SquareMatrix::~SquareMatrix() {
    for(int i=0; i<M; i++)
        delete[] container[i];

    delete[] container;
}

void SquareMatrix::print() const {
    for(int i=0; i<M; i++) {
        for (int j = 0; j < M; j++)
            cout << container[i][j] << " ";

        cout << endl;
    }
}

SquareMatrix &SquareMatrix::operator=(const SquareMatrix &m) {
    if(M!=m.M){
        for(int i=0; i<M; i++)
            delete[] container[i];

        delete[] container;

        M = m.M;
        container = new double*[M];
        for(int i=0; i<M; i++)
            container[i] = new double[M];

    }

    for(int i=0; i<M; i++)
        for(int j=0; j<M; j++)
            container[i][j] = m[i][j];

    return *this;
}

SquareMatrix &SquareMatrix::operator+=(const SquareMatrix &m) {
    if(M == m.M){
        for(int i=0; i<M; i++)
            for(int j=0; j<M; j++)
                container[i][j] += m[i][j];
    }
    return *this;
}

SquareMatrix &SquareMatrix::operator-=(const SquareMatrix &m) {
    if(M == m.M){
        for(int i=0; i<M; i++)
            for(int j=0; j<M; j++)
                container[i][j] -= m[i][j];
    }
    return *this;
}

SquareMatrix &SquareMatrix::operator*=(const SquareMatrix &m) {
   *this = *this*m;

   return *this;
}

SquareMatrix &SquareMatrix::operator=(double val) {
    for(int i=0; i<M; i++)
        for(int j=0; j<M; j++)
            container[i][j] = val;

    return *this;
}

SquareMatrix &SquareMatrix::operator+=(double val) {
    for(int i=0; i<M; i++)
        for(int j=0; j<M; j++)
            container[i][j] += val;

    return *this;
}

SquareMatrix &SquareMatrix::operator-=(double val) {
    for(int i=0; i<M; i++)
        for(int j=0; j<M; j++)
            container[i][j] -= val;

    return *this;
}

SquareMatrix &SquareMatrix::operator*=(double val) {
    for(int i=0; i<M; i++)
        for(int j=0; j<M; j++)
            container[i][j] *= val;

    return *this;
}

SquareMatrix &SquareMatrix::operator/=(double val) {
    for(int i=0; i<M; i++)
        for(int j=0; j<M; j++)
            container[i][j] /= val;

    return *this;
}

SquareMatrix SquareMatrix::operator+(const SquareMatrix &m) const {
    SquareMatrix nm = SquareMatrix{*this};
    nm += m;

    return nm;
}

SquareMatrix SquareMatrix::operator-(const SquareMatrix &m) const {
    return SquareMatrix(*this)-=m;
}

SquareMatrix SquareMatrix::operator*(const SquareMatrix &m) const {
    SquareMatrix nm{M};

    for(int i=0; i<M; i++)
        for(int j=0; j<M; j++)
            for(int k=0; k<M; k++)
                nm[i][j]+= container[i][k]*m[k][j];

    return nm;
}

SquareMatrix SquareMatrix::operator+(double val) const {
    return SquareMatrix(*this)+=val;
}

SquareMatrix SquareMatrix::operator-(double val) const {
    return SquareMatrix(*this)-=val;
}

SquareMatrix SquareMatrix::operator*(double val) const {
    return SquareMatrix(*this)*=val;
}

SquareMatrix SquareMatrix::operator/(double val) const {
    return SquareMatrix(*this)/=val;
}

bool SquareMatrix::operator==(const SquareMatrix &m) const {
    if(M !=m.M)
        return false;
    else{
        for(int i=0; i<M; i++)
            for(int j=0; j<M; j++)
                if(container[i][j]!=m[i][j])
                    return false;
    }

    return true;
}

bool SquareMatrix::operator!=(const SquareMatrix &m) const {
    return !(*this==m);
}


int main()
{
   SquareMatrix m{10};
   for(int i=1; i<=10; i++)
       m[i-1][i-1] = i;

   m+=1;
   m.print();

   SquareMatrix m2{m};
   m2/=10;

   cout << endl << endl;
   m2.print();

    return 0;

}
