#pragma once

#include <iostream>

using namespace std;

#define RTree_template template<typename Data_t, typename Elem_t, uint NDims, int NMaxNodes, int NMinNodes>
#define RTree_t RTree<Data_t, Elem_t, NDims, NMaxNodes, NMinNodes>

#define _ZOMBIE_

uint pageIDr = 0;

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
//        Box(Box &_cpy) : min(_cpy.min),  max(_cpy.max)          {}

        Elem_t area();

        bool operator<(Box _othr) {
            #ifdef _ZOMBIE_
                cout << "Areas: " << area() << " vs " << _othr.area() << endl;
            #endif // _ZOMBIE_
            return area() < _othr.area();
        }
        
        Box operator+(Box &_othr) {
            Box result;

            for(uint i = 0; i < NDims; ++i) {
                result.min.axes[i] = min.axes[i];
                result.max.axes[i] = max.axes[i];
            }
            result += _othr;
//            for(uint i = 0; i < NDims; ++i) {
//                result.min.axes[i] = min.axes[i] < _othr.min.axes[i] ? min.axes[i] : _othr.min.axes[i];
//                result.max.axes[i] = max.axes[i] > _othr.max.axes[i] ? max.axes[i] : _othr.max.axes[i];
//            }
            return result;
        }

        Box& operator+=(Box _othr) {
            for(uint i = 0; i < NDims; ++i) {
                if(_othr.min.axes[i] < min.axes[i]) min.axes[i] = _othr.min.axes[i];
                if(_othr.max.axes[i] > max.axes[i]) max.axes[i] = _othr.max.axes[i];
            }

            // #ifdef _ZOMBIE_
            //     cout << "(";
            //     for(uint i = 0; i < NDims; ++i) {
            //         cout << min.axes[i] << "\t";
            //     }
            //     cout << ")\t(";
            //     for(uint i = 0; i < NDims; ++i) {
            //         cout << max.axes[i] << "\t";
            //     }
            //     cout << ")\n";
            // #endif // _ZOMBIE_

            return *this;
        }

        Point   min,
                max;
    };

    //Cada Nodo en una página
    struct Node {
        // Node() : page_child(NULL), hasChild(false)   {}
        Node() : child(NULL) {}        
        Node(Data_t &data, Point &pos);
        ~Node();

        Box nodeBox() {
            if(child)
                return child->box;
            return Box(pos, pos);
        }

        Data_t  data;
        Point   pos;
        Page    *child;
    };

    //Página de NMaxNodes Nodos
    struct Page {
        Page();
        ~Page();

        inline bool isLeaf()    {   return level == 0;  }

        inline bool notFull()   {   return size < NMaxNodes;  }

        void partition(Page *part1, Page *part2);

        void partitionTo(Page *part);

        void rebound();

        void insert(Box _bound, Node *p_dataNode, bool _toReallocate = false);

        inline Page*& children(uint pos)   { return nodes[pos]->child;     }

        uint    size,
                level;
        Box box;
        Node *nodes[NMaxNodes];
        Page *parent;
        int     ID;
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
    #ifdef _ZOMBIE_
        cout << "Tree killed" << endl;
    #endif // _ZOMBIE_
}

RTree_template
RTree_t::Node::Node(Data_t &_data, Point &_pos) :
    child(NULL)
{
    data = _data;
    pos = _pos;
}

RTree_template
RTree_t::Node::~Node() {
    if(child)
        delete child;
#ifdef _ZOMBIE_
    cout << data << endl;
#endif // _ZOMBIE_
}

RTree_template
RTree_t::Page::Page() :
    size(0),
    level(0),
    ID(pageIDr++),
    parent(NULL)                                //Es hoja cuando se crea
{
    for(uint i = 0; i < NMaxNodes; ++i) {
        nodes[i] = NULL;
//        children(i) = NULL;
    }
}

RTree_template
RTree_t::Page::~Page() {
    // if(level == 0)
    for(int i = 0; i < NMaxNodes; ++i)
        if(nodes[i])    delete nodes[i];
    #ifdef _ZOMBIE_
        cout << "Page killed" << endl;
    #endif // _ZOMBIE_
}

//FUNCIONES
RTree_template
Elem_t RTree_t::Box::area() {
    Elem_t area = 1;
    for(uint i = 0; i < NDims; ++i) {
        area *= max.axes[i] - min.axes[i];
    }
    return area;
}

RTree_template
void RTree_t::insert(Point point, Data_t data) {
    Box bound(point, point);
    root->insert(bound, new Node(data, point));
}

RTree_template
void RTree_t::Page::rebound() {
//    if(size == 0)   return;
    Point _tmp1 = nodes[0]->nodeBox().min,
          _tmp2 = nodes[0]->nodeBox().max;
    box.min = _tmp1;
    box.max = _tmp2;
    for(uint i = 1; i < size; i++)
        box += nodes[i]->nodeBox();
}

RTree_template
void RTree_t::Page::partition(Page *part1, Page *part2) {
    for(uint i = 0; i < NMaxNodes;) {
        if(i < NMinNodes)
            part1->insert(nodes[i]->nodeBox(), nodes[i]);
        else
            part2->insert(nodes[i]->nodeBox(), nodes[i]);
        children(i) = NULL;
        nodes[i++] = NULL;
    }
    size = 0;
}

RTree_template
void RTree_t::Page::partitionTo(Page *part) {
    for(uint i = NMinNodes; i < NMaxNodes;) {
        part->insert(nodes[i]->nodeBox(), nodes[i]);
        nodes[i++] = NULL;
        children(i++) = NULL;
    }
    size = NMinNodes;
    rebound();
}

RTree_template
void RTree_t::Page::insert(Box _bound, Node *p_dataNode, bool _toReallocate) {
    if(level > 0) {
        if(_toReallocate) {
            nodes[size++] = p_dataNode;
            box += _bound;                  //Adaptación del bounding rectangle a la medida
            return;
        }
        auto min_chld = children(0);
        for(uint i = 1; i < size; ++i) {
            if((children(i)->box) + _bound < (min_chld->box) + _bound)
//            if(min_chld->box < children(i)->box)
                min_chld = children(i);
        }
        box += _bound;
        min_chld->insert(_bound, p_dataNode);

        return;
    }

    if(size < NMaxNodes) {
        //Inicializa los tamaños del bounding rectangle
        if(size == 0) {
            box.min = _bound.min;
            box.max = _bound.max;
        }

        nodes[size++] = p_dataNode;
        box += _bound;                  //Adaptación del bounding rectangle a la medida
    }
    else {
        if(parent && parent->notFull()) {    //Preguntar al padre si tiene espacio
            Page *partition = new Page();
            partitionTo(partition);
            Node *newNode = new Node();
            newNode->child = partition;
//            parent->nodes[parent->size++] = newNode;
            partition->insert(_bound, p_dataNode);
            parent->insert(newNode->nodeBox(), newNode, true);
//            parent->children((parent->size)-1) = partition;
        }
        else {
            Page    *partition1 = new Page(),   *partition2 = new Page();
            partition(partition1, partition2);      //Solve children here (partition don't have children)
            Node    *newNode1 = new Node(),     *newNode2 = new Node();
            newNode1->child = partition1;       newNode2->child = partition2;
            this->insert(newNode1->nodeBox(), newNode1);    this->insert(newNode2->nodeBox(), newNode2);
            children(0) = partition1;                       children(1) = partition2;
            partition1->parent = this;                      partition2->parent = this;
            ++level;        //El árbol aumenta su altura
            this->insert(_bound, p_dataNode);
        }
    }
        
}

#undef RTree_templateLATE
#undef RTREE_QUAL
