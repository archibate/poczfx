//
// Created by admin on 2022/7/28.
//
#pragma once

#include "scanner.h"
#include <any>
#include <vector>
#include <string>
#include <variant>
#include <map>
#include <memory>
namespace zeno::zfx {
   /*
    * 最顶层的ast节点
    * */
   class AST;

   /*
    * 对AST做遍历的Visitor
    * 这是一个基类，定义了缺省的遍历方式，子类可以覆盖他的实现方法,修改遍历方法
    * */
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
       virtual std::any visit(AST &node, std::string additional = "");

       virtual std::any visitProg(Prog &prog, std::string additional = "");

       virtual std::any visitVariableDecl(VariableDecl &variableDecl, std::string additional = "");

       virtual std::any visitVariableStatement(VariableStatement &variableStatement, std::string additional = "");

       virtual std::any visitFunctionDecl(FunctionDecl &functionDecl, std::string additional = "");

       virtual std::any visitCallSignature(CallSignature &callSignature, std::string additional = "");

       virtual std::any visitParameterList(ParameterList &parameterList, std::string additional = "");

       virtual std::any visitBlock(Block &block, std::string additional = "");

       virtual std::any visitExpressionStatement(ExpressionStatement &expressionStatement, std::string additional = "");

       virtual std::any visitReturnStatement(ReturnStatement &returnStatement, std::string additional = "");

       virtual std::any visitIfStatement(IfStatement &ifStatement, std::string additional = "");

       virtual std::any visitForStatement(ForStatement &forStatement, std::string additional = "");

       virtual std::any visitBinary(Binary &binary, std::string additional = "");

       virtual std::any visitUnary(Unary &unary, std::string additional = "");

       virtual std::any visitIntegerLiteral(IntegerLiteral &integerLiteral, std::string additional = "");

       virtual std::any visitFloatLiteral(FloatLiteral &floatLiteral, std::string additional = "");

       virtual std::any visitStringLiteral(StringLiteral &stringLiteral, std::string additional = "");

