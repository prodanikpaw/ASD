#pragma once
#include "list.h"
#include "Monom.h"

class Polynom {
private:
    string _name;
    List<Monom> _polynom;

    void _normalize();
    void _insertSorted(const Monom& monom);
    void _parseString(const string& str);


public:
    Polynom();
    explicit Polynom(const string& str);
    explicit Polynom(const char* str);
    Polynom(const string& name, const string& str);
    Polynom(const Polynom& other);

    ~Polynom() = default;

    Polynom& operator=(const Polynom& other);

    string getName() const;
    void setName(const string& newName);

    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;
    Polynom operator*(double scalar) const;
    Polynom operator/(double scalar) const;

    Polynom operator-() const;

    Polynom& operator+=(const Polynom& other);
    Polynom& operator-=(const Polynom& other);
    Polynom& operator*=(const Polynom& other);
    Polynom& operator*=(double scalar);
    Polynom& operator/=(double scalar);

    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;

    double evaluate(const TVector<double>& point) const;
    double evaluate(double x, double y, double z) const;

    void addMonom(const Monom& monom);

    friend ostream& operator<<(ostream& os, const Polynom& polynom);
    friend istream& operator>>(istream& is, Polynom& polynom);

    string toString() const;
    bool isZero() const;
    int getMonomCount() const;

    List<Monom>::Iterator begin() { return _polynom.begin(); }
    List<Monom>::Iterator end() { return _polynom.end(); }
    List<Monom>::Iterator begin() const { return _polynom.begin(); }
    List<Monom>::Iterator end() const { return _polynom.end(); }
};


void Polynom::_parseString(const string& str) {
    if (str.empty()) return;
    string s;
    for (char c : str) {
        if (c != ' ') {
            s += c;
        }
    }

    if (s == "0") return;

    string current;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        if ((c == '+' || c == '-') && !current.empty()) {
            try {
                Monom m(current);
                if (!m.isZero()) {
                    addMonom(m);
                }
            }
            catch (const exception& e) {
            }
            current = "";
            current += c;
        }
        else {
            current += c;
        }
    }
    if (!current.empty()) {
        try {
            Monom m(current);
            if (!m.isZero()) {
                addMonom(m);
            }
        }
        catch (const exception& e) {
        }
    }

    _normalize();
}


Polynom operator*(double scalar, const Polynom& polynom);


Polynom::Polynom() : _name("P") {}

Polynom::Polynom(const string& str) : _name("P") {
    _parseString(str);
}

Polynom::Polynom(const string& name, const string& str) : _name(name) {
    _parseString(str);
}

Polynom::Polynom(const char* str) : Polynom(string(str)) {}



Polynom::Polynom(const Polynom& other) : _name(other._name) {
    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
        _polynom.push_back(*it);
    }
}

Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        _name = other._name;
        while (!_polynom.is_empty()) {
            _polynom.pop_front();
        }

        for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
            _polynom.push_back(*it);
        }
    }
    return *this;
}

string Polynom::getName() const {
    return _name;
}

void Polynom::setName(const string& newName) {
    _name = newName;
}

void Polynom::_insertSorted(const Monom& monom) {
    auto it = _polynom.begin();
    int pos = 0;
    while (it != _polynom.end() && it->isMoreThan(monom)) {
        ++it;
        ++pos;
    }

    auto current = _polynom.begin();
    int currentPos = 0;
    bool found = false;

    while (current != _polynom.end()) {
        if (current->isSimilar(monom)) {
            Monom sum = *current + monom;
            if (sum.isZero()) {
                _polynom.pop(currentPos);
            }
            else {
                _polynom.pop(currentPos);
                auto insertIt = _polynom.begin();
                int insertPos = 0;
                while (insertIt != _polynom.end() && insertIt->isMoreThan(sum)) {
                    ++insertIt;
                    ++insertPos;
                }
                _polynom.insert(insertPos, sum);
            }
            found = true;
            break;
        }
        ++current;
        ++currentPos;
    }

    if (!found) {
        _polynom.insert(pos, monom);
    }
}

