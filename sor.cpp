#include <iostream>
#include <vector>
using namespace std;
using LL = long long;
int n;
#define MAXN 1003
const LL MOD = 1e9;

LL DP[MAXN][MAXN][2];
int tab[MAXN];

LL Calc (int i, int j, int pos)
{
    if (DP[i][j][pos] != -1)
        return DP[i][j][pos];

    if (pos == 0) //z lewej
    {
        DP[i][j][0] = (tab[i] < tab[i+1]) * Calc(i+1, j, 0)
            + (tab[i] < tab[j]) * Calc(i+1, j, 1);
    }
    else //pos == 1 , z prawej
    {
        DP[i][j][1] = (tab[j] > tab[i]) * Calc(i, j-1, 0)
            + (tab[j] > tab[j-1]) * Calc(i, j-1, 1);
    }

    DP[i][j][pos] = DP[i][j][pos] % MOD;
    return DP[i][j][pos];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
        {
            DP[i][j][0] = -1;
            DP[i][j][1] = -1;
        }

    for (int i = 0; i < MAXN; ++i)
    {
        DP[i][i][0] = 0;
        DP[i][i][1] = 1;
    }

    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> tab[i];

    cout << (Calc(0, n-1, 0) + Calc(0, n-1, 1)) % MOD;

    return 0;
}