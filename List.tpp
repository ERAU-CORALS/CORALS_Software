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

#ifndef __LIST_TPP__ // These are called "#include guards"
#define __LIST_TPP__ // Differentiates header files, ignores additional declarations from the same file

#include <stdlib.h> // C Standard Library, general utility functions

namespace DataStructures { // Begin namespace DataStructures, encapsulates all code to this name

namespace __List { // Nested namespace, sub-sect of DataStructures for specifity

template<typename _T> // Defining a template STRUCT for a ListNode using a generic type _T (type not value, placeholder for any data type)
struct ListNode { // Typical doubly linked list definition
    ListNode<_T> *prev; // Member: Define pointer to a ListNode of the same type - link to previous node in a doubly linked list
    ListNode<_T> *next; // same but for next node
    _T data; // Define data member of type _T - stores actual data for the node
};

} // end namespace __List

using ListSize_t = unsigned int; // Defines type alias for unsigned int as ListSize_t

template<typename T> // Define template CLASS for List using a generic type T
class List {

    using ListNode = __List::ListNode<T>; // Creates alias ListNode for __List::ListNode<T> (ListNode is a type defined in the __List namespace) (shortcut to avoid typing)
        // NOTE: (namespace)::(type) is the syntax for accessing a type defined in a namespace
    public: // Accessible to all code outside of this class (List)

        List() { // Default constructor for List class
            front = NULL; // Initialize front pointer to NULL
            back = NULL; 
            list_size = 0; 
        }
        ~List() { // Destructor for List class
            T temp; // Temp var type T
            while (list_size > 0) pop_front(temp); // Removes front node and stores in temp var until empty
        }

        void push_front(T data) { // Function to add a node to the front of the list
            if (list_size == 0) { 
                front = back = new ListNode; // create a new node and set front and back pointers to it (front = first data point, etc. + "new" allocates var on heap)
                front->data = data; // Set data of ListNode pointed to by front (-> is used to dereference pointer and access member)
                front->prev = NULL; // Set prev member of ListNode pointed to by front to NULL
                front->next = NULL; 
            }
            else { 
                front->prev = new ListNode; // Create a new node and set it as the previous node of the current front node
                front = front->prev; // Set front pointer to the new node
                front->data = data; // Set data of new ListNode
                front->prev = NULL; // Encapsulate list
            }
            list_size++; // Increment list_size
        }
        void push_back(T data) { // Function to add a node to the back of the list
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

        void pop_front(T& data) { // Function to remove front node from list (& is used to pass by reference)
            if (list_size == 0) return; // Do nothing if list is empty
            data = front->data; // Set var to data of front node
            list_size--; 
            if (list_size == 0) { // If list empty after removal
                delete front; // Deallocate front node (delete operator deallocates and calls destructor)
                front = NULL;
                back = NULL;
            }
            else {
                front = front->next; // Define new front node
                delete front->prev;
                front->prev = NULL;
            }
        }
        void pop_back(T& data) { // Function to remove back node from list
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
        T pop_front() { // Function to remove front node from list and return data
            T data; // Define var to store data
            pop_front(data); // Call function to remove front node
            return data; 
        }
        T pop_back() { // Function to remove back node from list and return data
            T data;
            pop_back(data);
            return data;
        }

        inline T& peek_front() { // Function to get REFERENCE to data of front node
            return front->data; 
        }
        inline T& peek_back() { // Function to get REFERENCE to data of back node
            return back->data;
        }

        ListSize_t size() { //Function to return size of list using alias ListSize_t for unsigned int
            return list_size;
        }

        inline bool empty() { // Function to check if list is empty
            return list_size == 0; // Compares list size to 0 and returns boolean
        }

        T& operator[](ListSize_t index) { // Operator overload for [] to access data at index (Allows modification of list elements at index)
            ListNode *current = front; // Define pointer to front node of type ListNode as current
            for (ListSize_t i = 0; i < index; i++) { // Iterate through list up to listed index
                current = current->next; // Set current to next node
            }
            return current->data;
        }
        const T& operator[](const ListSize_t index) const { // Const Operator overload for [] to access data at index (Does not allow modification of list elements at index)
            ListNode *current = front;
            for (ListSize_t i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }

    private: // Accessible only to this class (List)

        ListNode *front; 
        ListNode *back;

        ListSize_t list_size; 

};

} // end namespace DataStructures

#endif // __LIST_TPP__ // End of include guard