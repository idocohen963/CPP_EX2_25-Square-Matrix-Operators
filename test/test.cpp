// idocohen963@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/SquareMat.hpp"
#include "doctest.h"
#include <iostream>
#include <cmath>

using namespace matrix_ops;
using namespace doctest;

TEST_CASE("operator[]") {
    SUBCASE("const matrix") {
        const SquareMat m(2);
        CHECK(m[0][0] == 0.0);
        CHECK_THROWS_AS(m[2][0], std::out_of_range);
    }

    SUBCASE("non-const matrix") {
        SquareMat m(2);
        CHECK(m[0][0] == 0.0);
        CHECK_THROWS_AS(m[2][2], std::out_of_range);
    }
}

TEST_CASE("Constructor and basic operations") {
    SUBCASE("Default constructor initializes to zeros") {
        SquareMat m(3);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                CHECK(m[i][j] == 0.0);
            }
        }
    }
    
    SUBCASE("Invalid size throws exception") {
        CHECK_THROWS_AS(SquareMat(0), std::length_error);
        CHECK_THROWS_AS(SquareMat(-1), std::length_error);
    }
    
    SUBCASE("Copy constructor creates deep copy") {
        SquareMat m1(2);
        m1[0][0] = 1.0;
        m1[0][1] = 2.0;
        m1[1][0] = 3.0;
        m1[1][1] = 4.0;
        
        SquareMat m2(m1);
        CHECK(m2[0][0] == 1.0);
        CHECK(m2[0][1] == 2.0);
        CHECK(m2[1][0] == 3.0);
        CHECK(m2[1][1] == 4.0);
        
        // Modify m1 and check that m2 is unchanged
        m1[0][0] = 5.0;
        CHECK(m2[0][0] == 1.0);
    }
    
}

TEST_CASE("Assignment operators") {
    SUBCASE("Copy assignment creates deep copy") {
        SquareMat m1(2);
        m1[0][0] = 1.0;
        m1[0][1] = 2.0;
        m1[1][0] = 3.0;
        m1[1][1] = 4.0;
        
        SquareMat m2(3); // Different size

        CHECK(m2[2][2] == 0);
        m2 = m1;
        
        CHECK(m2[0][0] == 1.0);
        CHECK(m2[0][1] == 2.0);
        CHECK(m2[1][0] == 3.0);
        CHECK(m2[1][1] == 4.0);
        
        // Modify m1 and check that m2 is unchanged
        m1[0][0] = 5.0;
        CHECK(m2[0][0] == 1.0);
    }
    
    SUBCASE("Self-assignment works correctly") {
        SquareMat m(2);
        m[0][0] = 1.0;
        m[0][1] = 2.0;
        m[1][0] = 3.0;
        m[1][1] = 4.0;
        
        m = m;
        
        CHECK(m[0][0] == 1.0);
        CHECK(m[0][1] == 2.0);
        CHECK(m[1][0] == 3.0);
        CHECK(m[1][1] == 4.0);
    }
    
}

TEST_CASE("Static methods") {
    SUBCASE("Identity matrix creation") {
        SquareMat id = SquareMat::identity(3);
        
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == j) {
                    CHECK(id[i][j] == 1.0);
                } else {
                    CHECK(id[i][j] == 0.0);
                }
            }
        }
    }
    
    SUBCASE("Invalid size for identity throws exception") {
        CHECK_THROWS_AS(SquareMat::identity(0), std::length_error);
        CHECK_THROWS_AS(SquareMat::identity(-1), std::length_error);
    }
}

TEST_CASE("Access operators") {
    SquareMat m(3);
    
    SUBCASE("Valid access works") {
        m[0][0] = 1.0;
        m[1][2] = 2.0;
        
        CHECK(m[0][0] == 1.0);
        CHECK(m[1][2] == 2.0);
    }
    
    SUBCASE("Out of bounds access throws exception") {
        CHECK_THROWS_AS(m[-1][0], std::out_of_range);
        CHECK_THROWS_AS(m[3][0], std::out_of_range);
        CHECK_THROWS_AS(m[0][-1], std::out_of_range);
        CHECK_THROWS_AS(m[0][3], std::out_of_range);
    }
}

