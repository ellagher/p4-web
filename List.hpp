#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  List() {
    first = NULL;
    last = NULL;
  }

  List(const List<T> &other) {
    first = NULL;
    last = NULL;
    copy_all(other);
  }

  ~List() {
    clear();
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return size() == 0;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    Node* iterator = first;
    int size = 0;
    while(iterator != NULL) {
      iterator = iterator->next;
      size++;
    }
    return size;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(size() != 0);
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    assert(size() != 0);
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    // if list is empty, the front and back just become the element being added
    if(size() == 0) {
      Node* n = new Node();
      n->next = NULL;
      n->prev = NULL;
      n->datum = datum;
      first = n;
      last = n;
    }
    else {
      Node* n = new Node();
      n->datum = datum;
      n->next = first; // make the new node point at the previous head
      n->prev = NULL; // no prev for the front
      first->prev = n; // point current head at the new head
      first = n; // set the head to the new node
    }
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    // if list is empty, the front and back just become the element being added
    if(size() == 0) {
      Node* n = new Node();
      n->next = NULL;
      n->prev = NULL;
      n->datum = datum;
      first = n;
      last = n;
    }
    else {
      Node* n = new Node();
      n->datum = datum;
      n->prev = last; // make new node's prev point to current tail
      n->next = NULL; // make new node's prev point to NULL (end)
      last->next = n; // make the tail's next point at this node
      last = n; // make this node the new tail
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(size() != 0);
    // handle special case of only one element in the list
    if(size() == 1) {
      delete(first);
      first = NULL;
      last = NULL;
    }
    else {
      Node* temp = first;
      first = first->next;
      first->prev = NULL;
      delete(temp);
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(size() != 0);
    // handle special case of only one element in the list
    if(size() == 1) {
      delete(first);
      first = NULL;
      last = NULL;
    }
    else {
      Node* temp = last;
      last->prev->next = NULL; // make the new last point at null
      last = last->prev; // update last to the prev
      delete(temp);
    }
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    Node* cur = first;
    Node* prev = NULL;
    while(cur != NULL) {
      prev = cur;
      cur = cur->next;
      delete(prev);
    }
    first = NULL;
    last = NULL;
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    assert(first == NULL);
    Node* other_n = other.first;
    while(other_n != NULL) {
      push_back(other_n->datum);
      other_n = other_n->next;
    }

  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  

public:  
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    bool operator==(const Iterator& rhs) const {
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(const Iterator& rhs) const {
      if(rhs == NULL) return false; // if rhs is null they are not equal
      return node_ptr != rhs.node_ptr;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    T& operator*() {
      return node_ptr->datum;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here
    friend class Node;
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p) {
      node_ptr = p;
    }

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator(last->next);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    // case 1: remove from front
    if(i.node_ptr == first) {
      pop_front();
    }
    // case 2: remove from back
    else if(i.node_ptr == last) {
      pop_back();
    }
    // case 3: remove from middle
    else {
      Node* temp = i.node_ptr;
      i.node_ptr->prev->next = i.node_ptr->next;
      i.node_ptr->next->prev = i.node_ptr->prev;
      delete(temp);
    }

  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    if(i.node_ptr == first) {
      push_front(datum);
    }
    else {
      Node* n = new Node();
      n->datum = datum;
      n->prev = i.node_ptr->prev;
      n->next = i.node_ptr;
      i.node_ptr->prev->next = n;
      i.node_ptr->prev = n;
    }
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
