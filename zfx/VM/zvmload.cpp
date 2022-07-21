//
// Created by admin on 2022/7/15.
//
#include "zvm.h"
#include <string.h>

template<typename T>
struct TempBuffer {
    zfx_State* l;
    T* data;
    size_t count;
    TempBuffer(zfx_State* l, size_t count) {

    }

    ~TempBuffer() {

    }

    T& operator[](size_t index) const {

    }

    int zfx_load() {
        //在里面设置proto这一个结构
    }

};