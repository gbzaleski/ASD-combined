#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 69;
vector <vector <int>> Graph(MAXN);
int n;

void DFS(int v, int clr, vector <int> &scc)
{
    scc[v] = clr;
    for (auto nei: Graph[v])
    {
        if (scc[nei] == -1)
            DFS(nei, clr,  scc);
    }
}

bool cmpvec (const vector<int> &a, const vector<int> &b)
{
    return a.front() < b.front();
}

void addEdge(int a, int b)
{
    Graph[a].push_back(b);
    Graph[b].push_back(a);
}

int pt;
int main()
{
    ios_base::sync_with_stdio(0);
    cin >> n;
    stack <int> S;
    for (int i = 0; i <n; ++i)
    {
        cin >> pt;
        pt--;
        if (S.empty() || S.top() < pt)
        {
            S.push(pt);
            continue;
        }

        int top = S.top();
        while (S.size() && S.top() > pt)
        {
            addEdge(S.top(), pt);
            S.pop();
        }

        S.push(top);
    }


    vector <int> scc(n, -1);
    int cnt = 0;

    for (int v = 0; v < n; ++v)
    {
        if (scc[v] == -1)
        {
            DFS(v, cnt, scc);
            cnt++;
           // cout << endl;
        }
    }

    vector <vector <int>> sccs(cnt);
    for (int v = 0; v < n; ++v)
    {
        sccs[scc[v]].push_back(v + 1);
    }

    for (int i = 0; i < cnt; ++i)
    {
       sort(sccs[i].begin(), sccs[i].end());
    }
    sort(sccs.begin(), sccs.end(), [](vector<int> &a, vector<int> &b){ return a[0]<b[0];});

    cout << cnt << "\n";
    for (auto sk: sccs)
    {
        cout << sk.size() << " ";
        for (auto vv:sk)
            cout << vv << " ";
        cout << "\n";
    }
    return 0;
}

/*
4
3 4 1 2
*/
