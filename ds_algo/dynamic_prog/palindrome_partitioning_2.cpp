/*
 * Author   : Shubham Garg
 * Date     : March 8, 2020 
 * Problem  : https://leetcode.com/problems/palindrome-partitioning-ii/
 * Solution : https://www.youtube.com/watch?v=lDYIvtBVmgo
 * Build    : g++ -std=c++11 -lstdc++ palindrome_partitioning_2.cpp
 */ 

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

//first try, close but not working
//initial values and states decision correct
//recursion wrong
int minCut_not_working(string s) {
    if(s.size() == 0) return 0;

    int sz = s.size();

    int dp[sz][sz];
    memset(dp,0,sizeof(dp));

    for(int i=0; i<sz; i++){
        dp[i][i] = 0;
    }

    for(int i=0; i<sz-1; i++){
        if(s[i] == s[i+1])
            dp[i][i+1] = 0;
        else
            dp[i][i+1] = 1;
    }

    int j;
    for(int k=2; k<sz; k++){
        for(int i=0; i<sz-1; i++){
            j = i+k;
            if(j >= sz)
                continue;

            if(s[i] == s[j]){
                if(dp[i][j-1] == dp[i+1][j] && k%2 == 0){
                    dp[i][j] = dp[i+1][j-1];
                    continue;
                }
                if(dp[i][j-1] == dp[i+1][j] && k%2 == 1){
                    dp[i][j] = dp[i+1][j] + 1;
                    continue;
                }

                dp[i][j] = min(dp[i][j-1],dp[i+1][j]);
            }
            else{
                if(dp[i][j-1] == dp[i+1][j] && dp[i+1][j] == dp[i+1][j-1] && k%2 == 0){
                    dp[i][j] = dp[i+1][j-1];
                    continue;
                }

                if(dp[i][j-1] == dp[i+1][j] && k%2 == 1){
                    if(dp[i+1][j-1] != 0)
                        dp[i][j] = dp[i+1][j-1];
                    else
                        dp[i][j] = dp[i][j-1] + 1;
                    continue;
                }

                dp[i][j] = min(dp[i][j-1],dp[i+1][j]) + 1;
            } 
        }
    }

    for(int i=0;i<sz;i++){
        for(int j=0;j<sz;j++){
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }

    return dp[0][sz-1];

}


/*
 * Actual DP :
 *      1. States : dp[i][j] -> minCut value of string from index i to j
 *      2. recursion:
 *          dp[i][j] = {
 *                          0 , if str(i,j) is palindrome
 *                          1 + min(dp[i][k] + dp[k+1][j]) where i<=k<j
 *                     }
 *      3. Initial value :
 *          dp[i][j] = 0 if i==j
 *          dp[i][i+1] = 0 if s[i] == s[i+1]
 *                     = 1 if s[i] != s[i+1] where i<sz-1
 * 
 * Time complexity : 
 *      First implementation : O(n^4) due to palindrome func containing a loop
 *      Second implementation : O(n^3) optimized palindrome using DP instead of func calling
 *      Third implementation : O(n^2) -> https://www.geeksforgeeks.org/palindrome-partitioning-dp-17/
 *
*/

int palindrome(string s, int i, int j){
    while(i<=j){
        if(s[i] != s[j]) return 0;

        i++;
        j--;
    }
    return 1;
}

int minCut_On3(string s){
    if(s.size() == 0) return 0;

    int sz = s.size();
    
    //define large arrays like this
    //stack not able to handle?
    //in gdb using set max-value-size unlimited didnt work
    int **dp = new int*[sz];
    bool **pal = new bool*[sz];

    for(int i=0; i<sz; i++){
        dp[i] = new int[sz];
        memset(dp[i],0,sz*sizeof(int));

        pal[i] = new bool[sz];
        memset(pal[i],false,sz*sizeof(bool));
    }


    //to set all the bytes to 0
   
    //initial value
    for(int i=0; i<sz; i++){
        dp[i][i] = 0;
        pal[i][i] = true;
    }

    for(int i=0; i<sz-1; i++){
        if(s[i] == s[i+1]){
            dp[i][i+1] = 0;
            pal[i][i+1] = true;
        } else {
            dp[i][i+1] = 1;
            pal[i][i+1] = false;
        }
    }

    int j;
    for(int l=2; l<sz; l++){
        for(int i=0; i<sz-1; i++){
            j = i+l;
            if(j >= sz)
                continue;

            if(s[i] == s[j] && pal[i+1][j-1]){
                dp[i][j] = 0;
                pal[i][j] = true;
            }else{
                int mn = INT32_MAX;
                for(int k=i; k<j; k++){
                    mn = min(mn, dp[i][k]+dp[k+1][j]);
                }
                dp[i][j] = 1+mn;
                pal[i][j] = false;
            }
        } 
    }
    return dp[0][sz-1];
}


// O(n^2) implementation
int minCut(string s){
    if(s.size() == 0) return 0;

    int sz = s.size();
    
    //define large arrays like this
    //stack not able to handle?
    //in gdb using set max-value-size unlimited didnt work
    int *dp = new int[sz];
    bool **pal = new bool*[sz];

    for(int i=0; i<sz; i++){
        pal[i] = new bool[sz];
        memset(pal[i],false,sz*sizeof(bool));
    }
   
    //initial value
    for(int i=0; i<sz; i++){
        dp[i] = 0;
        pal[i][i] = true;
    }

    for(int i=0; i<sz-1; i++){
        if(s[i] == s[i+1]){
            pal[i][i+1] = true;
        } else {
            pal[i][i+1] = false;
        }
    }

    int j;
    for(int l=2; l<sz; l++){
        for(int i=0; i<sz-1; i++){
            j = i+l;
            if(j >= sz)
                continue;

            if(s[i] == s[j] && pal[i+1][j-1]){
                pal[i][j] = true;
            }else{
                pal[i][j] = false;
            }
        } 
    }

    for(int i=0; i<sz; i++){
        if(pal[0][i]){
            dp[i] = 0;
        }else{
            dp[i] = INT32_MAX;
            for(int j = 0; j<i; j++){
                if(pal[j+1][i] && 1 + dp[j] < dp[i]){
                    dp[i] = 1 + dp[j];
                }
            }
        }
    }

    return dp[sz-1];
}


int main(int argc, char** argv){
    
    //cout<<minCut("aab")<<endl;
    //cout<<minCut("aabbcc")<<endl;
    //cout<<minCut("cabababcbc")<<endl;
    //cout<<minCut("leet")<<endl;
    //cout<<minCut("coder")<<endl;
    cout<<minCut("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")<<endl;
    return 0;
}
