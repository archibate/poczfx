//
// Created by admin on 2022/7/28.
//
#pragma once

#include "scanner.h"
#include <any>
#include <vector>
#include <string>
#include <variant>

namespace zeno::zfx {
   /*
    * 最顶层的ast节点
    * */
   class AST;
   class AstVisitor {
   public:
       //对抽象类的访问
       //对于相应的具体类，会调用visitor合适的具体方法

       //获取该AST节点所属哪一个FunctionDecl
       std::any getEnclosingFunctionDecl(AST &node) {

       }

       //获取该节点所属的作用域Scope
       std::any getEnclosingScope() {

       }
       virtual std::any visit(AST &node);

       virtual std::any visitProg();

       virtual std::any visitVariableDecl();

       virtual std::any visitVariableStatement();

       virtual std::any visitFunctionDecl();

       virtual std::any visitCallSignature();

       virtual std::any visitParameterList();

       virtual std::any visitBlock();

       virtual std::any visitExpressionStatement();

       virtual std::any visitReturnStatement();

       virtual std::any visitIfStatement();

       virtual std::any visitForStatement();

       virtual std::any visitBinary();

       virtual std::any visitUnary();

       virtual std::any visitIntegerLiteral();

       virtual std::any visitFloatLiteral();

       virtual std::any visitStringLiteral();

       virtual std::any visitFunctionCall();

   };

   //打印Ast调试信息
   class AstDumper : public AstVisitor{
   public:
       //重写AstVisitor的方法,打印AST节点的信息
   };


    struct AST {
        //在Token开始的位置
        //在Token结束的位置

        //父节点，初始化为空, 如果为空则代表是根节点
        AST() {

        }

        virtual std::any accept(AstVisitor &visitor) = 0;//AST是纯虚类

        //virtual std::string toString() ;
    };

    /*
     * 语句
     * 子类包括函数声明， 表达式语句
     * */
    struct Statement : public AST {
        Statement() {

        }
    };

    //所有的声明都会对应一个符号
    struct Decl : public AST{
        std::string name;
        Decl() {

        }
    };

    //函数声明节点
    struct FunctionDecl : public Decl {
        std::string name;
        CallSignature callSignature;
        Block body;
        Scope scope;
        FunctionSymbol sym;
        FunctionKind functionKind;
        FunctionDecl () {

        }

        std::any accept(AstVisitor &visitor) {

        }
    };

    struct ParameterList : public AST{
        std::vector<VariableDecl> params;
        ParameterList() {

        }

        std::any accept(AstVisitor &visitor) {

        }

    };

    struct Block : public Statement{

    };
    /*
     * 变量声明语句
     * */
    struct VariableStatement : public Statement {
        VariableDecl variableDecl;
        std::any accept(AstVisitor &visitor) {
            //返回visitor调用的方法
        }
        VariableStatement() {

        }
    };

    struct VariableDecl : public Decl {
        //代表Type的Ast节点
        //变量类型 符号，参数，浮点，整数， 字符串
        //变量符号 varSymbol
        //变量初始化所用的表达式 init
        std::any accept(AstVisitor &visitor) {
            //调用visitor方法
        }
    };

    //表达式语句就是在表达式后面加一个
    class ExpressionStmt : public Statement{

    };


   class Binary : public Expression {
       //运算符
       //左边表达式
       //右边表达式
       std::any accept(AstVisitor &visitor) {

       }

   };

   class Unary : public Expression {
        //运算符和表达式
   };
//$
    struct AstParm : public AST {
        std::string name;//同理如果是$F,那么string就是“F”，同理如果$有初始值的话那么也需要一个类型type和value
        //同里在parser的visit时，我们也是调用一个构造函数来构造这一个节点
        //一个Parm 和一个Sym ast节点有这么些内容 name 比如"clr" "pos" "F" 类型:vec3, int float, string 如果有初始值那么会加一个value
    };


//@节点
    struct AstSym : public AST {
        std::string name;//属性名字比如是clr的话就是“clr”,
        //我们需要添加两个类型 @pos = vec3(3, 2, 1)，那么需要 一个type:三维，浮点，整数，字符串 string，然后一个value,value代表一个初始值
        //最后我们在visit时候调用这个AST节点的构造函数
    };




    //字面零:包含字符串字面零， 整数字面零， 浮点数字面量
    struct Literal : public Expression {
        std::variant<std::string, float, int> value;
        Literal() {

        }

        std::string toString() {

        }
    };

    //字符串
    struct StringLiteral : public Literal {
        //在构造函数中将类型设置为string

        std::string get() const {
            return value.get<std::string>();
        }

        std::any accept(AstVisitor &visitor) {
             return visitor.visitStringLiteral(this);
        }
    };

    struct IntegerLiteral : public Literal {
        //在构造函数里将type设置为int

        int get() const {
            return value.get<int>();
        }

        std::any accept(AstVisitor &visitor) {
            return visitor.visitIntegerLiteral(this);
        }
    };

    struct FloatLiteral : public Literal {
        //构造函数中将类型设置为float

        float get() {
            return value.get<float>();
        }

        std::any accept(AstVisitor &visitor) {
            return visitor.visitFloatLiteral();
        }
    };

    //后续还会有null 和 boolean字面量
}
