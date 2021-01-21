#include <bits/stdc++.h>
using namespace std;
#define D 21
#define MAXN 1000069
int Anc[MAXN][D];
int Depth[MAXN];
int farstInTree[MAXN];
int farstOutside[MAXN];
vector <vector <int>> Graph(MAXN);

int getDist(int a, int b);

void DFS (int node, int prev, int dist)
{
    Depth[node] = dist;
    Anc[node][0] = prev;
    farstInTree[node] = node;

    for (int k=1; k!=D; ++k)
        Anc[node][k] = Anc[Anc[node][k-1]][k-1];

    for (auto nei:Graph[node])
        if (nei != prev)
            DFS(nei, node, dist+1);

    for (auto nei:Graph[node])
    {
        if (nei != prev)
        {
            if (Depth[farstInTree[nei]] > Depth[farstInTree[node]])
                farstInTree[node] = farstInTree[nei];
        }
    }


}

void DFS2 (int node, int prev, int dist)
{
    farstOutside[node] = node;

    if (node != prev)
    {
        int father = prev;
        int second_syn = -1;
        for (auto syn:Graph[father])
        {
            if (syn != node && syn != Anc[father][0])
                second_syn = syn;
        }

        int dist_father = getDist(father, farstOutside[father]) + 1;

        if (second_syn != -1)
        {
            int dist_brat = getDist(second_syn, farstInTree[second_syn]) + 2;

            if (dist_father > dist_brat)
                farstOutside[node] = farstOutside[father];
            else
                farstOutside[node] =  farstInTree[second_syn];
        }
        else
        {
            farstOutside[node] = farstOutside[father];
        }

        //cout << node << " =-> " << farstOutside[node] << endl;
    }

    for (auto nei:Graph[node])
        if (nei != prev)
            DFS2(nei, node, dist+1);
}

int Jump (int node, int len)
{
    int lvl = 0;
    while (len)
    {
        if (len%2) node = Anc[node][lvl];
        lvl++;
        len >>= 1;
    }
    return node;
}

int getLCA (int a, int b)
{
    if (Depth[a] < Depth[b])
        swap(a, b);

    a = Jump(a, Depth[a] - Depth[b]);
    if (a == b)
        return a;

    for (int i = D-1; i >= 0; --i)
    {
        if (Anc[a][i] != Anc[b][i])
        {
            a = Anc[a][i];
            b = Anc[b][i];
        }
    }

    return Anc[a][0];
}

inline int getDist(int a, int b)
{
    return Depth[a] + Depth[b] - 2*Depth[getLCA(a,b)];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t,n;
    cin >> n;
    for (int a,b,v = 1; v <= n; ++v)
    {
         cin >> a >> b;
         if (a != -1)
         {
             Graph[v].push_back(a);
             Graph[a].push_back(v);
         }
         if (b != -1)
         {
            Graph[v].push_back(b);
            Graph[b].push_back(v);
         }
    }

    DFS(1, 1, 0);
    DFS2(1, 1, 0);
/*
    for (int i = 1; i <= n; ++i)
    {
        cout << i << ": ";
        for (auto nei:Graph[i])
            cout << nei << " ";
        cout << " [" << farstInTree[i] << ", " << farstOutside[i] << "]";
        cout << endl;
    }
*/

    cin >> t;
    int v, dist;
    while (t--)
    {
        cin >> v >> dist;

        int go_up_from_dwn = getDist(v, farstInTree[v]) - dist;
        if (go_up_from_dwn >= 0)
        {
            cout << Jump(farstInTree[v], go_up_from_dwn) << "\n";
            continue;
        }

        int go_the_oppos = getDist(v, farstOutside[v]) - dist;
        if (go_the_oppos >= 0)
        {
            int LCA = getLCA(v, farstOutside[v]);
            if (go_the_oppos <= getDist(farstOutside[v], LCA))
            {
                cout << Jump(farstOutside[v], go_the_oppos) << "\n";
            }
            else
            {
                go_the_oppos -= getDist(farstOutside[v], LCA);
                cout << Jump(v, getDist(v, LCA) - go_the_oppos) << "\n";
            }
            continue;
        }

        cout << "-1\n";
    }
    return 0;
}

/*

8
3 4
-1 6
2 5
-1 -1
7 -1
-1 -1
8 -1
-1 -1
6
1 3
1 4
1 5
6 1
6 4
6 5
*/