void Polynom::_normalize() {
    if (_polynom.is_empty()) return;

    TVector<Monom> temp;
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        temp.push_back(*it);
    }

    while (!_polynom.is_empty()) {
        _polynom.pop_front();
    }

    for (int i = 0; i < temp.getsize() - 1; ++i) {
        for (int j = 0; j < temp.getsize() - i - 1; ++j) {
            if (!temp[j].isMoreThan(temp[j + 1])) {
                Monom tmp = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < temp.getsize(); ++i) {
        _insertSorted(temp[i]);
    }
}

void Polynom::addMonom(const Monom& monom) {
    if (monom.isZero()) return;
    _insertSorted(monom);
}

Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result(*this);
    result.setName("Result");

    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
        result.addMonom(*it);
    }

    return result;
}

Polynom Polynom::operator-(const Polynom& other) const {
    Polynom result("Result", "");

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        result.addMonom(*it);
    }

    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
        result.addMonom(-(*it));
    }

    return result;
}

Polynom Polynom::operator*(const Polynom& other) const {
    Polynom result("Result", "");

    for (auto it1 = _polynom.begin(); it1 != _polynom.end(); ++it1) {
        for (auto it2 = other._polynom.begin(); it2 != other._polynom.end(); ++it2) {
            result.addMonom((*it1) * (*it2));
        }
    }

    return result;
}

Polynom Polynom::operator*(double scalar) const {
    Polynom result("Result", "");

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        result.addMonom((*it) * scalar);
    }

    return result;
}

Polynom Polynom::operator/(double scalar) const {
    if (abs(scalar) < 1e-10) {
        throw invalid_argument("Division by zero");
    }

    Polynom result("Result", "");

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        result.addMonom((*it) / scalar);
    }

    return result;
}

Polynom Polynom::operator-() const {
    Polynom result("Result", "");

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        result.addMonom(-(*it));
    }

    return result;
}


Polynom& Polynom::operator+=(const Polynom& other) {
    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
        addMonom(*it);
    }
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
    for (auto it = other._polynom.begin(); it != other._polynom.end(); ++it) {
        addMonom(-(*it));
    }
    return *this;
}

Polynom& Polynom::operator*=(const Polynom& other) {
    *this = *this * other;
    return *this;
}

Polynom& Polynom::operator*=(double scalar) {
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        *it *= scalar;
    }
    return *this;
}

Polynom& Polynom::operator/=(double scalar) {
    if (abs(scalar) < 1e-10) {
        throw invalid_argument("Division by zero");
    }
    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        *it /= scalar;
    }
    return *this;
}



bool Polynom::operator==(const Polynom& other) const {
    if (_polynom.size() != other._polynom.size()) return false;

    auto it1 = _polynom.begin();
    auto it2 = other._polynom.begin();

    while (it1 != _polynom.end() && it2 != other._polynom.end()) {
        if (*it1 != *it2) return false;
        ++it1;
        ++it2;
    }

    return true;
}

bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}

double Polynom::evaluate(const TVector<double>& point) const {
    double result = 0.0;

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        result += it->evaluate(point);
    }

    return result;
}

double Polynom::evaluate(double x, double y, double z) const {
    if (VARIABLES_COUNT != 3) {
        throw runtime_error("This method is only for 3 variables");
    }

    TVector<double> point(3);
    point[0] = x;
    point[1] = y;
    point[2] = z;
    return evaluate(point);
}

string Polynom::toString() const {
    if (_polynom.is_empty()) return "0";

    ostringstream oss;
    bool first = true;

    for (auto it = _polynom.begin(); it != _polynom.end(); ++it) {
        if (!first) {
            if (it->getCoefficient() > 0) {
                oss << "+";
            }
        }
        oss << *it;
        first = false;
    }

    return oss.str();
}

bool Polynom::isZero() const {
    return _polynom.is_empty();
}

int Polynom::getMonomCount() const {
    return _polynom.size();
}

ostream& operator<<(ostream& os, const Polynom& polynom) {
    os << polynom._name << " = " << polynom.toString();
    return os;
}

istream& operator>>(istream& is, Polynom& polynom) {
    cout << "Enter polynomial name: ";
    is >> polynom._name;
    cout << "Enter polynomial expression: ";
    string input;
    is.ignore();
    getline(is, input);
    polynom = Polynom(polynom._name, input);
    return is;
}

Polynom operator*(double scalar, const Polynom& polynom) {
    return polynom * scalar;
}