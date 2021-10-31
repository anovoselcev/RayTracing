#ifndef BSPTREE_HPP
#define BSPTREE_HPP

#include <vector>
#include <array>
#include <set>
#include <iostream>

#include "polygon/polygon.hpp"

namespace rytg{

    class Triangle;

    class BSPtree{
        public:

        struct Node{
            Polygon* obj = nullptr;
            Node* lhs = nullptr;
            Node* rhs = nullptr;
            size_t id = 0;
        };

        BSPtree() = default;

        BSPtree(std::ostream& os);

        BSPtree(const std::vector<Triangle>& c);

        BSPtree(const BSPtree&) = delete;

        BSPtree& operator=(const BSPtree&) = delete;

        ~BSPtree();

        void add(Polygon* t);

        void balanced();

        private:

        Node* root_ = nullptr;

        size_t num_leafs = 0;

        std::set<size_t> ids_;

        std::ostream& os_ = std::cout;

        size_t top_id = 0;

        enum class SIDE{
            UNKNOWN = 0,
            LHS = 1,
            RHS = 2
        };

        void generate(const std::vector<Triangle>& c);

        void addStandartNode(Node* leaf, SIDE s, Polygon* t, size_t id = 0);

        void addInternal(Node* root, Polygon* p, size_t id = 0);

        void delNode(Node* n);

        void printIntersection(size_t id);

        std::array<Polygon*, 2> split(Polygon* p, const Plane& pl);
  
    };
}

#endif
