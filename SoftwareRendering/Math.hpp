#pragma once

#include <array>
#include <math.h>

namespace Math
{
    template<class Data>
    class TVec2
    {
    public:
        TVec2()
            : m_Elements{ 0, 0}
        {
        }

        TVec2(const Data& e0, const Data& e1)
            : m_Elements{ e0, e1}
        {
        }

        TVec2(const TVec2<Data>& v)
            : m_Elements(v.m_Elements)
        {
        }

        inline const TVec2<Data>& operator=(TVec2<Data> v)
        {
            std::swap(m_Elements, v.m_Elements);
            return *this;
        }

        inline const TVec2<Data> operator+(const TVec2<Data>& v) const
        {
            return { m_Elements[0] + v[0], m_Elements[1] + v[1] };
        }

        inline const TVec2<Data>& operator+=(const TVec2<Data>& v)
        {
            m_Elements = operator+(v).m_Elements;
        }

        inline const TVec2<Data> operator-(const TVec2<Data>& v) const
        {
            return { m_Elements[0] - v[0], m_Elements[1] - v[1] };
        }

        inline const TVec2<Data>& operator-=(const TVec2<Data>& v)
        {
            m_Elements = operator-(v).m_Elements;
        }

        inline const TVec2<Data> operator/(const float v) const
        {
            return { m_Elements[0] / v, m_Elements[1] / v };
        }

        inline Data& operator[](const unsigned int n)
        {
            return m_Elements[n];
        }

        inline const Data& operator[](const unsigned int n) const
        {
            return m_Elements[n];
        }

        inline float Length2() const
        {
            const float l = m_Elements[0] * m_Elements[0] + m_Elements[1] * m_Elements[1];
            return l;
        }

        inline float Length() const
        {
            const float l = Length2();
            return std::sqrt(l);
        }

    private:
        std::array<Data, 2> m_Elements;
    };

    template<class Data>
    inline TVec2<Data> operator*(const float l, const TVec2<Data>& r)
    {
        return TVec2(l * r[0], l * r[1]);
    }

    template<class Data>
    inline TVec2<Data> operator*(const TVec2<Data>& l, const float r)
    {
        return operator*(r, l);
    }

    typedef TVec2<float> fVec2;

    template<class Data>
    class TVec3
    {
    public:
        TVec3()
            : m_Elements{ 0, 0, 0 }
        {
        }

        TVec3(const Data& e0, const Data& e1, const Data& e2)
            : m_Elements{ e0, e1, e2 }
        {
        }

        TVec3(const TVec3<Data>& v)
            : m_Elements(v.m_Elements)
        {
        }

        inline const TVec3<Data>& operator=(TVec3<Data> v)
        {
            std::swap(m_Elements, v.m_Elements);
            return *this;
        }

        inline const TVec3<Data> operator+(const TVec3<Data>& v) const
        {
            return { m_Elements[0] + v[0], m_Elements[1] + v[1], m_Elements[2] + v[2] };
        }

        inline const TVec3<Data>& operator+=(const TVec3<Data>& v)
        {
            m_Elements = operator+(v).m_Elements;
        }

        inline const TVec3<Data> operator-(const TVec3<Data>& v) const
        {
            return { m_Elements[0] - v[0], m_Elements[1] - v[1], m_Elements[2] - v[2] };
        }

        inline const TVec3<Data>& operator-=(const TVec3<Data>& v)
        {
            m_Elements = operator-(v).m_Elements;
        }

        inline const TVec3<Data> operator/(const float v) const
        {
            return { m_Elements[0] / v, m_Elements[1] / v, m_Elements[2] / v };
        }

        inline const TVec3<Data>& operator/=(const float v)
        {
            m_Elements[0] /= v;
            m_Elements[1] /= v;
            m_Elements[2] /= v;

            return *this;
        }

        inline const TVec3<Data>& operator*=(const float v)
        {
            m_Elements[0] *= v;
            m_Elements[1] *= v;
            m_Elements[2] *= v;

            return *this;
        }

        inline Data& operator[](const unsigned int n)
        {
            return m_Elements[n];
        }

        inline const Data& operator[](const unsigned int n) const
        {
            return m_Elements[n];
        }

        inline float Length2() const
        {
            const float l = m_Elements[0] * m_Elements[0] + m_Elements[1] * m_Elements[1] + m_Elements[2] * m_Elements[2];
            return l;
        }

        inline float Length() const
        {
            const float l = Length2();
            return std::sqrt(l);
        }

