//
// Created by admin on 2022/6/30.
//
#include "ByteCodeBuilder.h"

#include <algorithm>
#include <string>

namespace zfx {


    //写一个函数返回字节码长度,因为我们的OpCode是继承自std::u32的所以是四字节

    static int OpCodeLength = 4;

}