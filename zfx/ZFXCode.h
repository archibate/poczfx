#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "span.h"
#include <string_view>

namespace zeno::zfx {

struct ZFXCode {
    std::vector<std::string> syms;
    std::vector<std::uint32_t> codes;
    std::size_t nregs{};

    explicit ZFXCode(std::string_view ins);
};

}
