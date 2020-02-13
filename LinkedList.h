#pragma once
#include <iostream>
#include <vector>

template <typename T>
class LinkedList {
  
  private:
    unsigned int size;

    class Node {
      T value;
      Node* next = nullptr;
      Node* previous = nullptr;
    };

    Node* head;

    Node* tail;

    Node* follower;

  public:
    //
    //Behaviors
    //
    void PrintForward() const;

    void PrintReverse() const;

    void PrintForwardRecursive(const Node* node) const;

    void PrintReverseRecursive(const Node* node) const;

    //
    //Accessors
    //
    unsigned int NodeCount() const;

    void FindAll(std::vector<Node*> &outData, const T&value) const;

    const Node* Find(const T &data) const;

    Node* Find(const T &data);

    const Node* GetNode(unsigned int index) const;

    Node* GetNode(unsigned int index);

    Node* Head();

    const Node* Head() const;

    Node* Tail();

    const Node* Tail() const;

    //
    //Insertion
    //
    void AddHead(const T &data);
    
    void AddTail(const T &data);

    void AddNodesHead(const T* data, unsigned int count);

    void AddNodesTail(const T* data, unsigned int count);

    void InsertAfter(Node* node, const T &data);

    void InsertBefore(Node* node, const T &data);

    void InsertAt(const T &data, unsigned int index);

    //
    //Removal
    //
    bool RemoveHead();

    bool RemoveTail();

    unsigned int Remove(const T &data);

    bool removeAt(int index);

    void Clear();

    //
    //Operators
    //
    const T & operator[](unsigned int index) const;

    T & operator[](unsigned int index);

    bool operator==(const LinkedList<T> &rhs) const;

    LinkedList<T> & operator=(const LinkedList<T> &rhs);

    //
    //Construction / Destruction
    //
    LinkedList();

    LinkedList(const LinkedList<T> &list);

    ~LinkedList();
};

//
//Behaviors
//
template <typename T>
void LinkedList<T>::PrintForward() const {
  Node* target = this->head;
  while(target != nullptr) {
    std::cout << target->value << std::endl;
    target = target->next;
  }
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
  
}
