# Cpp_EX4

Tree Class
The Tree class template represents a k-ary tree structure where each node holds a value of type T. It supports various operations including adding nodes, iterating in different orders, and visualization using SFML.

Constructor (Tree(size_t k = 2)): Initializes a tree with a default arity of 2.
Destructor (~Tree()): Destroys the tree and frees memory.
get_k(): Returns the arity k of the tree.
get_root(): Returns a pointer to the root node.
add_root(const Node<T>& root_node): Sets the root node if it doesn't already exist.
add_sub_node(Node<T>& parent, Node<T>& child): Adds a child node to a specified parent node.
Iterators
The class provides several iterators (PreOrderIterator, PostOrderIterator, InOrderIterator, BFSIterator, DFSIterator, HeapIterator) for traversing the tree in different orders and heap order.

PreOrderIterator: Iterates in pre-order (root, left, right).
PostOrderIterator: Iterates in post-order (left, right, root).
InOrderIterator: Iterates in-order (left, root, right).
BFSIterator: Iterates using Breadth-First Search order.
DFSIterator: Iterates using Depth-First Search order.
HeapIterator: Iterates in heap order for binary trees (k=2).
Visualization
operator<<: Friend function to visualize the tree using SFML, providing a graphical representation in a window.
Dependencies
Dependencies: Requires Node.hpp for node structure and operations, TreeVisualizer.hpp for visualization, and SFML for graphical output.
Exception Handling
Exception Handling: Throws runtime errors for operations like duplicate root addition, parent not found, and exceeding maximum children limit.
This class template provides a flexible and efficient way to manage and traverse k-ary trees, with support for graphical visualization using SFML.

Node Class
The Node class template represents a node in a tree structure, holding a value of type T and pointers to its children nodes.

Constructor (Node(const T& val)): Constructs a node with the given value.
Destructor (~Node()): Destroys the node.
get_value(): Returns the value stored in the node.
getChildren(): Returns a reference to the vector of children nodes.
addChild(Node* child, size_t k): Adds a child node to the current node. It performs checks for null child, maximum children limit (k), and type compatibility.
Private Members
value: Holds the value of type T.
children: Vector holding pointers to child nodes.
Exception Handling
Exception Handling: Throws runtime errors for operations such as adding a null child, exceeding the maximum children limit, and mismatched child node type.
Dependencies
Dependencies: Requires <vector>, <cstddef>, <iostream>, and <stdexcept> for standard library functionalities.
Notes
Explicit keyword: Ensures explicit construction from T to avoid unintended implicit conversions.
Type Checking: Uses typeid to ensure that added child nodes are of type Node<T>.
This class template provides essential functionalities for managing nodes within a tree structure, focusing on type safety and error handling during child node addition.

TreeVisualizer Class
The TreeVisualizer class is responsible for visualizing a tree structure represented by nodes of type T using the SFML graphics library.

Constructor (TreeVisualizer(sf::RenderWindow& window, const Node<T>& rootNode)):
Initializes the visualizer with a reference to an SFML RenderWindow and the root node of the tree to be visualized. It loads the 'arial.ttf' font for node labels.

visualize():
Main function that starts the visualization loop. It positions nodes starting from the root and continuously updates the SFML window until it is closed. Nodes are drawn as circles with labels showing their values, connected by lines representing parent-child relationships.

Private Members
window: Reference to the SFML RenderWindow used for displaying the tree visualization.
rootNode: Reference to the root node of the tree being visualized.
font: SFML font used for rendering node labels.
nodeRadius: Radius of nodes (circles) in the visualization.
verticalSpacing: Vertical spacing between nodes in the visualization.
initialHorizontalSpacing: Initial horizontal spacing for the root node.
positions: Map to store positions (coordinates) of each node in the tree visualization.
Private Functions
positionNodes(const Node<T>* node, float x, float y, float horizontalSpacing):
Recursively positions nodes starting from a given node (node) at coordinates (x, y) with specified horizontal spacing (horizontalSpacing). It updates the positions map with each node's position.
Dependencies
Dependencies:
Requires SFML (<SFML/Graphics.hpp>) for graphical rendering.
Uses <iostream>, <map>, <iomanip>, and <sstream> for standard library functionalities.
Assumes Node.hpp contains the definition of Node<T>.
Visualization Details
Node Representation: Nodes are represented as circles with a specified radius (nodeRadius) and filled with a blue color.
Text Labeling: Each node displays its value formatted to show three digits before the decimal point using a purple-colored text label.
Connections: Lines (edges) connecting nodes are drawn in black to visually represent parent-child relationships.
Error Handling
Error Handling: Provides error messages to std::cerr for cases such as null nodes and missing child nodes during the positioning process.
This class facilitates the visual representation of tree structures using SFML, providing a clear and interactive display of node relationships within the tree.

Complex Class
The Complex class represents complex numbers with real and imaginary parts.

Constructors
Complex(): Default constructor initializing both real and imaginary parts to 0.0.
Complex(double re, double im): Constructor initializing the real and imaginary parts with specified values (re and im).
Getter Methods
getReal() const: Returns the real part of the complex number.
getImaginary() const: Returns the imaginary part of the complex number.
Setter Methods
setReal(double re): Sets the real part of the complex number to re.
setImaginary(double im): Sets the imaginary part of the complex number to im.
Arithmetic Operations
operator+(const Complex& other) const: Addition operator for complex numbers.
operator-(const Complex& other) const: Subtraction operator for complex numbers.
operator*(const Complex& other) const: Multiplication operator for complex numbers.
operator/(const Complex& other) const: Division operator for complex numbers.
Comparison Operators
operator==(const Complex& other) const: Equality comparison operator.
operator!=(const Complex& other) const: Inequality comparison operator.
operator<(const Complex& other) const: Less than comparison operator.
operator>(const Complex& other) const: Greater than comparison operator.
Output Stream Operator
operator<<(std::ostream& os, const Complex& c): Output stream operator to print the complex number in the format real + imaginary i.

Implementation of Tests Using doctest.h
Each class in this project has been thoroughly tested using the doctest.h framework to ensure correctness and reliability of functionality. Below is a formal explanation of the testing approach and methodology:

Tree Class Testing
Purpose: The Tree class manages a k-ary tree structure, supporting operations such as node addition and various tree traversal methods.

Testing Approach:

Unit Tests: Implemented unit tests for methods like add_root, add_sub_node, and iterators (PreOrderIterator, PostOrderIterator, InOrderIterator, BFSIterator, DFSIterator, HeapIterator).
Coverage: Ensured comprehensive coverage of edge cases, such as adding nodes, handling maximum children limits, and verifying iterator functionality.
Assertions: Used doctest.h assertions (CHECK, CHECK_EQ, CHECK_NE, etc.) to validate expected behavior against actual results.
Node Class Testing
Purpose: The Node class represents nodes within the Tree structure, containing a value and child nodes.

Testing Approach:

Constructor Tests: Verified correct initialization of node values.
Child Management: Tested adding child nodes, ensuring limits on maximum children, and handling null child nodes.
Type Safety: Validated that only Node<T> instances can be added as children.
Exception Handling: Checked for appropriate exceptions when adding invalid or exceeding children limits.