    private:
        std::array<Data, 3> m_Elements;
    };

    template<class Data>
    inline TVec3<Data> operator*(const float l, const TVec3<Data>& r)
    {
        return TVec3(l * r[0], l * r[1], l * r[2]);
    }

    template<class Data>
    inline TVec3<Data> operator*(const TVec3<Data>& l, const float r)
    {
        return operator*(r, l);
    }

    typedef TVec3<float>        fVec3;
    typedef TVec3<int>          iVec3;
    typedef TVec3<unsigned int> uVec3;

    template<class Data>
    class TVec4
    {
    public:
        TVec4()
            : m_Elements{ 0, 0, 0, 0 }
        {
        }

        TVec4(const TVec3<Data>& v)
        {
            m_Elements[0] = v[0];
            m_Elements[1] = v[1];
            m_Elements[2] = v[2];
            m_Elements[3] = 1;
        }

        TVec4(const Data& e0, const Data& e1, const Data& e2, const Data& e3)
            : m_Elements{ e0, e1, e2, e3 }
        {
        }

        TVec4(const TVec4<Data>& v)
            : m_Elements(v.m_Elements)
        {
        }

        operator TVec3<Data>() const
        {
            return TVec3<Data>(m_Elements[0], m_Elements[1], m_Elements[2]);
        }

        operator TVec2<Data>() const
        {
            return TVec2<Data>(m_Elements[0], m_Elements[1]);
        }

        inline const TVec4<Data>& operator=(TVec4<Data> v)
        {
            std::swap(m_Elements, v.m_Elements);
            return *this;
        }

        inline const TVec4<Data> operator+(const TVec4<Data>& v) const
        {
            return { m_Elements[0] + v[0], m_Elements[1] + v[1], m_Elements[2] + v[2], m_Elements[3] + v[3] };
        }

        inline const TVec4<Data>& operator+=(const TVec4<Data>& v)
        {
            m_Elements = operator+(v).m_Elements;
        }

        inline const TVec4<Data> operator-(const TVec4<Data>& v) const
        {
            return { m_Elements[0] - v[0], m_Elements[1] - v[1], m_Elements[2] - v[2], m_Elements[3] - v[3] };
        }

        inline const TVec4<Data>& operator-=(const TVec4<Data>& v)
        {
            m_Elements = operator-(v).m_Elements;
        }

        inline TVec4<Data> operator/(const float v) const
        {
            return { m_Elements[0] / v, m_Elements[1] / v, m_Elements[2] / v, m_Elements[3] / v };
        }

        inline const TVec4<Data>& operator/=(const float v)
        {
            m_Elements = { m_Elements[0] / v, m_Elements[1] / v, m_Elements[2] / v, m_Elements[3] / v };
            return *this;
        }

        inline Data& operator[](const unsigned int n)
        {
            return m_Elements[n];
        }

        inline const Data& operator[](const unsigned int n) const
        {
            return m_Elements[n];
        }

        inline float Length2() const
        {
            const float l = m_Elements[0] * m_Elements[0] + m_Elements[1] * m_Elements[1] + m_Elements[2] * m_Elements[2] + m_Elements[3] * m_Elements[3];
            return l;
        }

        inline float Length() const
        {
            const float l = Length2();
            return std::sqrt(l);
        }

    private:
        std::array<Data, 4> m_Elements;
    };

    template<class Data>
    inline TVec4<Data> operator*(const float l, const TVec4<Data>& r)
    {
        return TVec4(l * r[0], l * r[1], l * r[2], l * r[3]);
    }

    template<class Data>
    inline TVec4<Data> operator*(const TVec4<Data>& l, const float r)
    {
        return operator*(r, l);
    }

    typedef TVec4<float>        fVec4;
    typedef TVec4<int>          iVec4;
    typedef TVec4<unsigned int> uVec4;

    template<class Data>
    inline Data Dot(const TVec3<Data>& l, const TVec3<Data>& r)
    {
        return l[0] * r[0] + l[1] * r[1] + l[2] * r[2];
    }

    template<class Data>
    inline Data Dot(const TVec4<Data>& l, const TVec4<Data>& r)
    {
        return l[0] * r[0] + l[1] * r[1] + l[2] * r[2] + l[3] * r[3];
    }

    template<class Data>
    inline Data Dot(const TVec2<Data>& l, const TVec2<Data>& r)
    {
        return l[0] * r[0] + l[1] * r[1];
    }

