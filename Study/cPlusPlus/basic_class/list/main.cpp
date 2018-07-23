#include "list.h"
#include "list.cpp"


void Test01()
{
    List<int> l1;
    l1.PushBack(1);
    l1.PushBack(3);
    l1.PushBack(5);
    l1.PushBack(7);
    l1.Display();
    l1.PushFront(2);
    l1.PushFront(4);
    l1.PushFront(6);
    l1.PushFront(8);
    l1.Display();
    l1.PopBack();
    l1.PopBack();
    l1.PopBack();
    l1.Display();
    cout << "front : " << l1.Front() << endl;
    cout << "back : " << l1.Back() << endl;
    l1.PopFront();
    l1.PopFront();
    l1.PopFront();
    l1.Display();
    cout << "size: " << l1.Size() << endl;
    l1.PopFront();
    l1.PopFront();
    cout << "size: " << l1.Size() << endl;
    if(l1.Empty())
    {
        cout << "链表为空" << endl;
    }
    
}

int main()
{
    Test01();
    cout << endl;
    cout << endl;
    cout << endl;
    return 0;
}
