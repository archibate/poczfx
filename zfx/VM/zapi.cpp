//
// Created by admin on 2022/7/11.
//
//一些对于虚拟机找操作的接口

#include "zapi.h"
#include "zstate.h"
//获取栈中下标为index的元素
static Object* index2addr(zfx_State* L, int index) {
    if (index > 0) {
        Object* o = L->base + (index - 1);

    } else if () {

    } else {

    }

}

void zfx_getTop() {

}

void zfx_setTop() {

};

void zfx_remove() {

}

void zfx_insert() {

}

void zfx_replace() {

}

void lua_pushValue() {

}

int zfx_type() const {

}

const char* zfx_TypeName() const {

}

int lua_equal() {

}


int zfx_checkStack() {
    //用来判断栈是否溢出了

}

//从一个from移动到to
void zfx_xmove() {

}

//留给其他语言的接口
void zfx_pushNil(zfx_State* l) {

}

void zfx_pushNumber(zfx_State* l, float n) {
    setnvalue(l->top, n);
    //压进去
    return;
}

void zfx_pushInteger(zfx_State* l, int n) {
    //设置栈顶得值
    setnvalue(l->top, n);
    //压进去
    return ;
}

void zfx_pushVector(zfx_State* l, float x, float y, float z) {
    setvvalue(l->top, x, y, z, 0.0f);
    //压进去
    return ;
}


