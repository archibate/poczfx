//
// Created by admin on 2022/8/23.
//
#pragma once
#include "ast.h"
#include <any>
#include <memory>
#include <map>
#include <vector>

//暂时没有IR，但是我在汇编之上封装了一层抽象例如:Inst Oprand之类
//汇编操作码
enum class AsmOpCode {

};

class Inst {
public:
    //指令的几个参数
    AsmOpCode op;
    uint32_t numOprands;
    static uint32_t index;
    std::string comment; //指令的注释
    virtual std::string toString() = 0;
    Inst(AsmOpCode op, uint32_t numOprands, std::string comment) : op(op), numOprands(numOprands),comment(comment) {
        //下标加加
        index++;
    }
};

class Inst_0 : public Inst{
public:
    Inst_0(AsmOpCode op) : Inst(op, 0) {

    }

    std::string toString() override {

    }
};

class Inst_1 : public Inst {
public:
    std::shared_ptr<Oprand> oprand;
    Inst_1(AsmOpCode code) : Ins(Op, 1) {

    }

    std::string toString() override {

    }

};

class Inst_2 : public Inst {
public:
    std::shared_ptr<Oprand> oprand1;
    std::shared_ptr<Oprand> oprand2;
    Inst_2(AsmOpCode code, std::shared_ptr<Oprand> &oprand1, std::shared_ptr<Oprand> &oprand2) :
    Inst(op, 2), oprand1(oprand1), oprand2(oprand2){

    }

    std::string toString() override {

    }
};


//操作数的种类
enum class OprandKind {
    //抽象度比较高的操作数
    varIndex,
    returnSlot, // 用于存放返回值的位置，通常是一个寄存器
    bb,         // 跳转指令返回的基本快
    function,
    stringConst, //字符串常量

    //抽象度低的操作数接近汇编
    regist,     //物理内存寄存器
    memory,     //内存地址
    immediate,  //立即数
    label,      //标签

    flag
};

//根据数据类型获取正确的参数和寄存器
class OpCodeUtil {
public:

};


std::string toString(AsmOpCode op) {

}

std::string toString(OprandKind, kind) {

}
//操作数
class Oprand {
    OprandKind kind;
    std::any value;
    std::string name;

    //判断操作数是否一致
    template<typename T>
    bool isSame(std::shared_ptr<Oprand> &oprand1) {
        return this->kind == oprand1->kind  && std::any_cast<T>(this->value) == std::any_cast<T>(this->value);
    }

    virtual std::string toString() {
        if () {

        } else if() {

        } else if() {

        } else {

        }
    }
};

class VarOprand : public Oprand {
public:
    std::string toString() override {

    }
};

class FunctionOprand : public Oprand {
public:
    std::shared_ptr<Type> returnType;  //返回值类型
    std::vector<std::shared_ptr<Oprand>> args;
    std::string functionName;
    FunctionOprand() {

    }

    std::string toString() override {
        return "_";
    }
};

//条件语句产生的
class CmpOrand : public Oprand {
public:
    CmpOrand() {

    }
};
//寄存器
class Register : public Oprand {
public:
    Register() {

    }

    //可供分配寄存器的数量
    const static uint32_t numAvailableRegs = 13;//去除掉rbp和rsp，再保留一个寄存器后

    //32位寄存器


    //64位可供分配的寄存器
    //static std::vector<std::shared_ptr<Oprand>>
    std::string toString() override {
        return "%" + std::any_cast<std::string>(this->value);
    }

};

//指令的基本块，块内都是线性序列
class BasicBlock {
public:
    std::vector<std::shared_ptr<Inst>> insts;//基本块内的指令
    size_t funIndex{-1}; //函数编号
    size_t bbIndex{-1};  //基本块的编号
    bool isDestination{false}; // 用来判断是否有其他块跳转该块

    std::string getName() {
        if (this->bbIndex != -1 && this->funIndex != -1) {

        } else if(bbIndex != -1){

        } else {

        }

    }

    std::string toString() {
        std::string str;
        if (this->isDestination) {
            //
        } else{
            
        }

        return str;
    }
};

class AsmModule {
public:
    //zfx中每一个函数对应的指令数组
    std::map<std::string, std::vector<std::shared_ptr<BasicBlock>>> fun2Code;


    //字符串常量
    std::vector<std::string> stringConsts;

