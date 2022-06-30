//
// Created by admin on 2022/6/29.
//
//这是一个用来build字节码的
#include "bc.h"
#include <string>

namespace zfx {
    //一个纯虚类
    class BytecodeEncoder {
    public:
        virtual ~BytecodeEncoder();
        virtual std::uint32_t encodeOp() = 0;//
    };

    class BytecodeBuilder {
    public:
        BytecodeBuilder(BytecodeEncoder *encoder = nullptr);


        //接下来就是添加各类指令的方法
    private:
        //这些都是zfx中的常量
        struct Constant {

        };

        struct Jump {
            //跳转指令
        };
    };
}