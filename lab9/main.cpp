#include <iostream>
#include <cstring>

template <typename K, typename V>
class Map {
private:
    struct Node {
        K key;
        V value;
        Node* next;
    };

    Node* head;
    int size;

public:
    Map() : head(nullptr), size(0) {}

    ~Map() {
        Clear();
    }

    V& operator[](const K& key) {
        Node* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }

        Node* newNode = new Node{key, V(), nullptr};
        if (head == nullptr) {
            head = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        size++;
        return head->value;
    }

    bool Get(const K& key, V& value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int Count() const {
        return size;
    }

    void Clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        size = 0;
    }

    bool Delete(const K& key) {
        if (head == nullptr) {
            return false;
        }
        if (head->key == key) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }
        Node* current = head;
        while (current->next != nullptr) {
            if (current->next->key == key) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool Includes(const Map<K, V>& map) {
        Node* current = map.head;
        while (current != nullptr) {
            V value;
            if (!Get(current->key, value)) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Map<K, V>& map) {
        Node* current = map.head;
        int index = 0;
        while (current != nullptr) {
            os << "Index:" << index << ", Key=" << current->key << ", Value=" << current->value << std::endl;
            current = current->next;
            index++;
        }
        return os;
    }

    template <typename T>
    class iterator {
    private:
        Node* current;
        int index;

    public:
        iterator(Node* node, int i) : current(node), index(i) {}

        bool operator!=(const iterator<T>& other) const {
            return current != other.current;
        }

        iterator<T>& operator++() {
            current = current->next;
            index++;
            return *this;
        }

        std::tuple<K, V, int> operator*() const {
            return std::make_tuple(current->key, current->value, index);
        }
    };

    iterator<std::tuple<K, V, int>> begin() {
        return iterator<std::tuple<K, V, int>>(head, 0);
    }

    iterator<std::tuple<K, V, int>> end() {
        return iterator<std::tuple<K, V, int>>(nullptr, size);
    }
};

int main() {
    Map<int, const char*> m;
    m[10] = "C++";
    m[20] = "test";
    m[30] = "Poo";

    std::cout << m;

    m[20] = "result";

    std::cout << m;

    return 0;
}