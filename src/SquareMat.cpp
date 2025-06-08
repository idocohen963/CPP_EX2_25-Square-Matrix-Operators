/**
 * @file SquareMat.cpp
 * @brief Implementation of the SquareMat class
 * 
 * This file contains the implementation of the SquareMat class methods
 * declared in SquareMat.hpp.
 */

#include "../include/SquareMat.hpp"

namespace matrix_ops {

// Private helper methods

double SquareMat::sum() const {
    double result = 0.0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result += matrix[i][j];
        }
    }
    return result;
}

// Returns the remainder of a divided by b, always non-negative if b > 0
double SquareMat::modulo(double a, int b) const {
    int q = (int)(a / b);  // Truncate towards zero (not always like floor)
    if (a < 0 && a != b * q) {
        q -= 1;  // Correction if a is negative and not divisible by b
    }
    return a - b * q;
}

double SquareMat::determinantHelper(double** mat, int n) const {
    // Base cases
    if (n == 1) {
        return mat[0][0];
    }
    if (n == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }

    double det = 0.0;
    int sign = 1;
    
    // Allocate memory for minor matrix
    double** minor = new double*[n-1];
    for (int i = 0; i < n-1; ++i) {
        minor[i] = new double[n-1];
    }
    
    // Calculate determinant using cofactor expansion along first row
    for (int j = 0; j < n; ++j) {
        // Create minor matrix by excluding first row and current column
        for (int i = 1; i < n; ++i) {
            int col_index = 0;
            for (int j2 = 0; j2 < n; ++j2) {
                if (j2 == j) continue;
                minor[i-1][col_index++] = mat[i][j2];
            }
        }
        
        // Add cofactor to determinant
        det += sign * mat[0][j] * determinantHelper(minor, n-1);
        sign = -sign;
    }
    
    // Free memory
    for (int i = 0; i < n-1; ++i) {
        delete[] minor[i];
    }
    delete[] minor;
    
    return det;
}


// Constructors and destructor

SquareMat::SquareMat(int size) {
    if (size <= 0) {
        throw std::length_error("Matrix size must be positive");
    }
    
    this->size = size;
    matrix = new double*[size];
    
    for (int i = 0; i < size; ++i) {
        matrix[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

SquareMat::SquareMat(const SquareMat& other) : size(other.size) {
    matrix = new double*[size];
    
    for (int i = 0; i < size; ++i) {
        matrix[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

SquareMat::~SquareMat() {
    if (matrix != nullptr) {
        for (int i = 0; i < size; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

// Assignment operators

SquareMat& SquareMat::operator=(const SquareMat& other) {
    if (this == &other) {
        return *this;
    }
    
    // Clean up existing resources
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    
    // Copy from other
    size = other.size;
    matrix = new double*[size];
    
    for (int i = 0; i < size; ++i) {
        matrix[i] = new double[size];
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
    
    return *this;
}

// Static methods

SquareMat SquareMat::identity(int size) {
    if (size <= 0) {
        throw std::length_error("Matrix size must be positive");
    }
    
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        result.matrix[i][i] = 1.0;
    }
    
    return result;
}

// Access operators

SquareMat::RowProxy SquareMat::operator[](int row) {
    if (row < 0 || row >= size) {
        throw std::out_of_range("Row index out of range");
    }
    return RowProxy(matrix[row], size);
}

const SquareMat::RowProxy SquareMat::operator[](int row) const {
    if (row < 0 || row >= size) {
        throw std::out_of_range("Row index out of range");
    }
    return RowProxy(matrix[row], size);
}

// Arithmetic operators

SquareMat SquareMat::operator+(const SquareMat& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Matrix sizes do not match for addition");
    }
    
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
    }
    
    return result;
}

SquareMat SquareMat::operator-(const SquareMat& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Matrix sizes do not match for subtraction");
    }
    
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
        }
    }
    
    return result;
}

SquareMat SquareMat::operator-() const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.matrix[i][j] = -matrix[i][j];
        }
    }
    
    return result;
}

SquareMat SquareMat::operator*(const SquareMat& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Matrix sizes do not match for multiplication");
    }
    
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double sum = 0.0;
            for (int k = 0; k < size; ++k) {
                sum += matrix[i][k] * other.matrix[k][j];
            }
            result.matrix[i][j] = sum;
        }
    }
    
    return result;
}

