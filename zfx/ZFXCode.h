#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include "span.h"
#include <string_view>

namespace zeno::zfx {

struct zfx_CompileOptions {

};

std::string zfx_compile(std::string_view source, size_t size, zfx_CompileOptions& options) {
    //Options是可选的
    //compile函数定义在Compiler.cpp文件中
    std::string result = compile();

    return std::move(result);
}

struct ZFXCode {
    std::vector<std::string> syms;
    std::vector<std::uint32_t> codes;
    std::size_t nregs{};

    explicit ZFXCode(std::string_view ins);
};

}
