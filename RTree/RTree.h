#pragma once

#include <iostream>

using namespace std;

#define RTree_temp template<typename Data_t, int NMaxNodes, int NMinNodes>
#define RTree_t RTree<Data_t, NMaxNodes, NMinNodes>

template <typename Data_t, int NMaxNodes = 3, int NMinNodes = NMaxNodes/2>
class RTree
{
protected:
    struct Node;

public:
    RTree();
    ~RTree();

private:
    
};

RTree_temp
RTree_t::RTree()
{
}

RTree_temp
RTree_t::~RTree()
{
}

#undef RTREE_TEMPLATE
#undef RTREE_QUAL