#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
    private:
    T value; 
    std::vector<Node*> children; 
    //bool destroyed; 

    public:
    explicit Node(const T& val) : value(val) {}

    ~Node() {}

    T get_value() const { return value; }

    const std::vector<Node*>& getChildren() const { return children; }

    void addChild(Node* child, size_t k) {
        if (child == nullptr) {
            throw std::runtime_error("Cannot add a null child");
        }
        if (children.size() > k) {
            throw std::runtime_error("Maximum children exceeded");
        }
        if (typeid(*child) != typeid(Node<T>)) {
            throw std::runtime_error("Child node type does not match");
        }
        children.push_back(child);
    }
};

#endif // NODE_HPP