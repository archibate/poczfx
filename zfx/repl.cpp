//
// Created by admin on 2022/7/15.
//
#include <optional>

enum class CompileFormat{

};
static bool compileFile(const char* name, CompileFormat format) {
    std::optional<std::string> source = readFile(name);
    //读取
    if (!source) {
        fprintf();
        return false;
    }

    zfx::BytecodeBuilder bcb;
    if (CompileFormat == CompileFormat::Text) {

        bcb.setDumpSource(*source);
    }

    zfx::compileOrThrow(bcb, *source);//只是编译出字节码

    //zfx_State* l = globalState.get()
}