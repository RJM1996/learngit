#include "./list.h"

// 尾插
template<class T>
void List<T>::PushBack(const T& x)
{
    Insert(_head, x);
}
// 头插
template<class T>
void List<T>::PushFront(const T& x)
{
    Insert(_head->_next, x);
}
// 尾删
template<class T>
void List<T>::PopBack()
{
    Erase(_head->_prev);
}
// 头删
template<class T>
void List<T>::PopFront()
{
    Erase(_head->_next);
}

/*
// 查找元素
template<class T>
Node* List<T>::Find(const T& x)
{

}
*/

// 在任意位置插入节点
template<class T>
void List<T>::Insert(Node *pos, const T& x)
{
    assert(pos);
    Node* prev = pos->_prev;
    Node* new_node = new Node(x);
    new_node->_prev = prev;
    prev->_next = new_node;
    new_node->_next = pos;
    pos->_prev = new_node;
}
// 删除任意位置的节点
template<class T>
void List<T>::Erase(Node *pos)
{
    assert(pos && pos != _head);
    Node* prev = pos->_prev;
    Node* next = pos->_next;
    prev->_next = next;
    next->_prev = prev;
    delete pos;
}
