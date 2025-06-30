#pragma once
#include <iostream>
#include <cmath>

class vector3
{
    float x_, y_, z_;

    float length_ = x_ * x_ + y_ * y_ + z_ * z_;
    float magnitude_ = std::sqrt(length_);

public:
    explicit vector3(const float x = 0.0, const float y = 0.0, const float z = 0.0) : x_(x), y_(y), z_(z)
    {
    }
    float get_length() const
    {
        return length_;
	}
    // Getter methods for the coordinates
    float get_x() const;
    float get_y() const;
    float get_z() const;

    float magnitude() const;
    // Setter methods for the coordinates
    void set_x(float new_x);
    void set_y(float new_y);
    void set_z(float new_z);

    // Operators
    vector3 operator+(const vector3& other) const;
    void operator+=(const vector3& other);
    vector3 operator -(const vector3& other) const;
    void operator-=(const vector3& other);
    vector3 operator*(float s) const;
    vector3 operator*(const vector3& other) const;
    vector3 operator/(int s) const;
    vector3 operator-() const;
    bool operator==(const vector3& zero) const;
    float dot_product(const vector3& other) const;
    float angle_with(const vector3& other) const; // returns in radians
	float getNorm()const; // returns the norm of the vector
    vector3 normalize() const;
    vector3 cross_product(const vector3& other) const;
    static vector3 zero();

    friend std::ostream& operator<<(std::ostream& os, const vector3& v)
    {
        os << "(" << v.get_x() << ", " << v.get_y() << ", " << v.get_z() << ")";
        return os;
    }
    void reset();
};