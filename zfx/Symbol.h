//
// Created by admin on 2022/7/26.
//
//关于zfx变量的一些符号属性,
#pragma once
#incldue <string>
#include <any>

/*
 * 符号类型
 * */
enum class SymKind {

};
//注意Symbol 不是@这个sym,而是一个基类一个符号基类
class Symbol {
public:
//有这么几个参数
    std::string name;//变量名，@clr的话 name = clr
    //类型 type
    //SymKind

    Symbol() {

    }

    std::any accept(SymbolVisitor &visitor);
};


class VarSymbol : public Symbol {
public:

};

class FunctionSymbol : Symbol{
public:

};

/*
class Sym : public Symbol{
public:

};
class ParamSym : public Symbol {
public:

};
*/

//由于目前并没有自定义函数， 所以这里的FunctionSymbol 是只代表所有内置的函数


class SymbolVisitor {
public:
    std::any visitVarSymbol() {
    //其实就是打印出sym.name和SymKind
    }

    std::any visitFunctionSymbol() {
//和visitFunctionSymbol差不多
    }
};



//一些系统内置符号
extern std::map<std::string, std::shared_ptr<FunctionSymbol>> built_fun;



