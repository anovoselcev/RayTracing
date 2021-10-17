#include "bsp_tree.hpp"
#include "../polygon/triangle.hpp"
#include "../polygon/chunk_triangle.hpp"
#include "../geo/plane.hpp"
#include "../geo/line.hpp"

#include <iostream>
#include <sstream>




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

        BSPtree::BSPtree(const std::vector<Triangle>& c){
            double result;

            std::cout << "1" << std::endl;
            /*
            Triangle trig = c[0];
            Point p1 = trig.getPoint(0);
            Point p2 = trig.getPoint(1);
            Point p3 = trig.getPoint(2);
            */
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

        void BSPtree::generate(const std::vector<Triangle>& c){
            // тут вроде используется механизм с++, когда без счетчика попеременно в obj присваиваются элементы ряда с
            for(const auto& obj : c){
                // вот тут не особо понял, что происходит
                Polygon* trig = new Triangle(obj);
                std::cout << "2" << std::endl;
                add(trig);
            }
        }

        void BSPtree::add(Polygon* obj){
            std::cout << "3" << std::endl;
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

        void BSPtree::addStandartNode(Node* leaf, Triangle* obj){
            leaf = new Node;
            leaf->obj = obj;
            num_leafs++;
        }

        void BSPtree::addChunkedNode(Node* leaf, Triangle* obj){
            auto chunks = Triangle::splitToChunks(obj, leaf->obj->getPlane());
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

        void BSPtree::addInternal(Node* root, Triangle* t){
            bool chunked = false;
            std::cout << "4" << std::endl;
            while(root != nullptr && !chunked){
                Plane p(*(root->obj));
                if(p.isAbove(*t)){
                    std::cout << "6" << std::endl;
                    root = root->rhs;
                }
                else if(p.isBelow(*t)){
                    std::cout << "7" << std::endl;
                    root = root->lhs;
                }
                else if(p.isOnPlane(*t)){
                    std::cout << "5" << std::endl;
                    // To delete
                    if(root->obj->isIntersection(t)){
                        std::cout << "Intersection: "
                                  << printTriangle(t)
                                  << printTriangle(root->obj)
                                  << std::endl;
                    }
                    root = root->lhs;
                }
                else if(p.isIntersection(*t)){
                    std::cout << "8" << std::endl;
                    // To delete
                    if(root->obj->isIntersection(t)){
                        std::cout << "Intersection: "
                                  << printTriangle(t)
                                  << "---"
                                  << printTriangle(root->obj)
                                  << std::endl;
                    }
                    if(root->lhs)
                        root = root->lhs;
                    else if(root->rhs)
                        root = root->rhs;
                    else
                        chunked = true;
                }

            }
            if(chunked)
                addChunkedNode(root, t);
            else
                addStandartNode(root, t);
        } 

}
