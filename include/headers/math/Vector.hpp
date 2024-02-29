#pragma once

#include "Matrix.hpp"

namespace EngineJ::math::matrix {
    struct VecN : public MatMN {
        explicit VecN(int order = 2);
        explicit VecN(std::initializer_list<float> il);
        explicit VecN(MatMN& mat);
        explicit VecN(MatMN&& mat);

        float& Get(int index);
        float& Get(int index) const;

        float Length() const;
        float LengthSquared() const;

        int Order() const;

        float& operator[](int index);
        float& operator[](int index) const;
    };

    struct Vec2 : public VecN {
        Vec2();
        explicit Vec2(std::initializer_list<float> il);
        explicit Vec2(MatMN& vec);
        explicit Vec2(MatMN&& vec);

        float& x();
        float& y();

        float& r();
        float& g();
    };

    struct Vec3 : public Vec2 {
        Vec3();
        explicit Vec3(std::initializer_list<float> il);
        explicit Vec3(MatMN& vec);
        explicit Vec3(MatMN&& vec);

        float& z();

        float& b();
    };

    struct Vec4 : public Vec3 {
        Vec4();
        explicit Vec4(std::initializer_list<float> il);
        explicit Vec4(MatMN& vec);
        explicit Vec4(MatMN&& vec);

        float& w();

        float& a();
    };
}