/**
 * @file SquareMat.hpp
 * @brief Header file for the SquareMat class, implementing square matrix operations
 * 
 * This file contains the declaration of the SquareMat class which implements
 * various operations on square matrices including arithmetic operations,
 * matrix-specific operations like transpose and determinant, and comparison operations.
 */

#pragma once

#include <iostream>
#include <stdexcept>
namespace matrix_ops {

/**
 * @class SquareMat
 * @brief A class representing a square matrix with various operations
 * 
 * This class implements a square matrix with dynamic memory allocation
 * and provides various operations such as addition, subtraction, multiplication,
 * determinant calculation, transpose, and more.
 */
class SquareMat {
private:
    /**
     * @class RowProxy
     * @brief A proxy class for safe row access with bounds checking
     * 
     * This inner class provides safe access to matrix rows with bounds checking
     * to prevent out-of-bounds access.
     */
    class RowProxy {
    private:
        double* row;
        int size;
    public:
        /**
         * @brief Construct a new Row Proxy object
         * 
         * @param row Pointer to the row data
         * @param size Size of the row
         */
        RowProxy(double* row, int size) : row(row), size(size) {}
        
        /**
         * @brief Access element at specified column index with bounds checking
         * 
         * @param col Column index
         * @return double& Reference to the element
         * @throw std::out_of_range if index is out of bounds
         */
        double& operator[](int col) {
            if (col < 0 || col >= size) {
                throw std::out_of_range("Column index out of range");
            }
            return row[col];
        }
        
        /**
         * @brief Access element at specified column index with bounds checking (const version)
         * 
         * @param col Column index
         * @return const double& Const reference to the element
         * @throw std::out_of_range if index is out of bounds
         */
        const double& operator[](int col) const {
            if (col < 0 || col >= size) {
                throw std::out_of_range("Column index out of range");
            }
            return row[col];
        }
    };

    double** matrix;  ///< 2D array to store matrix elements
    int size;         ///< Size of the square matrix (n x n)

    /**
     * @brief Calculate the sum of all elements in the matrix
     * 
     * @return double Sum of all elements
     */
    double sum() const;

    /**
    * @brief Returns the remainder of a divided by b, always non-negative if b > 0.
    * 
    * This function computes the mathematical modulo operation for doubles and integers,
    * ensuring the result is always non-negative
    * 
    * @param a The dividend (double)
    * @param b The divisor (int)
    * @return double The remainder of a divided by b
    */
    double modulo(double a, int b) const;

    /**
     * @brief Helper function for determinant calculation
     * 
     * @param mat Matrix for which to calculate determinant
     * @param n Size of the matrix
     * @return double Determinant value
     */
    double determinantHelper(double** mat, int n) const;


public:
    /**
     * @brief Construct a new Square Mat object initialized to zeros
     * 
     * @param size Size of the square matrix
     * @throw std::length_error if size is less than or equal to 0
     */
    explicit SquareMat(int size);

    /**
     * @brief Copy constructor
     * 
     * @param other Matrix to copy
     */
    SquareMat(const SquareMat& other);

    /**
     * @brief Destructor
     */
    ~SquareMat();

    /**
     * @brief Copy assignment operator
     * 
     * @param other Matrix to copy
     * @return SquareMat& Reference to this matrix
     */
    SquareMat& operator=(const SquareMat& other);

    /**
     * @brief Create an identity matrix of specified size
     * 
     * @param size Size of the identity matrix
     * @return SquareMat Identity matrix
     * @throw std::length_error if size is less than or equal to 0
     */
    static SquareMat identity(int size);

    /**
     * @brief Get the size of the matrix
     * 
     * @return int Size of the matrix
     */
    int getSize() const { return size; }

    /**
     * @brief Access row at specified index with bounds checking
     * 
     * @param row Row index
     * @return RowProxy Proxy object for the row
     * @throw std::out_of_range if index is out of bounds
     */
    RowProxy operator[](int row);

    /**
     * @brief Access row at specified index with bounds checking (const version)
     * 
     * @param row Row index
     * @return const RowProxy Const proxy object for the row
     * @throw std::out_of_range if index is out of bounds
     */
    const RowProxy operator[](int row) const;

    /**
     * @brief Add two matrices
     * 
     * @param other Matrix to add
     * @return SquareMat Result of addition
     * @throw std::invalid_argument if matrices have different sizes
     */
    SquareMat operator+(const SquareMat& other) const;

    /**
     * @brief Subtract two matrices
     * 
     * @param other Matrix to subtract
     * @return SquareMat Result of subtraction
     * @throw std::invalid_argument if matrices have different sizes
     */
    SquareMat operator-(const SquareMat& other) const;

    /**
     * @brief Negate all elements of the matrix
     * 
     * @return SquareMat Negated matrix
     */
    SquareMat operator-() const;

    /**
     * @brief Multiply two matrices
     * 
     * @param other Matrix to multiply with
     * @return SquareMat Result of multiplication
     * @throw std::invalid_argument if matrices have different sizes
     */
    SquareMat operator*(const SquareMat& other) const;

    /**
     * @brief Multiply matrix by scalar
     * 
     * @param scalar Scalar value
     * @return SquareMat Result of multiplication
     */
    SquareMat operator*(double scalar) const;

