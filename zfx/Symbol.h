//
// Created by admin on 2022/7/26.
//
//关于zfx变量的一些符号属性,
#pragma once
#include <string>
#include <any>
#include <map>
#include <vector>

namespace zeno::zfx {
/*
 * 符号类型
 * */
    enum class SymKind {
        Attribute, Parameter , Variable, Function
    };

    inline std::string SymKindToString(SymKind kind) {
        std::map<SymKind, std::string> kindString {
                {SymKind::Attribute, "Attribute"},
                {SymKind::Parameter, "Parameter"},
                {SymKind::Variable, "Variable"},
                {SymKind::Function, "Function"},
        }

        auto it = kindString.find(kind);
        if (it != kindString.end()) {
            return it->second;
        }
        return "";
    }
//注意Symbol 不是@这个sym,而是一个基类一个符号基类
    class Symbol {
    public:
//有这么几个参数
        std::string name;//变量名，@clr的话 name = clr
        Type type; //这里的Type,举个例子来说就是@clr 那他的类型就是vec3 float
        SymKind kind;

        Symbol(const std::string &name, Type type, SymKind kind) :
        name(name), type(type), kind(kind){

        }

        virtual std::any accept(SymbolVisitor &visitor) = 0; //让继承他的AttributeSymbol和FunctionSymbol去重写他
    };

//@, $, 变量
    class VarSymbol : public Symbol {
    public:
        VarSymbol() : {

        }

        std::any accept(SymbolVisitor &visitor) override {
            return visitor.visitVarSymbol();
        }
    };

    class FunctionSymbol : Symbol {
    public:
        std::vector<VarSymbol> vars;//本地变量的列表

        uint32_t opStackSize = 10;  //操作数栈的大小

        std::vector<uint8_t> byteCode;

        FunctionDecl *decl;//存放AST， 作为代码运行

        FunctionSymbol()  {

        }

        std::any accept(SymbolVisitor &visitor) {
            return visitor.visitFunctionSymbol(this);
        }

        //获取参数数量
        uint32_t getNumParams() {

        }
    };


    class SymbolVisitor {
    public:
        std::any visitVarSymbol() {

            return std::any();
        }

        std::any visitFunctionSymbol() {

            return std::any();
        }
    };


    //一些系统内置符号
    extern std::map<std::string, std::shared_ptr<FunctionSymbol>> built_fun;
}





