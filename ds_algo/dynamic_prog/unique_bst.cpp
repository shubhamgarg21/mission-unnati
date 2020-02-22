/*
 * Author   : Shubham Garg
 * Date     : Feb 22, 2020 
 * Problem  : https://leetcode.com/problems/unique-binary-search-trees/
 * Solution : https://www.youtube.com/watch?v=YDf982Lb84o
 * Build    : g++ -std=c++11 -lstdc++ unique_bst.cpp
 */ 

#include <iostream>
#include <vector>

using namespace std;

int numTrees(int n) {
    if (n <= 1) return n;

    int dp[n+1] = {0};
    dp[0] = 1;
    dp[1] = 1;

    for(int i =2; i<=n ;i++){
        for(int j=0; j<i;j++){
            dp[i] += dp[j]*dp[i-j-1];
        }
    }

    return dp[n];
}


int main(int argc, char** argv){
    
    cout<<numTrees(6)<<endl;

    return 0;
}
