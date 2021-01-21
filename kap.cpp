#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 * 2 + 69;
const int INF = 1e9 + 2137;
vector <vector <int>> Graph(MAXN);

struct point
{
    int x;
    int y;
    int ind;
};

point Points[MAXN];
vector <point> byX;
vector <point> byY;
int n;

bool cmpX(const point &A, const point &B)
{
    return A.x < B.x || (A.x == B.x && A.y < B.y);
}

bool cmpY(const point &A, const point &B)
{
    return A.y < B.y || (A.y == B.y && A.x < B.x);
}

inline int getDis(const int &A, const int &B)
{
    return min(abs(Points[A].x - Points[B].x), abs(Points[A].y - Points[B].y));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    point p;
    for (int i = 0; i < n; ++i)
    {
        cin >> p.x >> p.y;
        p.ind = i;
        Points[i] = p;
        byX.push_back(p);
        byY.push_back(p);
    }

    sort(byX.begin(), byX.end(), cmpX);
    sort(byY.begin(), byY.end(), cmpY);

    point pp, pnext;
    for (int i = 0; i < n - 1; ++i)
    {
        pp = byX[i];
        pnext = byX[i+1];
        Graph[pp.ind].push_back(pnext.ind);
        Graph[pnext.ind].push_back(pp.ind);
    }

    for (int i = 0; i < n - 1; ++i)
    {
        pp = byY[i];
        pnext = byY[i+1];
        Graph[pp.ind].push_back(pnext.ind);
        Graph[pnext.ind].push_back(pp.ind);
    }

    vector <int> Dist(n, INF);
    vector <bool> Vis(n);
    priority_queue <pair<int,int>> PQ; // -dist, v

    Dist[0] = 0;
    Vis[0] = true;
    PQ.push(make_pair(0,0));

    while (PQ.size())
    {
        int v = PQ.top().second;
        //cout << v << " <- \t";
        PQ.pop();
        for (auto nei:Graph[v])
        {
            int curdis = getDis(v, nei);
            if (Dist[v] + curdis < Dist[nei])
            {
                Dist[nei] = Dist[v] + curdis;
                PQ.push(make_pair(-Dist[nei], nei));
            }
        }
    }

    cout << Dist[n-1];

    return 0;
}
