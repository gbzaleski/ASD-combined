#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2 *1e5 + 2137;
const int INF = 1e9 + 696969;
vector <int> type(MAXN);
vector <vector<int>> Graph(MAXN);
int n,a,b,t, ans;

void DFS (int v, vector <int> &dis, int cur_dist)
{
    dis[v] = cur_dist;
    for (auto nei: Graph[v])
    {
        if (dis[nei] == INF)
            DFS(nei, dis, cur_dist + 1);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> type[i];
        type[i]--;
    }

    int w = n - 1;
    while (w--)
    {
        cin >> a >> b;
        a--, --b;
        Graph[a].push_back(b);
        Graph[b].push_back(a);
    }

    ans = 0;
    for (int t = 0; t < 10; ++t)
    {
        vector <int> dis(n, INF);
        for (int v = 0; v < n; ++v)
        {
            if (type[v] == t)
            {
                DFS(v, dis, 0);
                v = n;
            }
        }

        int max_dist = 0;
        int node = -1;
        for (int v = 0; v < n; ++v)
        {
            if (type[v] == t && max_dist < dis[v])
            {
                max_dist = dis[v];
                node = v;
            }
        }

        if (node != -1)
        {
            dis = vector<int>(n, INF);
            DFS(node, dis, 0);
            for (int v = 0; v < n; ++v)
            {
                if (type[v] == t)
                {
                    ans = max(ans, dis[v]);
                }
            }
        }

    }

    cout << ans;
    return 0;
}
