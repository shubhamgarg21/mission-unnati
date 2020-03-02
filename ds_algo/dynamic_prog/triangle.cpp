/*
 * Author   : Shubham Garg
 * Date     : Mar 02, 2020 
 * Problem  : https://leetcode.com/problems/triangle/
 * Build    : g++ -std=c++11 -lstdc++ triangle.cpp
 */ 

#include <iostream>
#include <vector>

using namespace std;
int minimumTotal(vector<vector<int>>& triangle) {
    vector<vector<int>> dp;
    
    int rows = triangle.size();
    if(rows == 0) return 0;

    int col;
    for(int i=0;i<rows;i++){
        col = triangle[i].size();

        vector<int> vals;
        if(i == 0){
            vals.push_back(triangle[i][0]);
            dp.push_back(vals);
            continue;
        }

        for(int j=0;j<col;j++){
            int ind1 = j -1;
            int ind2 = j;

            int val = 0;
            if(ind1>=0 && ind1<=i-1 && ind2>=0 && ind2<=i-1){
                val = min(dp[i-1][ind1],dp[i-1][ind2]);
            }else if((ind1<0 || ind1 > i-1) && (ind2>=0 && ind2<=i-1)){
                val = dp[i-1][ind2];
            }else if((ind1>=0 && ind1<=i-1) && (ind2 < 0 || ind2>i-1)){
                val = dp[i-1][ind1];
            }
            vals.push_back(triangle[i][j] + val);
        }
        dp.push_back(vals);
    }
    
    vector<int> last = dp[rows -1];

    int mn = last[0];
    for(int i = 1;i<last.size();i++){
        if(last[i] < mn)
            mn = last[i];
    }
    
    return mn;
}


int main(int argc, char** argv){
    vector<vector<int>> triangle = { {2},
                                    {3,4},
                                   {6,5,7},
                                  {4,1,8,3},
                                {3,14,100,1,2} };
    cout<<minimumTotal(triangle)<<endl;
    return 0;
}
