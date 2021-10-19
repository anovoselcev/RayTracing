#include "bsp_tree.hpp"
#include "../polygon/triangle.hpp"
#include "../polygon/chunk_triangle.hpp"
#include "../geo/plane.hpp"
#include "../geo/line.hpp"

#include <iostream>
#include <sstream>

#include <array>



namespace rytg{


void printIntersection(const Polygon* t, const Polygon* p){
    size_t id1, id2;
    if(Triangle::isTriangle(t))
        id1 = dynamic_cast<const Triangle*>(t)->getID();
    else
        id1 = dynamic_cast<const ChunkTriangle*>(t)->getParentID();

    if(Triangle::isTriangle(p))
        id2 = dynamic_cast<const Triangle*>(p)->getID();
    else
        id2 = dynamic_cast<const ChunkTriangle*>(p)->getParentID();
    std::cout << id1
              << " "
              << id2
              << std::endl;
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
    else{
        Triangle* tr = dynamic_cast<Triangle*>(obj);
        addInternal(root_, tr);
    }
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

void BSPtree::addChunkedNode(Node* leaf, const std::array<Polygon*, 2>& chunks){
    if(chunks[0]){
        leaf->lhs = new Node;
        leaf->lhs->obj = chunks[0];
        num_leafs++;
    }
    if(chunks[1]){
        leaf->rhs = new Node;
        leaf->rhs->obj = chunks[1];
        num_leafs++;
    }
}

void BSPtree::addNode(Node* root, Node* lhs, Node* rhs){
    Triangle* t = nullptr;
    if(lhs && rhs) t = Triangle::mergeChunks(lhs->obj, rhs->obj);
    if(t){
        addInternal(root, t);
        addNode(root, lhs->lhs, lhs->rhs);
        addNode(root, rhs->lhs, rhs->rhs);
        delete lhs;
        delete rhs;
        return;
    }
    if(lhs){
        t = dynamic_cast<Triangle*>(lhs->obj);
        addInternal(root, t);
        addNode(root, lhs->lhs, lhs->rhs);
        delete lhs;
    }
    if(rhs){
        t = dynamic_cast<Triangle*>(rhs->obj);
        addInternal(root, t);
        addNode(root, rhs->lhs, rhs->rhs);
        delete rhs;
    }

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
            if(root->obj->isIntersection(t))
                printIntersection(t, root->obj);

            if(!root->lhs){
                s = SIDE::LHS;
                break;
            }

            root = root->lhs;
        }
        else if(p.isIntersection(*t)){
            // To delete
            if(root->obj->isIntersection(t))
                printIntersection(t, root->obj);

            //findIntersectionAfterAddForChunk(root->lhs, t);
            //findIntersectionAfterAddForChunk(root->rhs, t);
            if(root->lhs){
                if(root->rhs && !ChunkTriangle::isChunks(root->rhs->obj, root->lhs->obj))
                    findIntersectionAfterAddForChunk(root->rhs, t);
                root = root->lhs;
            }
            else if(root->rhs){
                if(root->lhs && !ChunkTriangle::isChunks(root->rhs->obj, root->lhs->obj))
                    findIntersectionAfterAddForChunk(root->lhs, t);
                root = root->rhs;
            }
            else{
                std::array<Polygon*,2> chunks = {nullptr, nullptr};
                if(Triangle::isTriangle(t))
                    chunks = Triangle::splitToChunks(dynamic_cast<Triangle*>(t), p);
                else if(ChunkTriangle::isChunck(t))
                    chunks = ChunkTriangle::splitChunk(dynamic_cast<ChunkTriangle*>(t), p);

                if(chunks[0] && chunks[1]){
                    /*
                    Triangle* par = dynamic_cast<const ChunkTriangle*>(chunks[0])->getParent();
                    if(root->lhs && root->rhs && !ChunkTriangle::isChunks(root->rhs->obj, root->lhs->obj)){
                        findIntersectionAfterAddForChunk(root->lhs, par);
                        findIntersectionAfterAddForChunk(root->rhs, par);
                    }*/
                    addChunkedNode(root, chunks);
                }
                else if(chunks[0]){
                    if(root->lhs) addInternal(root->lhs, dynamic_cast<Triangle*>(chunks[0]));
                    else {
                        findIntersectionAfterAddForChunk(root->rhs, t);
                        addStandartNode(root, SIDE::LHS, chunks[0]);
                    }
                }
                else if(chunks[1]){
                    if(root->rhs)   addInternal(root->rhs, dynamic_cast<Triangle*>(chunks[1]));
                    else{
                        findIntersectionAfterAddForChunk(root->lhs, t);
                        addStandartNode(root, SIDE::RHS, chunks[1]);
                    }
                }
                return;
            }
        }

    }
    addStandartNode(root, s, dynamic_cast<Triangle*>(t));
}

void BSPtree::findIntersectionAfterAddForChunk(Node* side, const Polygon* pol){
    if(side == nullptr) return;
    const Triangle* t = dynamic_cast<const Triangle*>(pol);
    Plane p(*(side->obj));
    if(p.isAbove(*t)){
        side = side->rhs;
    }
    else if(p.isBelow(*t)){
        side = side->lhs;
    }
    else if(p.isOnPlane(*t)){
        // To delete
        if(side->obj->isIntersection(t))
            printIntersection(t, side->obj);
        side = side->lhs;
    }
    else if(p.isIntersection(*t)){
        // To delete
        if(side->obj->isIntersection(t))
            printIntersection(t, side->obj);
        findIntersectionAfterAddForChunk(side->lhs, t);
        findIntersectionAfterAddForChunk(side->rhs, t);
        return;
    }

    return findIntersectionAfterAddForChunk(side, t);
}

}
