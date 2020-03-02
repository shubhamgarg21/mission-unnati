/*
 * Author   : Shubham Garg
 * Date     : Mar 02, 2020 
 * Problem  : https://leetcode.com/problems/distinct-subsequences/
 * Solution : https://www.geeksforgeeks.org/count-distinct-occurrences-as-a-subsequence/
 * Build    : g++ -std=c++11 -lstdc++ distinct_subsequences.cpp
 */ 

#include <iostream>
#include <vector>

using namespace std;

int numDistinct(string s, string t) {
    int m = s.size();
    int n = t.size();
    
    if(n > m) return 0;

    //use unsigned integer to resolve memory overflow of int
    //values will always be positive, so smart think to do
    unsigned int dp[m+1][n+1];
    for(int i=0;i<m+1;i++)
        dp[i][0] = 1;

    for(int j=1; j<n+1; j++)
        dp[0][j] = 0;

    for(int i=1;i<m+1;i++){
        for(int j=1; j<n+1; j++){
            if(s[i-1] == t[j-1]){
                dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
            }else{
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    
    return dp[m][n];
}



int main(int argc, char** argv){
    //cout<<numDistinct("rabbbit","rabbit")<<endl;
    cout<<numDistinct("babgbag","bag")<<endl;
    return 0;
}
