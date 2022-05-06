#pragma once

#include <iostream>
#include <memory>

namespace bicycle {

    template<typename ValueType>
    struct Node {
        ValueType value;
        Node *next;
        Node *prev;

        bool HasNext() const {
            return next != nullptr;
        }

        bool HasPrev() const {
            return prev != nullptr;
        }

        ~Node() {
            //std::cerr << "NODE DESTRUCTED!" << std::endl;
        }
    };

    template<typename ValueType>
    Node<ValueType> *ConstructNode(const ValueType &value) {
        return new Node<ValueType>{value, nullptr, nullptr};
    }

    template<typename ValueType>
    class LinkedList {
    public:

        LinkedList() = default;

        LinkedList(LinkedList &&) = default;

        LinkedList(const LinkedList &) = delete;

        LinkedList &operator=(const LinkedList &) = delete;

        template<typename Callback>
        void TravelWithCallback(Callback callback) {
            Node<ValueType> *curr = front_;
            while (curr) {
                Node<ValueType> *next = curr->next;
                callback(curr);
                curr = next;
            }
        }

        template<typename Callback>
        void TravelWithCallback(Callback callback) const {
            Node <ValueType>* curr = front_;
            while (curr) {
                Node<ValueType> *next = curr->next;
                callback(curr);
                curr = next;
            }
        }

        ~LinkedList() {
            TravelWithCallback([](Node<ValueType> *val) {
                delete val;
            });
        }

        void Print(std::ostream &out = std::cout) const {
            TravelWithCallback([&](Node<ValueType> *val) {
                if (val != tail_) {
                    out << val->value << " <-> ";
                } else {
                    out << val->value;
                }

                return;
            });
        }

        Node<ValueType> *PushBack(Node<ValueType> *val) {
            if (front_ == nullptr && tail_ == nullptr) {
                tail_ = front_ = val;
            } else {
                tail_->next = val;
                val->prev = tail_;
                tail_ = val;
            }
            size_++;
            return tail_;
        }

        Node<ValueType> *PushBack(const ValueType &value) {
            return PushBack(ConstructNode(value));
        }

        Node<ValueType> *PushFront(const ValueType &value) {
            return PushFront(ConstructNode(value));
        }

        Node<ValueType> *PushFront(Node<ValueType> *val) {
            if (front_ == nullptr && tail_ == nullptr) {
                tail_ = front_ = val;
            } else {
                front_->prev = val;
                val->next = front_;
                front_ = val;
            }
            size_++;
            return front_;
        }

        Node<ValueType> *InsertAfter(Node<ValueType> *after_this, const ValueType &value) {
            if (after_this == tail_ || size_ == 1) {
                return PushBack(value);
            }
            auto new_node = ConstructNode(value);
            new_node->next = after_this->next;
            new_node->prev = after_this;
            after_this->next = new_node;
            size_++;
            if (after_this == tail_) {
                tail_ = new_node;
            }

            return new_node;
        }

        Node<ValueType> *InsertBefore(Node<ValueType> *before_this, const ValueType &value) {
            if (before_this == front_ || size_ == 1) {
                return PushFront(value);
            }

            auto new_node = ConstructNode(value);
            new_node->prev = before_this->prev;
            new_node->next = before_this;

            before_this->prev->next = new_node;
            before_this->prev = new_node;



            if (before_this == front_) {
                front_ = new_node;
            }
            size_++;

            return new_node;
        }

        Node<ValueType> *Erase(Node<ValueType> *erase_this) {
            auto prev_node = erase_this->prev;
            auto next_node = erase_this->next;

            if (prev_node) {
                prev_node->next = next_node;
            }

            if (next_node) {
                next_node->prev = prev_node;
            }

            erase_this->next = nullptr;
            erase_this->prev = nullptr;

            size_--;

            if (erase_this == front_) {
                front_ = next_node;
            }
            if (erase_this == tail_) {
                tail_ = prev_node;
            }

            delete erase_this;
            return next_node;
        }

        size_t Size() const {
            return size_;
        }

    private:
        Node<ValueType> *front_ = nullptr;
        Node<ValueType> *tail_ = nullptr;
        size_t size_ = 0;
    };

}