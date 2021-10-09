#include "bsp_tree.hpp"
#include "../polygon/triangle.hpp"
#include "../geo/plane.hpp"

#include <vector>


namespace rytg{

        BSPtree::BSPtree(const std::vector<Triangle>& c){
            generate(c);
        }

        void BSPtree::generate(const std::vector<Triangle>& c){
            for(const auto& obj : c){
                add(obj);
            }
        }

        void BSPtree::add(const Triangle& obj){
            
            if(root_ == nullptr){
                root_ = new Node;
                root_->obj = new Triangle(obj);
            }
            else{
                Node* curr = root_;
                while(curr != nullptr){
                    Plane p(*(curr->obj));
                    if(p.isAbove(obj)){
                        curr = curr->rhs;
                    }
                    else if(p.isBelow(obj)){
                        curr = curr->lhs;
                    }
                    else if(curr->obj->isIntersection(obj)){

                    }
                    else if(p.isOnPlane(obj)){
                        curr = curr->lhs;
                    }

                }
                curr = new Node;
                curr->obj = new Triangle(obj);
            }
        
        }       

}