    /**
     * @brief Multiplies each element in one matrix by the 
     *        corresponding element in the second matrix.
     * 
     * @param other Matrix for element-wise multiplication
     * @return SquareMat Result of element-wise multiplication
     * @throw std::invalid_argument if matrices have different sizes
     */
    SquareMat operator%(const SquareMat& other) const;

    /**
     * @brief Apply modulo operation with scalar to each element
     * 
     * @param scalar Scalar for modulo operation
     * @return SquareMat Result of modulo operation
     * @throw std::invalid_argument if scalar is 0
     */
    SquareMat operator%(int scalar) const;

    /**
     * @brief Divide matrix by scalar
     * 
     * @param scalar Scalar divisor
     * @return SquareMat Result of division
     * @throw std::invalid_argument if scalar is 0 or negative 
     */
    SquareMat operator/(double scalar) const;

    /**
     * @brief Raise matrix to a non-negative integer power
     * 
     * @param power Power to raise to (must be >= 0)
     * @return SquareMat Result of power operation
     * @throw std::invalid_argument if power is negative
     */
    SquareMat operator^(int power) const;

    /**
     * @brief Pre-increment operator (add 1 to all elements)
     * 
     * @return SquareMat& Reference to this matrix
     */
    SquareMat& operator++();

    /**
     * @brief Post-increment operator (add 1 to all elements)
     * 
     * @return SquareMat Copy of matrix before increment
     */
    SquareMat operator++(int);

    /**
     * @brief Pre-decrement operator (subtract 1 from all elements)
     * 
     * @return SquareMat& Reference to this matrix
     */
    SquareMat& operator--();

    /**
     * @brief Post-decrement operator (subtract 1 from all elements)
     * 
     * @return SquareMat Copy of matrix before decrement
     */
    SquareMat operator--(int);

    /**
     * @brief Transpose the matrix
     * 
     * @return SquareMat Transposed matrix
     */
    SquareMat operator~() const;

    /**
     * @brief Calculate determinant of the matrix
     * 
     * @return double Determinant value
     */
    double operator!() const;

    /**
     * @brief Check if two matrices have equal sum of elements
     * 
     * @param other Matrix to compare with
     * @return bool True if sums are equal
     */
    bool operator==(const SquareMat& other) const;

    /**
     * @brief Check if two matrices have different sum of elements
     * 
     * @param other Matrix to compare with
     * @return bool True if sums are different
     */
    bool operator!=(const SquareMat& other) const;

    /**
     * @brief Check if sum of elements is less than other matrix
     * 
     * @param other Matrix to compare with
     * @return bool True if sum is less
     */
    bool operator<(const SquareMat& other) const;

    /**
     * @brief Check if sum of elements is greater than other matrix
     * 
     * @param other Matrix to compare with
     * @return bool True if sum is greater
     */
    bool operator>(const SquareMat& other) const;

    /**
     * @brief Check if sum of elements is less than or equal to other matrix
     * 
     * @param other Matrix to compare with
     * @return bool True if sum is less or equal
     */
    bool operator<=(const SquareMat& other) const;

    /**
     * @brief Check if sum of elements is greater than or equal to other matrix
     * 
     * @param other Matrix to compare with
     * @return bool True if sum is greater or equal
     */
    bool operator>=(const SquareMat& other) const;

    /**
     * @brief Add and assign another matrix
     * 
     * @param other Matrix to add
     * @return SquareMat& Reference to this matrix
     * @throw std::invalid_argument if matrices have different sizes
     */
    SquareMat& operator+=(const SquareMat& other);

    /**
     * @brief Subtract and assign another matrix
     * 
     * @param other Matrix to subtract
     * @return SquareMat& Reference to this matrix
     * @throw std::invalid_argument if matrices have different sizes
     */
    SquareMat& operator-=(const SquareMat& other);

    /**
     * @brief Multiply and assign with another matrix
     * 
     * @param other Matrix to multiply with
     * @return SquareMat& Reference to this matrix
     * @throw std::invalid_argument if matrices have different sizes
     */
    SquareMat& operator*=(const SquareMat& other);

    /**
     * @brief Multiply and assign with scalar
     * 
     * @param scalar Scalar value
     * @return SquareMat& Reference to this matrix
     */
    SquareMat& operator*=(double scalar);

    /**
     * @brief Element-wise multiply and assign with another matrix
     * 
     * @param other Matrix for element-wise multiplication
     * @return SquareMat& Reference to this matrix
     * @throw std::invalid_argument if matrices have different sizes
     */
    SquareMat& operator%=(const SquareMat& other);

    /**
     * @brief Apply modulo operation with scalar and assign
     * 
     * @param scalar Scalar for modulo operation
     * @return SquareMat& Reference to this matrix
     * @throw std::invalid_argument if scalar is 0
     */
    SquareMat& operator%=(int scalar);

    /**
     * @brief Divide by scalar and assign
     * 
     * @param scalar Scalar divisor
     * @return SquareMat& Reference to this matrix
     * @throw std::invalid_argument if scalar is 0
     */
    SquareMat& operator/=(double scalar);

    /**
     * @brief Friend function for scalar * matrix multiplication
     * 
     * @param scalar Scalar value
     * @param mat Matrix to multiply
     * @return SquareMat Result of multiplication
     */
    friend SquareMat operator*(double scalar, const SquareMat& mat);

    /**
     * @brief Friend function for matrix output
     * 
     * @param os Output stream
     * @param mat Matrix to output
     * @return std::ostream& Reference to output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);
};

} // namespace matrix_ops
