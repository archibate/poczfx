#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "span.h"
#include <string_view>

namespace zeno::zfx {

struct zfx_CompileOptions {

};

std::string zfx_compile(std::string_view source, size_t size, zfx_CompileOptions& options);

struct ZFXCode {
    std::vector<std::string> syms;
    std::vector<std::uint32_t> codes;
    std::size_t nregs{};

    explicit ZFXCode(std::string_view ins);
};

}
