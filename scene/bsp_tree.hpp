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

        BSPtree() = default;

        BSPtree(const std::vector<Triangle>& c);

        ~BSPtree();

        void add(Polygon* t);

        void balanced();

        private:

        Node* root_ = nullptr;

        size_t num_leafs = 0;

        enum class SIDE{
            UNKNOWN = 0,
            LHS = 1,
            RHS = 2
        };

        void generate(const std::vector<Triangle>& c);

        void addStandartNode(Node* leaf, SIDE s, Polygon* t);

        void addChunkedNode(Node* leaf, const std::array<Polygon*, 2>&);

        void addInternal(Node* root, Polygon* p);

        void addNode(Node* root, Node* lhs, Node* rhs);

        void delNode(Node* n);

        void findIntersectionAfterAddForChunk(Node* side, const Polygon* t);
  
    };
}

#endif
