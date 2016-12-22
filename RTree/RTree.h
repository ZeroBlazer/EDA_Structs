#pragma once

#include <iostream>

using namespace std;

#define RTree_template template<typename Data_t, typename Elem_t, uint NDims, int NMaxNodes, int NMinNodes>
#define RTree_t RTree<Data_t, Elem_t, NDims, NMaxNodes, NMinNodes>

#define _ZOMBIE_
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
        inline Point()                                     {   for(uint i = 0; i < NDims; ++i) axes[i] = 0;  }
        inline Point(Elem_t x)                             {   axes[0] = x; }
        inline Point(Elem_t x, Elem_t y)                   {   axes[0] = x; axes[1] = y;    }
        inline Point(Elem_t x, Elem_t y, Elem_t z)         {   axes[0] = x; axes[1] = y; axes[2] = z;    }
        // Point(Point &to_copy)                              {   for(uint i = 0; i < NDims; ++i) axes[i] = to_copy.axes[i];  }

        inline Point& operator=(Point &other) {
            for(uint i = 0; i < NDims; ++i)
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
        Box(Point &_min, Point &_max) : min(_min),  max(_max)   {}

        bool operator<(Box &_othr);
        
        Box& operator+(Box &_othr) {
            Box result();
            for(uint i = 0; i < NDims; ++i) {
                result.min.axes[i] = min.axes[i] < _othr.min.axes[i] ? min.axes[i] : _othr.min.axes[i];
                result.max.axes[i] = max.axes[i] > _othr.max.axes[i] ? max.axes[i] : _othr.max.axes[i];
            }

            return result;
        }

        Box& operator+=(Box &_othr) {
            for(uint i = 0; i < NDims; ++i) {
                if(_othr.min.axes[i] < min.axes[i]) min.axes[i] = _othr.min.axes[i];
                if(_othr.max.axes[i] > max.axes[i]) max.axes[i] = _othr.max.axes[i];
            }

#ifdef _ZOMBIE_
    for(uint i = 0; i < NDims; ++i) {
        cout << min.axes[i] << "\t";
    }
    cout << endl;
#endif // _ZOMBIE_

            return *this;
        }

        Point   min,
                max;
    };

    //Cada Nodo en una página
    struct Node {
        Node() : page_child(NULL), hasChild(false)   {}
        Node(Data_t &data, Point &pos);
        ~Node();

        bool hasChild;

        union {
            struct {
                Data_t  dat;
                Point   pos;
            } data;
            Page *page_child;
        };
    };

    //Página de NMaxNodes Nodos
    struct Page {
        Page();
        ~Page();

        inline bool isLeaf()   {   return level == 0;  }

        void insert(Box &_bound, Node *p_dataNode);

        size_t  size,
                level;
        Box box;
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
RTree_t::Node::Node(Data_t &_data, Point &_pos) :
    hasChild(false)
{
    data.dat = _data;
    data.pos = _pos;
}

RTree_template
RTree_t::Node::~Node() {
    if(hasChild)
        delete page_child;
#ifdef _ZOMBIE_
    cout << data.dat << endl;
#endif // _ZOMBIE_
}

RTree_template
RTree_t::Page::Page() :
    size(0),
    level(0)                                //Es hoja cuando se crea
{
    for(uint i = 0; i < NMaxNodes; ++i)
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
    // auto to_insert = new Node(data);
    // root->insert(to_insert);
    Box bound(point, point);
    root->insert(bound, new Node(data, point));
}

RTree_template
void RTree_t::Page::insert(Box &_bound, Node *p_dataNode) {
    cout << "Tamaño de página: " << size << endl;
    if(size < NMaxNodes) {
        //Inicializa los tamaños del bounding rectangle
        if(size == 0) {
            box.min = _bound.min;
            box.max = _bound.max;
        }

        nodes[size++] = p_dataNode;
        //Adaptación del bounding rectangle a la medida
        box += _bound;
            // for(uint i = 0; i < NDims; ++i) {       
            //     if(box.min.axes[i] > _bound.axes[i]) box.min.axes[i] = _bound.axes[i];
            //     if(box.max.axes[i] < _bound.axes[i]) box.max.axes[i] = _bound.axes[i];
            // }
    }
    else
        cout << "split" << endl;
}


#undef RTree_templateLATE
#undef RTREE_QUAL