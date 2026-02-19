#ifndef OOP_COMPLEX_H
#define OOP_COMPLEX_H

class complex {
public:
    float real=1,imag=0;

    float absolute_squared() {
        return (real * real) + (imag * imag);
    }
};

#endif //OOP_COMPLEX_H