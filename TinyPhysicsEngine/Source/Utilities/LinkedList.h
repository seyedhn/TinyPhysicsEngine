#pragma once

template<typename T>
struct Node
{
  Node() : next(nullptr) {}
  Node(T& head) : data(head), next(nullptr){}
  Node(const T& head) : data(head), next(nullptr) {}

  T data;
  Node* next;
};


template<typename T>
class List
{
public:
  List();
  List(const T& data);
  void AddNode(const T& _data); 

private:
  Node<T>* head;

};


//DEFINITIONS
////////////////////////////////////////////////////////

template <typename T> List<T>::List() : head(nullptr) {}
template <typename T> List<T>::List(const T& _data) : head(_data) {}

template <typename T>
void List<T>::AddNode(const T& _data)
{
  Node<T>* newNode = new Node<T>(_data);
  newNode->next = head->next;
  head->next = newNode;
}
