#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include "TreeVisualizer.hpp"
#include <stdexcept>         
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>



template <typename T, size_t K = 2>
class Tree {
private:
    Node<T>* root;
    size_t k;

public:
    Tree(size_t k = 2 ) : root(nullptr), k(k) {}
    ~Tree() { delete root; }
    
    // Get method for k
    size_t get_k() const { return k; }

    // Get method for root
    Node<T>* get_root() const { return root; }

    void add_root(const Node<T>& root_node) {
        if (root != nullptr) {
            throw std::runtime_error("Root node already exists.");
        }
        
        root = new Node<T>(root_node);
    }

    // Add a child node to a specified parent node
    void add_sub_node(Node<T>& parent, Node<T>& child) {
        if (root == nullptr) {
            throw std::runtime_error("Root node does not exist.");
        }

        // Find the parent node in the tree
        Node<T>* parentNode = nullptr;
        std::queue<Node<T>*> nodeQueue;
        nodeQueue.push(root);

        while (!nodeQueue.empty()) {
            Node<T>* currentNode = nodeQueue.front();
            nodeQueue.pop();

            if (currentNode->get_value() == parent.get_value()) {
                parentNode = currentNode;
                break;
            }

            for (auto childNode : currentNode->getChildren()) {
                nodeQueue.push(childNode);
            }
        }

        if (parentNode == nullptr) {
            throw std::runtime_error("Parent node not found.");
        }

        // Check if maximum children limit is reached
        if (parentNode->getChildren().size() > k) {
            throw std::runtime_error("Maximum children limit reached for the parent node.");
        }

        // Add the child node to the parent
        parentNode->addChild(new Node<T>(child.get_value()) , k);
    }
/*****************************************************************************************/
    // Iterator class definitions
    class PreOrderIterator {
    private:
        std::vector<Node<T>*> stack;

    public:
        PreOrderIterator(Node<T>* root) {
            if (root != nullptr) {
                stack.push_back(root);
            }
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !stack.empty();
        }

        Node<T>* operator*() const {
            return stack.back();
        }

        Node<T>* operator->() const {
            return stack.back();
        }

        PreOrderIterator& operator++() {
            Node<T>* current = stack.back();
            stack.pop_back();
            for (auto it = current->getChildren().rbegin(); it != current->getChildren().rend(); ++it) {
                stack.push_back(*it);
            }
            return *this;
        }
    };

    PreOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }
/*****************************************************************************************/
// Post-order iterator
    class PostOrderIterator
    {
        private:
        std::stack<Node<T> *> nodeStack; 
        Node<T> *current; 
        size_t k; 

        void pushLeftmost(Node<T>* currentNode) {
            while (currentNode) {
                nodeStack.push(currentNode);
                if (!currentNode->getChildren().empty()) {
                    currentNode = currentNode->getChildren().front();
                } else {
                    break;
                }
            }
        }
        public:
        // Constructor
        PostOrderIterator(Node<T>* root, size_t k) : current(nullptr), k(k) {
            if (root) {
                k == 2 ? pushLeftmost(root) : nodeStack.push(root);
            }
            ++(*this);
        }
        // Comparison operator !=
        bool operator!=(const PostOrderIterator& other) const {
            return current != other.current;
        }

        // Dereference operator *
        Node<T>* operator*() const {
            return *current;
        }
        Node<T>* operator->() const {
            return current;
        }
         // Increment operator ++
        PostOrderIterator& operator++() {
            if (nodeStack.empty()) {
                current = nullptr;
                return *this;
            }
            Node<T>* currentNode = nodeStack.top();
            nodeStack.pop();
            if( k == 2)
            {
                // If there are nodes in the stack and the next node is not the child of the top of the stack
                if (!nodeStack.empty()) {
                    if (nodeStack.top()->getChildren().size() > 1 && currentNode == nodeStack.top()->getChildren()[0])
                        pushLeftmost(nodeStack.top()->getChildren()[1]);
                }
                current = currentNode ;
            }
            else {
                for (auto i = currentNode->getChildren().rbegin(); i < currentNode->getChildren().rend() ; i++)
                {
                    if(*i != nullptr) nodeStack.push(*i);
                }
                current = currentNode ;
            }
            return *this;
        }
    };
    PostOrderIterator begin_post_order() const
    {
        return PostOrderIterator(root, k); // Return iterator starting at root
    }

    PostOrderIterator end_post_order() const
    {
        return PostOrderIterator(nullptr, k); // Return iterator at end
    }

    /*****************************************************************************************/

    // InOrder Iterator
    class InOrderIterator {
    private:
        std::stack<Node<T>*> stack;
        size_t k;

        void pushLeftmost(Node<T>* node) {
            while (node != nullptr) {
                stack.push(node);
               if (!node->getChildren().empty()) node = node->getChildren().front();
               else break;
            }
        }

    public:
        InOrderIterator(Node<T>* root, size_t k) : k(k) {
            if (k == 2) {
                pushLeftmost(root);
            } else {
                stack.push(root);
                while (!stack.empty() && !stack.top())
                {
                    stack.pop();
                }
                
            }
        }

        bool operator!=(const InOrderIterator& other) const {
            return !stack.empty() || !other.stack.empty();
        }

        Node<T>& operator*() const {
            return *stack.top();
        }

        Node<T>* operator->() const {
            return stack.top();
        }

        InOrderIterator& operator++() {
            if (stack.empty()) {
                return *this;
            }

            Node<T>* node = stack.top();
            stack.pop();

            if (k == 2) {
                if (!node->getChildren().empty() && node->getChildren().size() > 1) {
                    pushLeftmost(node->getChildren()[1]);
                }
            } else {
                for (auto it = node->getChildren().rbegin(); it != node->getChildren().rend(); ++it) {
                    if (*it != nullptr) {
                        stack.push(*it);
                    }
                }
            }
            return *this;
        }
    };

    InOrderIterator begin_in_order() {
        return InOrderIterator(root, k);
    }

    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr, k);
    }
