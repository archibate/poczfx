#include "zfx.h"
#include <iostream>
#include "magic_enum.hpp"

using namespace zeno::zfx;

std::ostream &operator<<(std::ostream &os, Op const &op) {
    return os << "Op::" << magic_enum::enum_name(op);
}

int main() {
    ZFXTokenizer tok;
    tok.tokenize("!a+b+c");
    for (auto const &t: tok.tokens) {
        overloaded{
        [&] (std::string const &t) {
            std::cout << '"' << t << '"' << std::endl;
        },
        [&] (auto const &t) {
            std::cout << t << std::endl;
        },
        }.match(t);
    }
    return 0;
}
