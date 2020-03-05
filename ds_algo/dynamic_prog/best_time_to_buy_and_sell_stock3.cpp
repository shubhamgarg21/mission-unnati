/*
 * Author   : Shubham Garg
 * Date     : March 06, 2020 
 * Problem  : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
 *          : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
 * Solution : https://www.youtube.com/watch?v=oDhu5uGq_ic
 *          : https://www.youtube.com/watch?v=Pw6lrYANjz4
 * Build    : g++ -std=c++11 -lstdc++ best_time_to_buy_and_sell_stock3.cpp
 */ 

#include <iostream>
#include <vector>

using namespace std;

int maxProfit1stTry(vector<int>& prices) {
    if(prices.size() == 0) return 0;

    int dp[prices.size()];
    for(int i=0;i<prices.size();i++)
        dp[i] = 0;

    int buy_price = prices[0];
    int sell_price = prices[0];

    for(int i=1; i<prices.size(); i++){
        if(prices[i] > sell_price){
            sell_price = prices[i];
        }else{
            dp[i] = sell_price - buy_price;
            buy_price = prices[i];
            sell_price = prices[i];
        }
    }
    if(buy_price < sell_price){
        if(sell_price - buy_price > dp[prices.size()-1]){
            dp[prices.size()-1] = sell_price - buy_price;
        }
    }

    int max = 0;
    int max2 = 0;
    for(int i=0; i<prices.size(); i++){
        if(dp[i] > max){
            max2 = max;
            max = dp[i];
        }else if(dp[i] > max2){
            max2 = dp[i];
        }

        cout<<dp[i]<<" ";
    }

    return max+max2;
}


/*
 * DP : 
 *      T[i][j] = max{ 
 *                      T[i][j-1],
 *                      price[j] + max(-price[x] + T[i-1][x]) where 0<= x < j
 *                   }
 *
 * Time : O(n*k)
 * Space : O(n*k)
*/

int maxProfitKTransactions(vector<int>& prices, int k) {
    if(prices.size() == 0) return 0;

    int dp_profits[k+1][prices.size()];

    for(int i=0; i<k+1; i++)
        dp_profits[i][0] = 0;

    for(int j=0; j<prices.size(); j++)
        dp_profits[0][j] = 0;

    for(int i=1; i<k+1; i++){
        int profit = INT32_MIN;
        for(int j=1; j<prices.size(); j++){
            profit = max(profit, dp_profits[i-1][j-1] - prices[j-1]);

            dp_profits[i][j] = max(dp_profits[i][j-1],prices[j] + profit);
        }
    }

    return dp_profits[k][prices.size()-1];
}


/*
 * Space : O(n)
*/
int maxProfitKTransactionsSpaceOpt(vector<int>& prices, int k) {
    if(prices.size() == 0) return 0;

    if(k > prices.size()){
        // simple case in which we can do more transactions then the number of days.
        int profit = 0;
        for(int i =0; i<prices.size() - 1; i++){
            if(prices[i+1] > prices[i])
                profit += prices[i+1] - prices[i];
        }
        return profit;
    }

    int dp_profits[2][prices.size()];

    for(int i=0; i<2; i++)
        dp_profits[i][0] = 0;

    for(int j=0; j<prices.size(); j++)
        dp_profits[0][j] = 0;

    int ind, pre;
    for(int i=1; i<k+1; i++){
        ind = i%2;
        pre = 1 - ind;
        int profit = INT32_MIN;
        for(int j=1; j<prices.size(); j++){
            profit = max(profit, dp_profits[pre][j-1] - prices[j-1]);

            dp_profits[ind][j] = max(dp_profits[ind][j-1],prices[j] + profit);
        }
    }

    return dp_profits[ind][prices.size()-1];
}


int maxProfit(vector<int>& prices) {
    return maxProfitKTransactions(prices,2);
}

int main(int argc, char** argv){
    vector<int> prices = {7,1,5,3,6,4};
    //vector<int> prices = {2,1,2,1,0,1,2};
    //vector<int> prices = {3,3};
    //vector<int> prices = {1,4,1,4,3,1};
    cout<<maxProfit(prices);


    return 0;
}