TEST_CASE("Arithmetic operators") {
    SquareMat m1(2);
    m1[0][0] = 1.0;
    m1[0][1] = 2.0;
    m1[1][0] = 3.0;
    m1[1][1] = 4.0;
    
    SquareMat m2(2);
    m2[0][0] = 5.0;
    m2[0][1] = 6.0;
    m2[1][0] = 7.0;
    m2[1][1] = 8.0;
    
    SUBCASE("Addition") {
        SquareMat result = m1 + m2;
        
        CHECK(result[0][0] == 6.0);
        CHECK(result[0][1] == 8.0);
        CHECK(result[1][0] == 10.0);
        CHECK(result[1][1] == 12.0);
    }
    
    SUBCASE("Addition with different sizes throws exception") {
        SquareMat m3(3);
        CHECK_THROWS_AS(m1 + m3, std::invalid_argument);
    }
    
    SUBCASE("Subtraction") {
        SquareMat result = m2 - m1;
        
        CHECK(result[0][0] == 4.0);
        CHECK(result[0][1] == 4.0);
        CHECK(result[1][0] == 4.0);
        CHECK(result[1][1] == 4.0);
    }
    
    SUBCASE("Subtraction with different sizes throws exception") {
        SquareMat m3(3);
        CHECK_THROWS_AS(m1 - m3, std::invalid_argument);
    }
    
    SUBCASE("Unary minus") {
        SquareMat result = -m1;
        
        CHECK(result[0][0] == -1.0);
        CHECK(result[0][1] == -2.0);
        CHECK(result[1][0] == -3.0);
        CHECK(result[1][1] == -4.0);
    }
    
    SUBCASE("Matrix multiplication") {
        SquareMat result = m1 * m2;
        
        CHECK(result[0][0] == 19.0);
        CHECK(result[0][1] == 22.0);
        CHECK(result[1][0] == 43.0);
        CHECK(result[1][1] == 50.0);
    }
    
    SUBCASE("Matrix multiplication with different sizes throws exception") {
        SquareMat m3(3);
        CHECK_THROWS_AS(m1 * m3, std::invalid_argument);
    }
    
    SUBCASE("Scalar multiplication (matrix * scalar)") {
        SquareMat result = m1 * 2.0;
        
        CHECK(result[0][0] == 2.0);
        CHECK(result[0][1] == 4.0);
        CHECK(result[1][0] == 6.0);
        CHECK(result[1][1] == 8.0);
    }
    
    SUBCASE("Scalar multiplication (scalar * matrix)") {
        SquareMat result = 2.0 * m1;
        
        CHECK(result[0][0] == 2.0);
        CHECK(result[0][1] == 4.0);
        CHECK(result[1][0] == 6.0);
        CHECK(result[1][1] == 8.0);
    }
    
    SUBCASE("Element-wise multiplication") {
        SquareMat result = m1 % m2;
        
        CHECK(result[0][0] == 5.0);
        CHECK(result[0][1] == 12.0);
        CHECK(result[1][0] == 21.0);
        CHECK(result[1][1] == 32.0);
    }
    
    SUBCASE("Element-wise multiplication with different sizes throws exception") {
        SquareMat m3(3);
        CHECK_THROWS_AS(m1 % m3, std::invalid_argument);
    }
    
    SUBCASE("Modulo with scalar") {
        SquareMat m(2);
        m[0][0] = 5.5;
        m[0][1] = -2.5;
        m[1][0] = 10.5;
        m[1][1] = -7.5;
        
        SquareMat result = m % 3;
        
        CHECK(result[0][0] == Approx(2.5)); // Approx is a helper from doctest for comparing floating-point values with tolerance (not exact equality).
        CHECK(result[0][1] == Approx(0.5));
        CHECK(result[1][0] == Approx(1.5));
        CHECK(result[1][1] == Approx(1.5));
    }
    
    SUBCASE("Modulo by zero/negative throws exception") {
        CHECK_THROWS_AS(m1 % 0, std::invalid_argument);
        CHECK_THROWS_AS(m1 %= -2, std::invalid_argument);
    }
    
    SUBCASE("Division by scalar") {
        SquareMat result = m1 / 2.0;
        
        CHECK(result[0][0] == 0.5);
        CHECK(result[0][1] == 1.0);
        CHECK(result[1][0] == 1.5);
        CHECK(result[1][1] == 2.0);
    }
    
    SUBCASE("Division by zero throws exception") {
        CHECK_THROWS_AS(m1 / 0.0, std::invalid_argument);
    }
}

