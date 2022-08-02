
//
// Created by admin on 2022/7/11.
//
//主要实现两个接口,一个是从虚拟机栈中取出一个Object
//另一个是将Object插入到虚拟机栈中
#pragma once

#include "../Object.h

extern const Object* zfx_toObject();
extern void zfx_pushObject();
