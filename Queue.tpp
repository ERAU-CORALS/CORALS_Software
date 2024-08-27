/**
 ********************************************************************************
 * @file    Queue.tpp
 * @author  Logan Ruddick (Logan@Ruddicks.net)
 * @brief   Queue Template Implementation
 * @version 1.0
 * @date    2024-03-20
 ********************************************************************************
 * @copyright Copyright (c) 2024
 ********************************************************************************
**/

#ifndef __QUEUE_TPP__
#define __QUEUE_TPP__

#include <stdlib.h>

namespace DataStructures {

namespace __Queue {

template<typename _T>
struct QueueNode {
    QueueNode<_T> *next;
    _T data;
};

} // end namespace __Queue

using QueueSize_t = unsigned int;

template<typename T>
class Queue {

    using QueueNode = __Queue::QueueNode<T>;

    public:

        Queue() {
            head = NULL;
            queue_size = 0;
        }
        ~Queue() {
            T temp;
            while (queue_size > 0) pop(temp);
        }

        void push(T data) {
            if (queue_size == 0) {
                head = new QueueNode;
                head->data = data;
                head->next = head;
            }
            else {
                QueueNode *new_node = new QueueNode; 
                new_node->data = data;
                new_node->next = head->next;
                head->next = new_node;
                head = new_node; 
            }
            queue_size++;
        }
        void pop(T& data) {
            if (queue_size == 0) return;
            data = head->next->data;
            queue_size--;
            if (queue_size == 0) {
                delete head;
                head = NULL;
            }
            else {
                QueueNode *rm = head->next;
                head->next = rm->next;
                delete rm;
            }
        }
        inline T pop() {
            T data;
            pop(data);
            return data;
        }
        inline T& peek() { return head->next->data; }

        inline QueueSize_t size() { return queue_size; }
        inline bool empty() { return queue_size == 0; }

    private:

        QueueNode *head;
        QueueSize_t queue_size;

};

} // end namespace DataStructures

#endif // __LIST_HPP__