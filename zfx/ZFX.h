//
// Created by admin on 2022/7/5.
//
#pragma once

#include <stdint.h>
#include <functional>

//如果zfx可以调用cpp写的函数，那么需要做一个转换才能注册到zfx的虚拟机中去
//using Zfx_CFunction = std::function<int()>
//zfx虚拟机的一些参数
//索引如果为-1的化
#define ZFX_REGISTRYINDEX (-1000)

enum class Zfx_Type {

};

using Zfx_Number = double;
using Zfx_Integer = int;


//接下来两个函数一共是创建zfx的虚拟机栈，另一个是销毁虚拟机栈

//接下来是关于虚拟机栈的操作

extern int zfx_absIndex();

//返回栈中元素的个数,也就是返回栈顶元素的索引
extern int zfx_getTop();

//设置栈顶的位置，高了的话用nil补足
extern void zfx_setTop();

//将指定索引值压入栈中
extern void zfx_pushValue();

//移除掉指定索引上的值
extern void zfx_remove();

//将栈顶的值插入到指定索引位置处
extern void zfx_insert();

//弹出栈顶的值，并将该值设置到指定索引位置处
extern void zfx_replace();

//用来检查栈中是否有足够空间
extern void zfx_checkStack();

//留给Cpp语言调用zfx的接口
extern void zfx_pushNil();

//注意number是浮点数float
extern void zfx_pushNumber();

extern void zfx_pushInteger();

//zfx函数的调用操作接口


//加载和运行zfx函数

extern void zfx_call();