#include "bsp_tree.hpp"
#include "../polygon/triangle.hpp"
#include "../polygon/chunk_triangle.hpp"
#include "../geo/plane.hpp"
#include "../geo/line.hpp"

#include <iostream>
#include <sstream>

#include <array>
#include <map>
#include <set>


namespace rytg{

class IntersectionMap{

    std::map<size_t, std::set<size_t>> i_map;

    void insert_internal(size_t key, size_t val){
        if(i_map[key].find(val) == i_map[key].end()){
            std::cout << key << " " << val << std::endl;
            i_map[key].insert(val);
        }
    }

public:

    void insert(size_t lhs, size_t rhs){
        if(i_map.find(lhs) != i_map.end())
            insert_internal(lhs, rhs);
        else if(i_map.find(rhs) != i_map.end())
            insert_internal(rhs, lhs);
        else{
            insert_internal(lhs, rhs);
        }
    }
};


void printIntersection(const Polygon* t, const Polygon* p){
    static IntersectionMap im;
    size_t id1, id2;
    if(Triangle::isTriangle(t))
        id1 = dynamic_cast<const Triangle*>(t)->getID();
    else
        id1 = dynamic_cast<const ChunkTriangle*>(t)->getParentID();

    if(Triangle::isTriangle(p))
        id2 = dynamic_cast<const Triangle*>(p)->getID();
    else
        id2 = dynamic_cast<const ChunkTriangle*>(p)->getParentID();

    im.insert(id1, id2);
}

BSPtree::BSPtree(const std::vector<Triangle>& c){
    generate(c);
}

BSPtree::~BSPtree(){
    delNode(root_);
}

void BSPtree::delNode(Node* n){
    if(!n) return;
    num_leafs--;
    auto lhs = n->lhs;
    auto rhs = n->rhs;
    delete n->obj;
    delete n;
    delNode(lhs);
    delNode(rhs);
}

void BSPtree::balanced(){

}

void BSPtree::generate(const std::vector<Triangle>& c){
    for(const auto& obj : c){
        Polygon* trig = new Triangle(obj);
        add(trig);
    }
}

void BSPtree::add(Polygon* obj){
    if(root_ == nullptr){
        root_ = new Node;
        root_->obj = obj;
        num_leafs = 1;
    }
    else addInternal(root_, obj);
}

void BSPtree::addStandartNode(Node* leaf, SIDE s , Polygon* obj){
    if(s == SIDE::LHS){
        leaf->lhs = new Node;
        leaf = leaf->lhs;
    }
    else if(s == SIDE::RHS){
        leaf->rhs = new Node;
        leaf = leaf->rhs;
    }
    else{
        return;
    }
    leaf->obj = obj;
    num_leafs++;
}

void BSPtree::addInternal(Node* root, Polygon* t){
    SIDE s = SIDE::UNKNOWN;
    while(root){
        Plane p(*(root->obj));
        if(p.isAbove(*t)){
            if(!root->rhs){
                s = SIDE::RHS;
                break;
            }
            root = root->rhs;
        }
        else if(p.isBelow(*t)){
            if(!root->lhs){
                s = SIDE::LHS;
                break;
            }

            root = root->lhs;
        }
        else if(p.isOnPlane(*t)){
            // To delete
            if(root->obj->isIntersection(t) && !ChunkTriangle::isSameParent(t, root->obj))
                printIntersection(t, root->obj);

            if(!root->lhs){
                s = SIDE::LHS;
                break;
            }

            root = root->lhs;
        }
        else if(p.isIntersection(*t)){
            // To delete
           if(root->obj->isIntersection(t) && !ChunkTriangle::isSameParent(t, root->obj))
                printIntersection(t, root->obj);

            std::array<Polygon*,2> chunks = {nullptr, nullptr};
            if(Triangle::isTriangle(t))
                chunks = Triangle::splitToChunks(dynamic_cast<Triangle*>(t), p);
            else if(ChunkTriangle::isChunck(t))
                chunks = ChunkTriangle::splitChunk(dynamic_cast<ChunkTriangle*>(t), p);

            if(chunks[0]){
                if(root->lhs) addInternal(root->lhs, chunks[0]);
                else          addStandartNode(root, SIDE::LHS, chunks[0]);
            }
            if(chunks[1]){
                if(root->rhs)   addInternal(root->rhs, chunks[1]);
                else            addStandartNode(root, SIDE::RHS, chunks[1]);
            }
            return;
        }

    }
    addStandartNode(root, s, t);
}

}
