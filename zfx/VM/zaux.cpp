//
// Created by admin on 2022/7/17.
//

#include <string

//将堆栈索引值转换为正数,如果是负数或者是超出栈的索引那就取栈的top
#define abs_index(L, i) ((i) > 0 || i < ZFX_REGISTRYINDEX ? (i) : zfx_gettop(L))

