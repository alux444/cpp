#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <sstream>
using namespace std;

int main()
{
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int tags, queries;
  cin >> tags >> queries;

  cin.ignore(); // ignores the newline

  vector<string> rawTags(tags);
  for (auto &tag : rawTags)
  {
    getline(cin, tag);
  }

  vector<string> rawQueries(queries);
  for (auto &q : rawQueries)
  {
    getline(cin, q);
  }

  // for (auto& tag : rawTags) {
  //     cout << tag << endl;
  // }
  // for (auto& q : rawQueries) {
  //     cout << q << endl;
  // }

  string curTag;
  std::map<string, string> map;
  vector<string> curTags;
  for (int i = 0; i < tags; i++)
  {
    curTag = rawTags[i];
    // std::remove - remove all values by rearranging and returns an iterator at the new start
    // .erase to remove everything outside of between the given iterators

    // remove " and >
    curTag.erase(
        std::remove(curTag.begin(), curTag.end(), '\"'),
        curTag.end());
    curTag.erase(
        std::remove(curTag.begin(), curTag.end(), '>'),
        curTag.end());

    bool isClosingTag = curTag.substr(0, 2) == "</";
    if (isClosingTag)
    {
      curTags.pop_back();
      continue;
    }

    std::stringstream ss;
    ss << curTag;

    string tag, attribute, value;
    char ch;
    // reads < tag attribute = value >
    ss >> ch >> tag >> attribute >> ch >> value;

    string fullTag = "";
    if (curTags.size() > 0)
    {
      // reverse begin - reverse iterator
      // so get the last item
      fullTag = *curTags.rbegin();
      fullTag = fullTag + "." + tag; // <- parent.currentTag format
    }
    else
    {
      fullTag = tag;
    }

    // current tag as the full tag
    curTags.push_back(fullTag);
    // query name: tag~attribute
    map[*curTags.rbegin() + "~" + attribute] = value;

    // keep doing this for possible future values
    while (ss)
    {
      ss >> attribute >> ch >> value;
      map[*curTags.rbegin() + "~" + attribute] = value;
    }
  }

  for (int i = 0; i < queries; i++)
  {
    if (map.find(rawQueries[i]) == map.end())
    {
      cout << "Not Found!" << endl;
    }
    else
    {
      cout << map[rawQueries[i]] << endl;
    }
  }

  return 0;
}
