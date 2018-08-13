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


// #include <bits/stdc++.h>
// using namespace std;
// 
// int main()
// {
//     int n;
//     cin >> n;
//     int arr[100000];
//     int sum = 0;
//     int sum_arr[1024];
//     for(int i=1; i<=n; i++)
//     {
//         cin >> arr[i];
//         sum += arr[i];
//         sum_arr[i] = sum;
//     }
//     int m;
//     cin >> m;
//     int q[1024];
//     for(int j=1; j<=m; j++)
//     {
//         cin >> q[j];
//     }
// 
//         int l = 1;
//         int r = n;
//         int mid = (r-l)/2;
//     for(int i=1; i<=m; i++)
//     {
//         for(int j=l; j<=r; j++)
//         {
//             if(q[i] <= sum_arr[j])
//             {
//                 cout << j << endl;
//                 break;
//             }
//             else if(q[i] > sum_arr[mid])
//             {
//                 l = mid + 1;
//                 r = n;
//                 mid = (l-r)/2;
//             }
//         }
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

struct comp
{
    bool operator() (const Interval& l, const Interval& r)
    {
        return l.start < r.start;
    }
} comp;

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> ret;
        int size = intervals.size();
        if( size == 0  )
            return ret;
        // 先以 start 为基准升序排序
        sort(intervals.begin(), intervals.end(), comp);

        // 1. 定义一个 vector 存放结果, 先把第一个区间加入结果
        ret.push_back(intervals[0]);

        // 2. 拿第二个区间的 start 和 结果中当前区间的 end 比较
        for(int i = 1; i < size; i++)
        {
            int ret_size = ret.size();
            // 如果 start 大于 end, 就直接把第二个区间放进结果中

            // 否则将当前结果区间的 end 和第二个区间的 end 比较, 较大者作为合并区间的 end

            // 3. 每次加入新区间时都如此比较, 直到所有区间加入结果中, 合并完毕
            if(intervals[i].start > ret[ret_size-1].end)
            {
                ret.push_back(intervals[i]);
            }
            else
            {
                ret[ret_size-1].end = max(intervals[i].end, ret[ret_size-1].end);
            }
        }
        return ret;
    }
};

    template<class container>
void printContainer(container& s)
{
    typename container::const_iterator it = s.begin();
    while(it != s.end())
    {
        cout << (*it).start << ":" << (*it).end << endl;
        ++it;
    }
    cout << endl;
}

void test()
{
    Solution s;
    vector<Interval> vc;
    Interval inter(1, 3);
    Interval inter1(0, 2);
    Interval inter2(2, 3);
    Interval inter3(4, 6);
    Interval inter4(4, 5);
    Interval inter5(5, 5);
    Interval inter6(0, 2);
    Interval inter7(3, 3);
    vc.push_back(inter);
    vc.push_back(inter1);
    vc.push_back(inter2);
    vc.push_back(inter3);
    vc.push_back(inter4);
    vc.push_back(inter5);
    vc.push_back(inter6);
    vc.push_back(inter7);
    sort(vc.begin(), vc.end(), comp);
    vc = s.merge(vc);
    printContainer(vc);
}


int main()
{
    test();
    return 0;
}
