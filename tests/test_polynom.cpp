
#include <gtest/gtest.h>
#include "C:\Users\Proda\source\ASD\lib_Polynom\Polynom.h"


TEST(MonomTest, DefaultConstructor) {
    Monom m;
    EXPECT_DOUBLE_EQ(m.getCoefficient(), 0.0);
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        EXPECT_EQ(m.getPower(i), 0);
    }
    EXPECT_TRUE(m.isZero());
}

TEST(MonomTest, ConstructorWithCoefficient) {
    Monom m(3.5);
    EXPECT_DOUBLE_EQ(m.getCoefficient(), 3.5);
    for (int i = 0; i < VARIABLES_COUNT; ++i) {
        EXPECT_EQ(m.getPower(i), 0);
    }
}

TEST(MonomTest, ConstructorWithPowers) {
    TVector<int> powers(3);
    powers[0] = 2;
    powers[1] = 1;
    powers[2] = 0;

    Monom m(2.5, powers);
    EXPECT_DOUBLE_EQ(m.getCoefficient(), 2.5);
    EXPECT_EQ(m.getPower(0), 2);
    EXPECT_EQ(m.getPower(1), 1);
    EXPECT_EQ(m.getPower(2), 0);
}

TEST(MonomTest, ConstructorFromString) {
    Monom m1("2x^2y");
    EXPECT_DOUBLE_EQ(m1.getCoefficient(), 2.0);
    EXPECT_EQ(m1.getPower(0), 2); // x
    EXPECT_EQ(m1.getPower(1), 1); // y

    Monom m2("-3.5z^3");
    EXPECT_DOUBLE_EQ(m2.getCoefficient(), -3.5);
    EXPECT_EQ(m2.getPower(2), 3); // z

    Monom m3("x^2");
    EXPECT_DOUBLE_EQ(m3.getCoefficient(), 1.0);
    EXPECT_EQ(m3.getPower(0), 2);
}

TEST(MonomTest, CopyConstructor) {
    TVector<int> powers(3);
    powers[0] = 2;
    powers[1] = 1;
    powers[2] = 0;

    Monom m1(2.5, powers);
    Monom m2(m1);

    EXPECT_EQ(m1, m2);
}

TEST(MonomTest, AssignmentOperator) {
    TVector<int> powers(3);
    powers[0] = 2;
    powers[1] = 1;
    powers[2] = 0;

    Monom m1(2.5, powers);
    Monom m2;
    m2 = m1;

    EXPECT_EQ(m1, m2);
}

TEST(PolynomTest, DefaultConstructor) {
    Polynom p;
    EXPECT_EQ(p.getName(), "P");
    EXPECT_TRUE(p.isZero());
    EXPECT_EQ(p.getMonomCount(), 0);
    EXPECT_EQ(p.toString(), "0");
}

TEST(PolynomTest, ConstructorFromString) {
    Polynom p("x^2 + 2x + 1");
    EXPECT_EQ(p.getName(), "P");
    EXPECT_FALSE(p.isZero());
    EXPECT_EQ(p.getMonomCount(), 3);
    EXPECT_EQ(p.toString(), "x^2+2x+1");
}

TEST(PolynomTest, ConstructorWithNameAndString) {
    Polynom p("MyPoly", "x^2 + 2x + 1");
    EXPECT_EQ(p.getName(), "MyPoly");
    EXPECT_FALSE(p.isZero());
    EXPECT_EQ(p.getMonomCount(), 3);
    EXPECT_EQ(p.toString(), "x^2+2x+1");
}

TEST(PolynomTest, ConstructorFromCString) {
    Polynom p("x^2 + 2x + 1");
    EXPECT_EQ(p.getName(), "P");
    EXPECT_FALSE(p.isZero());
}

TEST(PolynomTest, CopyConstructor) {
    Polynom p1("Poly1", "x^2 + 2x + 1");
    Polynom p2(p1);

    EXPECT_EQ(p2.getName(), "Poly1");
    EXPECT_EQ(p2.getMonomCount(), 3);
    EXPECT_EQ(p1.toString(), p2.toString());
}

TEST(PolynomTest, AssignmentOperator) {
    Polynom p1("Poly1", "x^2 + 2x + 1");
    Polynom p2;
    p2 = p1;

    EXPECT_EQ(p2.getName(), "Poly1");
    EXPECT_EQ(p2.getMonomCount(), 3);
    EXPECT_EQ(p1.toString(), p2.toString());
}

TEST(PolynomTest, NameGettersAndSetters) {
    Polynom p("x^2 + 2x + 1");
    EXPECT_EQ(p.getName(), "P");

    p.setName("NewName");
    EXPECT_EQ(p.getName(), "NewName");
}

