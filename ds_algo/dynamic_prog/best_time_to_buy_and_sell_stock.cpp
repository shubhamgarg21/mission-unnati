//g++ -std=c++11 -lstdc++ best_time_to_buy_and_sell_stock.cpp 

#include <iostream>
#include <vector>

using namespace std;
int maxProfit(vector<int>& prices);

int maxProfit(vector<int>& prices) {
    if(prices.size() == 0) return 0;

    int dp[prices.size()];
    for(int i=0; i<prices.size(); i++){
        dp[i] = 0;
    }
    dp[0] = 0;

    int buy_price = prices[0];
    int sell_price = -1;

    for(int i=1; i<prices.size(); i++){
        if(prices[i] < buy_price){
            buy_price = prices[i];
            sell_price = -1;
            dp[i] = 0;
        }else if(prices[i] > sell_price && prices[i] > buy_price){
            sell_price = prices[i];
            dp[i] = sell_price - buy_price;
        }else  if(prices[i] < sell_price){
            dp[i] = dp[i-1];
        }
    }

    int max = -1;
    for(int i=0; i<prices.size(); i++){
        if(dp[i] > max)
            max = dp[i];
    }

    return max;
}

int main(int argc, char** argv){
    //vector<int> prices = {7,1,5,3,6,4};
    //vector<int> prices = {2,1,2,1,0,1,2};
    //vector<int> prices = {3,3};
    vector<int> prices = {1,4,1,4,3,1};
    cout<<maxProfit(prices);


    return 0;
}
