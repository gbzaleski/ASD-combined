#include <iostream>

using namespace std;
#define D 11
#define M 32768
#define TS 65536
#define MOD 1000000000
int tab[M];
long long Tree[TS][D];
int n,k;
long long res;

void insertion(int where, long long val, int lvl)
{
    where += M;
    Tree[where][lvl] = val%MOD;
    where /= 2;
    while (where)
    {
        Tree[where][lvl] = (Tree[2*where][lvl] + Tree[2*where+1][lvl])%MOD;
        where /=2;
    }
}

long long getSumFuk (int a, int b ,int lvl)
{
    a += M;
    b += M;

    long long ans = Tree[a][lvl]%MOD;
    if (a!=b) ans = (ans + Tree[b][lvl])%MOD;
    while (a/2 != b/2)
    {
        if (a%2 == 0) ans = (ans + Tree[a+1][lvl])%MOD;
        if (b%2 == 1) ans = (ans + Tree[b-1][lvl])%MOD;
        a /= 2;
        b /= 2;
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i != TS; ++i)
        for (int j = 0; j != D; ++j)
            Tree[i][j] = 0;
    res = 0;

    cin >> n >> k;
    for (int i = 0; i != n; ++i)
        cin >> tab[i];

    for (int i=0; i!=n; ++i)
    {
        int val = tab[i];
        insertion(val, 1, 0);
        for (int j = 1; j < k; ++j)
        {
            long long inp = getSumFuk(val+1, M-1, j-1);
            insertion(val, inp, j);
        }
    }

    cout << getSumFuk(0, M-1, k-1);

    return 0;
}