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

    ZFXParser par{tok.tokens};
    auto ast = par.expr_binary();
    if (!ast) throw std::runtime_error("failed to parse");

    ZFXLower low;
    auto irid = low.visit(ast.get());

    ZFXScanner sca{low.nodes};
    sca.scan();
    
    ZFXEmitter emi{sca.out_nodes, sca.reglut};
    emi.generate();
    for (auto c: emi.codes) {
        std::cout << c << std::endl;
    }

    return 0;
}
