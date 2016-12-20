#pragma once

#include <iostream>

using namespace std;

#define RTree_temp template<typename Data_t, typename Elem_t, size_t NDims, int NMaxNodes, int NMinNodes>
#define RTree_t RTree<Data_t, Elem_t, NDims, NMaxNodes, NMinNodes>

template <typename Data_t, typename Elem_t, size_t NDims = 2, int NMaxNodes = 8, int NMinNodes = NMaxNodes/2>
class RTree
{
protected:
    struct Page;

public:
    struct Point;

    RTree();
    virtual ~RTree();

    // void insert()
    void insert(Point point, Data_t data) 
    {
        cout << data << endl;
    }

    struct Point {
        Point()                                     {}
        Point(Elem_t x)                             {   axes[0] = x; }
        Point(Elem_t x, Elem_t y)                   {   axes[0] = x; axes[1] = y;    }
        Point(Elem_t x, Elem_t y, Elem_t z)         {   axes[0] = x; axes[1] = y; axes[2] = z;    }

        Elem_t  axes[NDims];
    };
    
protected:
    struct Box {
        Point   min,
                max;
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
    Page *root;
};

RTree_temp
RTree_t::RTree()
{
    root = new Page;
    root->level = 0;        //Es hoja cuando se crea
}

RTree_temp
RTree_t::~RTree()
{
    if(root)
        delete root;
}

#undef RTREE_TEMPLATE
#undef RTREE_QUAL