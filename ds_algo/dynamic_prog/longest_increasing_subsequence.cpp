/*
 * Author   : Shubham Garg
 * Date     : Mar 09, 2020 
 * Problem  : https://leetcode.com/problems/longest-increasing-subsequence/
 * Solution : https://www.youtube.com/watch?v=CE2b_-XfVDk
 *          : https://www.youtube.com/watch?v=S9oUiVYEq7E
 *          : https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
 * Build    : g++ -std=c++11 -lstdc++ longest_increasing_subsequence.cpp
 */ 

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;


struct lis{
    int len;
    int start;
    int end;
};

// my solution not working on all cases 20/24
int lengthOfLIS_notworking(vector<int>& nums) {
    if(nums.size() == 0) return 0;
    
    int sz = nums.size();
    lis dp[sz][sz];
    
    memset(dp, 0, sizeof(dp));

    for(int i=0; i<sz; i++){
        dp[i][i].len = 1;
        dp[i][i].start = i;
        dp[i][i].end = i;

        if(i < sz -1){
            if(nums[i+1] > nums[i]){
                dp[i][i+1].len = 2; 
                dp[i][i+1].start = i;
                dp[i][i+1].end = i+1;
            }
            else{
                dp[i][i+1].len = 1; 
                dp[i][i+1].start = i;
                dp[i][i+1].end = i;
            }
        }
    }

    int j;
    for(int l = 2; l<sz; l++){
        for(int i=0; i<sz-l; i++){
            j = i + l;
            if(j>=sz)
                continue;

            if(dp[i][j-1].len == dp[i+1][j].len){
                if(dp[i][j-1].len == dp[i+1][j-1].len){
                    dp[i][j].len = dp[i+1][j-1].len;
                    dp[i][j].start = dp[i+1][j-1].start;
                    dp[i][j].end = dp[i+1][j-1].end;
                }else{
                    if(dp[i][j-1].end < dp[i+1][j].start -1 ){
                        dp[i][j].len = dp[i][j-1].len;

                        if(nums[dp[i][j-1].end] > nums[dp[i+1][j].end]){
                            dp[i][j].start = dp[i+1][j].start;
                            dp[i][j].end = dp[i+1][j].end;
                        }else{
                            dp[i][j].start = dp[i][j-1].start;
                            dp[i][j].end = dp[i][j-1].end;
                        }
                    }else{
                        dp[i][j].len = dp[i][j-1].len + 1;
                        dp[i][j].start = dp[i][j-1].start;
                        dp[i][j].end = dp[i+1][j].end;
                    }
                }
            }else{
                if(dp[i][j-1].len > dp[i+1][j].len){
                    dp[i][j].len = dp[i][j-1].len;
                    dp[i][j].start = dp[i][j-1].start;
                    dp[i][j].end = dp[i][j-1].end;
                }else{
                    dp[i][j].len = dp[i+1][j].len;
                    dp[i][j].start = dp[i+1][j].start;
                    dp[i][j].end = dp[i+1][j].end;
                }
            }
        }
    }

    return dp[0][sz-1].len;
}

//O(n^2) solution
//O(nlog(n)) solution also available
int lengthOfLIS(vector<int>& nums) {
    if(nums.size() == 0) return 0;

    int dp[nums.size()];

    for(int i=0; i<nums.size(); i++){
        for(int j=0; j<nums.size(); j++){
            if(i == 0){
                dp[j] = 1;
            }else{
                if(j >= i)
                    continue;
                if(nums[j] < nums[i])
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
    }

    int ans = dp[0];
    for(int i=1; i<nums.size(); i++){
        ans = max(ans,dp[i]);
    }
    return ans;
}




int main(int argc, char** argv){
    //vector<int> nums = {10,9,2,5,3,7,101,18};
    vector<int> nums = {4,10,4,3,8,9};
    cout<<lengthOfLIS(nums)<<endl;
    return 0;
}
