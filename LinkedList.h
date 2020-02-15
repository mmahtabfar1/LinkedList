#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList {
  
  private:
    unsigned int size;

    class Node {
      public:
        T value;
        Node* next = nullptr;
        Node* previous = nullptr;
    };

    Node* head;

    Node* tail;

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

    void FindAll(std::vector<Node*>& outData, const T& value) const;

    const Node* Find(const T& data) const;

    Node* Find(const T& data);

    const Node* GetNode(unsigned int index) const;

    Node* GetNode(unsigned int index);

    Node* Head();

    const Node* Head() const;

    Node* Tail();

    const Node* Tail() const;

    //
    //Insertion
    //
    void AddHead(const T& data);
    
    void AddTail(const T& data);

    void AddNodesHead(const T* data, unsigned int count);

    void AddNodesTail(const T* data, unsigned int count);

    void InsertAfter(Node* node, const T& data);

    void InsertBefore(Node* node, const T& data);

    void InsertAt(const T& data, unsigned int index);

    //
    //Removal
    //
    bool RemoveHead();

    bool RemoveTail();

    unsigned int Remove(const T& data);

    bool removeAt(int index);

    void Clear();

    //
    //Operators
    //
    const T& operator[](unsigned int index) const;

    T& operator[](unsigned int index);

    bool operator==(const LinkedList<T>& rhs) const;

    LinkedList<T>& operator=(const LinkedList<T>& rhs);

    //
    //Construction / Destruction
    //
    LinkedList();

    LinkedList(const LinkedList<T>& list);

    ~LinkedList();
};

//
//constructors
//
template <typename T>
LinkedList<T>::LinkedList() {
  this->size = 0;
  this->head = nullptr;
  this->tail = nullptr;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
  //shallow copy
  this->size = list.size;
  
  Node* target = list.head;

  while(target != nullptr) {
    this->AddTail(target->value);
    target = target->next;
  }
}

//Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
  this->Clear();
}

//
//Behaviors
//
template <typename T>
void LinkedList<T>::PrintForward() const {
  Node* target = head;
  while(target != nullptr) {
    std::cout << target->value << std::endl;
    target = target->next;
  }
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
  Node* target = tail;
  while(target != nullptr) {
    std::cout << target->value << std::endl;
    target = target->previous;
  }
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
  if(node == nullptr) return;
  std::cout << node->value << std::endl;
  PrintForwardrecursive(node->next);
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
  if(node == nullptr) return;
  std::cout << node->value << std::endl;
  PrintReverseRecursive(node->previous);
}

//
//Accessors
//
template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
  return this->size;
}

template <typename T>
void LinkedList<T>::FindAll(std::vector<Node*>& outData, const T& value) const {
  //create pointer to head
  Node* target = head;
  
  //iterate through list looking for values to add to vector
  while(target != nullptr) {
    if(target->value == value) {
      outData.push_back(target);
    }
    target = target->next;
  }
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
  Node* target = head;
  while(target != nullptr) {
    if(target->value == data) return target;
    target = target->next;
  }
  return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
  Node* target = head;
  while(target != nullptr) {
    if(target->value == data) return target;
    target = target->next;
  }
  return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
  int counter = 0;
  Node* target = head;

  while(counter < index) {
    target = target->next;
    counter++;
  }
  return target;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
  int counter = 0;
  Node* target = head;

  while(counter < index) {
    target = target->next;
    counter++;
  }
  return target;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
  return this->head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
  return this->head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
  return this->tail;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
  return this->tail;
}

