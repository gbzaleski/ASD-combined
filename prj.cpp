#include <bits/stdc++.h>
using namespace std;
using LL = long long;
int n,m,k;
const int MAXN = 1e5 + 2137;
vector <vector<int>> Graph(MAXN);
int deg[MAXN];
LL cost[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;
    priority_queue <pair<LL,int>> PQ;
    for (int i = 0; i < n; ++i)
    {
        cin >> cost[i];
        deg[i] = 0;
    }

    int a,b;
    while (m--)
    {
        cin >> a >> b;
        a--, --b;
        deg[a]++;
        Graph[b].push_back(a);
    }

    for (int i = 0; i < n; ++i)
        if (deg[i] == 0)
            PQ.push({-cost[i], i});

    LL ans = 0;
    while (k--)
    {
       // cout << PQ.top().second + 1 << " - " << -PQ.top().first << "\n";
       // PQ.pop();

        ans = max(ans, -PQ.top().first);
        int v = PQ.top().second;
        PQ.pop();

        for (auto nei:Graph[v])
        {
            deg[nei]--;
            if (deg[nei] == 0)
                PQ.push({-cost[nei], nei});
        }
    }

    cout << ans;
    return 0;
}