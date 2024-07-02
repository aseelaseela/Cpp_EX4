#ifndef TREE_VISUALIZER_HPP
#define TREE_VISUALIZER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <iomanip> // For std::setprecision
#include <sstream> // For std::stringstream
#include "Node.hpp" // Assuming Node.hpp contains your Node<T> definition

template <typename T>
class TreeVisualizer {
public:
    TreeVisualizer(sf::RenderWindow& window, const Node<T>& rootNode);

    void visualize();

private:
    sf::RenderWindow& window;
    const Node<T>& rootNode;
    sf::Font font;
    const float nodeRadius = 35.f; // Radius of nodes
    const float verticalSpacing = 80.f; // Vertical spacing between nodes
    const float initialHorizontalSpacing = 200.f; // Initial horizontal spacing for root node
    std::map<const Node<T>*, sf::Vector2f> positions; // Map to store positions of nodes

    void positionNodes(const Node<T>* node, float x, float y, float horizontalSpacing);
};

template <typename T>
TreeVisualizer<T>::TreeVisualizer(sf::RenderWindow& window, const Node<T>& rootNode)
    : window(window), rootNode(rootNode) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: Failed to load font 'arial.ttf'. Make sure the file exists and the path is correct.\n";
    }
}

template <typename T>
void TreeVisualizer<T>::visualize() {
    // Positioning nodes starting from the root
    positionNodes(&rootNode, window.getSize().x / 2.f, nodeRadius + 50.f, initialHorizontalSpacing);

    // Main visualization loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with pink color
        window.clear(sf::Color(255, 192, 203)); // RGB values for pink

        // Draw nodes and their connections
        for (const auto& pair : positions) {
            const Node<T>* node = pair.first;
            sf::Vector2f position = pair.second;

            // Draw node as a circle
            sf::CircleShape circle(nodeRadius);
            circle.setFillColor(sf::Color::Blue); // Node color
            circle.setPosition(position - sf::Vector2f(nodeRadius, nodeRadius)); // Adjust position
            window.draw(circle);

            // Draw text label for node
            sf::Text text;
            text.setFont(font);

            // Format node value to show three digits before the decimal point
            std::stringstream ss;
            ss << std::fixed << std::setprecision(3) << node->get_value();
            text.setString(ss.str());

            text.setCharacterSize(12); // Font size
            text.setFillColor(sf::Color(128, 0, 128)); // RGB values for purple
            text.setStyle(sf::Text::Bold); // Set text style to bold
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f); // Center origin
            text.setPosition(position);
            window.draw(text);

            // Draw lines to connect node with its children
            for (const Node<T>* child : node->getChildren()) {
                if (child) {
                    sf::Vector2f childPosition = positions.at(child);

                    sf::Vertex line[] = {
                        sf::Vertex(position, sf::Color::Black), // Line start
                        sf::Vertex(childPosition, sf::Color::Black) // Line end
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        window.display(); // Display rendered frame
    }
}

template <typename T>
void TreeVisualizer<T>::positionNodes(const Node<T>* node, float x, float y, float horizontalSpacing) {
    if (!node) {
        std::cerr << "Error: Cannot position null node.\n";
        return;
    }

    // Store position of current node
    positions[node] = sf::Vector2f(x, y);

    // Calculate horizontal offset for child nodes
    float childXOffset = x - (node->getChildren().size() - 1) * horizontalSpacing / 2.f;

    // Recursively position child nodes
    for (size_t i = 0; i < node->getChildren().size(); ++i) {
        const Node<T>* child = node->getChildren()[i];
        if (child) {
            positionNodes(child, childXOffset + i * horizontalSpacing, y + verticalSpacing, horizontalSpacing / 2.f);
        } else {
            std::cerr << "Error: Child node at index " << i << " is null.\n";
        }
    }
}

#endif // TREE_VISUALIZER_HPP
