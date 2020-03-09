/*
 * Author   : Shubham Garg
 * Date     : Mar 09, 2020
 * Problem  : https://leetcode.com/problems/maximal-square/
 * Build    : g++ -std=c++11 -lstdc++ maximal_square.cpp
 */ 

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//hack this general function to calculate area
//based on min. side of the rectangle. so that
//it will only return area of square.
int maximalRectangleHist(int *arr , int n){
    stack<int> s;
    int top,i,area, max_area = -1;

    i = 0;
    int m1;
    while(i<n){
        if(s.empty() || arr[s.top()] <= arr[i]){
            s.push(i++);
        }else{
            top = s.top();
            s.pop();
            m1 = min(arr[top],(s.empty()?i:i - s.top() -1));
            area = m1*m1;
            if(area > max_area)
                max_area = area;
        }       
     }

    while(!s.empty()){
        top = s.top();
        s.pop();
        m1 = min(arr[top],(s.empty()?i:i - s.top() -1));
        area = m1*m1;
        //area = s.empty()?arr[top]*i:arr[top]*(i - s.top()-1);
        if(area > max_area)
            max_area = area;
    }

    return max_area;
}

// alternate simple DP soln : https://www.youtube.com/watch?v=_Lf1looyJMU
int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size();
    if(m == 0) return 0;

    int n = matrix[0].size();
    if(n == 0) return 0;

    int arr[n];
    for(int j=0; j<n; j++){
        arr[j] = 0;        
    }

    int area;
    int max_area = -1;

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(matrix[i][j] == '0')
                arr[j] = 0;
            else
                arr[j]++;
        }
        area = maximalRectangleHist(arr,n);
        if(area > max_area)
            max_area = area;
    }

    return max_area;        
}

int main(int argc, char** argv){
    vector<vector<char>> matrix = {
                                    {'1','0','1','0','0'},
                                    {'1','0','1','1','1'},
                                    {'1','1','1','1','1'},
                                    {'1','0','0','1','0'}
                                  };

    cout<<maximalSquare(matrix)<<endl;

    return 0;
}
