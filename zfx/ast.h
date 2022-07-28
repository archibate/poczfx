//
// Created by admin on 2022/7/28.
//

#pragma once

namespace zeno::zfx {
    struct AST {
        Token token;
        std::vector<std::uniqueptr<AST>> chs;
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

//整形字面量
    struct IntegerLiteral : public AST {
        int value;//字面量数值
        //构造函数
    };

    //浮点数
    struct FloatLiteral : public AST {
        float value;
    };

    //字符串
    struct StringLiteral : public AST {

    };

}