/*****************************************************************************************/

    // BFS Iterator
    class BFSIterator {
    private:
        std::queue<Node<T>*> queue;

    public:
        BFSIterator(Node<T>* root) {
            if (root != nullptr) {
                queue.push(root);
            }
        }

        bool operator!=(const BFSIterator& other) const {
            return !queue.empty() != !other.queue.empty();
        }

        Node<T>& operator*() const {
            return *queue.front();
        }

        Node<T>* operator->() const {
            return queue.front();
        }

        BFSIterator& operator++() {
            Node<T>* current = queue.front();
            queue.pop();
            for (auto &child : current->getChildren()) {
                if(child != nullptr)
                queue.push(child);
            }
            return *this;
        }
    };

    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    // Begin BFS Iterator
    BFSIterator begin() const{
        return BFSIterator(root);
    }

    // End BFS Iterator
    BFSIterator end() const{
        return BFSIterator(nullptr);
    }
/*****************************************************************************************/
    // DFS Iterator
    class DFSIterator {
    private:
        std::stack<Node<T>*> stack;

    public:
        DFSIterator(Node<T>* root) {
            if (root != nullptr) {
                stack.push(root);
            }
        }

        bool operator!=(const DFSIterator& other) const {
            return !stack.empty() != !other.stack.empty();
        }

        Node<T>& operator*() const {
            return *stack.top();
        }

        Node<T>* operator->() const {
            return stack.top();
        }

        DFSIterator& operator++() {
            Node<T>* current = stack.top();
            stack.pop();
            for (auto it = current->getChildren().rbegin(); it != current->getChildren().rend(); ++it) {
                if (*it != nullptr)
                {
                    stack.push(*it);
                }
            }
            return *this;
        }
    };

    DFSIterator begin_dfs_scan() {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() {
        return DFSIterator(nullptr);
    }
    
/*****************************************************************************************/
 // HeapIterator class for iterating over nodes of a binary tree in heap order
    class HeapIterator
    {
        private:
        std::vector<Node<T> *> heap; 
        size_t k;
        public:
        HeapIterator(Node<T> *node, size_t k) : k(k)
        {
            if (k == 2)
            {
            std::queue<Node<T>*> nodeQueue;
            if (node) {
                nodeQueue.push(node);
            }

            // Perform BFS to collect all nodes into the heap vector
            while (!nodeQueue.empty()) {
                Node<T>* currentNode = nodeQueue.front();
                nodeQueue.pop();
                heap.push_back(currentNode);

                for (auto child : currentNode->getChildren()) {
                    if (child != nullptr) {
                        nodeQueue.push(child);
                    }
                }
            }

            // Sort the heap vector based on node values to create a min-heap
            std::make_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) {
                return a->get_value() > b->get_value(); // Min-heap order
            });
            }
            else throw std::runtime_error("HeapIterator does not support k != 2."); // Throw error if tree is not binary
        }

        bool operator!=(const HeapIterator &other) const
        {
            return !heap.empty() != !other.heap.empty(); 
        }

        Node<T> *operator->() const
        {
            return heap.front(); 
        }

        Node<T> &operator*() const
        {
            return *heap.front(); 
        }

        HeapIterator &operator++()
        {
            if (!heap.empty()) {
                std::pop_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) {
                    return a->get_value() > b->get_value();
                });
                heap.pop_back();
            }
            return *this;
        }                       
    };

    HeapIterator begin_heap() const
    {
        return HeapIterator(root, k); // Return heap iterator starting at root
    }

    HeapIterator end_heap() const
    {
        return HeapIterator(nullptr, k); // Return heap iterator at end
    }
  /*****************************************************************************************/ 
    // Friend declaration for operator<<
friend std::ostream& operator<<(std::ostream& os, const Tree& tree) {
    sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Tree Visualization"); // SFML window

    // Assuming tree.get_root() returns Node<T>*
    Node<T>* rootNodePtr = tree.get_root();
    if (rootNodePtr) {
        TreeVisualizer<T> treeVisualizer(renderWindow, *rootNodePtr); // Visualizer for the tree
        treeVisualizer.visualize(); // Draw the tree using SFML window
    } else {
        std::cerr << "Error: Unable to visualize tree. Root node is null." << std::endl;
    }
    
    return os;
}


};


#endif // TREE_HPP