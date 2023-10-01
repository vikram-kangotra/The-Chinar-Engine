#pragma once

#include <stdint.h>
#include <initializer_list>
#include <algorithm>
#include <exception>
#include <cmath>

namespace Chinar {

    template <typename T, int m>
    class Vec {
        public:
            Vec() {}

            Vec(std::initializer_list<T> list) {
                if (list.size() != m) {
                    throw std::exception();
                }
                std::copy(list.begin(), list.end(), data);
            }

            Vec(T a) 
            : data{a} {}

            Vec(const Vec<T, m>& other) {
                std::copy(other.data, other.data + m, this->data);
            }

            Vec& operator=(const Vec<T, m>& other) {
                std::copy(other.data, other.data + m, this->data);
                return *this;
            }

            T& operator[](const uint32_t index) {
                if (index >= m) {
                    throw std::exception();   
                }
                return data[index];   
            }

            Vec& operator+=(const Vec<T, m>& other) {
                for (int i = 0; i < m; ++i) {
                    this->data[i] += other.data[i];   
                }
                return *this;
            }

            Vec operator+(const Vec<T,m>& other) const {
                Vec<T, m> ret = *this;
                return ret += other;
            }

            Vec& operator-=(const Vec<T, m>& other) {
                for (int i = 0; i < m; ++i) {
                    this->data[i] -= other.data[i];
                }
                return *this;
            }

            Vec operator-(const Vec<T, m>& other) const {
                Vec<T, m> ret = *this;
                return ret -= other;
            }

            Vec& operator*=(const Vec<T, m>& other) {
                for (int i = 0; i < m; ++i) {
                    this->data[i] *= other.data[i];
                }
                return *this;
            }

            Vec operator*(const Vec<T, m>& other) const {
                Vec<T, m> ret = *this;
                return ret *= other;
            }

            Vec& operator*=(const T& val) {
                for (int i = 0; i < m; ++i) {
                    this->data[i] *= val;
                }
                return *this;
            }

            Vec operator*(const T& val) const {
                Vec<T, m> ret = *this;
                return ret *= val;
            }

            Vec& operator/=(const T& val) {
                if (val == 0) {
                    throw std::exception();
                }
                for (auto& d : data) {
                    d /= val;
                }
                return *this;
            }

            Vec operator/(const T& val) const {
                Vec<T, m> ret = *this;
                return ret /= val;
            }

            float magnitudeSq() const {
                T ret;
                for (const auto& d : data) {
                    ret += d*d;
                }
                return ret;
            }

            float magnitude() const {
                return std::sqrt(magnitudeSq());
            }

            static Vec normalize(const Vec<T, m>& val) {
                return val / val.magnitude();
            }

        private:
            T data[m];
    };

    template <typename T = float>
    struct Vec2 : public Vec<T, 2> {
        T& x;
        T& y;
            
        Vec2()
        : x{(*this)[0]}, y{(*this)[1]} {}

        Vec2(std::initializer_list<T> list) 
        : Vec<T, 2>{list}
        , x{(*this)[0]}, y{(*this)[1]} {}

        Vec2(T a) 
        : Vec<T, 2>{a}
        , x{(*this)[0]}, y{(*this)[1]} {}

        Vec2(const Vec2<T>& other)
        : Vec<T, 2>{other}
        , x{(*this)[0]}, y{(*this)[1]} {}

        Vec2<T>& operator=(const Vec2<T>& other) {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }

        Vec2(const Vec<T, 2>& other)
        : Vec<T, 2>{other}
        , x{(*this)[0]}, y{(*this)[1]} {}
        
        float angle(const Vec2<T>& other) const {
            T dot = (*this) * other;
            T det = x * other.y - y * other.x;
            return -atan2(det, dot);
        }
        
    };
}
