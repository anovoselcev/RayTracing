#include "bsp_tree.hpp"
#include "../polygon/triangle.hpp"
#include "../polygon/chunk_triangle.hpp"
#include "../geo/plane.hpp"
#include "../geo/line.hpp"

#include <iostream>
#include <sstream>

#include <array>



namespace rytg{

std::string printPoint(Point p){
    std::stringstream ss;
    ss << "(" << p.x << "," << p.y << "," << p.z << ")";
    return ss.str();
}

std::string printTriangle(const Triangle* t){
    std::stringstream ss;
    ss << "{" << printPoint(t->getPoint(0)) << "," << printPoint(t->getPoint(1)) << "," << printPoint(t->getPoint(2)) << "}";
    return ss.str();
}

std::string printTriangle(const Polygon* p){
    if(const Triangle* t = dynamic_cast<const Triangle*>(p))
        return printTriangle(t);
    else if(const ChunkTriangle* ch = dynamic_cast<const ChunkTriangle*>(p))
        return printTriangle(ch->getParent());
    return std::string{};
}

void printIntersection(const Polygon* t, const Polygon* p){
    std::cout << "Intersection: "
              << printTriangle(t)
              << "---"
              << printTriangle(p)
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
        Node* save_lhs = leaf->lhs;
        Node* save_rhs = leaf->rhs;
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
        addNode(leaf, save_lhs, save_rhs);
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
                std::cout << "On plane" << std::endl;
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

                std::array<Polygon*,2> chunks = {nullptr, nullptr};
                if(Triangle::isTriangle(t))
                    chunks = Triangle::splitToChunks(dynamic_cast<Triangle*>(t), p);
                else if(ChunkTriangle::isChunck(t))
                    chunks = ChunkTriangle::splitChunk(dynamic_cast<ChunkTriangle*>(t), p);

                if(chunks[0] && chunks[1]){
                    findIntersectionAfterAddForChunk(root->lhs, t);
                    findIntersectionAfterAddForChunk(root->rhs, t);
                    addChunkedNode(root, chunks);
                }
                else if(chunks[0]){
                    if(root->lhs) addInternal(root->lhs, dynamic_cast<Triangle*>(chunks[0]));
                    else {
                        addStandartNode(root, SIDE::LHS, chunks[0]);
                        findIntersectionAfterAddForChunk(root->rhs, t);
                    }
                }
                else if(chunks[1]){
                    if(root->rhs)   addInternal(root->rhs, dynamic_cast<Triangle*>(chunks[1]));
                    else{
                        addStandartNode(root, SIDE::RHS, chunks[1]);
                        findIntersectionAfterAddForChunk(root->lhs, t);
                    }
                }
                return;
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
