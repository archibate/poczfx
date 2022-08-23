//
// Created by admin on 2022/8/23.
//
#pragma once
#include "ast.h"
#include <any>
#include <memory>

//暂时没有IR，但是我在汇编之上封装了一层抽象例如:Inst Oprand之类
//汇编操作码
enum class AsmOpCode {

};

//操作数的种类
enum class OprandKind {

};

//操作数
class Oprand {
    OprandKind kind;
    std::any value;
};

//寄存器
class Register : public Oprand {

};

//条件语句产生的Oprand
class CmpOrand : public Oprand {

};

//指令的基本块，块内都是线性序列
class BasicBlock {

};

class AsmModule {

};

class AsmGenerator : public AstVisitor {
    std::shared_ptr<AsmModule> asmModule;//编译后的模型

    //接下来就是重写AstVisitor中所有的visit方法
};