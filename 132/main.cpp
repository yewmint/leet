#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int minCut(string s) {
  if (s.size() <= 1) return 0;

  int len = s.size();
  vector<int> minCuts(len + 1);
  for (int i = 0; i <= len; ++i) {
    minCuts[i] = i - 1;
  }

  for (int i = 0; i < len; ++i) {
    for (int j = 0; i - j >= 0 && i + j < len && s[i - j] == s[i + j]; ++j) {
      minCuts[i + j + 1] = min(minCuts[i + j + 1], 1 + minCuts[i - j]);
    }

    for (int j = 0; i - j - 1 >= 0 && i + j < len && s[i - j - 1] == s[i + j]; ++j) {
      minCuts[i + j + 1] = min(minCuts[i + j + 1], 1 + minCuts[i - j - 1]);
    }
  }

  return minCuts[len];
}

int main() {
  cout << minCut("aab") << endl;
  system("pause");
}