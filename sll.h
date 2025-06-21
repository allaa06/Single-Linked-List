#ifndef SLL_H
#define SLL_H
#include <iostream>
#include <initializer_list>

template <typename T>
class SLL {
public:
    class iterator;
    class const_iterator;

    using size_type = unsigned int;
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

private:
    struct Node {
        T val;
        Node* next;
    };

    Node* head;

public:
    SLL();
    SLL(size_type count, value_type val = value_type());
    SLL(const SLL<T>& other);
    SLL(SLL<T>&& other);
    SLL(Node* ptr);
    ~SLL();

    bool empty() const;
    void clear() noexcept;
    size_type size() const;
    void print() const;
    void assign(const size_type count, value_type val);
    void assign(iterator first, iterator last);
    void assign(std::initializer_list<T> ilist);

    reference front();
    const_reference front() const;

    iterator insert_after(const_iterator pos,  const_reference value);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    void push_front(const T& value);
    void pop_front();
    void swap(SLL<T>& other);
    void merge(SLL<T>& other);
    void splice_after(const_iterator pos, SLL<T>& other);
    void remove(const_reference value);
    void reverse() noexcept;
    void unique();
    void sort();

    class iterator {
    public:
        explicit iterator(Node* ptr);
        reference operator*();
        iterator& operator++();


        bool operator==(const iterator& it) const;
        bool operator!=(const iterator& it) const;


    private:
        Node* curr;
    };

    class const_iterator {
    public:
        explicit const_iterator(const Node* ptr);
        const_reference operator*() const;
        const_iterator& operator++();

        bool operator==(const const_iterator& it) const;
        bool operator!=(const const_iterator& it) const;

    private:
        const Node* curr;
    };

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
};



template<typename T>
bool operator==( const SLL<T> l1,const SLL<T> l2);
template<typename T>
bool operator!=( const SLL<T> l1,const SLL<T> l2);
template<typename T>
bool operator>( const SLL<T> l1,const SLL<T> l2);
template<typename T>
bool operator<( const SLL<T> l1,const SLL<T> l2);
template<typename T>
bool operator>=( const SLL<T> l1,const SLL<T> l2);
template<typename T>
bool operator<=( const SLL<T> l1,const SLL<T> l2);



#endif
