//aseelzatmy3@gmail.com
// test.cpp
#include "doctest.h"
#include "Tree.hpp"
#include "Node.hpp"
#include "Complex.hpp"

using namespace std;

TEST_CASE("Adding sub nodes to a tree") {
    // Create a tree with maximum 2 children per node (binary tree)
    Tree<int> tree(2);

    // Add root node
    Node<int> root(1);
    tree.add_root(root);

    // Add child nodes
    Node<int> n1(2);
    Node<int> n2(3);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    // Add grandchildren
    Node<int> n3(4);
    Node<int> n4(5);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);

    // Check if nodes are added correctly
    SUBCASE("Valid tree structure") {
        CHECK(tree.begin_pre_order()->get_value() == 1); // Root node
        CHECK(tree.begin_pre_order()->getChildren().size() == 2); // Root's children

        auto rootChildren = tree.begin_pre_order()->getChildren();
        CHECK(rootChildren[0]->get_value() == 2); // First child
        CHECK(rootChildren[1]->get_value() == 3); // Second child

        auto firstChildChildren = rootChildren[0]->getChildren();
        CHECK(firstChildChildren[0]->get_value() == 4); // First grandchild
        CHECK(firstChildChildren[1]->get_value() == 5); // Second grandchild
    }

    SUBCASE("Adding sub nodes errors") {
        // Test case for adding to a non-existent parent node
        Node<int> nonExistentParent(100);
        CHECK_THROWS(tree.add_sub_node(nonExistentParent, n3));

        // Test case for exceeding maximum children limit
        Node<int> n5(6);
        Node<int> n6(7);
        CHECK_NOTHROW(tree.add_sub_node(n1, n5)); // Should add successfully
        CHECK_THROWS(tree.add_sub_node(n1, n6)); // Should throw because maximum limit reached
    }

    SUBCASE("Adding root node errors") {
        // Test case for attempting to add a root node when one already exists
        Node<int> newRoot(10);
        CHECK_THROWS(tree.add_root(newRoot)); // Should throw because root node already exists
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Test case for tree construction and destruction
    TEST_CASE("Tree Construction and Destruction") {
    // Test default construction and destruction
    {
        Tree<int> tree;
        CHECK(tree.get_root() == nullptr); // Ensure root is initially nullptr
    }

    // Test construction with a specific k value
    {
        Tree<int> tree(3);
        CHECK(tree.get_k() == 3); // Check if k value is correctly initialized
    }

    // Test destruction of tree with nodes
    {
        Tree<int> tree;
        Node<int> root(1);
        tree.add_root(root);

        // Add some nodes
        Node<int> n1(2);
        tree.add_sub_node(root, n1);

        // Manually destroy the tree here to ensure nodes are deleted
        // Note: This is not necessary in practice if the Tree destructor is correctly implemented
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 // Test case for adding root node
    TEST_CASE("Adding Root Node") {
        Tree<int> tree(2);

        // Add root node
        Node<int> root(1);
        CHECK_NOTHROW(tree.add_root(root)); // Should add root node without error

        // Adding root again should throw error
        Node<int> newRoot(10);
        CHECK_THROWS(tree.add_root(newRoot)); // Should throw because root node already exists
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("PreOrderIterator Test") {
    // Create a tree with maximum 2 children per node (binary tree)
    Tree<int, 2> tree;

    // Add root node
    Node<int> root(1);
    tree.add_root(root);

    // Add child nodes
    Node<int> n1(2);
    Node<int> n2(3);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    // Add grandchildren
    Node<int> n3(4);
    Node<int> n4(5);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);

    // Traverse the tree using PreOrderIterator and collect values
    std::vector<int> values;
    for (auto it = tree.begin_pre_order(); it != tree.end_pre_order(); ++it) {
        values.push_back((*it)->get_value());
    }

    // Verify the expected pre-order traversal sequence
    std::vector<int> expected = {1, 2, 4, 5, 3};
    CHECK(values == expected);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Testing PreOrderIterator") {
    Tree<int> tree(2);

    Node<int> root(1);
    tree.add_root(root);

    Node<int> n1(2);
    Node<int> n2(3);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    Node<int> n3(4);
    Node<int> n4(5);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);

    SUBCASE("PreOrderIterator initialization") {
        Tree<int>::PreOrderIterator it = tree.begin_pre_order();
        CHECK((*it)->get_value() == 1); // Should point to root node initially
    }

    SUBCASE("PreOrderIterator traversal") {
        Tree<int>::PreOrderIterator it = tree.begin_pre_order();
        CHECK((*it)->get_value() == 1); // Root node

        ++it;
        CHECK((*it)->get_value() == 2); // First child of root

        ++it;
        CHECK((*it)->get_value() == 4); // First grandchild of first child

        ++it;
        CHECK((*it)->get_value() == 5); // Second grandchild of first child

        ++it;
        CHECK((*it)->get_value() == 3); // Second child of root

        ++it;
        //CHECK(it != tree.end_pre_order()); // Ensure iterator reaches end
    }
}
TEST_CASE("Testing PreOrderIterator for Tree<double>") {
    Tree<double> three_ary_tree(3); // 3-ary tree

    // Create nodes
    Node<double> root_node(1.1);
    Node<double> n1(2.2);
    Node<double> n2(3.3);
    Node<double> n3(4.4);
    Node<double> n4(5.5);
    Node<double> n5(6.6);

    // Build the tree structure
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    SUBCASE("Valid PreOrderIterator traversal") {
        std::stringstream output;
        for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node) {
            output << node->get_value() << std::endl;
        }

        std::string expected_output = "1.1\n2.2\n5.5\n3.3\n6.6\n4.4\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("PreOrderIterator on an empty tree") {
        Tree<double> empty_tree(3);

        std::stringstream output;
        for (auto node = empty_tree.begin_pre_order(); node != empty_tree.end_pre_order(); ++node) {
            output << node->get_value() << std::endl;
        }

        CHECK(output.str().empty()); // Expecting no output for an empty tree
    }
}
TEST_CASE("Testing PreOrderIterator for Tree<std::string>") {
    Tree<std::string> string_tree(3); // 3-ary tree

    // Create nodes
    Node<std::string> root_node("Root");
    Node<std::string> n1("Node1");
    Node<std::string> n2("Node2");
    Node<std::string> n3("Node3");
    Node<std::string> n4("Node4");
    Node<std::string> n5("Node5");

    // Build the tree structure
    string_tree.add_root(root_node);
    string_tree.add_sub_node(root_node, n1);
    string_tree.add_sub_node(root_node, n2);
    string_tree.add_sub_node(root_node, n3);
    string_tree.add_sub_node(n1, n4);
    string_tree.add_sub_node(n2, n5);

    SUBCASE("Valid PreOrderIterator traversal") {
        std::stringstream output;
        for (auto node = string_tree.begin_pre_order(); node != string_tree.end_pre_order(); ++node) {
            output << node->get_value() << std::endl;
        }

        std::string expected_output =
            "Root\n"
            "Node1\n"
            "Node4\n"
            "Node2\n"
            "Node5\n"
            "Node3\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("PreOrderIterator on an empty tree") {
        Tree<std::string> empty_tree(3);

        std::stringstream output;
        for (auto node = empty_tree.begin_pre_order(); node != empty_tree.end_pre_order(); ++node) {
            output << node->get_value() << std::endl;
        }

        CHECK(output.str().empty()); // Expecting no output for an empty tree
    }
}

TEST_CASE("Testing Node<int> class") {
    SUBCASE("Adding valid children") {
        Node<int> root(1);
        Node<int> child1(2);
        Node<int> child2(3);

        CHECK_NOTHROW(root.addChild(&child1, 0)); // Should add child1 without exceptions
        CHECK_NOTHROW(root.addChild(&child2, 1)); // Should add child2 without exceptions

        auto children = root.getChildren();
        CHECK(children.size() == 2);
        CHECK(children[0]->get_value() == 2);
        CHECK(children[1]->get_value() == 3);
    }

    SUBCASE("Adding invalid children") {
        Node<int> root(1);
        Node<int> child(2);

        // Attempt to add a null child
        Node<int>* nullChild = nullptr;
        CHECK_THROWS(root.addChild(nullChild, 0));
}
}
TEST_CASE("Testing PostOrderIterator for Tree<double>") {
    Node<double> root_node = Node<double>(1.1);
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);
    Tree<double> three_ary_tree(3); // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);
    std::stringstream output;
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node) {
        output << node->get_value() << std::endl;
    }
    std::string expected_output = "1.1\n1.2\n1.5\n1.3\n1.6\n1.4\n";
    CHECK(output.str() == expected_output);
}
TEST_CASE("Testing PostOrderIterator for Tree<int>") {
    // Create nodes
    Node<int> root_node = Node<int>(1);
    Node<int> n1 = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    Node<int> n3 = Node<int>(4);
    Node<int> n4 = Node<int>(5);
    Node<int> n5 = Node<int>(6);
    Tree<int> three_ary_tree(3); // 3-ary tree.

    // Build the tree structure
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    SUBCASE("Valid PostOrderIterator traversal for int tree") {
        std::stringstream output;
        for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "1\n2\n5\n3\n6\n4\n";
        CHECK(output.str() == expected_output);
    }
}

