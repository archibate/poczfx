#include "zfx/ZFXCode.h"
#include "zfx/ZFXExec.h"
#include "magic_enum.hpp"
#include <iostream>
#include <map>

using namespace zeno::zfx;


int main() {
    ZFXCode co("a=a+a;");

    ZFXExec ex(co);
    for (int i = 0; i < ex.symtab.size(); i++) {
        auto const &sym = ex.symtab[i];
        ex.symtab[i] = Object{2};
    }
    ex.execute();

    std::cout << ex.symtab[0] << std::endl;
    std::cout << "done" << std::endl;
    return 0;
}
