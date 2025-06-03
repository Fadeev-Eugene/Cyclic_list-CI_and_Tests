#pragma once

#include <concepts>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>

template<typename T>
class CyclicList {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
        Node(T&& val) : value(std::move(val)), prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    size_t sz = 0;

public:
    CyclicList() noexcept = default;

    CyclicList(const CyclicList& other) {
        for (const auto& val : other) {
            push_back(val);
        }
    }

    CyclicList(CyclicList&& other) noexcept : head(other.head), sz(other.sz) {
        other.head = nullptr;
        other.sz = 0;
    }

    ~CyclicList() { clear(); }

    CyclicList& operator=(const CyclicList& other) {
        if (this != &other) {
            clear();
            for (const auto& val : other) {
                push_back(val);
            }
        }
        return *this;
    }

    CyclicList& operator=(CyclicList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            sz = other.sz;
            other.head = nullptr;
            other.sz = 0;
        }
        return *this;
    }

    // Вставка элементов
    void push_back(const T& val) {
        Node* node = new Node(val);
        if (!head) {
            node->next = node->prev = node;
            head = node;
        } else {
            Node* tail = head->prev;
            tail->next = node;
            node->prev = tail;
            node->next = head;
            head->prev = node;
        }
        ++sz;
    }

    void push_back(T&& val) {
        Node* node = new Node(std::move(val));
        if (!head) {
            node->next = node->prev = node;
            head = node;
        } else {
            Node* tail = head->prev;
            tail->next = node;
            node->prev = tail;
            node->next = head;
            head->prev = node;
        }
        ++sz;
    }

    void clear() noexcept {
        if (!head) return;
        Node* current = head;
        for (size_t i = 0; i < sz; ++i) {
            Node* to_delete = current;
            current = current->next;
            delete to_delete;
        }
        head = nullptr;
        sz = 0;
    }

    size_t size() const noexcept { return sz; }
    bool empty() const noexcept { return sz == 0; }

    template<bool IsConst>
    class Iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = std::conditional_t<IsConst, const T&, T&>;

         Iterator() : node(nullptr), list(nullptr), steps(0) {}
        Iterator(Node* n, const CyclicList* lst, size_t step = 0) : node(n), list(lst), steps(step) {}

        reference operator*() const {
            if (!node) throw std::runtime_error("Dereferencing null iterator");
            return node->value;
        }
        pointer operator->() const { return &(operator*()); }

        Iterator& operator++() {
            if (!node) throw std::runtime_error("Incrementing null iterator");
            node = node->next;
            ++steps;
            if (steps >= list->size()) {
                node = nullptr;
                steps = 0;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator--() {
            if (!node) throw std::runtime_error("Decrementing null iterator");
            if (steps == 0) {
                node = nullptr;
                throw std::runtime_error("Iterator cannot decrement before begin");
            }
            node = node->prev;
            --steps;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp = *this;
            --(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.node == rhs.node && lhs.list == rhs.list && lhs.steps == rhs.steps;
        }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return !(lhs == rhs); }

    private:
        Node* node;
        const CyclicList* list;
        size_t steps;
    };

    using iterator = Iterator<false>;
    using const_iterator = Iterator<true>;


    iterator begin() noexcept { return iterator(head, this, 0); }
    iterator end() noexcept { return iterator(nullptr, this, 0); }

    const_iterator begin() const noexcept { return const_iterator(head, this, 0); }
    const_iterator end() const noexcept { return const_iterator(nullptr, this, 0); }

    const_iterator cbegin() const noexcept { return const_iterator(head, this, 0); }
    const_iterator cend() const noexcept { return const_iterator(nullptr, this, 0); }

    bool operator==(const CyclicList& other) const {
        if (size() != other.size()) return false;
        auto it1 = begin();
        auto it2 = other.begin();
        while (it1 != end() && it2 != other.end()) {
            if (*it1 != *it2) return false;
            ++it1; ++it2;
        }
        return true;
    }

    bool operator!=(const CyclicList& other) const { return !(*this == other); }
};
