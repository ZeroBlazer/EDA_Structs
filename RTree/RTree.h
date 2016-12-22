#pragma once

#include <iostream>

using namespace std;

#define RTree_template template<typename Data_t, typename Elem_t, uint NDims, int NMaxNodes, int NMinNodes>
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
        inline Point()                                     {   for(int i = 0; i < NDims; ++i) axes[i] = 0;  }
        inline Point(Elem_t x)                             {   axes[0] = x; }
        inline Point(Elem_t x, Elem_t y)                   {   axes[0] = x; axes[1] = y;    }
        inline Point(Elem_t x, Elem_t y, Elem_t z)         {   axes[0] = x; axes[1] = y; axes[2] = z;    }

        inline Point& operator=(Point &other) {
            for(int i = 0; i < NDims; ++i)
                axes[i] = other.axes[i];
            return *this;
        }

        //Members
        Elem_t  axes[NDims];
    };
    
protected:
    //Bounding Rectangle
    struct Box {
        Box()   {}

        Point   min,
                max;
    };

    //Cada Nodo en una página
    struct Node {
        Node() : page_child(NULL), hasChild(false)   {}
        Node(Data_t &data);
        ~Node();

        Box box;
        bool hasChild;
        union {
            Page *page_child;
            Data_t data;
        };
    };

    //Página de NMaxNodes Nodos
    struct Page {
        Page();
        ~Page();

        inline bool isLeaf()   {   return level == 0;  }

        void insert(Node *p_dataNode);

        size_t  size,
                level;
        Node *nodes[NMaxNodes];
    };
};

//CONSTRUCTORES Y DESTRUCTORES DE LAS ESTRUCTURAS
RTree_template
RTree_t::RTree()
{
    root = new Page;
}

RTree_template
RTree_t::~RTree()
{
    if(root)
        delete root;
}

RTree_template
RTree_t::Node::
Node(Data_t &_data) :
    hasChild(false)
{
    data = _data;
}

RTree_template
RTree_t::Node::~Node() {
    if(hasChild)
        delete page_child;
    // cout << "Destructor Node correctamente" << endl;
}

RTree_template
RTree_t::Page::Page() :
    size(0),
    level(0)                                //Es hoja cuando se crea
{
    for(int i = 0; i < NMaxNodes; ++i)
        nodes[i] = NULL;
}

RTree_template
RTree_t::Page::~Page() {
    if(level == 0)
    for(int i = 0; i < NMaxNodes; ++i)
        if(nodes[i])
            delete nodes[i];
}

//FUNCIONES
RTree_template
void RTree_t::insert(Point point, Data_t data) {
    auto to_insert = new Node(data);
    to_insert->box.min = point;
    to_insert->box.max = point;
    root->insert(to_insert);
}

RTree_template
void RTree_t::Page::insert(Node *p_dataNode) {
    cout << "Tamaño de página: " << size << endl;
    if(size < NMaxNodes)
        nodes[size++] = p_dataNode;
    else
        cout << "Split" << endl;
}

#undef RTree_templateLATE
#undef RTREE_QUAL