    //输出asm这一模块的文件字符串
    std::string toString() {

    }
};

class TempStates {
public:

};

class AsmGenerator : public AstVisitor {
    std::shared_ptr<AsmModule> asmModule;//编译后的模型

    std::shared_ptr<BasicBlock> getCurrentBlock() {

    }

    std::shared_ptr<BasicBlock> newBlock() {
        auto bb = std::make_shared<BasicBlock>();

    }

    //接下来就是重写AstVisitor中所有的visit方法
    std::any visitProg() {
        //设置一些状态变量
        this->asmModule = std::make_shared<AsmModule>();

    }

    std::any visitReturnStatement(ReturnStatement &rtStmt) {
        if(rtStmt.exp != nullptr) {

        }
    }

    std::any visitIfStatement(IfStatement &ifStmt) {
        //初始化if和for要注意BasicBlock的构建
    }

    std::any visitForStatement(ForStatement &forStmt) {
        if(forStmt.init != nullptr) {
            //访问
        }
    }

    std::any visitVariableDecl(VariableDecl &variableDecl) {

    }

    std::any visitBinary(Binary &bi) {

    }

    std::any visitUnary(Unary &u) {

    }

    std::any visitVariable(Variable &variable) {

    }

    std::any visitIntegerLiteral(IntegerLiteral &integerLiteral) {

    }

    std::any visitFloatLiteral(FloatLiteral &floatLiteral) {

    }

    std::any visitStringLiteral(StringLiteral &stringLiteral) {

    }

    std::any visitFunctionCall() {

    }
};

//lower
/*对AsmModule做lower处理
 * 1.把虚拟寄存器转换成物理寄存器
 * 2.把本地变量换算成具体的物理寄存器
 * 3.把抽象的指令转换成具体的指令
 * 4.计算标签名称
 * 5.内存对齐
 * */
class Lower {
public:
    //前一步生成的LIR模型
    std::shared_ptr<AsmModule> asmModule;

    //当前的FunctionSymbol
    std::shared_ptr<FunctionSymbol> functionSym;

    //变量活跃性分析结果

    size_t numParams {0};//当前函数的参数

    //可以通过寄存器传递的参数的最大数量
    size_t MaxXmmRegParams = 8;//
};

/*
 * 控制流图
 * */
class CFG{
public:
    //基本快的列表，第一个和最后一个是图的root
    std::vector<std::shared_ptr<BasicBlock>> bbs;

    //每一个基本块输出的边
    std::map<std::shared_ptr<BasicBlock>, std::vector<std::shared_ptr<BasicBlock>>> edgesOut;
    //每一个基本快输入的边
    std::map<std::shared_ptr<BasicBlock>, std::vector<std::shared_ptr<BasicBlock>>> edgesIn;

    CFG(std::vector<std::shared_ptr<BasicBlock>> &bbs) : bbs(bbs) {
        this->buildCFG();
    }


private:
    void buildCFG() {
        //先开始构建edgesOut
        for (int i = 0; i < bbs.size() - 1; i++) {
            //-1是最后一个基本快不用分析
            auto bb = this->bbs[i];
            std::vector<std::shared_ptr<BasicBlock>> toBBs;
            if() {

            } else {

            }
        }

        //构建edgesIn
        for(auto &bb : edgesOut) {

        }
    }

    //打印基本快的信息
    std::string toString() {
        std::string str;
        str += "bbs:\n";
        for (auto &bb : this->bbs) {
            str += "\t" + bb->getName() + "\n";
        }

        for (auto &item : this->edgesOut) {
            str +=
        }

        for (auto &item : this->edgesIn) {
            auto &bb = item.first;
            auto &fromBBS = item.second;

        }
        return str;
    }
};

class LivenessResult {
public:
    std::map<> liveVars;
    std::map<> initialVars;
};
//变量活跃性分析
class LivenessAnalyzer {
public:
    //对一个AsmModule做变量活跃性分析
    std::shared_ptr<AsmModule> asmModule;
    LivenessAnalyzer() {

    }

    LivenessResult execute() {

    }

    //注意我们主要是对函数和基本块做分析

    //给每一个函数做变量分析
    void analyzeFunction() {

    }

    //给基本快做活跃性分析，是从基本快最后一条指令倒着分析
    bool analyzedBasicBlock() {

    }
};