    template<class Data>
    inline TVec3<Data> Cross(const TVec3<Data>& v1, const TVec3<Data>& v2)
    {
        return TVec3<Data>{ (v1[1] * v2[2] - v1[2] * v2[1]), (v1[2] * v2[0] - v1[0] * v2[2]), (v1[0] * v2[1] - v1[1] * v2[0]) };
    }

    template<class Data>
    inline Data CalculateArea(const TVec2<Data>& v1, const TVec2<Data>& v2)
    {
        return v1[0]*v2[1] - v1[1]*v2[0];
    }

    template<class Data>
    inline TVec3<Data> Normalize(const TVec3<Data>& v)
    {
        v / v.Length();
    }

    template <class Data>
    class TMat4x4
    {
    public:
        typedef TVec4<Data> Row;
    public:
        TMat4x4()
        {
        }

        TMat4x4(const TMat4x4<Data>& m)
            : m_Elements(m.m_Elements)
        {
        }

        TMat4x4( const std::array<Row,4>& rows)
            : m_Elements(rows)
        {
        }

        static TMat4x4<Data> E()
        {
            TMat4x4<Data> E;

            for (int i = 0; i < 4; ++i)
                E[i][i] = 1;

            return E;
        }

        inline Row& operator[](const unsigned int n)
        {
            return m_Elements[n];
        }
        
        inline const Row& operator[](const unsigned int n) const
        {
            return m_Elements[n];
        }

        inline const TMat4x4<Data>& operator=(const TMat4x4<Data>& m)
        {
            m_Elements = m.m_Elements;
            return *this;
        }

        inline TMat4x4<Data> operator+(const TMat4x4<Data>& r) const
        {
            return { (m_Elements[0] + r[0]),  (m_Elements[1] + r[1]),  (m_Elements[2] + r[2]),  (m_Elements[3] + r[3]) };
        }

        inline TMat4x4<Data> operator-(const TMat4x4<Data>& r) const
        {
            return { (m_Elements[0] - r[0]),  (m_Elements[1] - r[1]),  (m_Elements[2] - r[2]),  (m_Elements[3] - r[3]) };
        }

        inline TMat4x4<Data> operator*(const TMat4x4<Data>& r) const
        {
            TMat4x4<Data> m;
            for (int i = 0; i < 4; ++i)
                for (int k = 0; k < 4; ++k)
                    for (int j = 0; j < 4; ++j)
                        m[i][k] += m_Elements[i][j] * r[j][k];

            return m;
        }

        inline TVec4<Data> operator*(const TVec4<Data>& r) const
        {
            TVec4<Data> v;

            for (int i = 0; i < 4; ++i)
                v[i] = Dot(m_Elements[i], r);

            return v;
        }

    private:
        std::array<Row, 4> m_Elements;
    };

    typedef TMat4x4<float> Mat4x4;

    template<class Data>
    class Quaternion
    {
    public:
        Quaternion(const TVec4<Data>& v)
            : m_S(v[0])
            , m_V(v[1], v[2], v[3])
        {
        }

        Quaternion(const Data angle, const TVec3<Data>& axis)
            : m_S(std::cos(angle/2))
            , m_V(std::sin(angle/2) * axis)
        {
        }

        Quaternion<Data> operator*(const Quaternion& r) const
        {
            const Data s = m_S * r.m_S - Dot(m_V, r.m_V);
            const Data v = m_S * r.m_V + r.m_S * m_V + Cross(m_V, r.m_V);

            return Quaternion<Data>(s, v);
        }

        const Quaternion<Data>& operator*=(const Quaternion& r) const
        {
            m_S = m_S * r.m_S - Dot(m_V, r.m_V);
            m_V = m_S * r.m_V + r.m_S * m_V + Cross(m_V, r.m_V);

            return *this;
        }

        Quaternion<Data> operator*(const Data& r) const
        {
            const Data s = m_S * r;
            const Data v = m_V * r;

            return Quaternion<Data>(s, v);
        }

        const Quaternion<Data>& operator*=(const Data& r) const
        {
            m_S = m_S * r;
            m_V = m_V * r;

            return *this;
        }

    private:
        Data        m_S;
        TVec3<Data> m_V;
    };

    template<class Data>
    Quaternion<Data> operator*(const Data& l, const Quaternion<Data> r)
    {
        return r * l;
    }

