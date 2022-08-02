//
// Created by admin on 2022/6/30.
//
#include "../bc.h"
#include "ByteCodeBuilder.h"

#include <algorithm>
#include <string>

namespace zfx {


    //写一个函数返回字节码长度,我们指令是32个字节

    static int getOpLength(OpCode op) {
        switch(op) {
            case:
        }
        return 1;
    }
    static writeDouble(std::string& ss, double value) {
        ss.append(reinterpret_cast<const char*>(&value), sizeof (value));
    }

    static writeInt(std::string& ss, int value) {

    }

    //接下来是几个判断Op指令类型的函数
    inline bool isJump (Opcode op) {
        switch(op) {
            case :
                return true;
            default
                return false;
        }
    }

    int32_t BytecodeBuilder::addConstantNumber(double value) {
        Constant c = {Constant::Type::FLOAT};

        ConstantKey k = {Constant::Type::FLOAT};
        static_assert(sizeof() == sizeof(value), "");
    }

    int32_t BytecodeBuilder::addConstantNumber(int value) {
            //直接调用addConstant
    }

    int32_t BytecodeBuilder::addConstant(const ConstantKey &key, const Constant &value) {
        if (int32_t* cache = constantMap.find(key)) {
            return *cache;
        }

        //uint32_t id = ()
    }

    void BytecodeBuilder::emitABC(Opcode op, uint8_t a, uint8_t b, uint8_t c) {
            uint32_t insn = ;//指令
            insns.push_back(insn);
    }

    void BytecodeBuilder::emitAD(OpCode op, uint8_t a, uint16_t d) {

    }

    for (size_t i = 0; i < insns.size();) {
        uint32_t  insn = insns[i];
        //取出指令
    }

private:
    std::vector<uint32_t> insns;
}