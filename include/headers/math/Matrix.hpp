#pragma once

#include "EngineJCoreLibs.hpp"

namespace EngineJ::math::matrix
{
    struct MatMN {
        MatMN(int numRows, int numCols);
        ~MatMN();

        MatMN(const MatMN& mat);

        void Fill(float* newData, int offset = 0, int size = INFINITY);
        void Fill(std::initializer_list<float> il);

        float& Get(int row, int col);
        float& Get(int row, int col) const;

        float* operator[](int row);
        float* operator[](int row) const;
        void operator()(std::initializer_list<float> il);
        MatMN operator*(MatMN& b) const;

        MatMN Transpose() const;

        void Log(std::string label = "Matrix") const;

        int NumRows() const;
        int NumCols() const;

    protected:
        int numRows;
        int numCols;
        float* data;
    };

    struct MatN : public MatMN {
        explicit MatN(int order);
        explicit MatN(MatMN& mat);

        int Order();

        MatN operator*(MatN b);

    protected:
        int order;
    };

    struct Mat2 : public MatN {
        Mat2();
        explicit Mat2(std::initializer_list<float> il);
        explicit Mat2(MatN& mat);

        Mat2 operator*(Mat2 b);
    };

    struct Mat3 : public MatN {
        Mat3();
        explicit Mat3(std::initializer_list<float> il);
        explicit Mat3(MatN& mat);

        Mat3 operator*(Mat3 b);
    };

    struct Mat4 : public MatN {
        Mat4();
        explicit Mat4(std::initializer_list<float> il);
        explicit Mat4(MatN& mat);

        Mat4 operator*(Mat4 b);
    };
}
