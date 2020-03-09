/*
 * Author   : Shubham Garg
 * Date     : Mar 09, 2020 
 * Problem  : https://leetcode.com/problems/perfect-squares/
 * Solution : https://www.youtube.com/watch?v=KaXeidsmvVQ
 * Build    : g++ -std=c++11 -lstdc++ perfect_squares.cpp
 */ 

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int numSquares(int n) {
    if(n==0) return 0;
    int dp[n+1];
    //memset(dp, INT32_MAX, sizeof(dp));
    for(int i = 0; i<n+1; i++){
        dp[i] = INT32_MAX;
    }


    int i = 1;
    int sq;
    while(1){
        sq = i*i;
        if(sq > n) break;
        dp[sq] = 1;
        
        int j = 2;
        int mul;
        // handle multiples of sq
        while(1){
            mul = sq*j;
            if(mul > n) break;
            dp[mul] = min(dp[mul],j);

            j++;
        }
        i++;
    }

    dp[0] = 0;
    for(i = 2; i<n+1; i++){
        
        for(int j = 1; j*j <= i; j++){
            dp[i] = min(dp[i], 1 + dp[i - j*j]);
        }
    }
    for(int i = 1; i<n+1; i++){
        cout<<dp[i]<<" ";
    }
    cout<<endl;

    return dp[n];
}


int main(int argc, char** argv){
    cout<<numSquares(22)<<endl;    
    return 0;
}
