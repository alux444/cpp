#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <unordered_map>
using namespace std;

struct DSU
{
    vector<int> parent;
    DSU(int n) : parent(n)
    {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y)
    {
        parent[find(x)] = find(y);
    }
};

string getAlphabeticallyMinimalString(string s, vector<int> arr, vector<int> brr)
{
    int n = s.size();
    DSU dsu(n);
    for (int i = 0; i < arr.size(); ++i)
        dsu.unite(arr[i], brr[i]); // identify indices that are directly or indirectly connected

    unordered_map<int, vector<int>> groups;
    for (int i = 0; i < n; ++i)
        groups[dsu.find(i)].push_back(i); // group all indices in the same group

    string res = s;
    for (auto &[root, idxs] : groups)
    {
        string chars;
        for (int idx : idxs)
            chars += s[idx];
        sort(chars.begin(), chars.end());
        sort(idxs.begin(), idxs.end());
        for (int j = 0; j < idxs.size(); ++j)
            res[idxs[j]] = chars[j]; // assign the earliest lexicographic char to the earliest indices possible
    }
    return res;
}

int main()
{
    string s = "dbca";
    vector<int> arr = {0, 2, 3};
    vector<int> brr = {1, 3, 2};
    cout << getAlphabeticallyMinimalString(s, arr, brr) << endl; // Should print bdac
}