SquareMat SquareMat::operator*(double scalar) const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    
    return result;
}

SquareMat operator*(double scalar, const SquareMat& mat) {
    return mat * scalar;
}

SquareMat SquareMat::operator%(const SquareMat& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Matrix sizes do not match for element-wise multiplication");
    }
    
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.matrix[i][j] = matrix[i][j] * other.matrix[i][j];
        }
    }
    
    return result;
}

SquareMat SquareMat::operator%(int scalar) const {
    if (scalar <= 0) {
        throw std::invalid_argument("Cannot perform modulo by zero or negative number");
    }
    
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.matrix[i][j] = modulo(matrix[i][j], scalar);
            
            }
        }
    return result;
}

SquareMat SquareMat::operator/(double scalar) const {
    if (scalar == 0.0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.matrix[i][j] = matrix[i][j] / scalar;
        }
    }
    
    return result;
}

SquareMat SquareMat::operator^(int power) const {
    if (power < 0) {
        throw std::invalid_argument("Negative powers are not supported (inverse not implemented)");
    }
    if (power == 0) {
        return identity(size);
    }
    if (power == 1) {
        return *this;
    }
    SquareMat result = *this;
    int p = power-1;
    while(p != 0){
        result *= *this;
        p--;
    }
    return result;
    
}

// Increment and decrement operators

SquareMat& SquareMat::operator++() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            ++matrix[i][j];
        }
    }
    return *this;
}

SquareMat SquareMat::operator++(int) {
    SquareMat temp = *this;
    ++(*this);
    return temp;
}

SquareMat& SquareMat::operator--() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            --matrix[i][j];
        }
    }
    return *this;
}

SquareMat SquareMat::operator--(int) {
    SquareMat temp = *this;
    --(*this);
    return temp;
}

// Matrix operations

SquareMat SquareMat::operator~() const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.matrix[i][j] = matrix[j][i];
        }
    }
    return result;
}

double SquareMat::operator!() const {
    return determinantHelper(matrix, size);
}

// Comparison operators

bool SquareMat::operator==(const SquareMat& other) const {
    return sum() == other.sum();
}

bool SquareMat::operator!=(const SquareMat& other) const {
    return sum() != other.sum();
}

bool SquareMat::operator<(const SquareMat& other) const {
    return sum() < other.sum();
}

bool SquareMat::operator>(const SquareMat& other) const {
    return sum() > other.sum();
}

bool SquareMat::operator<=(const SquareMat& other) const {
    return sum() <= other.sum();
}

bool SquareMat::operator>=(const SquareMat& other) const {
    return sum() >= other.sum();
}

// Compound assignment operators

SquareMat& SquareMat::operator+=(const SquareMat& other) {
    if (size != other.size) {
        throw std::invalid_argument("Matrix sizes do not match for +=");
    }
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] += other.matrix[i][j];
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator-=(const SquareMat& other) {
    if (size != other.size) {
        throw std::invalid_argument("Matrix sizes do not match for -=");
    }
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] -= other.matrix[i][j];
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator*=(const SquareMat& other) {
    if (size != other.size) {
        throw std::invalid_argument("Matrix sizes do not match for *=");
    }
    
    // Create temporary matrix to store result
    SquareMat temp = *this * other;
    
    // Copy result back to this matrix
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = temp.matrix[i][j];
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator*=(double scalar) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator%=(const SquareMat& other) {
    if (size != other.size) {
        throw std::invalid_argument("Matrix sizes do not match for %=");
    }
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] *= other.matrix[i][j];
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator%=(int scalar) {
    if (scalar <= 0) {
        throw std::invalid_argument("Cannot perform modulo by zero or negative number");
    }
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = modulo(matrix[i][j], scalar);
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator/=(double scalar) {
    if (scalar == 0.0) {
        throw std::invalid_argument("Cannot divide by zero");
    }
    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] /= scalar;
        }
    }
    
    return *this;
}

// Stream output operator

std::ostream& operator<<(std::ostream& os, const SquareMat& mat) {
    for (int i = 0; i < mat.size; ++i) {
        os << "| " <<" ";
        for (int j = 0; j < mat.size; ++j) {
            os << mat.matrix[i][j]<<" ";
        }
        os << " |" << std::endl;
    }
    return os;
}

} // namespace matrix_ops
