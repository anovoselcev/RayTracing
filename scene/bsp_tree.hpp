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
        // Это вроде конструктор
        BSPtree(const std::vector<Triangle>& c);
        // Это диструктор 
        ~BSPtree();

        void add(Polygon* t);

        private:

        Node* root_ = nullptr;

        size_t num_leafs = 0;

        void generate(const std::vector<Triangle>& c);

        void addStandartNode(Node* leaf, Triangle* t);

        void addChunkedNode(Node* leaf, Triangle* t);

        void addInternal(Node* root, Triangle* p);

        void delNode(Node* n);
  
    };
}

#endif
