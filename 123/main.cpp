#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

int maxProfit(vector<int>& prices) {
  if (prices.size() == 0) return 0;

  const int LEN = prices.size();
  int maxPro = 0;

  // profit of first stock
  int pa = -1; 

  for (size_t i = 0; i < LEN; ++i) {
    if (i == 0) {
      pa = 0;
    }
    else {
      int tmpPa = pa + (prices[i] - prices[i - 1]);
      pa = tmpPa < 0 ? 0 : tmpPa;
    }

    // profit of second stock
    int pb = -1;
    for (size_t j = i; j < LEN; ++j) {
      if (j == i) {
        pb = 0;
      }
      else {
        int tmpPb = pb + (prices[j] - prices[j - 1]);
        pb = tmpPb < 0 ? 0 : tmpPb;
      }

      if (pa + pb > maxPro) {
        maxPro = pa + pb;
      }
    }
  }

  return maxPro;
}

// another solution from discuss, greedy
int anotherMaxProfit(vector<int>& prices) {
  int buyA = INT_MIN;
  int sellA = 0;
  int buyB = INT_MIN;
  int sellB = 0;

  for (int price : prices) {
    buyA = max(buyA, -price);
    sellA = max(sellA, buyA + price);
    buyB = max(buyB, sellA - price);
    sellB = max(sellB, buyB + price);
  }

  return sellB;
}

int main(int argc, char **argv) {
  vector<int> prices = { 0, 1, 2, 3, 4, 5, 4, 2, 0, 1, 2, 3, 4, 5 };
  cout << anotherMaxProfit(prices) << endl;
  system("pause");
}