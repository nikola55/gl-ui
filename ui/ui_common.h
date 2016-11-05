#ifndef UICOMMON_H
#define UICOMMON_H
#include <iostream>
#include <stdint.h>

namespace ui {

typedef uint32_t uint;
typedef uint64_t ulong;
typedef uint8_t byte;

template <class Ptr> class shared_ptr {

    template<class Ptr2> friend class shared_ptr;

protected:

    Ptr *value;
    uint *count;

public:
    shared_ptr(Ptr *v = 0) : value(v), count(new uint(1)) {

    }
    shared_ptr(const shared_ptr &o) : value(o.value), count(o.count) {
        count[0]++;
    }
    shared_ptr& operator=(const shared_ptr &o) {
        o.count[0]++;
        if(--count[0] == 0) {
            delete value;
            delete count;
        }
        value = o.value;
        count = o.count;
    }
    template< class Ptr2 > shared_ptr(const shared_ptr<Ptr2> &o) : value(o.value), count(o.count) {
        count[0]++;
    }
    template< class Ptr2 > shared_ptr operator=(const shared_ptr<Ptr2> &o) {
        o.count[0]++;
        if(--count[0]==0) {
            delete value;
            delete count;
        }
        value = o.value;
        count = o.count;
        return *this;
    }
    ~shared_ptr() {
        if(--count[0]==0) {
            delete value;
            delete count;
        }
    }
    operator Ptr*() {
        return value;
    }
    Ptr& operator*() {
        return *value;
    }
    Ptr* operator->() {
        return value;
    }
};

template <class _Type> class grid {
protected:
    grid(unsigned width, unsigned height, _Type *data, bool freeData) :
        m_width(width),
        m_height(height),
        m_data(data),
        m_ref_count(new unsigned(1)),
        m_freeData(freeData) {

    }
public:

    grid(unsigned width, unsigned height) :
        m_width(width),
        m_height(height),
        m_ref_count(new unsigned(1)),
        m_data(new _Type[m_width*m_height]),
        m_freeData(true) {

    }

    grid(const grid &x) :
        m_width(x.m_width),
        m_height(x.m_height),
        m_ref_count(x.m_ref_count),
        m_data(x.m_data),
        m_freeData(x.m_freeData) {

        m_ref_count[0]++;

    }

    virtual ~grid() {
        if (--m_ref_count[0] == 0) {
            if(m_freeData) {
                delete []m_data;
            }
            delete m_ref_count;
        }
    }

    _Type* data() {
        return m_data;
    }

    grid& operator=(const grid &x) {
        x.m_ref_count[0]++;
        if (--m_ref_count[0] == 0) {
            if(m_freeData) {
                delete []m_data;
            }
            delete m_ref_count;
        }
        m_width = x.m_width;
        m_height = x.m_height;
        m_ref_count = x.m_ref_count;
        m_data = x.m_data;
        m_freeData = x.m_freeData;
        return *this;
    }

    _Type& operator()(unsigned x, unsigned y) {
        return m_data[m_width * y + x];
    }

    const _Type& operator()(unsigned x, unsigned y) const {
        return m_data[m_width * y + x];
    }

    unsigned width() const { return m_width; }

    unsigned height() const { return m_height; }

private:
    unsigned m_width;
    unsigned m_height;
    unsigned *m_ref_count;
    _Type * m_data;
    bool m_freeData;
};

class image : public grid<byte> {
public:

    image(uint w, uint h, byte bitsPerPixel, byte *data, bool freeData) :
        grid(w, h, data, freeData),
        m_bitsPerSample(bitsPerPixel) {
    }

    image(const image &x) :
        grid(x),
        m_bitsPerSample(x.m_bitsPerSample) {
    }

    image& operator=(const image &x) {
        this->grid::operator =(x);
        m_bitsPerSample = x.m_bitsPerSample;
    }

    byte bitsPerSample() const {
        return m_bitsPerSample;
    }

private:
    byte m_bitsPerSample;
};

template < class _Type > struct vec2 {
    _Type x;
    _Type y;
};

typedef grid<float> mat3;

typedef vec2<uint> point;

inline void eye3x3(mat3 &m) {
    m(0,0) = 1.0f; m(0,1) = 0.0f; m(0,2) = 0.0f;
    m(1,0) = 0.0f; m(1,1) = 1.0f; m(1,2) = 0.0f;
    m(2,0) = 0.0f; m(2,1) = 0.0f; m(2,2) = 1.0f;
}

inline mat3 eye3x3() {
    mat3 eye(3,3);
    eye3x3(eye);
    return eye;
}

inline void trans3x3(mat3 &m, float x, float y) {
    m(0, 2) = x;
    m(1, 2) = y;
}

inline mat3 operator*(const mat3 &A, const mat3 &B) {
    bool allowed = A.width() == 3 && A.height() == 3 &&
            B.width() == 3 && B.height() == 3;
    if(allowed) {
        mat3 C(3,3);
        C(0,0) = A(0,0)*B(0,0) + A(0,1)*B(1,0) + A(0,2)*B(2,0);
        C(0,1) = A(0,0)*B(0,1) + A(0,1)*B(1,1) + A(0,2)*B(2,1);
        C(0,2) = A(0,0)*B(0,2) + A(0,1)*B(1,2) + A(0,2)*B(2,2);

        C(1,0) = A(1,0)*B(0,0) + A(1,1)*B(1,0) + A(1,2)*B(2,0);
        C(1,1) = A(1,0)*B(0,1) + A(1,1)*B(1,1) + A(1,2)*B(2,1);
        C(1,2) = A(1,0)*B(0,2) + A(1,1)*B(1,2) + A(1,2)*B(2,2);

        C(2,0) = A(2,0)*B(0,0) + A(2,1)*B(1,0) + A(2,2)*B(2,0);
        C(2,1) = A(2,0)*B(0,1) + A(2,1)*B(1,1) + A(2,2)*B(2,1);
        C(2,2) = A(2,0)*B(0,2) + A(2,1)*B(1,2) + A(2,2)*B(2,2);
        return C;
    }
    return mat3(1,1);
}

inline std::ostream& operator<<(std::ostream &os, const mat3 &m) {
    os << m(0,0) << ", " << m(0,1) << ", " << m(0,2) << std::endl;
    os << m(1,0) << ", " << m(1,1) << ", " << m(1,2) << std::endl;
    os << m(2,0) << ", " << m(2,1) << ", " << m(2,2) << std::endl;
    return os;
}

struct glyph_info {

    point advance;
    uint width;
    uint height;
    uint left;
    uint top;

    glyph_info(point a, uint w, uint h, uint l, uint t) :
        advance(a),
        width(w),
        height(h),
        left(l),
        top(t) {

    }

};

}

#endif // UICOMMON_H
