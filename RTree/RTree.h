#pragma once

#include <iostream>

using namespace std;

#define RTree_temp template<typename Data_t, typename Elem_t, uint NDims, int NMaxNodes, int NMinNodes>
#define RTree_t RTree<Data_t, Elem_t, NDims, NMaxNodes, NMinNodes>

//
template <typename Data_t, typename Elem_t, uint NDims = 2, int NMaxNodes = 8, int NMinNodes = NMaxNodes/2>
class RTree
{
protected:
    struct Page;

public:
    struct Point;

    RTree();
    virtual ~RTree();

    void insert(Point point, Data_t data);

private:
    Page *root;

//Estructuras primitivas
public:
    struct Point {
        inline Point()                                     {}
        inline Point(Elem_t x)                             {   axes[0] = x; }
        inline Point(Elem_t x, Elem_t y)                   {   axes[0] = x; axes[1] = y;    }
        inline Point(Elem_t x, Elem_t y, Elem_t z)         {   axes[0] = x; axes[1] = y; axes[2] = z;    }

        Elem_t  axes[NDims];
    };
    
protected:
    struct Box {
        Box();

        Point   min,
                max;
    };

    struct Node {
        Node() : page_child(NULL)   {}
        ~Node();

        Box box;
        union {
            Page *page_child;
            Data_t data;
        };
    };

    struct Page {
        Page();
        ~Page();

        inline bool isLeaf()   {   return level == 0;  }

        size_t  size,
                level;
        Node *nodes[NMaxNodes];
    };
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

RTree_temp
void RTree_t::insert(Point point, Data_t data) {
    cout << data << endl;
}

//CONSTRUCTORES Y DESTRUCTORES DE LAS ESTRUCTURAS
RTree_temp
RTree_t::Box::Box() {
    min = max = 0;
}

RTree_temp
RTree_t::Node::~Node() {
    if(page_child)
        delete page_child;
}

RTree_temp
RTree_t::Page::Page() :
    size(0),
    level(0)
{
    for(int i = 0; i < NMaxNodes; ++i)
        nodes[i] = NULL;
}

RTree_temp
RTree_t::Page::~Page() {
    for(int i = 0; i < NMaxNodes; ++i)
        if(nodes[i])
            delete nodes[i];
}


#undef RTREE_TEMPLATE
#undef RTREE_QUAL