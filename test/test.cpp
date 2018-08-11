// #include <stdio.h>
// #include <iostream>
// using namespace std;
// 
// class A
// {
//     char a[2];
// public:
//     virtual void aa(){};
// };
// 
// class B:public virtual A
// {
//     char b[2];
//     char a[2];
// public:
//     virtual void bb(){};
//     virtual void aa(){};
// };
// class C:public virtual B
// {
//     char a[2];
//     char b[2];
//     char c[2];
// public:
//     virtual void cc(){};
//     virtual void aa(){};
//     virtual void bb(){};
// };
// 
// void test()
// {
//     // int arr[]={1,2,3,4,5,6,7};
//     // int *p=arr;
//     // *(p++)+=89;
//     // printf("%d,%d\n",*p,*(++p)); // 3, 3
//     // return 0;
//     A a;
//     cout << sizeof(A) << endl;
//     cout << sizeof(B) << endl;
//     cout << sizeof(C) << endl;
// }
// 
// int getSize(int data[]){
//     return sizeof(data);
// }
// 
// 
// 
// // 单利模式
// class Singleton
// {
// public:
//     Singleton* getInstance()
//     {
//         if(instance == NULL)
//         {
//             // lock();
//             if(instance == NULL)
//             {
//                 instance =  new Singleton;
//             }
//             // unlock();
//         }
//         return instance;
//     }
// 
// private:
//     static Singleton* instance;
// };
// 
// int find()
// {
//     int count = 0;
//     int l, r;
//     cin >> l >> r;
//     for(int i=l; i<=r; i++)
//     {
//         if(i%3 != 1)
//         {
//             count++;
//         }
//     }
//     cout << count << endl;
// }
// 
// int main(){
//     // int data1[] = {1,2,3,4,5};
//     // int size1 = sizeof(data1);
// 
//     // int* data2 = data1;
//     // int size2 = sizeof(data2);
// 
//     // int size3 = getSize(data1);
// 
//     // printf("%d, %d, %d", size1, size2, size3);
//     
//     find();
//     return 0;
// 
// }
//
//


#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int arr[100000];
    int sum = 0;
    int sum_arr[1024];
    for(int i=1; i<=n; i++)
    {
        cin >> arr[i];
        sum += arr[i];
        sum_arr[i] = sum;
    }
    int m;
    cin >> m;
    int q[1024];
    for(int j=1; j<=m; j++)
    {
        cin >> q[j];
    }

        int l = 1;
        int r = n;
        int mid = (r-l)/2;
    for(int i=1; i<=m; i++)
    {
        for(int j=l; j<=r; j++)
        {
            if(q[i] <= sum_arr[j])
            {
                cout << j << endl;
                break;
            }
            else if(q[i] > sum_arr[mid])
            {
                l = mid + 1;
                r = n;
                mid = (l-r)/2;
            }
        }
    }
    return 0;
}
