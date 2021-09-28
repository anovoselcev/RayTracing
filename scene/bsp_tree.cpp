#include "bsp_tree.hpp"
#include "../figures/triangle.hpp"
#include "../figures/plane.hpp"

#include <vector>


namespace rytg{

        BSPtree::BSPtree(const std::vector<Triangle>& c){
            generate(c);
        }

        void BSPtree::generate(const std::vector<Triangle>& c){
            Node* curr = root_;
            Node* prev = nullptr;
            for(const auto& obj : c){
                curr->obj = new Triangle(obj);

            }
        }

        void BSPtree::add(const Triangle& obj){
            if(root_ == nullptr){
                root_ = new Node;
                root_->obj = new Triangle(obj);
            }
            else{
                Node* curr = root_;

            }

        }

        void BSPtree::make_tree (const Triangle& t){
            if(root_ == nullptr)
        }

        

}