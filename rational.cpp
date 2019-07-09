#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int sign(int a) {
    if (a > 0)
        return 1;
    else if (a == 0)
        return 0;
    else
        return -1;
}

class Rational {
private:
    int num, den;

public:
    explicit Rational(int x, int y = 1) :
        num(sign(x * y) * (abs(x) / gcd(x, y))), den(abs(y) / gcd(x, y)) {}
    Rational() : num(0), den(1) {}

    int numerator() const {
        return num;
    }

    int denominator() const {
        return den;
    }

    Rational operator + (Rational q) const {
        int n;
        int d;
        d = den * q.den;
        n = num * q.den + q.num * den;
        return Rational(n, d);
    }

    Rational operator - (Rational q) const {
        int n;
        int d;
        d = den * q.den;
        n = num * q.den - q.num * den;
        return Rational(n, d);
    }

    Rational operator * (Rational q) const {
        int n;
        int d;
        d = den * q.den;
        n = num * q.num;
        return Rational(n, d);
    }

    Rational operator / (Rational q) const {
        int n;
        int d;
        d = den * q.num;
        n = num * q.den;
        return Rational(n, d);
    }

    Rational& operator ++() {
        *this = (*this) + Rational(1);
        return *this;
    }

    Rational operator ++(int) {
        Rational output = *this;
        *this = (*this) + Rational(1);
        return output;
    }

    Rational operator --(int) {
        Rational output = *this;
        *this = (*this) - Rational(1);
        return output;
    }

    Rational& operator --() {
        *this = (*this) - Rational(1);
        return *this;
    }

    Rational operator - () const {
        return Rational(-1 *(*this).num, (*this).den);
    }

    Rational operator + () const {
        return *this;
    }

    bool operator == (Rational q) {
        return (den == q.den && num == q.num);
    }

    bool operator != (Rational q) {
        return (den != q.den || num != q.num);
    }
};

Rational operator + (Rational q, int a) {
    return q + Rational(a);
}

Rational operator + (int a, Rational q) {
    return q + Rational(a);
}

Rational operator - (Rational q, int a) {
    return q - Rational(a);
}

Rational operator - (int a, Rational q) {
    return q - Rational(a);
}

Rational operator * (Rational q, int a) {
    return q * Rational(a);
}

Rational operator * (int a, Rational q) {
    return q * Rational(a);
}

Rational operator / (Rational q, int a) {
    return q / Rational(a);
}

Rational operator / (int a, Rational q) {
    return q / Rational(a);
}

void operator += (Rational& q1, const Rational& q2) {
    q1 = q1 + q2;
}

void operator -= (Rational& q1, const Rational& q2) {
    q1 = q1 - q2;
}

void operator *= (Rational& q1, const Rational& q2) {
    q1 = q1 * q2;
}

void operator /= (Rational& q1, const Rational& q2) {
    q1 = q1 / q2;
}
