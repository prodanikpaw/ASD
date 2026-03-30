#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <Tvector.h>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include "Tvector.h"


using namespace std;
#ifndef VARIABLES_COUNT
#define VARIABLES_COUNT 3
#endif

const char VARIABLE_NAMES[] = { 'x', 'y', 'z', 'u', 'v', 'w', 'a', 'b', 'c', 'd' };

class Monom {
private:
    double coefficient;
    int powers[VARIABLES_COUNT];

public:
    Monom();
    explicit Monom(double coef);
    Monom(double coef, const TVector<int>& pows);
    Monom(const Monom& other);
    explicit Monom(const string& str);

    ~Monom() = default;

    Monom& operator=(const Monom& other);

    double getCoefficient() const;
    int getPower(int index) const;
    const int* getPowers() const;
    TVector<int> getPowersVector() const;

    void setCoefficient(double coef);
    void setPower(int index, int value);
    void setPowers(const TVector<int>& pows);

    bool isSimilar(const Monom& other) const;

    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    Monom operator+(const Monom& other) const;
    Monom operator-(const Monom& other) const;

    Monom operator*(const Monom& other) const;
    Monom operator/(const Monom& other) const;
    Monom operator*(double scalar) const;
    Monom operator/(double scalar) const;

    Monom operator-() const;

    Monom& operator+=(const Monom& other);
    Monom& operator-=(const Monom& other);
    Monom& operator*=(const Monom& other);
    Monom& operator/=(const Monom& other);
    Monom& operator*=(double scalar);
    Monom& operator/=(double scalar);

    double evaluate(const TVector<double>& point) const;
    double evaluate(double x, double y, double z) const; 


    bool isLessThan(const Monom& other) const;

    friend ostream& operator<<(ostream& os, const Monom& monom);
    friend istream& operator>>(istream& is, Monom& monom);

    string toString() const;
    bool isZero() const;
    int getVariablesCount() const;

    static char getVariableName(int index);
};

Monom operator*(double scalar, const Monom& monom);
Monom operator/(double scalar, const Monom& monom);


Monom::Monom() : coefficient(0.0) {
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        powers[i] = 0;
    }
}

Monom::Monom(double coef) : coefficient(coef) {
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        powers[i] = 0;
    }
}

Monom::Monom(double coef, const TVector<int>& pows) : coefficient(coef) {
    if (pows.getsize() != VARIABLES_COUNT) {
        throw std:: logic_error("Vector size must match VARIABLES_COUNT");
    }

    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        if (pows[i] < 0) {
            throw std::logic_error("Powers must be non-negative integers");
        }
        powers[i] = pows[i];
    }
}

Monom::Monom(const Monom& other) : coefficient(other.coefficient) {
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        powers[i] = other.powers[i];
    }
}

Monom::Monom(const string& str) {
    coefficient = 1.0;
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        powers[i] = 0;
    }

    if (str.empty()) {
        coefficient = 0.0;
        return;
    }

    const char* p = str.c_str();

    bool has_coef = false;
    string coef_str;

    if (*p == '+' || *p == '-' || (*p >= '0' && *p <= '9') || *p == '.') {
        has_coef = true;
        coef_str += *p;
        p++;

        while ((*p >= '0' && *p <= '9') || *p == '.') {
            coef_str += *p;
            p++;
        }

        if (coef_str == "+") coefficient = 1.0;
        else if (coef_str == "-") coefficient = -1.0;
        else coefficient = stod(coef_str);
    }

    while (*p) {
        char var = *p;
        p++;

        int power = 1;
        if (*p == '^') {
            p++;
            string power_str;
            while (*p >= '0' && *p <= '9') {
                power_str += *p;
                p++;
            }
            if (!power_str.empty()) {
                power = stoi(power_str);
            }
        }

        for (int i = 0; i < VARIABLES_COUNT; ++i) {
            if (VARIABLE_NAMES[i] == var) {
                powers[i] = power;
                break;
            }
        }
    }
}

Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        coefficient = other.coefficient;
        for (int i = 0; i < VARIABLES_COUNT; ++i) {
            powers[i] = other.powers[i];
        }
    }
    return *this;
}

double Monom::getCoefficient() const {
    return coefficient;
}

int Monom::getPower(int index) const {
    if (index < 0 || index >= VARIABLES_COUNT) {
        throw out_of_range("Variable index out of range");
    }
    return powers[index];
}

const int* Monom::getPowers() const {
    return powers;
}

TVector<int> Monom::getPowersVector() const {
    TVector<int> result(VARIABLES_COUNT);
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        result[i] = powers[i];
    }
    return result;
}

void Monom::setCoefficient(double coef) {
    coefficient = coef;
}

void Monom::setPower(int index, int value) {
    if (index < 0 || index >= VARIABLES_COUNT) {
        throw out_of_range("Variable index out of range");
    }
    if (value < 0) {
        throw logic_error("Power must be non-negative integer");
    }
    powers[index] = value;
}

void Monom::setPowers(const TVector<int>& pows) {
    if (pows.getsize() != VARIABLES_COUNT) {
        throw logic_error("Vector size must match VARIABLES_COUNT");
    }

    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        if (pows[i] < 0) {
            throw logic_error("Powers must be non-negative integers");
        }
        powers[i] = pows[i];
    }
}

bool Monom::isSimilar(const Monom& other) const {
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        if (powers[i] != other.powers[i]) {
            return false;
        }
    }
    return true;
}

bool Monom::operator==(const Monom& other) const {
    if (!isSimilar(other)) return false;
    return abs(coefficient - other.coefficient) < 1e-10;
}

bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

Monom Monom::operator+(const Monom& other) const {
    if (!isSimilar(other)) {
        throw logic_error("Cannot add dissimilar monomials");
    }

    Monom result(*this);
    result.coefficient += other.coefficient;
    return result;
}

Monom Monom::operator-(const Monom& other) const {
    if (!isSimilar(other)) {
        throw logic_error("Cannot subtract dissimilar monomials");
    }

    Monom result(*this);
    result.coefficient -= other.coefficient;
    return result;
}

Monom Monom::operator*(const Monom& other) const {
    Monom result;
    result.coefficient = coefficient * other.coefficient;

    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        result.powers[i] = powers[i] + other.powers[i];
    }

    return result;
}

Monom Monom::operator/(const Monom& other) const {
    if (abs(other.coefficient) < 1e-10) {
        throw logic_error("Division by zero");
    }

    Monom result;
    result.coefficient = coefficient / other.coefficient;

    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        result.powers[i] = powers[i] - other.powers[i];
        if (result.powers[i] < 0) {
            throw logic_error("Division results in negative power");
        }
    }

    return result;
}

Monom Monom::operator*(double scalar) const {
    Monom result(*this);
    result.coefficient *= scalar;
    return result;
}

Monom Monom::operator/(double scalar) const {
    if (abs(scalar) < 1e-10) {
        throw logic_error("Division by zero");
    }

    Monom result(*this);
    result.coefficient /= scalar;
    return result;
}

Monom Monom::operator-() const {
    Monom result(*this);
    result.coefficient = -coefficient;
    return result;
}

Monom& Monom::operator+=(const Monom& other) {
    if (!isSimilar(other)) {
        throw logic_error("Cannot add dissimilar monomials");
    }
    coefficient += other.coefficient;
    return *this;
}

Monom& Monom::operator-=(const Monom& other) {
    if (!isSimilar(other)) {
        throw logic_error("Cannot subtract dissimilar monomials");
    }
    coefficient -= other.coefficient;
    return *this;
}

Monom& Monom::operator*=(const Monom& other) {
    coefficient *= other.coefficient;
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        powers[i] += other.powers[i];
    }
    return *this;
}

Monom& Monom::operator/=(const Monom& other) {
    if (abs(other.coefficient) < 1e-10) {
        throw logic_error("Division by zero");
    }

    coefficient /= other.coefficient;
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        powers[i] -= other.powers[i];
        if (powers[i] < 0) {
            throw logic_error("Division results in negative power");
        }
    }
    return *this;
}

Monom& Monom::operator*=(double scalar) {
    coefficient *= scalar;
    return *this;
}

Monom& Monom::operator/=(double scalar) {
    if (abs(scalar) < 1e-10) {
        throw logic_error("Division by zero");
    }
    coefficient /= scalar;
    return *this;
}

// Вычисление значения в точке
double Monom::evaluate(const TVector<double>& point) const {
    if (point.getsize() != VARIABLES_COUNT) {
        throw logic_error("Point size must match VARIABLES_COUNT");
    }

    double result = coefficient;
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        if (powers[i] > 0) {
            result *= pow(point[i], powers[i]);
        }
    }
    return result;
}

double Monom::evaluate(double x, double y, double z) const {
    if (VARIABLES_COUNT != 3) {
        throw logic_error("This method is only for 3 variables");
    }

    TVector<double> point(3);
    point[0] = x;
    point[1] = y;
    point[2] = z;
    return evaluate(point);
}

bool Monom::isLessThan(const Monom& other) const {
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        if (powers[i] != other.powers[i]) {
            return powers[i] > other.powers[i];
        }
    }
    return false;
}

string Monom::toString() const {
    if (abs(coefficient) < 1e-10) return "0";

    ostringstream oss;

    if (abs(coefficient - 1.0) > 1e-10 && abs(coefficient + 1.0) > 1e-10) {
        oss << coefficient;
    }
    else if (abs(coefficient + 1.0) < 1e-10) {
        oss << "-";
    }

    bool hasVariables = false;
    for (int i = 0; i < VARIABLES_COUNT && i < sizeof(VARIABLE_NAMES); ++i) {
        if (powers[i] > 0) {
            oss << VARIABLE_NAMES[i];
            if (powers[i] > 1) {
                oss << "^" << powers[i];
            }
            hasVariables = true;
        }
    }

    if (!hasVariables) {
        if (abs(coefficient - 1.0) < 1e-10) oss << "1";
        else if (abs(coefficient + 1.0) < 1e-10) oss << "1";
    }

    return oss.str();
}

bool Monom::isZero() const {
    return abs(coefficient) < 1e-10;
}

int Monom::getVariablesCount() const {
    return VARIABLES_COUNT;
}

char Monom::getVariableName(int index) {
    if (index >= 0 && index < sizeof(VARIABLE_NAMES)) {
        return VARIABLE_NAMES[index];
    }
    return '?' + index;
}

ostream& operator<<(ostream& os, const Monom& monom) {
    os << monom.toString();
    return os;
}

istream& operator>>(istream& is, Monom& monom) {
    string input;
    is >> input;
    monom = Monom(input);
    return is;
}

Monom operator*(double scalar, const Monom& monom) {
    return monom * scalar;
}

Monom operator/(double scalar, const Monom& monom) {
    TVector<int> zeros(VARIABLES_COUNT);
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        zeros[i] = 0;
    }
    return Monom(scalar, zeros) / monom;
}
