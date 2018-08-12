#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int size_2 = grid.size();
        if(size_2 == 0)
            return 0;
        int size_1 = grid[1].size();
        if(size_1 == 0)
            return 0;
        int ret = 0;
        int w = size_1;
        int h = size_2;
        for(int i=0; i<size_2; i++)
        {
            for(int j=0; j<size_1; j++)
            {
                if(grid[i][j] == 1)
                {
                    ret++;
                    infect(grid, i, j, w, h);                    
                }
            }
        }
        return ret;       
    }

private:
    void infect(vector<vector<char>>& grid, int i, int j, int w, int h)
    {
        if(i <= 0 || i >= w || j <= 0 || j >= h || grid[i][j] != 1)
            return ;
        grid[i][j] = 2;

        /* 递归感染 */
        infect(grid, i, j-1, w, h);
        infect(grid, i, j+1, w, h);
        infect(grid, i-1, j, w, h);
        infect(grid, i+1, j, w, h);       
    }
};

void test()
{
    Solution s;
    char arr[4][4] = {
        {'1', '1', '0', '1'},
        {'1', '0', '0', '1'},
        {'1', '1', '0', '1'},
        {'0', '1', '0', '1'},
    };

    
    int ret = s.numIslands(grid);
    cout << "岛屿个数: " << ret << endl;
}

int main()
{
    test();
}
