/**
 ********************************************************************************
 * @file    List.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Doubly-Linked List Template Implementation
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __LIST_TPP__
#define __LIST_TPP__

#include <stdlib.h>

namespace DataStructures {
namespace List {

namespace __List {

template<typename _T>
struct ListNode {
    ListNode<_T> *prev;
    ListNode<_T> *next;
    _T data;
};

} // end namespace __List

using ListSize_t = unsigned int;

template<typename T>
class List {

    using ListNode = __List::ListNode<T>;

    public:

        List() {
            front = NULL;
            back = NULL;
            list_size = 0;
        }
        ~List() {
            T temp;
            while (list_size > 0) pop_front(temp);
        }

        void push_front(T data) {
            if (list_size == 0) {
                front = back = new ListNode;
                front->data = data;
                front->prev = NULL;
                front->next = NULL;
            }
            else {
                front->prev = new ListNode;
                front = front->prev;
                front->data = data;
                front->prev = NULL;
            }
            list_size++;
        }
        void push_back(T data) {
            if (list_size == 0) {
                front = back = new ListNode;
                back->data = data;
                back->prev = NULL;
                back->next = NULL;
            }
            else {
                back->next = new ListNode;
                back = back->next;
                back->data = data;
                back->next = NULL;
            }
            list_size++;
        }

        void pop_front(T& data) {
            if (list_size == 0) return;
            data = front->data;
            list_size--;
            if (list_size == 0) {
                delete front;
                front = NULL;
                back = NULL;
            }
            else {
                front = front->next;
                delete front->prev;
                front->prev = NULL;
            }
        }
        void pop_back(T& data) {
            if (list_size == 0) return;
            data = back->data;
            list_size--;
            if (list_size == 0) {
                delete back;
                front = NULL;
                back = NULL;
            }
            else {
                back = back->prev;
                delete back->next;
                back->next = NULL;
            }
        }
        T pop_front() {
            T data;
            pop_front(data);
            return data;
        }
        T pop_back() {
            T data;
            pop_back(data);
            return data;
        }

        inline T& peek_front() {
            return front->data;
        }
        inline T& peek_back() {
            return back->data;
        }

        ListSize_t size() {
            return list_size;
        }

        inline bool empty() {
            return list_size == 0;
        }

        T& operator[](ListSize_t index) {
            ListNode *current = front;
            for (ListSize_t i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }
        const T& operator[](const ListSize_t index) const {
            ListNode *current = front;
            for (ListSize_t i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }

    private:

        ListNode *front;
        ListNode *back;

        ListSize_t list_size;

};

} // end namespace List
} // end namespace DataStructures

#endif // __LIST_TPP__