TEST_CASE("Power operator") {
    SUBCASE("Power 0 returns identity") {
        SquareMat m(2);
        m[0][0] = 1.0;
        m[0][1] = 2.0;
        m[1][0] = 3.0;
        m[1][1] = 4.0;
        
        SquareMat result = m ^ 0;
        
        CHECK(result[0][0] == 1.0);
        CHECK(result[0][1] == 0.0);
        CHECK(result[1][0] == 0.0);
        CHECK(result[1][1] == 1.0);
    }
    
    SUBCASE("Power 1 returns the same matrix") {
        SquareMat m(2);
        m[0][0] = 1.0;
        m[0][1] = 2.0;
        m[1][0] = 3.0;
        m[1][1] = 4.0;
        
        SquareMat result = m ^ 1;
        
        CHECK(result[0][0] == 1.0);
        CHECK(result[0][1] == 2.0);
        CHECK(result[1][0] == 3.0);
        CHECK(result[1][1] == 4.0);
    }
    
    SUBCASE("Power 2 works correctly") {
        SquareMat m(2);
        m[0][0] = 1.0;
        m[0][1] = 2.0;
        m[1][0] = 3.0;
        m[1][1] = 4.0;
        
        SquareMat result = m ^ 2;
        
        CHECK(result[0][0] == 7.0);
        CHECK(result[0][1] == 10.0);
        CHECK(result[1][0] == 15.0);
        CHECK(result[1][1] == 22.0);
    }
}

TEST_CASE("Increment and decrement operators") {
    SquareMat m(2);
    m[0][0] = 1.0;
    m[0][1] = 2.0;
    m[1][0] = 3.0;
    m[1][1] = 4.0;
    
    SUBCASE("Pre-increment") {
        SquareMat& result = ++m;
        
        CHECK(&result == &m); // Should return reference to same object
        CHECK(m[0][0] == 2.0);
        CHECK(m[0][1] == 3.0);
        CHECK(m[1][0] == 4.0);
        CHECK(m[1][1] == 5.0);
    }
    
    SUBCASE("Post-increment") {
        SquareMat result = m++;
        
        CHECK(result[0][0] == 1.0);
        CHECK(result[0][1] == 2.0);
        CHECK(result[1][0] == 3.0);
        CHECK(result[1][1] == 4.0);
        
        CHECK(m[0][0] == 2.0);
        CHECK(m[0][1] == 3.0);
        CHECK(m[1][0] == 4.0);
        CHECK(m[1][1] == 5.0);
    }
    
    SUBCASE("Pre-decrement") {
        SquareMat& result = --m;
        
        CHECK(&result == &m); // Should return reference to same object
        CHECK(m[0][0] == 0.0);
        CHECK(m[0][1] == 1.0);
        CHECK(m[1][0] == 2.0);
        CHECK(m[1][1] == 3.0);
    }
    
    SUBCASE("Post-decrement") {
        SquareMat result = m--;
        
        CHECK(result[0][0] == 1.0);
        CHECK(result[0][1] == 2.0);
        CHECK(result[1][0] == 3.0);
        CHECK(result[1][1] == 4.0);
        
        CHECK(m[0][0] == 0.0);
        CHECK(m[0][1] == 1.0);
        CHECK(m[1][0] == 2.0);
        CHECK(m[1][1] == 3.0);
    }
}

TEST_CASE("Matrix operations") {
    SUBCASE("Transpose") {
        SquareMat m(2);
        m[0][0] = 1.0;
        m[0][1] = 2.0;
        m[1][0] = 3.0;
        m[1][1] = 4.0;
        
        SquareMat result = ~m;
        
        CHECK(result[0][0] == 1.0);
        CHECK(result[0][1] == 3.0);
        CHECK(result[1][0] == 2.0);
        CHECK(result[1][1] == 4.0);
    }
    
    SUBCASE("Determinant") {
        SquareMat m1(1);
        m1[0][0] = 5.0;
        CHECK(!m1 == 5.0);
        
        SquareMat m2(2);
        m2[0][0] = 1.0;
        m2[0][1] = 2.0;
        m2[1][0] = 3.0;
        m2[1][1] = 4.0;
        CHECK(!m2 == -2.0);
        
        SquareMat m3(3);
        m3[0][0] = 1.0;
        m3[0][1] = 2.0;
        m3[0][2] = 3.0;
        m3[1][0] = 4.0;
        m3[1][1] = 5.0;
        m3[1][2] = 6.0;
        m3[2][0] = 7.0;
        m3[2][1] = 8.0;
        m3[2][2] = 9.0;
        CHECK(!m3 == Approx(0.0));
    }
    SUBCASE("Determinant for special matrices") {
        // Identity matrix
        SquareMat id = SquareMat::identity(3);
        CHECK(!id == 1.0);

        // Matrix with identical rows (determinant should be 0)
        SquareMat m(2);
        m[0][0] = 1.0;
        m[0][1] = 2.0;
        m[1][0] = 1.0;
        m[1][1] = 2.0;
        CHECK(!m == Approx(0.0));

        // Matrix with a row of zeros (determinant should be 0)
        SquareMat m2(2);
        m2[0][0] = 0.0;
        m2[0][1] = 0.0;
        m2[1][0] = 3.0;
        m2[1][1] = 4.0;
        CHECK(!m2 == Approx(0.0));
    }
}