       virtual std::any visitFunctionCall(FunctionCall &functionCall, std::string additional = "");

   };

   //打印Ast调试信息
   class AstDumper : public AstVisitor{
   public:
       //重写AstVisitor的方法,打印AST节点的信息
   };


    struct AST {
        Position beginPos; //在Token开始的位置
        Position endPos;   //在Token结束的位置,其实Position 是可以省略的，但是还没想好

        //父节点，初始化为空, 如果为空则代表是根节点
        AST(Position beginPos, Position endPos) :
        beginPos(beginPos), endPos(endPos){

        }

        virtual std::any accept(AstVisitor &visitor, std::string additional) = 0;//AST是纯虚类

        //virtual std::string toString() ;
    };

    /*
     * 语句
     * 子类包括函数声明， 表达式语句
     * */
    struct Statement : public AST {
        Statement(Position beginPos, Position endPos) :
        AST(beginPos, endPos){

        }
    };

    //所有的声明都会对应一个符号
    struct Decl : public AST{
        std::string name;
        Decl(Position beginPos, Position endPos, const std::string &name) :
        AST(Position beginPos, Position endPos), name(name){

        }
    };

    struct Expression : public AST{
        Expression(Position beginPos, Position endPos) :
        AST(beginPos, endPos){

        }

        //表达式的类型
        
    };
    //函数声明节点
    struct FunctionDecl : public Decl {
        std::string name;
        CallSignature callSignature;
        std::shared_ptr<Block> body;//函数体
        std::shared_ptr<Scope> scope; //该函数所对的作用域
        std::shared_ptr<FunctionSymbol> sym;
        std::shared_ptr<FunctionKind> functionKind;
        FunctionDecl () {

        }

        std::any accept(AstVisitor &visitor, std::string additional) {
            return visitor.visitFunctionDecl(*this, additional);
        }
    };

    struct ParameterList : public AST{
        std::vector<VariableDecl> params;
        ParameterList(Position beginPos, Position endPos, std::vector<VariableDecl> &params) :
        {

        }

        std::any accept(AstVisitor &visitor) {
            return visitor.visitParameterList(*this);
        }

    };

    struct Block : public Statement{
        std::vector<std::shared_ptr<Statement>> stmts;
        std::shared_ptr<Scope> scope;//当前作用域
        Block(Position beginPos, Position endPos, std::vector<Statement> &stmts) {

        }

        std::any accept(AstVisitor &visitor, std::string additional) {
            return visitor.visitBlock(*this, additional);
        }
    };

    struct Prog : public Block{
        std::shared_ptr<FunctionSymbol> sym; //一个模块中的所有函数声明
        Prog(Position beginPos, Position endPos, std::vector<std::shared_ptr<AST>> &stmts) {

        }
        std::any accept(AstVisitor &visitor) {
            return visitor.visitProg(*this);
        }
    };
    /*
     * 变量声明语句
     * */

    struct VariableDecl : public Decl {
        //std::string name;//变量名
        //代表Type的Ast
        //变量类型 符号，参数，浮点，整数， 字符串
        std::shared_ptr<VarSymbol> sym;//变量符号 varSymbol
        std::shared_ptr<Expression> init;//变量初始化所用的表达式 init
        std::any accept(AstVisitor &visitor, std::string additional) {
            return visitor.visitVariableDecl(*this, additional);
        }
    };
    struct VariableStatement : public Statement {
        std::shared_ptr<VariableDecl> variableDecl;
        VariableStatement(Position beginPos, Position endPos, std::shared_ptr<AST> variableDecl) :
        Statement(beginPos, endPos), variableDecl(variableDecl){

        }

        std::any accept(AstVisitor &visitor) {
            return visitor.visitVariableStatement(*this, additional);
        }
    };

    //表达式语句就是在表达式后面加一个
    struct ExpressionStmt : public Statement{
        std::shared_ptr<Expression> exp;
        ExpressionStmt() {

        }

        std::any accept(AstVisitor &visitor) {
            return visitor.visitExpressionStatement(*this);
        }
    };

    struct Expression : public AST {
        std::shared_ptr<Type> type; //表达式的类型
        //bool shouldBeLeftValue {false}; 当前位置是否需要一个
        //bool isLeftValue{false}; //是否是左值
        std::any constValue;//本表达式的常量值
        Expression(Position beginPos, Position endPos) :
        AST(beginPos, endPos) {
        }


    };
    struct Binary : public Expression {
       OpCode op;//运算符
       std::shared_ptr<Expression> exp1;//左边表达式
       std::shared_ptr<Expression> exp2;//右边表达式

       Binary(Position beginPos, Position endPos, OpCode op,
              std::shared_ptr<AST> exp1, std::shared_ptr<AST> exp2) : Expression(beginPos, endPos),
              op(op), exp1(exp1), exp2(exp2) {

       }

       std::any accept(AstVisitor &visitor, std::string additional) {
            return visitor.visitBinary(*this, additional);
       }

   };

   class Unary : public Expression {
        //运算符和表达式
        OpCode op;
        std::shared_ptr<AST> exp;//表达式
        bool isPrefix;//判断是前缀还是后缀

        Unary(Position beginPos, Position endPos, OpCode op, std::shared_ptr<AST> exp, bool isPrefix) :
        Expression(beginPos, endPos), op(op), exp(exp), isPrefix(isPrefix){

        }

        std::any accept(AstVisitor &visitor, std::string additional) {
            return visitor.visitUnary(*this, additional);
        }
   };

   struct IfStatement : public Statement {
       std::shared_ptr<AST> condition;
       std::shared_ptr<Statement> stmt;
       std::shared_ptr<Statement> elseStmt;

       IfStatement() {

       }

       std::any accept(AstVisitor &visitor, std::string additional) {
           return visitor.visitIfStatement(*this, additional);
       }
   };

   struct ForStatement : public Statement {
        //for 循环的条件有点多
       ForStatement() {

       }

       std::any accept(AstVisitor &visitor, std::string additional) {
           return visitor.visitForStatement(*this, additional);
       }
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




    //字面量:包含字符串字面量， 整数字面量， 浮点数字面量
    struct Literal : public Expression {
        std::variant<std::string, float, int> value;
        Literal(Position beginPos, Position endPos, std::variant<std::string, float, int>& value) :
        Expression(), value(value){

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

        std::any accept(AstVisitor &visitor, std::string additional) {
             return visitor.visitStringLiteral(*this);
        }
    };

    struct IntegerLiteral : public Literal {
        //在构造函数里将type设置为int
        IntegerLiteral(Position beginPos, ) {

        }

        //将类型设置为int
        int get() const {
            return value.get<int>();
        }

        std::any accept(AstVisitor &visitor, std::string additional) {
            return visitor.visitIntegerLiteral(*this, additional);
        }
    };

    struct FloatLiteral : public Literal {
        //构造函数中将类型设置为float

        //将类型设置为float
        float get() {
            return value.get<float>();
        }

        std::any accept(AstVisitor &visitor, std::string additional) {
            return visitor.visitFloatLiteral(*this, additional);
        }
    };

    //后续还会有null 和 boolean字面量
}
