#include "scene/bsp_tree.hpp"
#include "polygon/triangle.hpp"
#include "polygon/chunk_triangle.hpp"
#include "geo/plane.hpp"
#include "geo/line.hpp"

#include <sstream>

#include <array>


namespace rytg{

BSPtree::BSPtree(std::ostream& os) : os_(os){}

BSPtree::BSPtree(const std::vector<Triangle>& c){
    generate(c);
}

BSPtree::~BSPtree(){
    for(const auto& el : ids_)
        os_ << el << "\n";
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
        root_->id = top_id++;
        num_leafs = 1;
    }
    else addInternal(root_, obj);
}

void BSPtree::addStandartNode(Node* leaf, SIDE s , Polygon* obj, size_t id){
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
    if(id != 0)
        leaf->id = id;

    else
        leaf->id = top_id++;
    leaf->obj = obj;
    num_leafs++;
}

void BSPtree::addInternal(Node* root, Polygon* t, size_t id){
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

            if(root->obj->isIntersection(t) && !ChunkTriangle::isSameParent(t, root->obj)){
                printIntersection(root->id);
                printIntersection(top_id);
            }

            if(!root->lhs){
                s = SIDE::LHS;
                break;
            }

            root = root->lhs;
        }
        else if(p.isIntersection(*t)){
            // To delete

           if(root->obj->isIntersection(t) && !ChunkTriangle::isSameParent(t, root->obj)){
                printIntersection(root->id);
                printIntersection(top_id);
           }

            std::array<Polygon*,2> chunks = split(t, p);

            if(chunks[0]){
                if(root->lhs) addInternal(root->lhs, chunks[0], top_id);
                else          addStandartNode(root, SIDE::LHS, chunks[0], top_id);
            }
            if(chunks[1]){
                if(root->rhs)   addInternal(root->rhs, chunks[1], top_id);
                else            addStandartNode(root, SIDE::RHS, chunks[1], top_id);
            }

            if(Triangle::isTriangle(t) && id == 0)
                top_id++;
            return;
        }

    }
    addStandartNode(root, s, t, id);
}

std::array<Polygon*, 2> BSPtree::split(Polygon* p, const Plane& pl){
    if(Triangle::isTriangle(p))
        return Triangle::splitToChunks(dynamic_cast<Triangle*>(p), pl);
    else if(ChunkTriangle::isChunck(p))
        return ChunkTriangle::splitChunk(dynamic_cast<ChunkTriangle*>(p), pl);
    return {nullptr, nullptr};
}

void BSPtree::printIntersection(size_t id){
    ids_.insert(id);
}
}
