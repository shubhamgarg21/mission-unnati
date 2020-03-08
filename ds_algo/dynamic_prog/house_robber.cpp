/*
 * Author   : Shubham Garg
 * Date     : March 08, 2020
 * Problem  : https://leetcode.com/problems/house-robber/
 * Build    : g++ -std=c++11 -lstdc++ house_robber.cpp
 */ 

#include <iostream>
#include <vector>

using namespace std;

int rob_first(vector<int>& nums) {
    if(nums.size() == 0) return 0;

    int *dp = new int[nums.size() + 2];
    
    dp[0] = 0;
    dp[1] = 0;

    for(int i=2; i<nums.size() + 2; i++){
        dp[i] = max(dp[i-1], nums[i-2] + dp[i-2]);
    }
   
    return dp[nums.size() + 1];
}

// constant space imp.
int rob(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    
    int d0 = 0;
    int d1 = 0;
    int d2;

    for(int i=0; i<nums.size(); i++){
        d2 = max(d1, nums[i] + d0);
        d0 = d1;
        d1 = d2;
    }
   
    return d2;
}


int main(int argc, char** argv){
    vector<int> nums = {1,2,3,1};

    cout<<rob(nums)<<endl;
    return 0;
}
