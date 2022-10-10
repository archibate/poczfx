//
// Created by admin on 2022/8/24.
//

#pragma once
#include<vector>

//生成基于图的IR
class Graph {

};

class IRNode {
    //在每一个IRNode节点中自动维护Use def链

    std::uint32_t index = -1;//当前节点的序号，未被正式赋值之前默认为-1
    //该节点的输入
    IRNode &inputs() {

    }
    //使用该节点的节点，形成ud链，自动维护
    std::vector<IRNode> uses;
};
