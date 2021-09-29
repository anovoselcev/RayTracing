#include "bsp_tree.hpp"
#include "../polygon/triangle.hpp"
#include "../polygon/plane.hpp"

#include <vector>


namespace rytg{

        BSPtree::BSPtree(const std::vector<Triangle>& c){
            generate(c);
        }

        void BSPtree::generate(const std::vector<Triangle>& c){
            Node* curr = root_;
            Node* prev = nullptr;
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
                Plane p(*(root_->obj));
                while(curr != nullptr){
                    if()
                }


            }

        }       

}