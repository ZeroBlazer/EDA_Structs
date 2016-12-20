#pragma once

#include <iostream>

using namespace std;

#define RTree_temp template<typename Data_t, typename Elem_t, size_t NDims, int NMaxNodes, int NMinNodes>
#define RTree_t RTree<Data_t, Elem_t, NDims, NMaxNodes, NMinNodes>

template <typename Data_t, typename Elem_t, size_t NDims = 2, int NMaxNodes = 3, int NMinNodes = NMaxNodes/2>
class RTree
{
protected:
    struct Page;

public:
    RTree();
    virtual ~RTree();

    void insert();

    struct Box {
        Elem_t  min[NDims],
                max[NDims];
    };

    struct Node {
        Box box;
        union {
            Page *page_child;
            Data_t data;
        };
    };

    struct Page {
        bool isLeaf()   {   return level == 0;  }

        size_t size;
        size_t level;
    };

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