//
// Created by admin on 2022/7/11.
//
//描述虚拟机栈
#pragma once

#include "../Object.h"


struct zfx_State {
    std::uint8_t status;
    Object top;
    Object base;
    Object stack_last;
    Object stack;

    int stackSize;
}