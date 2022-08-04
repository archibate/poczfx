#pragma once

#include <cstdint>
#include <variant>
#include <cmath>
#include <string_view>
#include "enumtools.h"
#include "overloaded.h"

namespace zeno::zfx {

#define setnvalue(obj, n) \
{ \
   Object* i_o = (obj)            \
                                  \
}

#define setvvalue(obj, x, y, z, w) \
{                                  \
   Object* i_o = (obj);            \
                                   \
}
namespace object_details {

struct Object;

struct Pointer {
    void *ptr;

    inline Object attr(std::string_view name);  // TODO
};

enum ObjectType : std::uint8_t {
    kPointer = 0,
    kInt = 1,
    kArray = 2,
    kFloat = 3,
};

union Object {
    //static_assert(!is_big_endian());
    //static_assert(sizeof(int) == 4);
    //static_assert(sizeof(float) == 4);
    //static_assert(sizeof(void *) == 8);

private:
    struct {
        Pointer p;
    } m_p;
    struct {
        int padding;
        float f;
    } m_f;
    struct {
        int padding;
        int i;
    } m_i;
    std::uintptr_t m_raw;
    int m_ty;

public:
    ObjectType type() const noexcept {
        return ObjectType{static_cast<std::uint8_t>(m_ty & 3)};
    }

    Object() noexcept : m_raw{} {}

    explicit Object(float a_f) noexcept
        : m_f{ObjectType::kFloat, a_f} {
    }

    explicit Object(int a_i) noexcept
        : m_i{ObjectType::kInt, a_i} {
    }

    explicit Object(Pointer a_p) noexcept
        : m_p{a_p} {
        m_raw &= ~std::uintptr_t{3};
    }

    explicit operator float() const noexcept {
        return m_f.f;
    }

    explicit operator int() const noexcept {
        return m_i.i;
    }

    explicit operator Pointer() const noexcept {
        return m_p.p;
    }

    Object operator()(std::initializer_list<Object> args) const {
        return {};
    }
};
#if 0
    enum class ObjectType {

    };
    struct Object {
        ObjectType type{};//对象类型，包括浮点，整数，字符串，数组(也就是vec3)
        unsigned long flags;//标志位
    };

    //字符串对象
    struct StringObject : public Object {
        size_t length;

    };

    //提供一些内置函数比如创建字符串, 拼接字符串之类
#endif
namespace details {
    using Variant = std::variant<float, int, Pointer>;

    inline Variant obj2var(Object a) noexcept {
        if (a.type() == ObjectType::kFloat) {
            return static_cast<float>(a);
        } else if (a.type() == ObjectType::kInt) {
            return static_cast<int>(a);
        } else if (a.type() == ObjectType::kPointer) {
            return static_cast<Pointer>(a);
        } else {
            return Pointer{};
        }
    }

    template <class A, class B>
    inline int cmp3w(A a, B b) noexcept {
        return a == b ? 0 : (a < b ? -1 : 1);
    }
}

inline Object operator+(Object a) noexcept {
    return std::visit([&] (auto a) {
        using A = decltype(a);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$pos")({});
        } else {
            return Object{+a};
        }
    }, details::obj2var(a));
}

inline Object operator-(Object a) noexcept {
    return std::visit([&] (auto a) {
        using A = decltype(a);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$neg")({});
        } else {
            return Object{-a};
        }
    }, details::obj2var(a));
}

inline Object operator+(Object a, Object b) noexcept {
    return std::visit([&] (auto a, auto b) {
        using A = decltype(a);
        using B = decltype(b);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$add")({Object{b}});
        } else if constexpr (std::is_same_v<B, Pointer>) {
            return b.attr("$radd")({Object{a}});
        } else {
            return Object{a + b};
        }
    }, details::obj2var(a), details::obj2var(b));
}

