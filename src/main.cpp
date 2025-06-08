// idocohen963@gmail.com
#include <iostream>
#include "../include/SquareMat.hpp"

using namespace matrix_ops;
using namespace std;

int main() {
    cout << "SquareMat Demo" << endl;
    cout << "======================" << endl << endl;
    
    // Create a 3x3 matrix
    cout << "Creating a 3x3 matrix m1:" << endl;
    SquareMat m1(3);
    m1[0][0] = 1; m1[0][1] = 2; m1[0][2] = 3;
    m1[1][0] = 4; m1[1][1] = 5; m1[1][2] = 6;
    m1[2][0] = 7; m1[2][1] = 8; m1[2][2] = 9;
    cout << m1 << endl;
    
    // Create another 3x3 matrix
    cout << "Creating another 3x3 matrix m2:" << endl;
    SquareMat m2(3);
    m2[0][0] = 9; m2[0][1] = 8; m2[0][2] = 7;
    m2[1][0] = 6; m2[1][1] = 5; m2[1][2] = 4;
    m2[2][0] = 3; m2[2][1] = 2; m2[2][2] = 1;
    cout << m2 << endl;
    
    // Addition
    cout << "Matrix addition (m1 + m2):" << endl;
    cout << m1 + m2 << endl;
    
    // Subtraction
    cout << "Matrix subtraction (m1 - m2):" << endl;
    cout << m1 - m2 << endl;
    
    // Multiplication
    cout << "Matrix multiplication (m1 * m2):" << endl;
    cout << m1 * m2 << endl;
    
    // Element-wise multiplication
    cout << "Element-wise multiplication (m1 % m2):" << endl;
    cout << m1 % m2 << endl;
    
    // Scalar multiplication
    cout << "Scalar multiplication (m1 * 2):" << endl;
    cout << m1 * 2 << endl;
    
    // Scalar division
    cout << "Scalar division (m1 / 2):" << endl;
    cout << m1 / 2 << endl;
    
    // Transpose
    cout << "Transpose of m1 (~m1):" << endl;
    cout << ~m1 << endl;
    
    // Determinant
    cout << "Determinant of m1 (!m1): " << !m1 << endl << endl;
    
    // Create an invertible matrix
    cout << "Creating an invertible matrix m3:" << endl;
    SquareMat m3(3);
    m3[0][0] = 1; m3[0][1] = 2; m3[0][2] = 3;
    m3[1][0] = 0; m3[1][1] = 1; m3[1][2] = 4;
    m3[2][0] = 5; m3[2][1] = 6; m3[2][2] = 0;
    cout << m3 << endl;
    
    // Determinant
    cout << "Determinant of m3 (!m3): " << !m3 << endl << endl;
    
    // Power
    cout << "m3 raised to power 2 (m3^2):" << endl;
    cout << (m3 ^ 2) << endl;
    
    // Identity matrix
    cout << "3x3 Identity matrix:" << endl;
    cout << SquareMat::identity(3) << endl;
    
    // Comparison operators
    cout << "Comparison of m1 and m2:" << endl << endl;
    cout << "m1 == m2: " << (m1 == m2 ? "true" : "false") << endl;
    cout << "m1 != m2: " << (m1 != m2 ? "true" : "false") << endl;
    cout << "m1 < m2: " << (m1 < m2 ? "true" : "false") << endl;
    cout << "m1 > m2: " << (m1 > m2 ? "true" : "false") << endl;
   
    cout << "m1:" << endl << endl;
    cout << m1 << endl;
    // ++m1 (pre-increment)
    cout << "Pre-increment (++m1):" << endl;
    ++m1;
    cout << m1 << endl;

    // m1++ (post-increment)
    cout << "Post-increment (m1++):" << endl;
    cout << m1++ << endl;
    cout << "After post-increment, m1:" << endl;
    cout << m1 << endl;

    // --m1 (pre-decrement)
    cout << "Pre-decrement (--m1):" << endl;
    --m1;
    cout << m1 << endl;

    // m1-- (post-decrement)
    cout << "Post-decrement (m1--):" << endl;
    cout << m1-- << endl;
    cout << "After post-decrement, m1:" << endl;
    cout << m1 << endl;

    // Compound assignment operators
    cout << "Compound assignment (m1 += m2):" << endl;
    m1 += m2;
    cout << m1 << endl;

    cout << "Compound assignment (m1 *= 2):" << endl;
    m1 *= 2;
    cout << m1 << endl;

    cout << "Compound assignment (m1 %= 3):" << endl;
    m1 %= 3;
    cout << m1 << endl;

    cout << "Compound assignment (m1 /= 2):" << endl;
    m1 /= 2;
    cout << m1 << endl;

    // Modulo operation
    cout << "Modulo operation (m1 % 3):" << endl;
    cout << (m1 % 3) << endl;

    // Access and modify a single element
    cout << "Accessing m1[0][1]: " << m1[0][1] << endl << endl;
    m1[0][1] = 42;
    cout << "After setting m1[0][1] = 42:" << endl;
    cout << m1 << endl;
    
    cout << "\nDemo completed successfully!" << endl;
    return 0;
}
