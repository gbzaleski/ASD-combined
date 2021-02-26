#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define MP make_pair
const int MAXN = 1e5 + 7;
const LL INF = 1e18;
int m,n,a,b,w;

vector <vector <int>> Graph(MAXN);
map<pair<int,int>, LL> wei;

inline LL getDis(const int &Av, const int &Bv)
{
    return wei[MP(Av, Bv)];
}

void DFS(int v, int fath, vector <bool> &vis, vector <LL> &dist, vector <int> &fathers)
{
    if (vis[v] == true)
        return;

    fathers[v] = fath;

    vis[v] = true;
    if (v == n - 1)
    {
        return;
    }

    sort(Graph[v].begin(), Graph[v].end());

    for (auto nei: Graph[v])
    {
        if (vis[nei] == false && dist[v] + getDis(v, nei) == dist[nei])
            DFS(nei, v, vis, dist, fathers);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);

    cin >> n >> m;
    while (m--)
    {
        cin >> a >> b >> w;
        a--, --b;

        Graph[a].push_back(b);
        Graph[b].push_back(a);
        wei[MP(a,b)] = w;
        wei[MP(b,a)] = w;
    }

    vector <LL> dist(n, INF);
    vector <bool> vis(n, false);
    priority_queue <pair<LL,int>> PQ; // -dist, v

    dist[0] = 0;
    PQ.push(make_pair(0,0));

    while (PQ.size())
    {
        int v = PQ.top().second;
        PQ.pop();

        if (vis[v] == true)
            continue;

        vis[v] = true;

        for (auto nei: Graph[v])
        {
            LL curdis = getDis(v, nei);
            if (dist[v] + curdis < dist[nei])
            {
                dist[nei] = dist[v] + curdis;
                PQ.push(MP(-dist[nei], nei));
            }
        }
    }

    vector <bool> vis2(n);
    vector <int> fath(n);
    DFS(0, -1, vis2, dist, fath);

    int k = n - 1;
    vector <int> ans;
    ans.push_back(k);
    while (k != -1)
    {
        ans.push_back(fath[k]);
        k = fath[k];
    }

    ans.pop_back();
    reverse(ans.begin(), ans.end());
    for (auto x: ans)
        cout << x + 1 << " ";

    return 0;
}
