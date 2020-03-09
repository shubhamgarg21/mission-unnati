/*
 * Author   : Shubham Garg
 * Date     : Mar 09, 2020 
 * Problem  : https://leetcode.com/problems/ugly-number-ii/
 * Solution : https://www.geeksforgeeks.org/ugly-numbers/
 * Build    : g++ -std=c++11 -lstdc++ ugly_number_2.cpp
 */ 

#include <iostream>
#include <vector>

using namespace std;

int nthUglyNumber(int n) {
    if(n < 6) return n;
   
    int dp[n];
    dp[0] = 1;
    
    int mn;
    int i2=0,i3=0,i5=0;

    int n2 = dp[0]*2;
    int n3 = dp[0]*3;
    int n5 = dp[0]*5;

    int nxt_val;
    for(int i = 1; i<n; i++){
        nxt_val = n2<n3?n2<n5?n2:n5:(n3<n5?n3:n5);
        dp[i] = nxt_val;
        if(nxt_val == n2){
            i2++;
            n2 = dp[i2]*2;
        }

        if(nxt_val == n3){
            i3++;
            n3 = dp[i3]*3;
        }

        if(nxt_val == n5){
            i5++;
            n5 = dp[i5]*5;
        }
        
    }

    return dp[n-1];
}


int main(int argc, char** argv){
    cout<<nthUglyNumber(10)<<endl;
    return 0;
}
