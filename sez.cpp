#include <iostream>
#include <vector>
using namespace std;
const int INF = 1e9 + 2137;

class Table
{
    public:
    vector <vector<int>> maxTable;
    vector <vector<int>> minTable;
    vector <int> log2;
    int M;
    int D;
    bool built;

    Table(int n)
    {
        D = 0;
        int s = 1;
        while (s <= n)
        {
            ++D;
            s <<= 1;
        }
        M = s;
        built = false;
        vector<int> row(D);

        maxTable.resize(M, row);
        minTable.resize(M, row);
        log2.resize(M);
    }

    void build()
    {
        for (int i = 2; i < M; i++)
            log2[i] = log2[i / 2] + 1;

        for (int p = 1; p < D; p++)
        {
            for (int i = 0; i + (1 << p) < M; i++)
            {
                long leftInterval = minTable[i][p - 1];
                long rightInterval = minTable[i + (1 << (p - 1))][p - 1];
                minTable[i][p] = min(leftInterval, rightInterval);

                leftInterval = maxTable[i][p - 1];
                rightInterval = maxTable[i + (1 << (p - 1))][p - 1];
                maxTable[i][p] = max(leftInterval, rightInterval);
            }
        }

        built = true;
    }

    int getMin(int l, int r)
    {
        if (built == false)
            build();

        int length = r - l + 1;
        int p = log2[length];
        int k = 1 << p;
        return min(minTable[l][p], minTable[r - k + 1][p]);
    }

    int getMax(int l, int r)
    {
        if (built == false)
            build();

        int len = r - l + 1;
        int p = log2[len];
        int k = 1 << p;
        return max(maxTable[l][p], maxTable[r - k + 1][p]);
    }
};

vector <Table> Hori;
vector <Table> Verti;
int n, m, q, val;

inline void scan(int &x)
{
    x = 0;
    register int c = getchar_unlocked();

    for(;c > 47 && c < 58;
         c = getchar_unlocked())
        x = (x << 1) + (x << 3) + c - 48;
}

class Tree
{
    public:
    vector <int> maxTree;
    vector <int> minTree;
    int M;
    bool built;

    Tree(int n)
    {
        int s = 1;
        while (s < n)
            s <<= 1;
        M = s;
        built = false;

        maxTree.resize(2 * M);
        minTree.resize(2 * M);
    }

    void build()
    {
        for (int p = M - 1; p > 0; --p)
        {
            maxTree[p] = max(maxTree[p*2], maxTree[p*2 + 1]);
            minTree[p] = min(minTree[p*2], minTree[p*2 + 1]);
        }
        built = true;
    }

    int getMax(int a, int b)
    {
        if (built == false)
            build();

        a += M;
        b += M;

        int ans = max(maxTree[a], maxTree[b]);

        while (a >> 1 != b >> 1)
        {
            if (a%2 == 0)
                ans = max(maxTree[a+1], ans);

            if (b%2 == 1)
                ans = max(maxTree[b-1], ans);

            a >>= 1;
            b >>= 1;
        }

        return ans;
    }

    int getMin(int a, int b)
    {
        if (built == false)
            build();

        a += M;
        b += M;

        int ans = min(minTree[a], minTree[b]);

        while (a >> 1 != b >> 1)
        {
            if (a%2 == 0)
                ans = min(minTree[a+1], ans);

            if (b%2 == 1)
                ans = min(minTree[b-1], ans);

            a >>= 1;
            b >>= 1;
        }

        return ans;
    }

};
vector <Tree> HoriTree;
vector <Tree> VertiTree;
bool onSeqmentTrees;

pair<int,int> solve(int x1, int y1, int x2, int y2)
{
    int mini = INF;
    int maxi = -INF;

    if (x2 - x1 <= y2 - y1)
    {
        for (int i = x1; i <= x2; ++i)
        {
            if (onSeqmentTrees)
            {
                maxi = max(maxi, HoriTree[i].getMax(y1, y2));
                mini = min(mini, HoriTree[i].getMin(y1, y2));
            }
            else
            {
                maxi = max(maxi, Hori[i].getMax(y1, y2));
                mini = min(mini, Hori[i].getMin(y1, y2));
            }

        }
    }
    else
    {
        for (int j = y1; j <= y2; ++j)
        {
            if (onSeqmentTrees)
            {
                maxi = max(maxi, VertiTree[j].getMax(x1, x2));
                mini = min(mini, VertiTree[j].getMin(x1, x2));
            }
            else
            {
                maxi = max(maxi, Verti[j].getMax(x1, x2));
                mini = min(mini, Verti[j].getMin(x1, x2));
            }
        }
    }

    return make_pair(maxi, mini);
}

// drzewa robione sa dla niekwadratowych plansz.
inline bool checkToDoTrees()
{
    return max(m,n)/min(m,n) > 10;
}

int VertiM, HoriM;

int main()
{
  /*  ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);*/

    scan(n);
    scan(m);
    scan(q);

    onSeqmentTrees = checkToDoTrees();

    for (int i = 0; i != n; ++i)
    {
        if (onSeqmentTrees)
            HoriTree.push_back(Tree(m));
        else
            Hori.push_back(Table(m));
    }

    for (int j = 0; j != m; ++j)
    {
        if (onSeqmentTrees)
            VertiTree.push_back(Tree(n));
        else
            Verti.push_back(Table(n));
    }

    if (onSeqmentTrees)
    {
        HoriM = HoriTree[0].M;
        VertiM = VertiTree[0].M;
    }

    for (int i = 0; i != n; ++i)
    {
        for (int j = 0; j != m; ++j)
        {
            scan(val);

            if (onSeqmentTrees)
            {
                HoriTree[i].minTree[j + HoriM] = val;
                HoriTree[i].maxTree[j + HoriM] = val;

                VertiTree[j].maxTree[i + VertiM] = val;
                VertiTree[j].minTree[i + VertiM] = val;
            }
            else
            {
                Hori[i].minTable[j][0] = val;
                Hori[i].maxTable[j][0] = val;

                Verti[j].maxTable[i][0] = val;
                Verti[j].minTable[i][0] = val;
            }
        }
    }

    int x1,y1,x2,y2;
    pair <int,int> res;
    while (q--)
    {
        scan(x1);
        scan(y1);
        scan(x2);
        scan(y2);

        res = solve(x1, y1, x2, y2);
       printf("%d\n", res.first - res.second);
    }

    return 0;
}
