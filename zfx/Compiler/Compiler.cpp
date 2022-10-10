//
// Created by admin on 2022/7/1.
//
#include "ByteCodeBuilder.h"
#include <algorithm>
#include <cmath>
#include <bitset>
#include <unordered_map>
namespace zfx {
    //开始构建字节码指令
    using namespace zfx::Compile ;

    static const uint32_t KMaxRegisterCount = 255;//标志一下寄存器的数量

    struct Compiler {
        struct RegScope;
        Compiler(BytecodeBuilder& bytecode, const ) {
//使用列表初始化，初始化一些局部变量
        }
        //得到局部变量的寄存器
        int getLocalReg() {

        }

        void emitLoadK() {
            //bytecode.emit()
        }


        bool canInlineFunctionBody() {
            //判断是否可以inline函数题
        }

        void compileExprTempOp() {

        }

    private:
        struct Function {
            //支持自定义函数
            uint32_t id;
            std::vector<> locals;//局部变量
            unsigned int stackSize = 0
            bool callInline = false;
        };

        //局部变量
        struct  Local {
            uint8_t reg = 0;

        };

        BytecodeBuilder& bytecode;
        std::unordered_map<> locals;
        std::unordered_map<> globals;
        std::unordered_map<> variablse
        std::unordered_map<> constansts;
        std::unordered_map<> lconstansts;

        unsigned int regTop = 0;
        unsigned int stacksize = 0;


    };

    std::string compile() {
        //编译结束
    }
}