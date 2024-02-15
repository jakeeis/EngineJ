#include "Vector.hpp"

#include "EngineJCoreLibs.hpp"

using namespace EngineJ::math::matrix;

// VecN
VecN::VecN(int order) : MatMN{ order, 1 } {}
VecN::VecN(std::initializer_list<float> il) : MatMN{ (int)il.size(), 1 }
{

    Fill(il);
};

VecN::VecN(MatMN& mat) : MatMN{ mat } {}

float& VecN::Get(int index) {
    return (*this)[index];
}

float& VecN::Get(int index) const {
    return (*this)[index];
}

float VecN::Length() const {
    return sqrt(LengthSquared());
}

float VecN::LengthSquared() const {
    float sum = 0.0;

    for (int i = 0; i < Order(); i++) sum += Get(i);

    return sum;
}

int VecN::Order() const { return NumCols(); };

float& VecN::operator[](int index) { return MatMN::Get(index, 0); }
float& VecN::operator[](int index) const { return MatMN::Get(index, 0); }

// Vec2
Vec2::Vec2() : Vec2{ 0.0, 0.0 } {}
Vec2::Vec2(std::initializer_list<float> il) : VecN(il.size()) { Fill(il); }
Vec2::Vec2(MatMN& vec) : VecN{ vec } {}

float& Vec2::x() { return Get(0); };
float& Vec2::y() { return Get(1); };

float& Vec2::r() { return Get(0); };
float& Vec2::g() { return Get(1); };

// Vec3
Vec3::Vec3() : Vec3{ 0.0, 0.0, 0.0 } {}
Vec3::Vec3(std::initializer_list<float> il) : Vec2{ il } {}
Vec3::Vec3(MatMN& vec) : Vec2{ vec } {}

float& Vec3::z() { return Get(2); };

float& Vec3::b() { return Get(2); };

// Vec4
Vec4::Vec4() : Vec4{ 0.0, 0.0, 0.0, 0.0 } {}
Vec4::Vec4(std::initializer_list<float> il) : Vec3{ il } {}
Vec4::Vec4(MatMN& vec) : Vec3{ vec } {
    if (vec.NumRows() != 4 || vec.NumCols() != 1)
        throw std::logic_error("Cannot cast to ");
}

float& Vec4::w() { return Get(3); };

float& Vec4::a() { return Get(3); };