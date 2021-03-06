#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList {
  
  public:

    class Node {
      public:
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
    };

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

    bool RemoveAt(unsigned int index);

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

  private:

    unsigned int size;

    Node* head;

    Node* tail;

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
  //construction
  this->head = nullptr;
  this->tail = nullptr;
  this->size = 0;

  //deep copy
  Node* target = list.head;

  while(target != nullptr) {
    this->AddTail(target->data);
    target = target->next;
  }
}

//Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
  //using clear will destroy all of the nodes in the list one by one
  //thus clearing all memory allocated to the structure
  this->Clear();
}

//
//Behaviors
//
template <typename T>
void LinkedList<T>::PrintForward() const {
  //prints the value of each node starting at the head until the target node is
  //null
  Node* target = head;
  while(target != nullptr) {
    std::cout << target->data << std::endl;
    target = target->next;
  }
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
  //same as above but starting at the tail and moving backwards
  Node* target = tail;
  while(target != nullptr) {
    std::cout << target->data << std::endl;
    target = target->prev;
  }
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
  //function to print value of the current node if not null and then call itsel
  //on the next node
  if(node == nullptr) return;
  std::cout << node->data << std::endl;
  PrintForwardRecursive(node->next);
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
  //same as above but will call itself on the previous node
  if(node == nullptr) return;
  std::cout << node->data << std::endl;
  PrintReverseRecursive(node->prev);
}

//
//Accessors
//
template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
  //returns the size of the list
  return this->size;
}