TEST_CASE("Comparison operators") {
    SquareMat m1(2);
    m1[0][0] = 1.0;
    m1[0][1] = 2.0;
    m1[1][0] = 3.0;
    m1[1][1] = 4.0;
    // Sum = 10.0
    
    SquareMat m2(2);
    m2[0][0] = 2.0;
    m2[0][1] = 3.0;
    m2[1][0] = 4.0;
    m2[1][1] = 5.0;
    // Sum = 14.0
    
    SquareMat m3(2);
    m3[0][0] = 4.0;
    m3[0][1] = 3.0;
    m3[1][0] = 2.0;
    m3[1][1] = 1.0;
    // Sum = 10.0
    
    SUBCASE("Equality") {
        CHECK(m1 == m3);
        CHECK(!(m1 == m2));
    }
    
    SUBCASE("Inequality") {
        CHECK(m1 != m2);
        CHECK(!(m1 != m3));
    }
    
    SUBCASE("Less than") {
        CHECK(m1 < m2);
        CHECK(!(m2 < m1));
        CHECK(!(m1 < m3));
    }
    
    SUBCASE("Greater than") {
        CHECK(m2 > m1);
        CHECK(!(m1 > m2));
        CHECK(!(m1 > m3));
    }
    
    SUBCASE("Less than or equal") {
        CHECK(m1 <= m2);
        CHECK(m1 <= m3);
        CHECK(!(m2 <= m1));
    }
    
    SUBCASE("Greater than or equal") {
        CHECK(m2 >= m1);
        CHECK(m1 >= m3);
        CHECK(!(m1 >= m2));
    }
}

TEST_CASE("Compound assignment operators") {
    SquareMat m1(2);
    m1[0][0] = 1.0;
    m1[0][1] = 2.0;
    m1[1][0] = 3.0;
    m1[1][1] = 4.0;
    
    SquareMat m2(2);
    m2[0][0] = 5.0;
    m2[0][1] = 6.0;
    m2[1][0] = 7.0;
    m2[1][1] = 8.0;
    
    SUBCASE("Addition assignment") {
        SquareMat m = m1;
        m += m2;
        
        CHECK(m[0][0] == 6.0);
        CHECK(m[0][1] == 8.0);
        CHECK(m[1][0] == 10.0);
        CHECK(m[1][1] == 12.0);
    }
    
    SUBCASE("Addition assignment with different sizes throws exception") {
        SquareMat m = m1;
        SquareMat m3(3);
        CHECK_THROWS_AS(m += m3, std::invalid_argument);
    }
    
    SUBCASE("Subtraction assignment") {
        SquareMat m = m2;
        m -= m1;
        
        CHECK(m[0][0] == 4.0);
        CHECK(m[0][1] == 4.0);
        CHECK(m[1][0] == 4.0);
        CHECK(m[1][1] == 4.0);
    }
    
    SUBCASE("Subtraction assignment with different sizes throws exception") {
        SquareMat m = m1;
        SquareMat m3(3);
        CHECK_THROWS_AS(m -= m3, std::invalid_argument);
    }
    
    SUBCASE("Multiplication assignment") {
        SquareMat m = m1;
        m *= m2;
        
        CHECK(m[0][0] == 19.0);
        CHECK(m[0][1] == 22.0);
        CHECK(m[1][0] == 43.0);
        CHECK(m[1][1] == 50.0);
    }
    
    SUBCASE("Multiplication assignment with different sizes throws exception") {
        SquareMat m = m1;
        SquareMat m3(3);
        CHECK_THROWS_AS(m *= m3, std::invalid_argument);
    }
    
    SUBCASE("Scalar multiplication assignment") {
        SquareMat m = m1;
        m *= 2.0;
        
        CHECK(m[0][0] == 2.0);
        CHECK(m[0][1] == 4.0);
        CHECK(m[1][0] == 6.0);
        CHECK(m[1][1] == 8.0);
    }
    
    SUBCASE("Element-wise multiplication assignment") {
        SquareMat m = m1;
        m %= m2;
        
        CHECK(m[0][0] == 5.0);
        CHECK(m[0][1] == 12.0);
        CHECK(m[1][0] == 21.0);
        CHECK(m[1][1] == 32.0);
    }
}