    inline Mat4x4 ConstructViewportMatrix(const unsigned int width, const unsigned int height)
    {
        return Mat4x4({ fVec4{static_cast<float>(width) / 2, 0, 0, static_cast<float>(width) / 2},
                        fVec4{0, static_cast<float>(height) / 2, 0, static_cast<float>(height) / 2},
                        fVec4{0, 0, 0.5f, 0.5f},
                        fVec4{0, 0, 0, 1} }
        );
    }

    inline float FindMax(const std::initializer_list<float>& values)
    {
        float max = *values.begin();
        for (const auto& value : values)
            if (value > max)
                max = value;

        return max;
    }

    inline float FindMin(const std::initializer_list<float>& values)
    {
        float min = *values.begin();
        for (const auto& value : values)
            if (value < min)
                min = value;

        return min;
    }

    struct RectBorder
    {
        fVec2 TopLeft;
        fVec2 BottomRight;
    };

    inline RectBorder FindRectBorder(const fVec2& a, const fVec2& b, const fVec2& c)
    {
        RectBorder border;
        border.TopLeft     = { FindMin({a[0], b[0], c[0]}), FindMin({a[1], b[1], c[1]}) };
        border.BottomRight = { FindMax({a[0], b[0], c[0]}), FindMax({a[1], b[1], c[1]}) };

        return border;
    }

    /*inline Mat4x4 CalculatePerspectiveTransformation(const float width, const float height, const float near, const float far)
    {
        return Mat4x4{ {
            fVec4{ 2 * near / width, 0, -1, 0 }, //предполагается, что r+b/r-b = 1, но на самом деле, r = width/2, l = -width/2
            fVec4{ 0, 2 * near/height, -1, 0},
            fVec4{ 0, 0, (far + near)/(far - near), -2*far*near/(far - near)},
            fVec4{ 0, 0, 1, 0}
        } };
    }*/

    /*inline Mat4x4 CalculatePerspectiveTransformation(const float width, const float height, const float near, const float far)
    {
        return Mat4x4{ {
            fVec4{ 2 * near / width, 0, 0, 0 },
            fVec4{ 0, 2 * near / height, 0, 0},
            fVec4{ 0, 0, (far + near) / (far - near), -2 * far*near / (far - near)},
            fVec4{ 0, 0, 1, 0}
        } };
    }*/

    inline Mat4x4 CalculatePerspectiveTransformation(const float fov, const float ratio, const float near, const float far)
    {
        const float tg = std::tan(fov/2);
        return Mat4x4{ {
            fVec4{ 1 / (ratio * tg), 0, 0, 0 },
            fVec4{ 0, 1 / (tg), 0, 0},
            fVec4{ 0, 0, (far + near) / (far - near), -2 * far*near / (far - near)},
            fVec4{ 0, 0, 1, 0}
        } };
    }

    inline Mat4x4 CalculateTranslationTransformation(const fVec3& v)
    {
        return Mat4x4{ {
            fVec4{1, 0, 0, v[0]},
            fVec4{0, 1, 0, v[1]},
            fVec4{0, 0, 1, v[2]},
            fVec4{0, 0, 0, 1   },
        } };
    }

    inline float ToRadians(const float angle)
    {
        return angle / (2 * 3.14159265358979323846);
    }

    inline Mat4x4 CalculateXRotation(const float angle)
    {
        const float s = std::sin(angle);
        const float c = std::cos(angle);

        return Mat4x4{ {
            fVec4{1, 0, 0, 0},
            fVec4{0, c, -s, 0},
            fVec4{0, s, c, 0},
            fVec4{0, 0, 0, 1},
            } };
    }

    inline Mat4x4 CalculateYRotation(const float angle)
    {
        const float s = std::sin(angle);
        const float c = std::cos(angle);

        return Mat4x4{ {
            fVec4{c, 0, s, 0},
            fVec4{0, 1, 0, 0},
            fVec4{-s, 0, c, 0},
            fVec4{0, 0, 0, 1},
            } };
    }

    inline Mat4x4 CalculateZRotation(const float angle)
    {
        const float s = std::sin(angle);
        const float c = std::cos(angle);

        return Mat4x4{ {
            fVec4{c, -s, 0, 0},
            fVec4{s, c, 0, 0},
            fVec4{0, 0, 1, 0},
            fVec4{0, 0, 0, 1},
            } };
    }

    inline Mat4x4 CalculateScaleTransformation(const fVec3& v)
    {
        return Mat4x4{ {
            fVec4{v[0], 0, 0,  0},
            fVec4{0, v[1], 0,  0},
            fVec4{0, 0, v[2],  0},
            fVec4{0, 0, 0, 1 },
        } };
    }

}