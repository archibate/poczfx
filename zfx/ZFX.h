//
// Created by admin on 2022/7/5.
//
#pragma once

#include <stdint.h>
#include <functional>

//如果zfx可以调用cpp写的函数，那么需要做一个转换才能注册到zfx的虚拟机中去
//using Zfx_CFunction = std::function<int()>


enum class Zfx_Type {

};

using Zfx_Number = double;
using Zfx_Integer = int;


//接下来两个函数一共是创建zfx的虚拟机栈，另一个是销毁虚拟机栈

//接下来是关于虚拟机栈的操作



//留给Cpp语言调用zfx的接口

//zfx函数的调用操作接口


//加载和运行zfx函数