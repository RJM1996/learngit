
#include <iostream>
using namespace std;

class Solution {
    public:
        void setZeroes(vector<vector<int> > &matrix) {
            if (matrix.size() == 0)
              return ;
            for (int row = 0; row < matrix.size(); row++)
            {
                for (int col = 0; col < matrix[row].size(); col++)
                {
                    if (matrix[row][col] == 0)
                    {
                        for(int cur_row = 0; cur_row < matrix.size(); cur_row++)
                        {
                            if(matrix[cur_row][col] != 0)
                              matrix[cur_row][col] = -INT_MAX;
                        }
                        for(int cur_col = 0; cur_col < matrix[row].size(); cur_col++)
                        {
                            if(matrix[row][cur_col] != 0)
                              matrix[row][cur_col] = -INT_MAX;
                        }
                    }
                }
            }

            for (int row = 0; row < matrix.size(); row++)
            {
                for (int col = 0; col < matrix[row].size(); col++)
                {
                    if(matrix[row][col] == -INT_MAX)
                      matrix[row][col] = 0;
                }
            }            
        }
};
