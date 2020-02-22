/*
 * Author   : Shubham Garg
 * Date     : Feb 22, 2020 
 * Problem  : https://leetcode.com/problems/interleaving-string/
 * Solution : https://www.youtube.com/watch?v=ih2OZ9-M3OM
 * Build    : g++ -std=c++11 -lstdc++ interleaving_string.cpp
 */ 

#include <iostream>
#include <vector>
#include<bits/stdc++.h>

using namespace std;

bool isInterleave_recursive(string s1, string s2, string s3) {
    if(s1.size() + s2.size() != s3.size())
        return false;

    if(s1.size() == 0 && s2.size() != 0) 
        return s2.compare(s3) == 0;

    if(s2.size() == 0 && s1.size() != 0)
        return s1.compare(s3) == 0;

    if(s1.size() == 0 && s2.size() == 0)
        return true;

    if(s1[0] == s2[0] && s1[0] == s3[0]){
        return isInterleave_recursive(s1.substr(1),s2,s3.substr(1)) ||
            isInterleave_recursive(s1,s2.substr(1),s3.substr(1));
    }else if(s1[0] == s3[0]){
        return isInterleave_recursive(s1.substr(1),s2,s3.substr(1));
    }else if(s2[0] == s3[0]){
        return isInterleave_recursive(s1,s2.substr(1),s3.substr(1));
    }else{
        return false;
    }
}


bool isInterleave(string s1, string s2, string s3) {
    if(s1.size() + s2.size() != s3.size())
        return false;

    bool dp[s1.size() + 1][s2.size() + 1];
    memset(dp,0,sizeof(dp));
    dp[0][0] = true;

    for(int i = 1; i <s1.size()+1;i++){
        if(s1[i-1] == s3[i-1]){
            dp[i][0] = dp[i-1][0];
        }else{
            dp[i][0] = false;
        }
    }

    for(int j = 1; j <s2.size()+1; j++){
        if(s2[j-1] == s3[j-1]){
            dp[0][j] = dp[0][j-1];
        }else{
            dp[0][j] = false;
        }
    }

    for(int i = 1; i <s1.size()+1;i++){
        for(int j = 1; j <s2.size()+1; j++){
            bool val1,val2;
            
            if(s3[i+j -1] == s1[i-1]){
                val1 = dp[i-1][j];
            }else{
                val1 = false;
            }
            
            if(s3[i+j-1] == s2[j-1]){
                val2 = dp[i][j-1];
            }else{
                val2 = false;
            }
            
            dp[i][j] = val1 || val2;
        }
    }
         
    return dp[s1.size()][s2.size()];
}



int main(int argc, char** argv){
    //cout<<isInterleave("a","","a")<<endl;
    //cout<<isInterleave("bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa",
    //                    "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab",
    //                    "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab")<<endl;

    cout<<isInterleave("aabc","abad","aabadabc");

    return 0;
}
