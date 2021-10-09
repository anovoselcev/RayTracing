#ifndef BSPTREE_HPP
#define BSPTREE_HPP

#include <vector>
#include "../polygon/polygon.hpp"

namespace rytg{

    class Triangle;

    class BSPtree{

        public:

        struct Node{
            Polygon* obj = nullptr;
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

#endif