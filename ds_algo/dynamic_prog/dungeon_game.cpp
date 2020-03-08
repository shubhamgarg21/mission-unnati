/*
 * Author   : Shubham Garg
 * Date     : March 08, 2020 
 * Problem  : https://leetcode.com/problems/dungeon-game/
 * Build    : g++ -std=c++11 -lstdc++ dungeon_game.cpp
 */ 

#include <iostream>
#include <vector>

using namespace std;

void display_dp(int **dp, int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
}

int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int m = dungeon.size();
    if(m == 0) return 0;
    int n = dungeon[0].size();
    if(n == 0) return 0;

    int **dp = new int*[m];
    for(int i=0; i<m; i++){
        dp[i] = new int[n];
    }

    int val_neg, val_sq;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(i == 0 && j == 0){
                //initial value
                dp[0][0] = dungeon[m-1][n-1] > 0 ? 1 : 1 - dungeon[m-1][n-1];
                continue;
            }

            if(i == 0){
                val_neg = dp[i][j-1];
            }else if(j == 0){
                val_neg = dp[i-1][j];
            }else{
                val_neg = min(dp[i-1][j],dp[i][j-1]);
            }

            val_sq = val_neg - dungeon[m-i-1][n-j-1];
            dp[i][j] = val_sq <= 0 ? 1 : val_sq;
        }
    }
    
    // display_dp(dp,m,n);
    //handle memory leak
    int ans = dp[m-1][n-1];
    for(int i=0; i<m; i++){
        delete [] dp[i];
    }
    delete [] dp;
    return ans;
}


int main(int argc, char** argv){
    vector<vector<int>> dungeon = {{-2,-3,3},{-5,-10,1},{10,30,-5}};
    cout<<calculateMinimumHP(dungeon)<<endl; 
    return 0;
}
