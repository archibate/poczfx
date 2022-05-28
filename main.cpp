#include "zfx/ZFXCode.h"
#include "zfx/ZFXExec.h"
#include "magic_enum.hpp"
#include <iostream>
#include <map>

using namespace zeno::zfx;


int main() {
    ZFXCode co("a+b+c");

    std::map<std::string, std::uint32_t> syms;
    for (int i = 0; i < co.syms.size(); i++) {
        auto const &sym = co.syms[i];
        co.symtab[i] = &syms[sym];
    }

    ZFXExec ex(co);
    ex.execute();

    return 0;
}
