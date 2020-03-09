/*
 * Author   : Shubham Garg
 * Date     : March 08, 2020
 * Problem  : https://leetcode.com/problems/house-robber-ii/
 * Solution : http://buttercola.blogspot.com/2015/09/leetcode-house-robber-ii.html
 * Build    : g++ -std=c++11 -lstdc++ house_robber_2.cpp
 */ 

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int rob_1(vector<int>& nums) {
    if(nums.size() == 0) return 0;

    int *dp = new int[nums.size() + 2];
    
    dp[0] = 0;
    dp[1] = 0;

    bool even = nums.size()%2 == 0;

    int mn = nums[0];
    int ind = 0;
    if(!even){
        for(int i=1; i<nums.size(); i++){
            if(nums[i] < mn){
                mn = nums[i];
                ind = i;
            }
        }

        nums.erase(nums.begin() + ind);
    }

    int min_val = INT32_MAX;

    for(int i=2; i<nums.size() + 2; i++){
         dp[i] = max(dp[i-1], nums[i-2] + dp[i-2]);
         /*
        if(even){
            dp[i] = max(dp[i-1], nums[i-2] + dp[i-2]);
        }else{
            if(i%2 == 0){
                // odd house
                if(i == 2)
                    dp[i] = max(dp[i-1], nums[i-2] + dp[i-2]);
                else{
                    dp[i] = max(dp[i-1], nums[i-2] + dp[i-2] - min_val);
                }
                min_val = min(min_val,nums[i-2]);
            }else{
                //even
                dp[i] = max(dp[i-1], nums[i-2] + dp[i-2]);
            }
        }
        */
    }
   
    return dp[nums.size() + 1];
}

// constant space imp.
int rob_2(vector<int>& nums) {
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

int rob_util(vector<int>& nums){
        if(nums.size() == 0) return 0;
        
        int *dp = new int[nums.size()];
        dp[0] = 0;
        dp[1] = 0;
        
        for(int i=2; i<nums.size()+2; i++){
            dp[i] = max(dp[i-1], nums[i-2] + dp[i-2]);
        }

        return dp[nums.size() + 1];
    }
    
    
int rob_notworking(vector<int>& nums) {
    if(nums.size() == 0) return 0;

    bool fst_house[nums.size() + 2];
    memset(fst_house,false,sizeof(fst_house));

    int *dp = new int[nums.size()];
    dp[0] = 0;
    dp[1] = 0;

    fst_house[0] = false;
    fst_house[1] = false;

    while(1){

        for(int i=2; i<nums.size()+2; i++){

            if(dp[i-1] > nums[i-2] + dp[i-2]){
                dp[i] = dp[i-1];
                fst_house[i] = fst_house[i-1];

                if(i == nums.size() + 1)
                    fst_house[i] = false;
            }else{
                dp[i] = nums[i-2] + dp[i-2];

                if(i-2 == 0)
                    fst_house[i] = true;
                else
                    fst_house[i] = fst_house[i-2];
            }
            //dp[i] = max(dp[i-1], nums[i-2] + dp[i-2]);
        }

        if(!fst_house[nums.size() + 1] || nums.size() < 3)
            return dp[nums.size() + 1];

        memset(fst_house,false,sizeof(fst_house));
        nums.push_back(nums[0]);
        nums.erase(nums.begin());
    }
}


/* 
 * The problem is similar to the last one. The only difference is we can either 
 *   1 Not rob the last one
 *   2 Not rob the first one.
 *     and calculate the maximum.
*/

int rob(vector<int>& nums) {
    if(nums.size() == 0) return 0;

    if(nums.size() == 1) return nums[0];

    //rob the 1st house
    int *dp = new int[nums.size()+1];
    dp[0] = 0;
    dp[1] = nums[0];
    //skip the last house
    for(int i=2; i<nums.size(); i++){
        dp[i] = max(dp[i-1], nums[i-1] + dp[i-2]);
    }

    //skip the 1st house, may or may not rob the last house
    int *dr = new int[nums.size()+1];
    dr[0] = 0;
    dr[1] = 0;
    //skip the last house
    for(int i=2; i<nums.size()+1; i++){
        dr[i] = max(dr[i-1], nums[i-1] + dr[i-2]);
    }
    return max(dp[nums.size()-1],dr[nums.size()]);
}




int main(int argc, char** argv){
    //vector<int> nums = {1,2,3,1};
    //vector<int> nums = {2,3,2};
    //vector<int> nums = {2,3,2,1,5};
    vector<int> nums = {2,1,1,2};
    cout<<rob(nums)<<endl;
    return 0;
}
