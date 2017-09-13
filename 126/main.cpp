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

struct MapNode {
  string word;
  vector<MapNode*> edges;
  vector<MapNode*> from;
  bool searching;
  bool pending;
  MapNode(string w) : word(w), edges(vector<MapNode*>()), from(vector<MapNode*>()), searching(false), pending(false) {}
};

void construct(vector<vector<string>> &ans, vector<string> &curList, MapNode *curNode, size_t level) {
  vector<string> tmpList(curList);
  tmpList[level] = curNode->word;

  if (level == 0) {
    ans.push_back(tmpList);
    return;
  }

  for (MapNode *node : curNode->from) {
    construct(ans, tmpList, node, level - 1);
  }
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
  vector<MapNode*> nodeList(wordList.size());
  for (size_t i = 0; i < wordList.size(); ++i) {
    nodeList[i] = new MapNode(wordList[i]);
  }

  bool isBeginIncluded = false;
  MapNode *beginNode = nullptr;
  MapNode *endNode = nullptr;

  for (auto node : nodeList) {
    if (node->word == endWord) endNode = node;
    if (node->word == beginWord) beginNode = node;
  }
  if (endNode == nullptr) {
    return vector<vector<string>>();
  }
  if (beginNode == nullptr) {
    beginNode = new MapNode(beginWord);
    nodeList.push_back(beginNode);
  }

  for (size_t i = 0; i < nodeList.size(); ++i) {
    auto nodeA = nodeList[i];
    for (size_t j = i + 1; j < nodeList.size(); ++j) {
      auto nodeB = nodeList[j];
      size_t diff = 0;
      for (size_t k = 0; k < nodeA->word.size(); ++k) {
        if (nodeA->word[k] != nodeB->word[k]) {
          ++diff;
        }
      }
      if (diff == 1) {
        nodeA->edges.push_back(nodeB);
        nodeB->edges.push_back(nodeA);
      }
    }
  }

  beginNode->searching = true;
  vector<MapNode*> curQueue(1, beginNode);
  vector<MapNode*> nextQueue;
  bool found = false;
  int level = 0;
  while (!found && curQueue.size() > 0) {
    ++level;
    for (MapNode *curNode : curQueue) {
      if (curNode->word == "rex" && level == 2) {
        cout << endl;
      }
      for (MapNode *nextNode : curNode->edges) {
        if (nextNode->searching) {
          continue;
        }

        if (nextNode == endNode) {
          found = true;
        }
        nextNode->from.push_back(curNode);

        if (nextNode->pending) {
          continue;
        }
        nextNode->pending = true;
        nextQueue.push_back(nextNode);
      }
    }

    curQueue.swap(nextQueue);
    nextQueue.clear();
    for (auto node : curQueue) {
      node->searching = true;
    }
  }

  if (!found) {
    return vector<vector<string>>();
  }

  vector<vector<string>> ans;
  vector<string> curList(level + 1);
  construct(ans, curList, endNode, level);

  return ans;
}

int main(int argc, char **argv) {
  vector<string> list = { "ted","tex","red","tax","tad","den","rex","pee" };
  auto ans = findLadders("red", "tax", list);
  system("pause");
}