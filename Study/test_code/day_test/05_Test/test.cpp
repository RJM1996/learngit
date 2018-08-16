#include <iostream>
#include <vector>
#include <stack>
#include <assert.h>
#include <string.h>

using namespace std;

/* strcpy */
char* mystrcpy(char* dest, const char* src)
{
    assert(dest && src);
    char* tmp = dest;
    while(*src != '\0')
    {
        *tmp = *src;
        tmp++;
        src++;
    }
    return dest;
}

void TestStrcpy()
{
    const char* s1 = "hello, world";
    char s2[20];
    int len = strlen(mystrcpy(s2, s1));
    cout << s1 << endl;
    cout << s2 << endl;
    cout << len << endl;
}

/* strncpy */
char* mystrncpy(char* dest, const char* src, size_t n)
{
    assert(dest && src);
    size_t i = 0;
    for(; i < n && *src != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}
void TestStrncpy()
{
    const char* s1 = "hello, world";
    char s2[20];
    int len = strlen(mystrncpy(s2, s1, 10));
    cout << s1 << endl;
    cout << s2 << endl;
    cout << len << endl;
}

/* qsort 递归版 */
void myqsort(vector<int>& vc, int left, int right)
{
    // int size = (int)vc.size();
    // if(size == 0)
    //     return ;
    if(left > right)
        return ;
    int tmp = vc[left]; /* tmp 基准值 */
    int i = left;
    int j = right;
    while(i != j)
    {
        // 先从右边开始找到一个比基准值小的
        while(i < j && vc[j] >= tmp) j-- ;
        // 再从左边开始找到一个比基准值大的
        while(i < j && vc[i] <= tmp) i++ ;
        // 找到了就交换
        if(i < j)
            swap(vc[i], vc[j]);
    }
    // 基准值归位
    vc[left] = vc[i];
    vc[i] = tmp;

    // 递归排序左右两边
    myqsort(vc, left, i-1);
    myqsort(vc, i+1, right);
}
/* qsort 非递归 */
int partition(vector<int>& vc, int left, int right)
{
    if(left > right || left < 0 || right <= 0)
        return -1;
    int tmp = vc[left];
    int i = left;
    int j = right;
    while(i != j)
    {
        while(i < j && vc[j] >= tmp) j--;
        while(i < j && vc[i] <= tmp) i++;
        if(i < j) swap(vc[i], vc[j]);
    }
    vc[left] = vc[i];
    vc[i] = tmp;
    return i;
}
void qsort_nonrecur(vector<int>& vc, int left, int right)
{
    if(left > right || left < 0 || right <= 0)
        return ;
    stack<int> s;
    s.push(right);
    s.push(left);
    int i = 0;
    int j = 0;
    while(!s.empty())
    {
        i = s.top();
        s.pop();
        j = s.top();
        s.pop();
        if(i < j)
        {
            int mid = partition(vc, i, j);
            if(i < mid)
            {
                s.push(mid-1);
                s.push(i);
            }
            if(j > mid)
            {
                s.push(j);
                s.push(mid+1);
            }
        }
    } // 栈为空, 退出循环
}
void TestQsort_nonrecur()
{
    int arr[10] = { 6,  1,  2, 7,  9,  3,  4,  5, 10,  8 };
    int len = sizeof(arr)/sizeof(arr[0]);
    vector<int> vc(arr, arr + len);
    vector<int>::iterator it = vc.begin();
    while(it != vc.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
    qsort_nonrecur(vc, 0 , len-1); /* 快速排序 */
    for(int i=0; i<len; i++)
    {
        cout << vc[i] << " ";
    }
    cout << endl;

}
void TestQsort()
{
    int arr[10] = { 6,  1,  2, 7,  9,  3,  4,  5, 10,  8 };
    int len = sizeof(arr)/sizeof(arr[0]);
    vector<int> vc(arr, arr + len);
    vector<int>::iterator it = vc.begin();
    while(it != vc.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
    myqsort(vc, 0 , len-1); /* 快速排序 */
    for(int i=0; i<len; i++)
    {
        cout << vc[i] << " ";
    }
    cout << endl;
}

static int a;
int b;
void Test_static()
{
    cout << "static a: " << a << endl;
    cout << "b : " << b << endl;
}

void TestConst()
{
    // char a = 'a';
    // char* const p = &a;
    // // p = NULL;
    // const char* q = &a;
    // // *q = 'b';
    // const char* const ptr = &a;
    // // ptr = NULL;
    // // *ptr = 'b';
}

int main()
{
    // TestStrcpy();
    // TestStrncpy();
    TestQsort();
    // TestQsort_nonrecur();
    // Test_static();
    // TestConst();
    return 0;
}
