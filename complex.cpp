#include <cmath>
#include <iostream>

using namespace std;

class Complex {
private:
    double re, im;

public:
    explicit Complex(double r, double i = 0) : re(r), im(i) {}

    Complex() : re(0), im(0) {}

    double& Re() {
        return re;
    }

    double& Im() {
        return im;
    }

    double Re() const {
        return re;
    }

    double Im() const {
        return im;
    }

    Complex conj() const {
        return Complex(re, -im);
    }

    Complex operator + () const {
        return *this;
    }

    Complex operator - () const {
        return Complex(-(*this).re, -(*this).im);
    }

    bool operator == (Complex z) const {
        return (re == z.re && im == z.im);
    }

    bool operator != (Complex z) const {
        return (re != z.re || im != z.im);
    }
};

Complex operator + (Complex z1, Complex z2) {
    return Complex(z1.Re() + z2.Re(), z1.Im() + z2.Im());
}

Complex operator + (Complex z, double a) {
    return Complex(z.Re() + a, z.Im());
}

Complex operator + (double a, Complex z) {
    return Complex(z.Re() + a, z.Im());
}

Complex operator - (Complex z1, Complex z2) {
    return Complex(z1.Re() - z2.Re(), z1.Im() - z2.Im());
}

Complex operator - (Complex z, double a) {
    return Complex(z.Re() - a, z.Im());
}

Complex operator - (double a, Complex z) {
    return Complex(a - z.Re(), -z.Im());
}

Complex operator * (Complex z1, Complex z2) {
    return Complex(z1.Re() * z2.Re() - z1.Im() * z2.Im(), z1.Re() * z2.Im() + z1.Im() * z2.Re());
}

Complex operator * (Complex z, double a) {
    return Complex(z.Re() * a, z.Im() * a);
}

Complex operator * (double a, Complex z) {
    return Complex(z.Re() * a, z.Im() * a);
}

Complex operator / (Complex z, double a) {
    return Complex(z.Re() / a, z.Im() / a);
}

Complex operator / (Complex z1, Complex z2) {
    double temp = (z2.conj() * z2).Re();
    return (z1 * z2.conj()) / temp;
}

Complex operator / (double a, Complex z2) {
    Complex z1(a);
    double temp = (z2.conj() * z2).Re();
    return (z1 * z2.conj()) / temp;
}

double abs(Complex z) {
    return sqrt(z.Re() * z.Re() + z.Im() * z.Im());
}
