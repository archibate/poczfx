#include "zfx.h"
#include <iostream>
#include "magic_enum.hpp"

using namespace zeno::zfx;

std::ostream &operator<<(std::ostream &os, Op const &op) {
    return os << "Op::" << magic_enum::enum_name(op);
}

std::ostream &operator<<(std::ostream &os, Token const &token) {
    overloaded{
        [&] (std::string const &t) {
            os << '"' << t << '"';
        },
        [&] (auto const &t) {
            os << t;
        },
    }.match(token);
    return os;
}

int main() {
    ZFXTokenizer tok;
    tok.tokenize("a+b+c");

    //for (auto const &token: tok.tokens)
        //std::cout << token << std::endl;

    ZFXParser par{tok.tokens};
    auto ast = par.expr_binary();
    if (!ast) throw std::runtime_error("failed to parse");
    //std::cout << ast->token << std::endl;

    return 0;
}
