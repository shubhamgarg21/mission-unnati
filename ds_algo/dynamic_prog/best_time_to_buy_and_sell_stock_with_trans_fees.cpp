/*
 * Author   : Shubham Garg
 * Date     : March 07, 2020 
 * Problem  : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
 * Build    : g++ -std=c++11 -lstdc++ best_time_to_buy_and_sell_stock_with_trans_fees.cpp
 */ 

#include <iostream>
#include <vector>

using namespace std;

/*
 * DP Solution - 
 *      1. Define states :
 *            buy[i] -> max profit till day i with transaction ending in buy
 *            sell[i] -> max profit till day i with transaction ending in sell
 *
 *      2. update function/ recursion : 
 *            buy[i] = max(buy[i-1], sell[i-1] - prices[i])
 *            sell[i] = max(sell[i-1], buy[i-1] + prices[i] - fee)
 *
 *      3. initial values : 
 *            buy[0] = -prices[0]   // day 0
 *            sell[0] = 0    //day 0
*/

int maxProfit(vector<int>& prices, int fee){
    if(prices.size() == 0) return 0;

    int *buy = new int[prices.size()];
    int *sell = new int[prices.size()];

    buy[0] = -prices[0];

    sell[0] = 0;

    for(int i=1; i<prices.size(); i++){
        buy[i] = max(buy[i-1], sell[i-1] - prices[i]);    
        sell[i] = max(sell[i-1], buy[i-1] + prices[i] - fee); 
    }

    return sell[prices.size()-1];
}

//space optimized
int maxProfit_SpaceOpt(vector<int>& prices, int fee){
    if(prices.size() == 0) return 0;

    int b0 = -prices[0];
    int s0 = 0;
    
    int b1,s1;

    for(int i=1; i<prices.size(); i++){
        b1 = max(b0, s0 - prices[i]);    
        s1 = max(s0, b0 + prices[i] -fee); 

        b0 = b1;
        s0 = s1;
    }

    return s1;
}

int main(int argc, char** argv){
    vector<int> prices = {1, 3, 2, 8, 4, 9};
    int fees = 2;

    cout<<maxProfit(prices, fees)<<endl;

    return 0;
}
