
#include <iostream>

using namespace std;

typedef int DataType;

struct ListNode
{
    // 默认公有
    DataType _data;
    ListNode* _next;
    ListNode* _prev;

    // 带参构造函数
    ListNode(DataType x)            
        :_data(x), 
        _next(NULL), 
        _prev(NULL)
    {}
};

// 带头双向循环链表
class List 
{
    typedef ListNode Node;
public:
    // 1.无参构造函数
    List()
        : _head(new Node(DataType()))
    {
        _head->_next = _head;
        _head->_prev = _head;
    }

    // 2.拷贝构造函数
    List(const List &l);

    // 3.赋值操作符重载
    List &operator= (const List &l);

    // 4.析构函数
    ~List();

    void PushBack(DataType x)
    void PushFront(DataType x);
    void PopBack();
    void PopFront();
    Node *Find(DataType x);
    void Insert(Node *pos, DataType x);
    void Erase(Node *pos);
private:
    Node *_head;
};
