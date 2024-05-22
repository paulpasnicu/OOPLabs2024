#include <iostream>

template<typename T>
class TreeNode {
public:
    // constructorul
    TreeNode(const T& value) {
        this->value = value; //valoarea nodului
        this->parent = nullptr; //nod parinte (null)
        this->child = nullptr; // copil (null)
        this->sibling = nullptr; // frate (null)
    }

    // add node
    void add_node(TreeNode<T>* parent, const T& value) {
        TreeNode<T>* new_node = new TreeNode<T>(value); //cream nod nou
        if (parent == nullptr) { //daca nu exista
            if (this->parent != nullptr) { // verificam daca nodul are parinte
                std::cout << "eroare" << std::endl;
                delete new_node;
                return;
            }
            this->parent = new_node;
        }
        else {
            new_node->parent = parent;
            if (parent->child == nullptr) {
                parent->child = new_node;
            } else {
                TreeNode<T>* currentChild = parent->child;
                // gasim copilul
                while (currentChild->sibling != nullptr) {
                    currentChild = currentChild->sibling;
                }
                currentChild->sibling = new_node;
            }
        }
    }

    // get node
    TreeNode<T>* get_node(TreeNode<T>* parent = nullptr) {
        if (parent == nullptr)
            return this->parent;
        return parent->child;
    }

    // delete node
    void delete_node(TreeNode<T>* node) {
        if (node == nullptr)
            return;

        if (node->parent != nullptr) {
            TreeNode<T>* currentChild = node->parent->child;
            if (currentChild == node) {
                node->parent->child = node->sibling;
            } else {
                while (currentChild->sibling != nullptr) {
                    if (currentChild->sibling == node) {
                        currentChild->sibling = node->sibling;
                        break;
                    }
                    currentChild = currentChild->sibling;
                }
            }
        }

        delete_subtree(node);
    }

    // find (cu pointer de functie)
    TreeNode<T>* find(bool (*compare)(const T&)) {
        if (compare(value))
            return this;

        TreeNode<T>* currentChild = child;
        while (currentChild != nullptr) {
            TreeNode<T>* result = currentChild->find(compare);
            if (result != nullptr)
                return result;
            currentChild = currentChild->sibling;
        }

        return nullptr;
    }

    // insert
    void insert(TreeNode<T>* parent, const T& value, int index) {
        if (parent != nullptr) {
            TreeNode<T>* currentChild = parent->child;
            int currentIndex = 0;
            while (currentChild != nullptr && currentIndex < index - 1) {
                currentChild = currentChild->sibling;
                currentIndex++;
            }

            if (currentIndex < index - 1) {
                std::cout << "index invalid" << std::endl;
                return;
            }

            TreeNode<T>* new_node = new TreeNode<T>(value);
            new_node->parent = parent;

            if (currentChild == nullptr) {
                parent->child = new_node;
            } else {
                new_node->sibling = currentChild->sibling;
                currentChild->sibling = new_node;
            }
        } else {
            std::cout << "eroare" << std::endl;
        }
    }

    // sort (cu pointer de functie)
    void sort(bool (*compare)(const T&, const T&) = nullptr) {
        if (child != nullptr) {
            TreeNode<T>* currentChild = child;
            while (currentChild != nullptr) {
                currentChild->sort(compare);
                currentChild = currentChild->sibling;
            }

            if (compare != nullptr) {
                bool swapped;
                do {
                    swapped = false;
                    currentChild = child;
                    while (currentChild->sibling != nullptr) {
                        if (compare(currentChild->value, currentChild->sibling->value)) {
                            T temp = currentChild->value;
                            currentChild->value = currentChild->sibling->value;
                            currentChild->sibling->value = temp;
                            swapped = true;
                        }
                        currentChild = currentChild->sibling;
                    }
                } while (swapped);
            } else {
                bool swapped;
                do {
                    swapped = false;
                    currentChild = child;
                    while (currentChild->sibling != nullptr) {
                        if (currentChild->value < currentChild->sibling->value) {
                            T temp = currentChild->value;
                            currentChild->value = currentChild->sibling->value;
                            currentChild->sibling->value = temp;
                            swapped = true;
                        }
                        currentChild = currentChild->sibling;
                    }
                } while (swapped);
            }
        }
    }

    // count
    int count(TreeNode<T>* node = nullptr) {
        if (node == nullptr)
            node = parent;

        int count = 0;
        TreeNode<T>* currentChild = node->child;
        while (currentChild != nullptr){
            count++;
            count += count(currentChild);
            currentChild = currentChild->sibling;
        }

        return count;
    }

private:
    T value;
    TreeNode<T>* parent;
    TreeNode<T>* child;
    TreeNode<T>* sibling;
};