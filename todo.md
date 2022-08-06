想把zfx 做成 lua那样的脚本语言，可以直接嵌入到C++中去，zfx可以调用C++的函数，C++也可以调用zfx函数

`zfx`的词法分析采用的是有限自动机, 通过维护一个CharStream的字符串流，通过`peek`预读一个字符,`next`读一个字符并且移动来解析`Token`
一个`Token`包含`TokenKind`(有这么几种类型, `string` `float`, `int` `vec3`, 操作符， 分隔符), `string` 代表文本内容例如
"+=", `std::any`代表任意类型的内容比如说整数，浮点数字符串,有一些`token`是空`any`
前端有一个要伺候的点是识别`vec3`
字节码生成思路和`emitAssembly`差不多通过访问 `ast``formart`生成，`ast`是由`parse``token`生成的
最后手工维护一个解释器

`Compiler`的做法是这样的，有两个头文件， 一个是`ByteCodeBuilder` 提供`builder` 字节码的一些方法
`Compiler`单元呢是在遍历 `ast`时候调用`builder`方法产生字节码
`Object`在`zfx`中是最基础的对象数据结构, 类似于`Python`的`PyObject`,我想在一些`Object`中保留一些函数指针来进行数值计算
总之`Object`是虚拟机运行时需要的东西
`Object`在头部需要几个标志位,用于以下几个用途比如判断是否需要`gc`

`zfx`中定义一个变量 `variableDecl` : '@'|`$` `Identifier` `=` `singleExpression`
一个`VariableDecl` `ast`节点只需要包含变量类型， 变量名称，初始化部分的值
一个`$T = 10` 会产生 两个`ast`节点 `VariableDecl` : `name`:T , `theType` : `param`  `IntegerLiteral` : 10
支持变量的初始化和定义后，我们就可以支持二元运算和赋值操作
赋值操作是右结合的
先解析赋值表达式，赋值表达式的每一个子节点可以是任意二元运算节点
`$T = $D = $F + 10`
`SingleExpression` : `assignment`
`assignment` : `binary` ('AssignmentOp' , `binary`)*
`binary` : `primary` (BinaryOp primary) 

伺候一下赋值表达式
函数签名`()`


`IfStatement` :
`If` '(' `expression` ')' `statement` (`ElseStatement`) `?`

```c++
//跳过 if 这一个 Token
//判断下一个预读 Token 是否是分隔符 ( 然后解析条件 expression

//解析 forStatement
// fo
```

在`zfx` 中定义 函数加一下 `function` 关键字

`@`是属性,但是他不代表数据类型
`Object`是`zfx`中所有变量的抽象定义，他代表了`zfx`中的所有变量
我想把老板张发财中的`context `或者是`Executable`做成对应于`lua`中的`lua_State`
其实就是维护一个全局的栈，保存zfx运行时的信息
zfx 要不要支持字符串，如果支持字符串，我的想法是采用lua的做法，就是在虚拟机的全局数据区维护一张
全局的map<>


zfx的字节码指令大小为32为 从低到高依次为OpCode A B C


zfx需要支持的数学函数有 `abs()` `cos()` `sin()` `ceil()`
`cross()`叉乘 `dot`点乘 `pow()` ''

`zapi.h`是暴露给外部调用的,外部调用者可以