TEST_CASE("Testing PostOrderIterator for Tree<std::string>") {
    // Create nodes
    Node<std::string> root_node = Node<std::string>("root");
    Node<std::string> n1 = Node<std::string>("child1");
    Node<std::string> n2 = Node<std::string>("child2");
    Node<std::string> n3 = Node<std::string>("child3");
    Node<std::string> n4 = Node<std::string>("grandchild1");
    Node<std::string> n5 = Node<std::string>("grandchild2");
    Tree<std::string> three_ary_tree(3); // 3-ary tree.

    // Build the tree structure
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    SUBCASE("Valid PostOrderIterator traversal for string tree") {
        std::stringstream output;
        for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "root\nchild1\ngrandchild1\nchild2\ngrandchild2\nchild3\n"; // Correct post-order output
        CHECK(output.str() == expected_output);
    }


    SUBCASE("Empty tree traversal for string tree") {
        Tree<std::string> empty_tree(3);
        std::stringstream output;
        for (auto node = empty_tree.begin_post_order(); node != empty_tree.end_post_order(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for string tree") {
        Tree<std::string> single_node_tree(3);
        Node<std::string> single_node("single");
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_post_order(); node != single_node_tree.end_post_order(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "single\n";
        CHECK(output.str() == expected_output);
    }
}
TEST_CASE("Testing PostOrderIterator for a Tree with 5 children and 4 grandchildren") {
    Node<std::string> root_node("root");
    Node<std::string> c1("c1");
    Node<std::string> c2("c2");
    Node<std::string> c3("c3");
    Node<std::string> c4("c4");
    Node<std::string> c5("c5");

    Node<std::string> gc1("gc1");
    Node<std::string> gc2("gc2");
    Node<std::string> gc3("gc3");
    Node<std::string> gc4("gc4");

    Tree<std::string> tree(5); // Assume a maximum of 5 children

    // Build the tree structure
    tree.add_root(root_node);
    tree.add_sub_node(root_node, c1);
    tree.add_sub_node(root_node, c2);
    tree.add_sub_node(root_node, c3);
    tree.add_sub_node(root_node, c4);
    tree.add_sub_node(root_node, c5);

    tree.add_sub_node(c1, gc1);
    tree.add_sub_node(c1, gc2);
    tree.add_sub_node(c1, gc3);
    tree.add_sub_node(c4, gc4);

    //           root
    //        /  |  \  \  \
    //     c1    c2 c3  c4  c5
    //   / | \           |
    // g1 g2  g3         g4

    std::stringstream output;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        output << node->get_value() << std::endl;
    }

    std::string expected_output = "root\nc1\ngc1\ngc2\ngc3\nc2\nc3\nc4\ngc4\nc5\n";
    CHECK(output.str() == expected_output);
}
TEST_CASE("Testing PostOrderIterator for a Tree of Complex numbers") {
    // Create complex number nodes
    Node<Complex> root_node(Complex(1.1, 1.1));
    Node<Complex> c1(Complex(2.2, 2.2));
    Node<Complex> c2(Complex(3.3, 3.3));
    Node<Complex> c3(Complex(4.4, 4.4));
    Node<Complex> c4(Complex(5.5, 5.5));
    Node<Complex> c5(Complex(6.6, 6.6));

    Node<Complex> gc1(Complex(7.7, 7.7));
    Node<Complex> gc2(Complex(8.8, 8.8));
    Node<Complex> gc3(Complex(9.9, 9.9));
    Node<Complex> gc4(Complex(10.10, 10.10));

    Tree<Complex> tree(5); // Assume a maximum of 5 children

    // Build the tree structure
    tree.add_root(root_node);
    tree.add_sub_node(root_node, c1);
    tree.add_sub_node(root_node, c2);
    tree.add_sub_node(root_node, c3);
    tree.add_sub_node(root_node, c4);
    tree.add_sub_node(root_node, c5);

    tree.add_sub_node(c1, gc1);
    tree.add_sub_node(c1, gc2);
    tree.add_sub_node(c1, gc3);
    tree.add_sub_node(c4, gc4);

    //           root
    //        /  |  \  \  \
    //     c1    c2 c3  c4  c5
    //   / | \           |
    // gc1 gc2  gc3         gc4

    std::stringstream output;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        output << node->get_value() << std::endl;
    }

    std::string expected_output = "1.1 + 1.1i\n"
                                  "2.2 + 2.2i\n"
                                  "7.7 + 7.7i\n"
                                  "8.8 + 8.8i\n"
                                  "9.9 + 9.9i\n"
                                  "3.3 + 3.3i\n"
                                  "4.4 + 4.4i\n"
                                  "5.5 + 5.5i\n"
                                  "10.1 + 10.1i\n"
                                  "6.6 + 6.6i\n";

    CHECK(output.str() == expected_output);
}

/************************************************************************************************************************/

TEST_CASE("Testing InOrderIterator for a Tree with 5 children and 4 grandchildren") {
    Node<std::string> root_node("root");
    Node<std::string> c1("c1");
    Node<std::string> c2("c2");
    Node<std::string> c3("c3");
    Node<std::string> c4("c4");
    Node<std::string> c5("c5");

    Node<std::string> gc1("gc1");
    Node<std::string> gc2("gc2");
    Node<std::string> gc3("gc3");
    Node<std::string> gc4("gc4");

    Tree<std::string> tree(5); // Assume a maximum of 5 children

    // Build the tree structure
    tree.add_root(root_node);
    tree.add_sub_node(root_node, c1);
    tree.add_sub_node(root_node, c2);
    tree.add_sub_node(root_node, c3);
    tree.add_sub_node(root_node, c4);
    tree.add_sub_node(root_node, c5);

    tree.add_sub_node(c1, gc1);
    tree.add_sub_node(c1, gc2);
    tree.add_sub_node(c1, gc3);
    tree.add_sub_node(c4, gc4);

    //           root
    //        /  |  \  \  \
    //     c1    c2 c3  c4  c5
    //   / | \           |
    // g1 g2  g3         g4

    std::stringstream output;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        output << node->get_value() << std::endl;
    }

    std::string expected_output = "root\nc1\ngc1\ngc2\ngc3\nc2\nc3\nc4\ngc4\nc5\n";
    CHECK(output.str() == expected_output);
}
TEST_CASE("Testing InOrderIterator for a Tree of Complex numbers") {
    // Create complex number nodes
    Node<Complex> root_node(Complex(1.1, 1.1));
    Node<Complex> c1(Complex(2.2, 2.2));
    Node<Complex> c2(Complex(3.3, 3.3));
    Node<Complex> c3(Complex(4.4, 4.4));
    Node<Complex> c4(Complex(5.5, 5.5));
    Node<Complex> c5(Complex(6.6, 6.6));

    Node<Complex> gc1(Complex(7.7, 7.7));
    Node<Complex> gc2(Complex(8.8, 8.8));
    Node<Complex> gc3(Complex(9.9, 9.9));
    Node<Complex> gc4(Complex(10.10, 10.10));

    Tree<Complex> tree(5); // Assume a maximum of 5 children

    // Build the tree structure
    tree.add_root(root_node);
    tree.add_sub_node(root_node, c1);
    tree.add_sub_node(root_node, c2);
    tree.add_sub_node(root_node, c3);
    tree.add_sub_node(root_node, c4);
    tree.add_sub_node(root_node, c5);

    tree.add_sub_node(c1, gc1);
    tree.add_sub_node(c1, gc2);
    tree.add_sub_node(c1, gc3);
    tree.add_sub_node(c4, gc4);

    //           root
    //        /  |  \  \  \
    //     c1    c2 c3  c4  c5
    //   / | \           |
    // gc1 gc2  gc3         gc4

    std::stringstream output;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        output << node->get_value() << std::endl;
    }

    std::string expected_output = "1.1 + 1.1i\n"
                                  "2.2 + 2.2i\n"
                                  "7.7 + 7.7i\n"
                                  "8.8 + 8.8i\n"
                                  "9.9 + 9.9i\n"
                                  "3.3 + 3.3i\n"
                                  "4.4 + 4.4i\n"
                                  "5.5 + 5.5i\n"
                                  "10.1 + 10.1i\n"
                                  "6.6 + 6.6i\n";

    CHECK(output.str() == expected_output);
}
TEST_CASE("Testing InOrderIterator for a binary Tree of strings") {
    Node<std::string> root_node("root");
    Node<std::string> c1("c1");
    Node<std::string> c2("c2");
    Node<std::string> c3("c3");
    Node<std::string> c4("c4");
    Node<std::string> c5("c5");

    Node<std::string> gc1("gc1");
    Node<std::string> gc2("gc2");
    Node<std::string> gc3("gc3");
    Node<std::string> gc4("gc4");

    Tree<std::string> tree(2); // Binary tree (each node has at most 2 children)

    // Build the tree structure
    tree.add_root(root_node);
    tree.add_sub_node(root_node, c1);
    tree.add_sub_node(root_node, c2);
    tree.add_sub_node(c1, gc1);
    tree.add_sub_node(c1, gc2);
    tree.add_sub_node(c2, c3);
    tree.add_sub_node(c3, c4);
    tree.add_sub_node(c3, c5);
    tree.add_sub_node(c4, gc3);
    tree.add_sub_node(c5, gc4);

    //            root
    //           /    \
    //        c1        c2
    //      /  \        |
    //   gc1  gc2      c3
    //                /   \
    //              c4     c5
    //             /        \
    //          gc3          gc4

    std::stringstream output;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        output << node->get_value() << std::endl;
    }

    std::string expected_output = "gc1\nc1\ngc2\nroot\ngc3\nc4\nc3\ngc4\nc5\nc2\n";
    CHECK(output.str() == expected_output);
}
TEST_CASE("Testing InOrderIterator for Tree<std::string>") {
    // Create nodes
    Node<std::string> root_node = Node<std::string>("root");
    Node<std::string> n1 = Node<std::string>("child1");
    Node<std::string> n2 = Node<std::string>("child2");
    Node<std::string> n3 = Node<std::string>("child3");
    Node<std::string> n4 = Node<std::string>("grandchild1");
    Node<std::string> n5 = Node<std::string>("grandchild2");
    Tree<std::string> three_ary_tree(3); // 3-ary tree.

    // Build the tree structure
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    SUBCASE("Valid InOrderIterator traversal for string tree") {
        std::stringstream output;
        for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "root\nchild1\ngrandchild1\nchild2\ngrandchild2\nchild3\n"; // 
        CHECK(output.str() == expected_output);
    }


    SUBCASE("Empty tree traversal for string tree") {
        Tree<std::string> empty_tree(3);
        std::stringstream output;
        for (auto node = empty_tree.begin_in_order(); node != empty_tree.end_in_order(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for string tree") {
        Tree<std::string> single_node_tree(3);
        Node<std::string> single_node("single");
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_in_order(); node != single_node_tree.end_in_order(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "single\n";
        CHECK(output.str() == expected_output);
    }
}
TEST_CASE("Testing InOrderIterator for a Binary Tree") {
    // Create nodes
    Node<std::string> root_node("root");
    Node<std::string> left_child("left");
    Node<std::string> right_child("right");
    Node<std::string> left_left_grandchild("left_left");
    Node<std::string> left_right_grandchild("left_right");
    Node<std::string> right_left_grandchild("right_left");
    Node<std::string> right_right_grandchild("right_right");
    
    Tree<std::string> binary_tree(2); // Binary tree with a maximum of 2 children per node

    // Build the tree structure
    binary_tree.add_root(root_node);
    binary_tree.add_sub_node(root_node, left_child);
    binary_tree.add_sub_node(root_node, right_child);
    binary_tree.add_sub_node(left_child, left_left_grandchild);
    binary_tree.add_sub_node(left_child, left_right_grandchild);
    binary_tree.add_sub_node(right_child, right_left_grandchild);
    binary_tree.add_sub_node(right_child, right_right_grandchild);

    // Tree structure:
    //        root
    //       /    \
    //    left   right
    //   /    \  /     \
    // left_left left_right right_left right_right

    SUBCASE("Valid InOrderIterator traversal for binary tree") {
        std::stringstream output;
        for (auto node = binary_tree.begin_in_order(); node != binary_tree.end_in_order(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "left_left\nleft\nleft_right\nroot\nright_left\nright\nright_right\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Empty tree traversal for binary tree") {
        Tree<std::string> empty_tree(2);
        std::stringstream output;
        for (auto node = empty_tree.begin_in_order(); node != empty_tree.end_in_order(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for binary tree") {
        Tree<std::string> single_node_tree(2);
        Node<std::string> single_node("single");
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_in_order(); node != single_node_tree.end_in_order(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "single\n";
        CHECK(output.str() == expected_output);
    }
}
/************************************************************************************************* */
TEST_CASE("Testing BFSIterator for Tree<std::string>") {
    // Create nodes
    Node<std::string> root_node("root");
    Node<std::string> child1("child1");
    Node<std::string> child2("child2");
    Node<std::string> child3("child3");
    Node<std::string> grandchild1("grandchild1");
    Node<std::string> grandchild2("grandchild2");

    Tree<std::string> tree(3); // 3-ary tree.

    // Build the tree structure
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child1);
    tree.add_sub_node(root_node, child2);
    tree.add_sub_node(root_node, child3);
    tree.add_sub_node(child1, grandchild1);
    tree.add_sub_node(child2, grandchild2);

    // Tree structure:
    //        root
    //     /   |   \
    // child1 child2 child3
    //   |       |
    // grandchild1 grandchild2

    SUBCASE("Valid BFSIterator traversal for tree") {
        std::stringstream output;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "root\nchild1\nchild2\nchild3\ngrandchild1\ngrandchild2\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Empty tree traversal for tree") {
        Tree<std::string> empty_tree(3);
        std::stringstream output;
        for (auto node = empty_tree.begin_bfs_scan(); node != empty_tree.end_bfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for tree") {
        Tree<std::string> single_node_tree(3);
        Node<std::string> single_node("single");
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_bfs_scan(); node != single_node_tree.end_bfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "single\n";
        CHECK(output.str() == expected_output);
    }
}
TEST_CASE("Testing BFSIterator for binary Tree<std::string>") {
    // Create nodes
    Node<std::string> root_node("root");
    Node<std::string> left_child("left");
    Node<std::string> right_child("right");
    Node<std::string> left_left_grandchild("left_left");
    Node<std::string> left_right_grandchild("left_right");
    Node<std::string> right_left_grandchild("right_left");
    Node<std::string> right_right_grandchild("right_right");

    Tree<std::string> binary_tree; // Binary tree.

    // Build the tree structure
    binary_tree.add_root(root_node);
    binary_tree.add_sub_node(root_node, left_child);
    binary_tree.add_sub_node(root_node, right_child);
    binary_tree.add_sub_node(left_child, left_left_grandchild);
    binary_tree.add_sub_node(left_child, left_right_grandchild);
    binary_tree.add_sub_node(right_child, right_left_grandchild);
    binary_tree.add_sub_node(right_child, right_right_grandchild);

    // Tree structure:
    //        root
    //       /    \
    //   left    right
    //  /   \    /   \
    // ll  lr  rl  rr
    // (ll: left_left, lr: left_right, rl: right_left, rr: right_right)

    SUBCASE("Valid BFSIterator traversal for binary tree") {
        std::stringstream output;
        for (auto node = binary_tree.begin_bfs_scan(); node != binary_tree.end_bfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "root\nleft\nright\nleft_left\nleft_right\nright_left\nright_right\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Empty tree traversal for binary tree") {
        Tree<std::string> empty_tree;
        std::stringstream output;
        for (auto node = empty_tree.begin_bfs_scan(); node != empty_tree.end_bfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for binary tree") {
        Tree<std::string> single_node_tree;
        Node<std::string> single_node("single");
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_bfs_scan(); node != single_node_tree.end_bfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "single\n";
        CHECK(output.str() == expected_output);
    }
}

TEST_CASE("Testing BFSIterator for 5-ary Tree<Complex>") {
    // Create nodes with complex numbers
    Node<Complex> root_node(Complex(0, 0));
    Node<Complex> child1(Complex(1, 1));
    Node<Complex> child2(Complex(2, 2));
    Node<Complex> child3(Complex(3, 3));
    Node<Complex> child4(Complex(4, 4));
    Node<Complex> child5(Complex(5, 5));

    Node<Complex> grandchild1(Complex(6, 6));
    Node<Complex> grandchild2(Complex(7, 7));
    Node<Complex> grandchild3(Complex(8, 8));
    Node<Complex> grandchild4(Complex(9, 9));

    Tree<Complex> five_ary_tree(5); // 5-ary tree

    // Build the tree structure
    five_ary_tree.add_root(root_node);
    five_ary_tree.add_sub_node(root_node, child1);
    five_ary_tree.add_sub_node(root_node, child2);
    five_ary_tree.add_sub_node(root_node, child3);
    five_ary_tree.add_sub_node(root_node, child4);
    five_ary_tree.add_sub_node(root_node, child5);

    five_ary_tree.add_sub_node(child1, grandchild1);
    five_ary_tree.add_sub_node(child1, grandchild2);
    five_ary_tree.add_sub_node(child2, grandchild3);
    five_ary_tree.add_sub_node(child3, grandchild4);

    // Expected BFS order:
    //        0 + 0i
    //      /  |  \  \  \
    // 1 + 1i 2 + 2i 3 + 3i 4 + 4i 5 + 5i
    //  /  \      \
    // 6+6i 7+7i 8+8i 9+9i

    SUBCASE("Valid BFSIterator traversal for 5-ary tree of Complex numbers") {
        std::stringstream output;
        for (auto node = five_ary_tree.begin_bfs_scan(); node != five_ary_tree.end_bfs_scan(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output = 
            "0 + 0i\n"
            "1 + 1i\n"
            "2 + 2i\n"
            "3 + 3i\n"
            "4 + 4i\n"
            "5 + 5i\n"
            "6 + 6i\n"
            "7 + 7i\n"
            "8 + 8i\n"
            "9 + 9i\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Empty tree traversal for 5-ary tree of Complex numbers") {
        Tree<Complex> empty_tree(5);
        std::stringstream output;
        for (auto node = empty_tree.begin_bfs_scan(); node != empty_tree.end_bfs_scan(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for 5-ary tree of Complex numbers") {
        Tree<Complex> single_node_tree(5);
        Node<Complex> single_node(Complex(10, 10));
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_bfs_scan(); node != single_node_tree.end_bfs_scan(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output = "10 + 10i\n";
        CHECK(output.str() == expected_output);
    }
}

/***************************************************************************************************************/
TEST_CASE("Testing DFSIterator for Tree<std::string>") {
    // Create nodes
    Node<std::string> root_node("root");
    Node<std::string> child1("child1");
    Node<std::string> child2("child2");
    Node<std::string> child3("child3");
    Node<std::string> grandchild1("grandchild1");
    Node<std::string> grandchild2("grandchild2");

    Tree<std::string> tree(3); // 3-ary tree.

    // Build the tree structure
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child1);
    tree.add_sub_node(root_node, child2);
    tree.add_sub_node(root_node, child3);
    tree.add_sub_node(child1, grandchild1);
    tree.add_sub_node(child2, grandchild2);

    // Tree structure:
    //        root
    //     /   |   \
    // child1 child2 child3
    //   |       |
    // grandchild1 grandchild2

    SUBCASE("Valid DFSIterator traversal for tree") {
        std::stringstream output;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "root\nchild1\ngrandchild1\nchild2\ngrandchild2\nchild3\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Empty tree traversal for tree") {
        Tree<std::string> empty_tree(3);
        std::stringstream output;
        for (auto node = empty_tree.begin_dfs_scan(); node != empty_tree.end_dfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for tree") {
        Tree<std::string> single_node_tree(3);
        Node<std::string> single_node("single");
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_dfs_scan(); node != single_node_tree.end_dfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "single\n";
        CHECK(output.str() == expected_output);
    }
}

TEST_CASE("Testing DFSIterator for binary Tree<std::string>") {
    // Create nodes
    Node<std::string> root_node("root");
    Node<std::string> left_child("left");
    Node<std::string> right_child("right");
    Node<std::string> left_left_grandchild("left_left");
    Node<std::string> left_right_grandchild("left_right");
    Node<std::string> right_left_grandchild("right_left");
    Node<std::string> right_right_grandchild("right_right");

    Tree<std::string> binary_tree(2); // Binary tree.

    // Build the tree structure
    binary_tree.add_root(root_node);
    binary_tree.add_sub_node(root_node, left_child);
    binary_tree.add_sub_node(root_node, right_child);
    binary_tree.add_sub_node(left_child, left_left_grandchild);
    binary_tree.add_sub_node(left_child, left_right_grandchild);
    binary_tree.add_sub_node(right_child, right_left_grandchild);
    binary_tree.add_sub_node(right_child, right_right_grandchild);

    // Tree structure:
    //        root
    //       /    \
    //   left    right
    //  /   \    /   \
    // ll  lr  rl  rr
    // (ll: left_left, lr: left_right, rl: right_left, rr: right_right)

    SUBCASE("Valid DFSIterator traversal for binary tree") {
        std::stringstream output;
        for (auto node = binary_tree.begin_dfs_scan(); node != binary_tree.end_dfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "root\nleft\nleft_left\nleft_right\nright\nright_left\nright_right\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Empty tree traversal for binary tree") {
        Tree<std::string> empty_tree(2);
        std::stringstream output;
        for (auto node = empty_tree.begin_dfs_scan(); node != empty_tree.end_dfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for binary tree") {
        Tree<std::string> single_node_tree(2);
        Node<std::string> single_node("single");
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_dfs_scan(); node != single_node_tree.end_dfs_scan(); ++node) {
            output << node->get_value() << std::endl;
        }
        std::string expected_output = "single\n";
        CHECK(output.str() == expected_output);
    }
}

TEST_CASE("Testing DFSIterator for 5-ary Tree<Complex>") {
    // Create nodes with complex numbers
    Node<Complex> root_node(Complex(0, 0));
    Node<Complex> child1(Complex(1, 1));
    Node<Complex> child2(Complex(2, 2));
    Node<Complex> child3(Complex(3, 3));
    Node<Complex> child4(Complex(4, 4));
    Node<Complex> child5(Complex(5, 5));

    Node<Complex> grandchild1(Complex(6, 6));
    Node<Complex> grandchild2(Complex(7, 7));
    Node<Complex> grandchild3(Complex(8, 8));
    Node<Complex> grandchild4(Complex(9, 9));

    Tree<Complex> five_ary_tree(5); // 5-ary tree

    // Build the tree structure
    five_ary_tree.add_root(root_node);
    five_ary_tree.add_sub_node(root_node, child1);
    five_ary_tree.add_sub_node(root_node, child2);
    five_ary_tree.add_sub_node(root_node, child3);
    five_ary_tree.add_sub_node(root_node, child4);
    five_ary_tree.add_sub_node(root_node, child5);

    five_ary_tree.add_sub_node(child1, grandchild1);
    five_ary_tree.add_sub_node(child1, grandchild2);
    five_ary_tree.add_sub_node(child2, grandchild3);
    five_ary_tree.add_sub_node(child3, grandchild4);

    // Expected DFS order:
    //        0 + 0i
    //      /  |  \  \  \
    // 1 + 1i 2 + 2i 3 + 3i 4 + 4i 5 + 5i
    //  /  \      \
    // 6+6i 7+7i 8+8i 9+9i

    SUBCASE("Valid DFSIterator traversal for 5-ary tree of Complex numbers") {
        std::stringstream output;
        for (auto node = five_ary_tree.begin_dfs_scan(); node != five_ary_tree.end_dfs_scan(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output = 
            "0 + 0i\n"
            "1 + 1i\n"
            "6 + 6i\n"
            "7 + 7i\n"
            "2 + 2i\n"
            "8 + 8i\n"
            "3 + 3i\n"
            "9 + 9i\n"
            "4 + 4i\n"
            "5 + 5i\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Empty tree traversal for 5-ary tree of Complex numbers") {
        Tree<Complex> empty_tree(5);
        std::stringstream output;
        for (auto node = empty_tree.begin_dfs_scan(); node != empty_tree.end_dfs_scan(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for 5-ary tree of Complex numbers") {
        Tree<Complex> single_node_tree(5);
        Node<Complex> single_node(Complex(10, 10));
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_dfs_scan(); node != single_node_tree.end_dfs_scan(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output = "10 + 10i\n";
        CHECK(output.str() == expected_output);
    }
}
/************************************************************************************************* */
TEST_CASE("Testing DFSIterator for Tree<Complex>") {
    // Create nodes with complex numbers
    Node<Complex> root_node(Complex(0, 0));
    Node<Complex> child1(Complex(1, 1));
    Node<Complex> child2(Complex(2, 2));
    Node<Complex> child3(Complex(3, 3));
    Node<Complex> child4(Complex(4, 4));
    Node<Complex> child5(Complex(5, 5));

    Node<Complex> grandchild1(Complex(6, 6));
    Node<Complex> grandchild2(Complex(7, 7));
    Node<Complex> grandchild3(Complex(8, 8));
    Node<Complex> grandchild4(Complex(9, 9));

    Tree<Complex> tree(5); 

    // Build the tree structure
    tree.add_root(root_node);
    tree.add_sub_node(root_node, child1);
    tree.add_sub_node(root_node, child2);
    tree.add_sub_node(root_node, child3);
    tree.add_sub_node(root_node, child4);
    tree.add_sub_node(root_node, child5);

    tree.add_sub_node(child1, grandchild1);
    tree.add_sub_node(child1, grandchild2);
    tree.add_sub_node(child2, grandchild3);
    tree.add_sub_node(child3, grandchild4);

    // Expected DFS order:
    //        0 + 0i
    //      /  |  \  \  \
    // 1 + 1i 2 + 2i 3 + 3i 4 + 4i 5 + 5i
    //  /  \      \
    // 6+6i 7+7i 8+8i 9+9i

    SUBCASE("Valid DFSIterator traversal for complex number tree") {
        std::stringstream output;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output =
            "0 + 0i\n"
            "1 + 1i\n"
            "6 + 6i\n"
            "7 + 7i\n"
            "2 + 2i\n"
            "8 + 8i\n"
            "3 + 3i\n"
            "9 + 9i\n"
            "4 + 4i\n"
            "5 + 5i\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Empty tree traversal for complex number tree") {
        Tree<Complex> empty_tree;
        std::stringstream output;
        for (auto node = empty_tree.begin_dfs_scan(); node != empty_tree.end_dfs_scan(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for complex number tree") {
        Tree<Complex> single_node_tree;
        Node<Complex> single_node(Complex(10, 10));
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_dfs_scan(); node != single_node_tree.end_dfs_scan(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output = "10 + 10i\n";
        CHECK(output.str() == expected_output);
    }
}
/************************************************************************************************* */
TEST_CASE("Testing HeapIterator for Tree<int>") {
    // Create nodes
    Node<int> root_node(10);
    Node<int> left_child(5);
    Node<int> right_child(15);
    Node<int> left_left_grandchild(3);
    Node<int> left_right_grandchild(7);
    Node<int> right_left_grandchild(12);
    Node<int> right_right_grandchild(20);

    Tree<int> binary_tree; // Binary tree

    // Build the binary tree structure
    binary_tree.add_root(root_node);
    binary_tree.add_sub_node(root_node, left_child);
    binary_tree.add_sub_node(root_node, right_child);
    binary_tree.add_sub_node(left_child, left_left_grandchild);
    binary_tree.add_sub_node(left_child, left_right_grandchild);
    binary_tree.add_sub_node(right_child, right_left_grandchild);
    binary_tree.add_sub_node(right_child, right_right_grandchild);

    // Tree structure:
    //        10
    //       /  \
    //      5    15
    //     / \   / \
    //    3   7 12  20

    SUBCASE("Valid HeapIterator traversal for binary tree") {
        std::stringstream output;
        for (auto node = binary_tree.begin_heap(); node != binary_tree.end_heap(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output =
            "3\n"
            "5\n"
            "7\n"
            "10\n"
            "12\n"
            "15\n"
            "20\n";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Empty tree traversal for binary tree") {
        Tree<int> empty_tree;
        std::stringstream output;
        for (auto node = empty_tree.begin_heap(); node != empty_tree.end_heap(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output = "";
        CHECK(output.str() == expected_output);
    }

    SUBCASE("Single node tree traversal for binary tree") {
        Tree<int> single_node_tree;
        Node<int> single_node(50);
        single_node_tree.add_root(single_node);
        std::stringstream output;
        for (auto node = single_node_tree.begin_heap(); node != single_node_tree.end_heap(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output = "50\n";
        CHECK(output.str() == expected_output);
    }
}
/************************************************************************************************* */
TEST_CASE("Testing HeapIterator for Tree<double>") {
    // Create nodes with double values
    Node<double> root_node(10.5);
    Node<double> child1(5.5);
    Node<double> child2(15.5);
    Node<double> left_left_grandchild(3.5);
    Node<double> left_right_grandchild(7.5);
    Node<double> right_left_grandchild(12.5);
    Node<double> right_right_grandchild(20.5);

    Tree<double> binary_tree; // Binary tree

    // Build the binary tree structure
    binary_tree.add_root(root_node);
    binary_tree.add_sub_node(root_node, child1);
    binary_tree.add_sub_node(root_node, child2);
    binary_tree.add_sub_node(child1, left_left_grandchild);
    binary_tree.add_sub_node(child1, left_right_grandchild);
    binary_tree.add_sub_node(child2, right_left_grandchild);
    binary_tree.add_sub_node(child2, right_right_grandchild);

    // Tree structure:
    //        10.5
    //       /    \
    //     5.5    15.5
    //    / \    /   \
    //  3.5  7.5 12.5  20.5

        std::stringstream output;
        for (auto node = binary_tree.begin_heap(); node != binary_tree.end_heap(); ++node) {
            output << node->get_value() << "\n";
        }
        std::string expected_output =
            "3.5\n"
            "5.5\n"
            "7.5\n"
            "10.5\n"
            "12.5\n"
            "15.5\n"
            "20.5\n";
        CHECK(output.str() == expected_output);
}
/************************************************************************************************* */
TEST_CASE("Testing HeapIterator for Tree<Complex>") {
    // Create nodes with complex numbers
    Node<Complex> root_node(Complex(0, 0));
    Node<Complex> child1(Complex(1, 1));
    Node<Complex> child2(Complex(2, 2));
    Node<Complex> child3(Complex(3, 3));
    Node<Complex> child4(Complex(4, 4));
    Node<Complex> child5(Complex(5, 5));

    Node<Complex> grandchild1(Complex(6, 6));
    Node<Complex> grandchild2(Complex(7, 7));
    Node<Complex> grandchild3(Complex(8, 8));
    Node<Complex> grandchild4(Complex(9, 9));

    Tree<Complex> five_ary_tree(5); // 5-ary tree

    // Build the tree structure
    five_ary_tree.add_root(root_node);
    five_ary_tree.add_sub_node(root_node, child1);
    five_ary_tree.add_sub_node(root_node, child2);
    five_ary_tree.add_sub_node(root_node, child3);
    five_ary_tree.add_sub_node(root_node, child4);
    five_ary_tree.add_sub_node(root_node, child5);

    five_ary_tree.add_sub_node(child1, grandchild1);
    five_ary_tree.add_sub_node(child1, grandchild2);
    five_ary_tree.add_sub_node(child2, grandchild3);
    five_ary_tree.add_sub_node(child3, grandchild4);

    // Expected heap order:
    //        0 + 0i
    //      /  |  \  \  \
    // 1 + 1i 2 + 2i 3 + 3i 4 + 4i 5 + 5i
    //  /  \      \
    // 6+6i 7+7i 8+8i 9+9i

    CHECK_THROWS_AS(five_ary_tree.begin_heap(), std::runtime_error);

}
/************************************************************************************************* */
TEST_CASE("Testing HeapIterator for Tree<std::string>") {
    // Create nodes with string values
    Node<std::string> root_node("root");
    Node<std::string> child1("child1");
    Node<std::string> child2("child2");
    Node<std::string> child3("child3");
    Node<std::string> child4("child4");
    Node<std::string> child5("child5");

    Tree<std::string> five_ary_tree(5); // 5-ary tree

    // Build the tree structure
    five_ary_tree.add_root(root_node);
    five_ary_tree.add_sub_node(root_node, child1);
    five_ary_tree.add_sub_node(root_node, child2);
    five_ary_tree.add_sub_node(root_node, child3);
    five_ary_tree.add_sub_node(root_node, child4);
    five_ary_tree.add_sub_node(root_node, child5);

    // Expected heap order:
    //        root
    //      /  |  \  \  \
    // child1 child2 child3 child4 child5

    CHECK_THROWS_AS(five_ary_tree.begin_heap(), std::runtime_error);
}
/************************************************************************************************* */
TEST_CASE("Node class addChild method tests") {
    SUBCASE("Adding a null child") {
        Node<int> parent(10);
        Node<int>* nullChild = nullptr;

        // Adding a null child should throw a std::runtime_error
        CHECK_THROWS_AS(parent.addChild(nullChild, 2), std::runtime_error);
    }

    SUBCASE("Adding too many children") {
        Node<int> parent(10);
        Node<int> child1(20);
        Node<int> child2(30);

        parent.addChild(&child1, 2);
        parent.addChild(&child2, 2);

        // Adding a third child should throw a std::runtime_error
        Node<int> child3(40);
        parent.addChild(&child3, 2);
        CHECK_THROWS_AS(parent.addChild(&child3, 2), std::runtime_error);
    }

}
TEST_CASE("Tree Class Destructor") {
    SUBCASE("Destructor Test") {
        Tree<int> tree;
        Node<int> root(1);
        tree.add_root(root);

        Node<int> child1(2);
        tree.add_sub_node(root, child1);

        Node<int> child2(3);
        tree.add_sub_node(root, child2);

        // Ensure nodes are properly deleted by destructor
        // No explicit check needed, as destructor should handle cleanup
    }
}
TEST_CASE("Complex Constructors") {
    // Default Constructor
    SUBCASE("Default Constructor") {
        Complex c;
        CHECK(c.getReal() == 0.0);
        CHECK(c.getImaginary() == 0.0);
    }

    // Parameterized Constructor
    SUBCASE("Parameterized Constructor") {
        Complex c(1.0, 2.0);
        CHECK(c.getReal() == 1.0);
        CHECK(c.getImaginary() == 2.0);
    }
}

TEST_CASE("Getter and Setter Methods") {
    Complex c;

    // Getter Methods
    SUBCASE("Getter Methods") {
        CHECK(c.getReal() == 0.0);
        CHECK(c.getImaginary() == 0.0);
    }

    // Setter Methods
    SUBCASE("Setter Methods") {
        c.setReal(3.0);
        c.setImaginary(4.0);
        CHECK(c.getReal() == 3.0);
        CHECK(c.getImaginary() == 4.0);
    }
}

TEST_CASE("Arithmetic Operations") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);

    // Addition
    SUBCASE("Addition") {
        Complex result = c1 + c2;
        CHECK(result.getReal() == 4.0);
        CHECK(result.getImaginary() == 6.0);
    }

    // Subtraction
    SUBCASE("Subtraction") {
        Complex result = c1 - c2;
        CHECK(result.getReal() == -2.0);
        CHECK(result.getImaginary() == -2.0);
    }

    // Multiplication
    SUBCASE("Multiplication") {
        Complex result = c1 * c2;
        CHECK(result.getReal() == -5.0);
        CHECK(result.getImaginary() == 10.0);
    }

    // Division
    SUBCASE("Division") {
        Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);

    // Perform division
    Complex result = c1 / c2;

    // Adjust these checks for precision as needed
    CHECK(std::abs(result.getReal() - 0.44) < 0.01);
    CHECK(std::abs(result.getImaginary() - 0.08) < 0.01);
    }
}

TEST_CASE("Comparison Operators") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex c3(1.0, 2.0);

    // Equality
    SUBCASE("Equality") {
        CHECK(c1 == c3);
        CHECK_FALSE(c1 == c2);
    }

    // Inequality
    SUBCASE("Inequality") {
        CHECK(c1 != c2);
        CHECK_FALSE(c1 != c3);
    }

    // Less Than
    SUBCASE("Less Than") {
        CHECK(c1 < c2);
        CHECK_FALSE(c2 < c1);
    }

    // Greater Than
    SUBCASE("Greater Than") {
        CHECK(c2 > c1);
        CHECK_FALSE(c1 > c2);
    }
}

TEST_CASE("Output Stream Operator") {
    Complex c(1.0, 2.0);

    // Output Format
    SUBCASE("Output Format") {
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str() == "1 + 2i");
    }
}

