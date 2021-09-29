#pragma once

#include <vector>

namespace rytg{

    class Triangle;

    class BSPtree{

        public:

        struct Node{
            Triangle* obj = nullptr;
            Node* lhs = nullptr;
            Node* rhs = nullptr;
        };

        BSPtree(const std::vector<Triangle>& c);

        void add(const Triangle& t);

        private:

        Node* root_ = nullptr;

        void generate(const std::vector<Triangle>& c);
  
    };

}