template <typename T>
void LinkedList<T>::FindAll(std::vector<Node*>& outData, const T& value) const {
  //create pointer to head
  Node* target = head;
  
  //iterate through list looking for values to add to vector
  while(target != nullptr) {
    if(target->data == value) {
      outData.push_back(target);
    }
    target = target->next;
  }
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {

  //iterate throught the list and return a pointer to the first node with the
  //given data
  //if no matches are found nullptr is returned

  Node* target = head;
  while(target != nullptr) {
    if(target->data == data) return target;
    target = target->next;
  }
  return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {

  //same as above but non-const version to allow the pointer to be used to
  //alter data in the list

  Node* target = head;
  while(target != nullptr) {
    if(target->data == data) return target;
    target = target->next;
  }
  return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {

  //check validity of index
  if(index > (this->size - 1)) {
    throw std::out_of_range("Error invalid index");
  }

  //move index times to the next node from the head and return the destination
  //node

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
  //check validity of index
  if(index > (this->size - 1)) {
    throw std::out_of_range("Error invalid index");
  }

  //same as above except is non-const allowing the returned pointer to be used
  //to change the list

  int counter = 0;
  Node* target = head;

  while(counter < index) {
    target = target->next;
    counter++;
  }
  return target;
}

//const and non-const methods to access the head and tail pointers
//respectively

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

  //if the size of the list is 0 then there is no need for a temp or previous
  //pointers
  
  if(size == 0) {
    head = new Node;
    head->data = data;
    tail = head;
    size++;
  }

  //add a new node at the head and change the next and previous pointers
  //accordingly 
  else {
    Node* temp = head;
    head = new Node;
    head->data = data;
    head->next = temp;
    temp->prev = head;
    size++;
  }
}

template <typename T>
void LinkedList<T>::AddTail(const T& data) {

  //same as above but for the tail

  if(size == 0) {
    tail = new Node;
    tail->data = data;
    head = tail;
    size++;
  }
  else {
    Node* temp = tail;
    tail = new Node;
    tail->data = data;
    temp->next = tail;
    tail->prev = temp;
    size++;
  }
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {

  //use the previuosly defined AddHead() method to add count elements to the
  //front of the list
  //note: in order to preserve the original order of the elements they are
  //added in reverse order (like a stack)

  for(int i=(count-1); i>=0; i--) {
    AddHead(data[i]);
  }
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {

  //same as the above method but does the same for the tail
  //note: elements are added in their given order in the array. (like adding to
  //the end of queue.

  for(unsigned int i=0; i<count; i++) {
    AddTail(data[i]);
  }
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {

  //takes care of the edge case for the tail since tail's "next" is nullptr
  
  if(node == this->tail) {
    AddTail(data);
    return;
  }

  //creates a new node and changes the linking to make it come after the given
  //node

  Node* target = new Node;

  target->data = data;
  target->prev = node;
  target->next =(node->next);
  node->next = target;
  target->next->prev = target;

  //increment the size of the list by one
  this->size++;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {

  //takes care of the edge case fo rthe head since head's "previous" is nullptr

  if(node == this->head) {
    AddHead(data);
    return;
  }

  //creates a new node and changes the linking to make it come before the given
  //node

  Node* target = new Node;

  target->data = data;
  target->next = node;
  target->prev = node->prev;
  node->prev->next = target;
  node->prev = target;

  //increment the size of the list by one
  this->size++;
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
  //check validity of index
  if(index > this->size) {
    throw std::out_of_range("Error: invalid index");
  }
  
  //if attempting to add at the very end just add tail
  if(index == this->size) {
    AddTail(data);
    return;
  }

  //move down the list index times
  
  unsigned int counter = 0;
  Node* target = head;

  while(counter != index) {
    target = target->next;
    counter++;
  }

  //use InserBefore() to insert the index at the correct position in the list

  InsertBefore(target, data);
}

//
//Removal
//
template <typename T>
bool LinkedList<T>::RemoveHead() {
  //fails if the list doesnt have a head
  if(this->size == 0) return false;

  //delete the head
  else {
    Node* temp = head;
    head = head->next;

    //if the list is not empty now set the previous to null
    if(this->head != nullptr) head->prev = nullptr;
    delete temp;
    this->size--;
  }

  return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
  //fails if the list doesnt have a tail
  if(this->tail == nullptr) return false;

  //delete the tail
  else {
    Node* temp = tail;
    tail = tail->prev;

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
    if(target->data == data) {
      //create temp node pointer and move target to the next node
      Node* temp = target;
      target = target->next;
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;

      //remove the node, increment counter by one, and decrement size by one
      delete temp;
      counter++;
      this->size--;
      continue;
    }
    target = target->next;
  }
  return counter;
}

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
  //first check to see if index is valid
  if(index > (this->size-1) || index < 0) {
    return false;
  }

  //create a target node pointer and move down the list index times
  unsigned int counter = 0;
  Node* target = head;

  while(counter < index) {
    target = target->next;
    counter++;
  }

  //delete the target node and decrement size by one
  target->prev->next = target->next;
  target->next->prev = target->prev;
  delete target;
  this->size--;
  return true;
}

template <typename T>
void LinkedList<T>::Clear() {

  //keep removing the head node until you can't anymore
  //then set all instance variables to that of a newly created list
  
  while(RemoveHead());
  this->head = nullptr;
  this->tail = nullptr;
  this->size = 0;
}

//
//Operators
//
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
  //check validity of index
  if(index > (this->size - 1)) {
    throw std::out_of_range("Error: Invalid index");
  }

  //use previously declared GetNode method to access element at the given index
  //and return the value of the element
  return (this->GetNode(index))->data;

}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
  //check validity of index
  if(index > (this->size - 1)) {
    throw std::out_of_range("Error: Invalid index");
  }

  //use previously declared GetNode method ot access element at the given index
  //and return the value of the element
  return (this->GetNode(index))->data;

}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
  Node* target = head;
  const Node* rhstarget = rhs.Head();
  
  //while there is another element in this list
  while(target != nullptr) {
    //if there is not another element in the rhs then return false
    if(rhstarget == nullptr) return false;
    //if the datas are not equal then return false
    if(target->data != rhstarget->data) {
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
  
  //clear nodes
  this->Clear();

  //deep copy node list
  Node* target = rhs.head;

  while(target != nullptr) {
    this->AddTail(target->data);
    target = target->next;
  }

  return *this;
}