inline Object operator-(Object a, Object b) noexcept {
    return std::visit([&] (auto a, auto b) {
        using A = decltype(a);
        using B = decltype(b);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$sub")({Object{b}});
        } else if constexpr (std::is_same_v<B, Pointer>) {
            return b.attr("$rsub")({Object{a}});
        } else {
            return Object{a - b};
        }
    }, details::obj2var(a), details::obj2var(b));
}

inline Object operator*(Object a, Object b) noexcept {
    return std::visit([&] (auto a, auto b) {
        using A = decltype(a);
        using B = decltype(b);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$mul")({Object{b}});
        } else if constexpr (std::is_same_v<B, Pointer>) {
            return b.attr("$rmul")({Object{a}});
        } else {
            return Object{a * b};
        }
    }, details::obj2var(a), details::obj2var(b));
}

inline Object operator/(Object a, Object b) noexcept {
    return std::visit([&] (auto a, auto b) {
        using A = decltype(a);
        using B = decltype(b);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$div")({Object{b}});
        } else if constexpr (std::is_same_v<B, Pointer>) {
            return b.attr("$rdiv")({Object{a}});
        } else {
            return Object{a / b};
        }
    }, details::obj2var(a), details::obj2var(b));
}

inline Object operator%(Object a, Object b) noexcept {
    return std::visit([&] (auto a, auto b) {
        using A = decltype(a);
        using B = decltype(b);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$mod")({Object{b}});
        } else if constexpr (std::is_same_v<B, Pointer>) {
            return b.attr("$rmod")({Object{a}});
        } else {
            if constexpr (std::is_floating_point_v<A>) {
                return Object{std::fmod(a, static_cast<A>(b))};
            } else if constexpr (std::is_floating_point_v<B>) {
                return Object{std::fmod(static_cast<B>(a), b)};
            } else {
                return Object{a % b};
            }
        }
    }, details::obj2var(a), details::obj2var(b));
}

inline Object operator<<(Object a, Object b) noexcept {
    return std::visit([&] (auto a, auto b) {
        using A = decltype(a);
        using B = decltype(b);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$shl")({Object{b}});
        } else if constexpr (std::is_same_v<B, Pointer>) {
            return b.attr("$rshl")({Object{a}});
        } else {
            if constexpr (std::is_floating_point_v<A> || std::is_floating_point_v<B>) {
                return Object{static_cast<int>(a) << static_cast<int>(b)};
            } else {
                return Object{a << b};
            }
        }
    }, details::obj2var(a), details::obj2var(b));
}

inline Object cmp(Object a, Object b) noexcept {
    return std::visit([&] (auto a, auto b) {
        using A = decltype(a);
        using B = decltype(b);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$cmp")({Object{b}});
        } else if constexpr (std::is_same_v<B, Pointer>) {
            return b.attr("$rcmp")({Object{a}});
        } else {
            return Object{details::cmp3w(a, b)};
        }
    }, details::obj2var(a), details::obj2var(b));
}

inline Object pow(Object a, Object b) noexcept {
    return std::visit([&] (auto a, auto b) {
        using A = decltype(a);
        using B = decltype(b);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$pow")({Object{b}});
        } else if constexpr (std::is_same_v<B, Pointer>) {
            return b.attr("$rpow")({Object{a}});
        } else {
            return Object{std::pow(a, b)};
        }
    }, details::obj2var(a), details::obj2var(b));
}

inline Object atan2(Object a, Object b) noexcept {
    return std::visit([&] (auto a, auto b) {
        using A = decltype(a);
        using B = decltype(b);
        if constexpr (std::is_same_v<A, Pointer>) {
            return a.attr("$atan2")({Object{b}});
        } else if constexpr (std::is_same_v<B, Pointer>) {
            return b.attr("$ratan2")({Object{a}});
        } else {
            return Object{std::atan2(a, b)};
        }
    }, details::obj2var(a), details::obj2var(b));
}

}
    struct Proto {

    };
}
