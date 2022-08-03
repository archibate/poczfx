想把zfx 做成 lua那样的脚本语言，可以直接嵌入到C++中去，zfx可以调用C++的函数，C++也可以调用zfx函数

`zfx`的词法分析采用的是有限自动机, 通过维护一个CharStream的字符串流，通过`peek`预读一个字符,`next`读一个字符并且移动来解析`Token`
一个`Token`包含`TokenKind`(有这么几种类型, `string` `float`, `int` `vec3`, 操作符， 分隔符), `string` 代表文本内容例如
"+=", `std::any`代表任意类型的内容比如说整数，浮点数字符串,有一些`token`是空`any`
字节码生成思路和`emitAssembly`差不多通过访问 `ast``formart`生成，`ast`是由`parse``token`生成的
最后手工维护一个解释器

```c++
#include "zfx.h
#include "zfxlib.h

int main() {
    //创建zfx虚拟机栈
    ZfxState* l = Zfx_New_State();
    //调用Zfx.h中提供的函数
    
    
    
    zfx_close();
}
```
`Object`是`zfx`中所有变量的抽象定义，他代表了`zfx`中的所有变量
我想把老板张发财中的`context `或者是`Executable`做成对应于`lua`中的`lua_State`
其实就是维护一个全局的栈，保存zfx运行时的信息
zfx 要不要支持字符串，如果支持字符串，我的想法是采用lua的做法，就是在虚拟机的全局数据区维护一张
全局的map<>


zfx的字节码指令大小为32为 从低到高依次为OpCode A B C


zfx需要支持的数学函数有 `abs()` `cos()` `sin()` `ceil()`
`cross()`叉乘 `dot`点乘 `pow()` ''

`zapi.h`是暴露给外部调用的,外部调用者可以