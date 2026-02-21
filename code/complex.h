#ifndef OOP_COMPLEX_H
#define OOP_COMPLEX_H
#include <utility>

class complex {
public:
    long double real=0.f,imag=0.f;

    float absolute_squared() {
        return (real * real) + (imag * imag);
    }
    static std::pair<complex,complex> MatrixMultiply(complex a,complex b,complex mat[2][2]) {
        std::pair<complex,complex> state;
        state.first = mat[0][0]*a+mat[0][1]*b;
        state.second = mat[1][0]*a+mat[1][1]*b;
        return state;
    }
    complex operator*(complex num) {
        complex inm;
        inm.real = real*num.real - imag*num.imag;
        inm.imag = real*num.imag + num.real*imag;
        return inm;
    }
    complex operator+(complex num) {
        complex sum;
        sum.real = real+num.real;
        sum.imag = imag+num.imag;
        return sum;
    }
};

#endif //OOP_COMPLEX_H