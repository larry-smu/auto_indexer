#ifndef INC_20F_AUTO_IDX_DSLIST_H
#define INC_20F_AUTO_IDX_DSLIST_H

#include <iostream>

//Node for LinkedList
template <typename T>
struct Node {
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template <typename T>
class DSList {
private:
    Node<T>* head;
    Node<T>* tail;
    int length;

public:
    DSList();
    ~DSList();
    DSList(const DSList &);

    void push_back(T); //Append
    int search(T); //Search by data, return index
    T& at(int); //Search by index, return data
    int getLength();
    void print();
    void remove(int);
    void sort();
    bool find(T);

    DSList<T> &operator=(const DSList<T> &);

};

/**
 * Rule of Three
 **/

//Constructor
template<typename T>
DSList<T>::DSList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}

//Destructor
template<typename T>
DSList<T>::~DSList() {
    Node<T>* cur = this->head;

    while(cur != nullptr) {
        cur = cur->next;
        delete this->head;
        this->head = cur;
    }

    delete this->head;
}

//Copy Constructor
template<typename T>
DSList<T>::DSList(const DSList<T>& List)
{
    if ( List.head == nullptr) head = tail = nullptr;
    else {
        Node<T>* new_node = new Node<T>;
        new_node->data = List.head->data;
        new_node->next = nullptr;
        new_node->prev = nullptr;

        head = new_node;
        Node<T>* temp = List.head->next;
        Node<T>* tempThis = head;
        while (temp != nullptr) {
            Node<T>* new_cur_node = new Node<T>;
            new_cur_node->data = List.head->data;
            new_cur_node->next = nullptr;
            new_cur_node->prev = tempThis;

            tempThis->next = new_cur_node;
            tempThis = tempThis->next;
            temp = temp->next;

            free(new_cur_node);
        }
        tail = tempThis;

        delete temp;
    }
}

/**
 * Functions
 **/

//Append
template <typename T>
void DSList<T>::push_back(T data) {

    //Create a node for the input data
    Node<T>* new_node = new Node<T>;
    new_node->data = data;
    new_node->next = nullptr;

    //Append to the tail
    if(this->head != nullptr) {
        Node<T> *temp = this->tail;
        new_node->prev = temp;
        temp->next = new_node;
        this->tail = new_node;
    } else {
        this->head = new_node;
        this->tail = new_node;
    }

    //Increase the length of this Linked List by 1
    ++length;
};

//Search by data, return index
template <typename T>
int DSList<T>::search(T data) {

    //If the list is empty
    if(this->head == nullptr)
        return -1;

    Node<T>* cur = this->head;
    int index = 0;

    if(cur->data == data)
        return index;

    while(cur != nullptr) {
        cur = cur->next;
        ++index;
        if(cur->data == data)
            return index;
    }

    //Not found
    return -1;
}

//Search by index, return data
template <typename T>
T& DSList<T>::at(int index) {
    if(index == 0)
        return this->head->data;

    Node<T>* cur = this->head;

    for(int i = 0; i < index; ++i) {
        cur = cur->next;
    }

    return cur->data;
}

//getLength()
template <typename T>
int DSList<T>::getLength() {
    return length;
}

//print()
template <typename T>
void DSList<T>::print() {
    if(this->head == nullptr)
        std::cout << "Empty List" << std::endl;
    else {
        Node<T>* cur = this->head;

        while(cur != nullptr) {
            std::cout << cur->data << std::endl;
            cur = cur->next;
        }
    }
}

template<typename T>
void DSList<T>::remove(int index) {
    Node<T> *cur = this->head;
    Node<T> *temp;

    if(index == 0 && this->getsize() == 0)
        return;

    if(index >= this->getsize())
        return;

    else{
        int i = 0;
        while(i < index){
            temp = cur;
            cur = cur->next;
            ++i;
        }
        if(cur->next == nullptr)
            temp->next = nullptr;
        else
            temp->next = cur->next;
    }
}

template<typename T>
void DSList<T>::sort() {
    Node<T>* cur = this->head;
    Node<T>* compare = this->head;

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length - 1; ++j) {
            if (cur->data < compare->data) {
                T temp_data = cur->data;
                cur->data = compare->data;
                compare->data = temp_data;

            }
            compare = compare->next;
        }

        compare = this->head;
        cur = this->head->next;

        for (int z = 0; z < i; ++z) {
            cur = cur->next;
        }
    }
}

template<typename T>
bool DSList<T>::find(T data) {
    if(this->head == nullptr)
        return false;
    else {
        Node<T>* cur = this->head;

        while(cur != nullptr) {
            if(cur->data == data) return true;
            cur = cur->next;
        }
    }

    return false;
}


template<typename T>
DSList<T> &DSList<T>::operator= (const DSList<T> &l) {
    if (l.head == nullptr) head = tail = nullptr;
    else {
        Node<T>* new_node = new Node<T>;
        new_node->data = l.head->data;
        new_node->next = nullptr;
        new_node->prev = nullptr;

        head = new_node;
        Node<T>* temp = l.head->next;
        Node<T>* tempThis = head;
        while (temp != nullptr) {
            Node<T>* new_cur_node = new Node<T>;
            new_cur_node->data = l.head->data;
            new_cur_node->next = nullptr;
            new_cur_node->prev = tempThis;

            tempThis->next = new_cur_node;
            tempThis = tempThis->next;
            temp = temp->next;

            free(new_cur_node);
        }
        tail = tempThis;

        delete temp, tempThis, new_node;
    }

    return *this;
}


#endif //INC_20F_AUTO_IDX_DSLIST_H