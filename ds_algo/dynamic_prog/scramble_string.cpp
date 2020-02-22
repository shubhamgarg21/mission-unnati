/*
 * Author   : Shubham Garg
 * Date     : Feb 21, 2020 
 * Problem  : https://leetcode.com/problems/scramble-string/
 * Solution : http://leetcodesolutionandsummaries.blogspot.com/2015/01/scramble-string.html 
 * Build    : g++ -std=c++11 -lstdc++ scramble_string.cpp 
 */ 

#include <iostream>
#include <vector>
#include <bits/stdc++.h> 

using namespace std;

bool isAnagram(string s1, string s2){
    sort(s1.begin(),s1.end());
    sort(s2.begin(),s2.end());

    if(s1 == s2)
        return true;

    return false;
}

bool isScramble(string s1, string s2) {
    if(s1 == s2)
       return true;

    if(!isAnagram(s1,s2))
        return false;

    int ln = s1.size();
    for(int i=1; i<ln; i++){
        if((isScramble(s1.substr(0,i),s2.substr(0,i)) && isScramble(s1.substr(i,ln-i),s2.substr(i,ln-i))) ||
            (isScramble(s1.substr(0,i),s2.substr(ln-i,i)) && isScramble(s1.substr(i,ln-i),s2.substr(0,ln-i))))
            return true;
    }

    return false;
}

int main(int argc, char** argv){
    cout<<isScramble("great","rgtae")<<endl;
    return 0;
}