//
//Insertion
//
template <typename T>
void LinkedList<T>::AddHead(const T& data) {
  if(size == 0) {
    head = new Node;
    head->value = data;
    tail = head;
    size++;
  }
  else {
    Node* temp = head;
    head = new Node;
    head->value = data;
    head->next = temp;
    temp->previous = head;
    size++;
  }
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {
  if(size == 0) {
    tail = new Node;
    tail->value = data;
    head = tail;
    size++;
  }
  else {
    Node* temp = tail;
    tail = new Node;
    tail->value = data;
    temp->next = tail;
    tail->previous = temp;
    size++;
  }
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
  for(int i=(count-1); i>0; i++) {
    AddHead(data[i]);
  }
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
  for(unsigned int i=0; i<count; i++) {
    AddTail(data[i]);
  }
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
  Node* target = node;

  target = new Node;
  target->value = data;
  target->previous = node;
  target->next =(node->next);
  node->next = target;
  target->next->previous = target;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
  Node* target = node;

  target = new Node;
  target->value = data;
  target->next = node;
  node->previous->next = target;
  target->previous = node->previous;
  node->previous = target;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
  unsigned int counter = 0;
  Node* target = head;
  while(counter != index) target = target->next;

  InsertBefore(target, data);
}

//
//Removal
//
template <typename T>
bool LinkedList<T>::RemoveHead() {
  //fails if the list doesnt have a head
  if(this->head == nullptr) return false;

  //delete the head
  else {
    Node* temp = head;
    head = head->next;

    //if the list is not empty now set the previous to null
    if(this->head != nullptr) head->previous = nullptr;
    delete temp;
  }

  //decrease size of the list by 1
  size--;
  return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
  //fails if the list doesnt have a tail
  if(this->tail == nullptr) return false;

  //delete the tail
  else {
    Node* temp = tail;
    tail = tail->previous;

    //if the list is not empty now set the next to null
    if(this->tail != nullptr) tail->next = nullptr;
    delete temp;
  }
  
  //decrease size of the list by 1
  size--;
  return true;
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
  unsigned int counter = 0;

  Node* target = head;
  while(target != nullptr) {
    if(target->value == data) {
      //create temp node pointer and move target to the next node
      Node* temp = target;
      target = target->next;
      temp->previous->next = target;
      target->previous = temp->previous;
      //remove the node and increment counter by 1
      delete temp;
      counter++;
    }
  }
  return counter;
}

template <typename T>
bool LinkedList<T>::removeAt(int index) {
  //first check to see if index is valid
  if(index > (this->size-1) || index < 0) {
    return false;
  }

  //create a target node pointer and move down the list index times
  int counter = 0;
  Node* target = head;

  while(counter < index) {
    head = head->next;
    counter++;
  }

  //delete the target node
  target->previous->next = target->next;
  target->next->previous = target->previous;
  delete target;
  return true;
}

template <typename T>
void LinkedList<T>::Clear() {
  while(RemoveHead());
}

//
//Operators
//
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
  //check validity of index
  if(index > (this->size - 1) || index < 0) {
    throw std::out_of_range("Error: Invalid index");
  }

  unsigned int counter = 0;
  Node* target = head;

  while(counter < index) {
    target = target->next;
    counter++;
  }
  return target;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
  //check validity of index
  if(index > (this->size - 1) || index < 0) {
    throw std::out_of_range("Error: Invalid index");
  }

  unsigned int counter = 0;
  Node* target = head;

  while(counter < index) {
    target = target->next;
    counter++;
  }
  return target;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
  Node* target = head;
  Node* rhstarget = rhs.Head();
  
  //while there is another element in this list
  while(target != nullptr) {
    //if there is not another element in the rhs then return false
    if(rhstarget == nullptr) return false;
    //if the values are not equal then return false
    if(target->value != rhstarget->value) {
      return false;
    }
    //move to the next node for each list
    target = target->next;
    rhstarget = rhstarget->next;
  }
   
  return true;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
  //shallow copy
  this->size = rhs.size;

  //deep copy node list
  
  //clear nodes
  this->Clear();
  Node* target = rhs.head;

  while(target != nullptr) {
    this->AddTail(target->value);
    target = target->next;
  }

  return *this;
}

