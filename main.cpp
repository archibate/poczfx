#include "zfx.h"
#include <iostream>
#include "magic_enum.hpp"

using namespace zeno::zfx;

std::ostream &operator<<(std::ostream &os, Op const &op) {
    return os << "Op::" << magic_enum::enum_name(op);
}

int main() {
    ZFXTokenizer tok;
    tok.tokenize("!a+b ");
    for (auto const &t: tok.tokens) {
        std::visit([&] (auto const &t) {
            if constexpr (std::is_same_v<std::decay_t<decltype(t)>, std::string>) {
                std::cout << '"' << t << '"' << std::endl;
            } else {
                std::cout << t << std::endl;
            }
        }, t);
    }
    return 0;
}
