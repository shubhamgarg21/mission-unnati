/*
 * Author   : Shubham Garg
 * Date     : Feb 21, 2020
 * Problem  : https://leetcode.com/problems/maximal-rectangle/
 * Solution : https://www.youtube.com/watch?v=g8bSdXCG-lA
 *          : https://www.youtube.com/watch?v=ZmnqCZp9bBs
 * Build    : g++ -std=c++11 -lstdc++ maximal_rectangle.cpp
 */ 

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int maximalRectangleHist(int *arr , int n){
    stack<int> s;
    int top,i,area, max_area = -1;

    i = 0;
    while(i<n){
        if(s.empty() || arr[s.top()] <= arr[i]){
            s.push(i++);
        }else{
            top = s.top();
            s.pop();
            area = arr[top]*(s.empty()?i:i - s.top() -1);
            if(area > max_area)
                max_area = area;
        }       
     }

    while(!s.empty()){
        top = s.top();
        s.pop();
        area = s.empty()?arr[top]*i:arr[top]*(i - s.top()-1);
        if(area > max_area)
            max_area = area;
    }

    return max_area;
}

int getMaxArea(int hist[], int n) 
{ 
    // Create an empty stack. The stack holds indexes  
    // of hist[] array. The bars stored in stack are  
    // always in increasing order of their heights. 
    stack<int> s; 
  
    int max_area = 0; // Initialize max area 
    int tp;  // To store top of stack 
    int area_with_top; // To store area with top bar 
                       // as the smallest bar 
  
    // Run through all bars of given histogram 
    int i = 0; 
    while (i < n) 
    { 
        // If this bar is higher than the bar on top  
        // stack, push it to stack 
        if (s.empty() || hist[s.top()] <= hist[i]) 
            s.push(i++); 
  
        // If this bar is lower than top of stack,  
        // then calculate area of rectangle with stack  
        // top as the smallest (or minimum height) bar.  
        // 'i' is 'right index' for the top and element  
        // before top in stack is 'left index' 
        else
        { 
            tp = s.top();  // store the top index 
            s.pop();  // pop the top 
  
            // Calculate the area with hist[tp] stack  
            // as smallest bar 
            area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1); 
  
            // update max area, if needed 
            if (max_area < area_with_top) 
                max_area = area_with_top; 
        } 
    } 
  
    // Now pop the remaining bars from stack and calculate 
    // area with every popped bar as the smallest bar 
    while (s.empty() == false) 
    { 
        tp = s.top(); 
        s.pop(); 
        area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1); 
  
        if (max_area < area_with_top) 
            max_area = area_with_top; 
    } 
  
    return max_area; 
}


int maximalRectangle(vector<vector<char>>& matrix) {
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

    cout<<maximalRectangle(matrix)<<endl;

    //vector<int> grid = {2,1,2,3,1};
    //cout<<maximalRectangleHist(grid)<<endl;

    return 0;
}
