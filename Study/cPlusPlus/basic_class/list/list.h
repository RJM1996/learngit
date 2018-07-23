#pragma once

#include <iostream>
#include <assert.h>

using namespace std;

template<class T>
struct ListNode
{
    // 默认公有
    T _data;
    ListNode<T>* _next;
    ListNode<T>* _prev;

    // 带参构造函数
    ListNode(const T& x)            
        :_data(x)
        ,_next(NULL) 
        ,_prev(NULL)
    {}
};

// 带头双向循环链表
template<class T>
class List 
{
    typedef ListNode<T> Node;
public:
    // 1.无参构造函数
    List()
        : _head(new Node(T()))
    {
        // _head = new Node(T());
        _head->_next = _head;
        _head->_prev = _head;
    }

    // 2.拷贝构造函数
    // List(const List &l);

    // 3.赋值操作符重载
    List &operator= (const List &l);

    // 4.析构函数
    ~List()
    {
        if(_head)
        {
            delete[] _head;
            _head = NULL;
        }
    }

    void PushBack(const T& x);
    void PushFront(const T& x);
    void PopBack();
    void PopFront();
    Node *Find(const T& x);
    void Insert(Node *pos, const T& x);
    void Erase(Node *pos);
    // 打印链表
    void Display()
    {
        Node* cur = _head->_next;
        while(cur != _head)
        {
            cout << cur->_data << " " ;
            cur = cur->_next;
        }
        cout << endl;
    }
    bool Empty()
    {
        return _head->_prev == _head;
    }
    size_t Size()
    {
        size_t size = 0;
        Node* cur = _head->_next;
        while(cur != _head)
        {
            ++size;
            cur = cur->_next;
        }
        return size;
    }
    T& Back()
    {
        assert(!Empty());
        return _head->_prev->_data;
    }
    T& Front()
    {
        assert(!Empty());
        return _head->_next->_data;
    }
private:
    Node *_head;
};