TEST(PolynomTest, AddMonom) {
    Polynom p;
    EXPECT_TRUE(p.isZero());

    TVector<int> powers1(3);
    powers1[0] = 2;
    powers1[1] = 0;
    powers1[2] = 0;
    Monom m1(1.0, powers1); // x^2

    TVector<int> powers2(3);
    powers2[0] = 1;
    powers2[1] = 0;
    powers2[2] = 0;
    Monom m2(2.0, powers2); // 2x

    TVector<int> powers3(3);
    powers3[0] = 0;
    powers3[1] = 0;
    powers3[2] = 0;
    Monom m3(1.0, powers3); // 1

    p.addMonom(m1);
    EXPECT_EQ(p.getMonomCount(), 1);

    p.addMonom(m2);
    EXPECT_EQ(p.getMonomCount(), 2);

    p.addMonom(m3);
    EXPECT_EQ(p.getMonomCount(), 3);

    EXPECT_EQ(p.toString(), "x^2+2x+1");
}

// Тест для нормализации (объединения подобных мономов)
TEST(PolynomTest, NormalizeSimilarMonomials) {
    Polynom p("x^2 + 2x^2 + 3x^2");
    EXPECT_EQ(p.getMonomCount(), 1); // Должны объединиться в 6x^2

    string expected = "6x^2";
    EXPECT_EQ(p.toString(), expected);
}

TEST(PolynomTest, ZeroPolynomial) {
    Polynom p1;
    EXPECT_TRUE(p1.isZero());

    Polynom p2("0");
    EXPECT_TRUE(p2.isZero());

    Polynom p3("");
    EXPECT_TRUE(p3.isZero());
}

TEST(PolynomTest, AdditionOperator) {
    Polynom p1("P1", "x^2 + 2x");
    Polynom p2("P2", "x^2 - 2x");

    Polynom sum = p1 + p2;

    EXPECT_EQ(sum.getName(), "Result");
    EXPECT_EQ(sum.getMonomCount(), 1);
    EXPECT_EQ(sum.toString(), "2x^2");

    EXPECT_EQ(p1.getName(), "P1");
    EXPECT_EQ(p2.getName(), "P2");
}

TEST(PolynomTest, AdditionWithZero) {
    Polynom p1("P1", "x^2 + 2x");
    Polynom p2("P2", "0");

    Polynom sum = p1 + p2;

    EXPECT_EQ(sum.getName(), "Result");
    EXPECT_EQ(sum.getMonomCount(), 2);
    EXPECT_EQ(sum.toString(), "x^2+2x");
}

TEST(PolynomTest, SubtractionOperator) {
    Polynom p1("P1", "x^2 + 2x");
    Polynom p2("P2", "x^2");

    Polynom diff = p1 - p2;

    EXPECT_EQ(diff.getName(), "Result");
    EXPECT_EQ(diff.getMonomCount(), 1);
    EXPECT_EQ(diff.toString(), "2x");

    EXPECT_EQ(p1.getName(), "P1");
    EXPECT_EQ(p2.getName(), "P2");
}

TEST(PolynomTest, SubtractSelf) {
    Polynom p1("P1", "x^2 + 2x + 1");

    Polynom diff = p1 - p1;

    EXPECT_EQ(diff.getName(), "Result");
    EXPECT_TRUE(diff.isZero());
    EXPECT_EQ(diff.toString(), "0");
}

TEST(PolynomTest, MultiplicationOperator) {
    Polynom p1("P1", "x + 1");
    Polynom p2("P2", "x - 1");

    Polynom prod = p1 * p2;

    EXPECT_EQ(prod.getName(), "Result");
    EXPECT_EQ(prod.toString(), "x^2-1");
}

TEST(PolynomTest, MultiplicationByScalar) {
    Polynom p1("P1", "x^2 + 2x + 1");

    Polynom prod = p1 * 2.0;

    EXPECT_EQ(prod.getName(), "Result");
    EXPECT_EQ(prod.toString(), "2x^2+4x+2");
}

TEST(PolynomTest, ScalarMultiplicationLeft) {
    Polynom p1("P1", "x^2 + 2x + 1");

    Polynom prod = 3.0 * p1;

    EXPECT_EQ(prod.getName(), "Result");
    EXPECT_EQ(prod.toString(), "3x^2+6x+3");
}

TEST(PolynomTest, DivisionByScalar) {
    Polynom p1("P1", "2x^2 + 4x + 2");

    Polynom quot = p1 / 2.0;

    EXPECT_EQ(quot.getName(), "Result");
    EXPECT_EQ(quot.toString(), "x^2+2x+1");
}

TEST(PolynomTest, DivisionByZeroThrows) {
    Polynom p1("P1", "x^2 + 2x + 1");

    EXPECT_THROW(p1 / 0.0, invalid_argument);
}

TEST(PolynomTest, UnaryMinus) {
    Polynom p1("P1", "x^2 - 2x + 1");

    Polynom neg = -p1;

    EXPECT_EQ(neg.getName(), "Result");
    EXPECT_EQ(neg.toString(), "-x^2+2x-1");
}

TEST(PolynomTest, PlusEqualsOperator) {
    Polynom p1("P1", "x^2 + 2x");
    Polynom p2("P2", "x^2 - 2x");

    p1 += p2;

    // Имя должно остаться "P1"
    EXPECT_EQ(p1.getName(), "P1");
    EXPECT_EQ(p1.toString(), "2x^2");
}

