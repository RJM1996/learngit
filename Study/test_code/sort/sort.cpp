#include <iostream>
#include <stdio.h>
using namespace std;

#define TEST_HEAD printf("=====%s=====\n", __FUNCTION__)

// 排序
template<class T>
class Sort {
public:
    //  构造
    Sort(T* t_arr, size_t t_size)
        :m_arr(t_arr), m_size(t_size)
    {
       // cout << "size = " << m_size << endl;
    }
    //  析构
    ~Sort()
    {
        m_arr = NULL;
        m_size = 0;
    }

    // 1. 快速排序
    void QuickSort(int left, int right)
    {
        if( left > right )
            return ;
        int i = left; // i 从最左边开始
        int j = right; // j 从最右边开始
        T temp = m_arr[left]; // temp 就是基准值

        while(i != j)
        {
            while(m_arr[j] >= temp && i < j)
                --j;
            while(m_arr[i] <= temp && i < j)
                ++i;
            if(i < j)
                swap(m_arr[i], m_arr[j]);
        }

        // 基准值归位
        m_arr[left] = m_arr[i];
        m_arr[i] = temp;

        // 递归处理左右两边的序列
        QuickSort(left, i - 1);
        QuickSort(i + 1, right);
    }

    // 2. 冒泡排序
    void BubbleSort()
    {
        int i, j;
        for(i=0; i<m_size-1; i++)
        {
            for(j=0; j<m_size-i-1; j++)
            {
                if(m_arr[j] > m_arr[j+1])
                {
                    swap(m_arr[j], m_arr[j+1]);
                }
            }
        }
    }
    

    // 打印数组
    void print()
    {
        for(size_t i=0; i<m_size; i++)
        {
            cout << m_arr[i] << " ";
        }
        cout << endl;
    }
private:
    T* m_arr;
    size_t m_size;
} ;

void TestQuickSort()
{
    TEST_HEAD;
    // int arr[] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    char arr[] = {'a', 'c', 'g', 'h', 'f', 'b', 'd', 'e'};
    int len = sizeof(arr)/sizeof(arr[0]);
    // cout << "len = " << len << endl;
    // Sort<int> s(arr, len);
    Sort<char> s(arr, len);
    s.print();
    s.QuickSort(0, len-1);
    s.print();
}

void TestBubble()
{
    TEST_HEAD;
    int arr[] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    // char arr[] = {'a', 'c', 'g', 'h', 'f', 'b', 'd', 'e'};
    int len = sizeof(arr)/sizeof(arr[0]);
    // cout << "len = " << len << endl;
    Sort<int> s(arr, len);
    // Sort<char> s(arr, len);
    s.print();
    s.BubbleSort();
    s.print();
}

// 1. 快速排序
void QuickSort(int arr[], int left, int right)
{
    if(left > right)
        return ;
    int i, j, temp;
    temp = arr[left]; // temp 就是基准值
    i = left;
    j = right;
    while(i != j)
    {
        while(arr[j] >= temp && i < j)
            --j;
        while(arr[i] <= temp && i < j)
            ++i;
        if(i < j)
        {
            swap(arr[i], arr[j]);
        }
    }
    arr[left] = arr[i]; // 基准值归位到中间
    arr[i] = temp;

    QuickSort(arr, left, i - 1);
    QuickSort(arr, i + 1, right);
}

void print(int* arr, size_t size)
{
    for(size_t i=0; i<size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

/*
void TestQuickSort()
{
    int arr[] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
    size_t len = sizeof(arr)/sizeof(arr[0]);
    QuickSort(arr, 0, len-1);
    print(arr, len);
}
*/

int main()
{
    TestQuickSort();
    TestBubble();
    return 0;
}
