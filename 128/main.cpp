#include <unordered_map>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void traverse(){}

int longestConsecutive(vector<int>& nums) {
  unordered_map<int, int> maxRuler;
  int maxLen = 0;
  for (auto num : nums) {
    if (maxRuler[num]) continue;

    // if maxRuler[n] does not exist, it creates and returns 0
    auto curMaxLen = maxRuler[num - 1] + maxRuler[num + 1] + 1;
    maxRuler[num] = curMaxLen;

    // change values of 2 poles of local ruler
    maxRuler[num + maxRuler[num + 1]] = curMaxLen;
    maxRuler[num - maxRuler[num - 1]] = curMaxLen;

    maxLen = max(curMaxLen, maxLen);
  }

  return maxLen;
}

int anotherFaiedlongestConsecutive(vector<int>& nums) {
  if (nums.empty()) {
    return 0;
  }
  map<int, int> table;
  vector<int> unionFind(nums.size(), -1);

  for (size_t idx = 0; idx < nums.size(); ++idx) {
    table[nums[idx]] = idx;
  }

  for (size_t idx = 0; idx < nums.size(); ++idx) {
    auto cur = nums[idx];
    if (table.count(cur - 1) == 1) {
      unionFind[idx] = table[cur - 1];
    }
  }

  vector<int> stack;
  int maxLen = 1;
  for (size_t idx = 0; idx < unionFind.size(); ++idx) {
    int i = idx;
    while (unionFind[i] != -1) {
      stack.push_back(i);
      i = unionFind[i];
    }

    int len = 2;
    while (!stack.empty()) {
      i = stack.back();
      if (len > maxLen) {
        maxLen = len;
      }
      ++len;
      stack.pop_back();
    }
  }

  return maxLen;
}

int main() {
  vector<int> arr({ 100, 4, 200, 1, 3, 2 });
  cout << longestConsecutive(arr) << endl;
  system("pause");
}