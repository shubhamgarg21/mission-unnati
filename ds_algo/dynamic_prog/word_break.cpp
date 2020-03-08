/*
 * Author   : Shubham Garg
 * Date     : March 08, 2020 
 * Problem  : https://leetcode.com/problems/word-break/
 * Build    : g++ -std=c++11 -lstdc++ word_break.cpp
 */ 

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

//recursive solution - working
//exceeding time limit
//need to introduce DP
bool wordBreak_recursive(string s, vector<string>& wordDict) {
    if(s.size() == 0) return true;

    int i = 0; // index to trace string s
    int j; // index to trace dict word

    string word;
    vector<string>::iterator it;

    for(it = wordDict.begin();it != wordDict.end(); it++){
        word = *it;
        i = 0;
        for(j=0; j<word.size(); j++){
            if(word[j] != s[i]) break;

            i++;
        }

        if(i == word.size()){
            //the for loop ran without breaking

            if(wordBreak_recursive(s.substr(i),wordDict))
                return true;
        }
    }
    return false;
}


/*
 *  DP Solution :
 *      1. State : T[i] -> wordBreak uptp index i of string s
 *      2. Update function/recursion :
 *          T[i] = T[i - word.len] if word == s(i - word.len : i) loop over each word in the dict
 *               = false otherwise
 *      3. Initial values : 
 *          dp[0] to dp[i] = false , where i in the min word len in the dict
 *
*/
bool wordBreak(string s, vector<string>& wordDict) {
    if(s.size() == 0) return true;

    bool dp[s.size()];
    memset(dp,false,sizeof(dp));
    int i = 0; // index to trace string s
    int j; // index to trace dict word

    string word;
    vector<string>::iterator it;


    for(int i=0; i<s.size(); i++){
        for(it = wordDict.begin();it != wordDict.end(); it++){
            word = *it;
            if (i < word.size()-1){
                dp[i] = false;
                continue;
            }
            
            if(word.compare(s.substr(i-word.size()+1,word.size())) == 0){
                if(i-word.size()+1 > 0)
                    dp[i] = dp[i-word.size()];
                else
                    dp[i] = true;
            }

            if(dp[i]) break;
        }
    }


    return dp[s.size() - 1];
}


int main(int argc, char** argv){
    vector<string> wordDict = {"leet","code"};
    cout<<wordBreak("leetcode",wordDict)<<endl;
    
    vector<string> wordDict2 = {"apple","pen"};
    cout<<wordBreak("applepenapple",wordDict2)<<endl;

    vector<string> wordDict3 = {"cats","dog","sand","and","cat"};
    cout<<wordBreak("catsandog",wordDict3)<<endl;

    return 0;
}
