#include "Matrix.hpp"

using namespace EngineJ::math::matrix;

// MatMN
MatMN::MatMN(int numRows, int numCols)
    : numRows{ numRows }, numCols{ numCols }, data{ new float[numRows * numCols] }
{}

MatMN::~MatMN() {
    free((float*)data);
}

MatMN::MatMN(const MatMN& mat) : MatMN{ mat.NumRows(), mat.NumCols() } {
    Fill(mat.data);
}

void MatMN::Fill(float* newData, int offset, int size) {
    size = std::min(size, numRows * numCols - offset);

    std::copy(newData, newData + size, data);
}

void MatMN::Fill(std::initializer_list<float> il) {
    Fill(const_cast<float*>(il.begin()), 0, il.size());
}

float& MatMN::Get(int row, int col) { return (*this)[row][col]; };
float& MatMN::Get(int row, int col) const { return (*this)[row][col]; };

float* MatMN::operator[](int row) {
    return &data[row * numCols];
}
float* MatMN::operator[](int row) const {
    return &data[row * numCols];
}

void MatMN::operator()(std::initializer_list<float> il) {
    Fill(il);
}

MatMN MatMN::operator*(MatMN& b) const {
    if (numCols != b.NumRows()) {
        throw std::logic_error("Dimensions invalid for matrix multiplication");
    }

    MatMN result{ numRows, b.NumCols() };

    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < b.NumRows(); j++) {
            float sum = 0;

            for (int k = 0; k < numCols; k++) {
                sum += Get(i, k) * b[k][j];
            }

            result[i][j] = sum;
        }
    }

    return result;
}

MatMN MatMN::Transpose() const {
    MatMN result{ numCols, numRows };

    for (int i = 0; i < numCols; i++) {
        for (int j = 0; j < numRows; j++) {
            float temp = Get(i, j);
            Get(i, j) = Get(j, i);
            Get(j, i) = temp;
        }
    }

    return result;
}

void MatMN::Log(std::string label) const {
    using namespace std;

    cout << label << ":\n[\n";

    for (int i = 0; i < numRows; i++) {
        cout << "   [ ";

        for (int j = 0; j < numCols; j++) {
            cout << Get(i, j) << " ";
        }

        cout << "]\n";
    }

    cout << "]\n\n";
}

int MatMN::NumRows() const { return numRows; }
int MatMN::NumCols() const { return numCols; }

// MatN
MatN::MatN(int order) : MatMN{ order, order }, order{ order } {}
MatN::MatN(MatMN& mat) : MatMN{ mat }, order{ mat.NumCols() } {}

int MatN::Order() { return order; }

MatN MatN::operator*(MatN b) {
    MatMN result = static_cast<MatMN>(*this) * static_cast<MatMN&>(b);
    return static_cast<MatN>(result);
}

// Mat2
Mat2::Mat2() : MatN{ 2 } {}
Mat2::Mat2(std::initializer_list<float> il) : Mat2{} { Fill(il); }
Mat2::Mat2(MatN& mat) : MatN{ mat } {}

Mat2 Mat2::operator*(Mat2 b) {
    MatN result = static_cast<MatN&>(*this) * static_cast<MatN&>(b);
    return static_cast<Mat2>(result);
}

// Mat3
Mat3::Mat3() : MatN{ 3 } {}
Mat3::Mat3(std::initializer_list<float> il) : Mat3{} { Fill(il); }
Mat3::Mat3(MatN& mat) : MatN{ mat } {}

Mat3 Mat3::operator*(Mat3 b) {
    MatN result = static_cast<MatN&>(*this) * static_cast<MatN&>(b);
    return static_cast<Mat3>(result);
}

// Mat4
Mat4::Mat4() : MatN{ 4 } {}
Mat4::Mat4(std::initializer_list<float> il) : Mat4{} { Fill(il); }
Mat4::Mat4(MatN& mat) : MatN{ mat } {}

Mat4 Mat4::operator*(Mat4 b) {
    MatN result = static_cast<MatN&>(*this) * static_cast<MatN&>(b);
    return static_cast<Mat4>(result);
}