TEST(PolynomTest, MinusEqualsOperator) {
    Polynom p1("P1", "x^2 + 2x");
    Polynom p2("P2", "x^2");

    p1 -= p2;

    EXPECT_EQ(p1.getName(), "P1");
    EXPECT_EQ(p1.toString(), "2x");
}

TEST(PolynomTest, TimesEqualsScalar) {
    Polynom p1("P1", "x^2 + 2x + 1");

    p1 *= 2.0;

    EXPECT_EQ(p1.getName(), "P1");
    EXPECT_EQ(p1.toString(), "2x^2+4x+2");
}

TEST(PolynomTest, DivideEqualsScalar) {
    Polynom p1("P1", "2x^2 + 4x + 2");

    p1 /= 2.0;

    EXPECT_EQ(p1.getName(), "P1");
    EXPECT_EQ(p1.toString(), "x^2+2x+1");
}

TEST(PolynomTest, EqualityOperator) {
    Polynom p1("P1", "x^2 + 2x + 1");
    Polynom p2("P2", "x^2 + 2x + 1");
    Polynom p3("P3", "x^2 + 2x");

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_TRUE(p1 != p3);
}

// Тесты для вычисления значения в точке
TEST(PolynomTest, EvaluateWithTVector) {
    Polynom p("P1", "x^2 + 2x + 1");

    TVector<double> point(3);
    point[0] = 2.0; // x = 2
    point[1] = 0.0; // y = 0
    point[2] = 0.0; // z = 0

    double result = p.evaluate(point);
    EXPECT_DOUBLE_EQ(result, 9.0);
}

TEST(PolynomTest, EvaluateWithXYZ) {
    if (VARIABLES_COUNT >= 3) {
        Polynom p("P1", "x^2 + 2y + 3z");

        double result = p.evaluate(2.0, 3.0, 1.0);
        EXPECT_DOUBLE_EQ(result, 13.0);
    }
}


TEST(PolynomTest, MonomialOrdering) {
    Polynom p("P1", "y^2z^3 + 2y^2 + xy + 6");

    auto it = p.begin();

    // Проверяем порядок: сначала xy, потом y^2z^3, потом 2y^2, потом 6
    EXPECT_EQ(it->getPower(0), 1);
    EXPECT_EQ(it->getPower(1), 1);
    EXPECT_EQ(it->getPower(2), 0);
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 1.0);

    ++it;
    EXPECT_EQ(it->getPower(0), 0);
    EXPECT_EQ(it->getPower(1), 2);
    EXPECT_EQ(it->getPower(2), 3);
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 1.0);

    ++it;
    EXPECT_EQ(it->getPower(0), 0);
    EXPECT_EQ(it->getPower(1), 2);
    EXPECT_EQ(it->getPower(2), 0);
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 2.0);

    ++it;
    EXPECT_EQ(it->getPower(0), 0);
    EXPECT_EQ(it->getPower(1), 0);
    EXPECT_EQ(it->getPower(2), 0);
    EXPECT_DOUBLE_EQ(it->getCoefficient(), 6.0);
}

TEST(PolynomTest, ComplexExpression) {
    Polynom p1("P1", "x^2 + y^2 + z^2");
    Polynom p2("P2", "xy + yz + zx");

    Polynom sum = p1 + p2;
    Polynom prod = p1 * p2;

    EXPECT_EQ(sum.getName(), "Result");


    string sumStr = sum.toString();

    EXPECT_NE(sumStr.find("x^2"), string::npos);
    EXPECT_NE(sumStr.find("y^2"), string::npos);
    EXPECT_NE(sumStr.find("z^2"), string::npos);
    EXPECT_NE(sumStr.find("xy"), string::npos);
    EXPECT_NE(sumStr.find("yz"), string::npos);

    bool hasZx = (sumStr.find("zx") != string::npos) || (sumStr.find("xz") != string::npos);
    EXPECT_TRUE(hasZx);
    int plusCount = 0;
    for (char c : sumStr) {
        if (c == '+') plusCount++;
    }
    EXPECT_EQ(plusCount + 1, 6);

    EXPECT_FALSE(prod.isZero());
}

// Тест для итераторов
TEST(PolynomTest, IteratorTest) {
    Polynom p("P1", "x^2 + 2x + 1");

    int count = 0;
    for (auto it = p.begin(); it != p.end(); ++it) {
        count++;
    }

    EXPECT_EQ(count, 3);
}

TEST(PolynomTest, OutputOperator) {
    Polynom p("MyPoly", "x^2 + 2x + 1");

    ostringstream oss;
    oss << p;

    string expected = "MyPoly = x^2+2x+1";
    EXPECT_EQ(oss.str(), expected);
}

TEST(PolynomTest, ChainedOperations) {
    Polynom p1("A", "x + 1");
    Polynom p2("B", "x - 1");
    Polynom p3("C", "x^2");

    Polynom sum = p1 + p2;
    Polynom result = sum * p3;

    EXPECT_EQ(sum.getName(), "Result");
    EXPECT_EQ(result.getName(), "Result");
    EXPECT_EQ(result.toString(), "2x^3");

    EXPECT_EQ(p1.getName(), "A");
    EXPECT_EQ(p2.getName(), "B");
    EXPECT_EQ(p3.getName(), "C");
}