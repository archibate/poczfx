//
// Created by admin on 2022/8/4.
//
/*
 * 测试性的编译单元，用于将ast编译成opcode, 在visit的
 * */
#include "bc.h"
#include <iostream>
#include <string>

static const uint32_t MaxRegisterCount = 255;
static
static void writeInt(std::string &ss, int value) {

}
/*
 * @param AstNode
 * */

struct RegScope {
    RegScope(unsigned int top)  {
        //首先
    }


    ~RegScope() {
        //恢复栈顶值
    }
    unsigned int oldTop;
};

OpCode getUnary(Unary& op) {
     switch() {
         case :
     }
}

OpCode getBinary(AstBinary) {

}

/*
 *
 * */
OpCode getJumpOpCompare() {

}

bool isConstant() {

}

int32_t getConstantNumber() {

}

void compileExpr() {
    /*
     * 接下来就是一连串的if() compiler
     * */
}