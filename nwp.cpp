#include <cstdio>
using namespace std;
#define MAXN 1007
int n, m, range, maxVal, minVal;
int A[MAXN], B[MAXN];
const int MAXK = 21;
const int INF = 1e9 + 2137;
int DP[MAXN][MAXN][MAXK];

inline int max(int &a, int &b)
{
    if (a >= b)
        return a;
    return b;
}

inline int min(int &a, int &b)
{
    if (a <= b)
        return a;
    return b;
}

inline int LCIS()
{
    for (int k = 0; k < MAXK; ++k)
    {
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= m; ++j)
            {
                if (i == 0 || j == 0 || k == 0)
                {
                    DP[i][j][k] = INF;
                }
                else if (A[i] == B[j])
                {
                    DP[i][j][k] = INF;
                    int val = A[i];
                    int min_before = min(DP[i-1][j][k], DP[i][j-1][k]);
                    int min_lower = DP[i-1][j-1][k-1];

                    if (k == 1)
                    {
                        DP[i][j][k] = val;
                    }
                    if (min_lower <= val + range)
                    {
                        DP[i][j][k] = max(min_lower, val);
                    }
                    else
                        DP[i][j][k] = min(min_before, DP[i][j][k]);
                }
                else
                {
                    DP[i][j][k] = min(DP[i-1][j][k], DP[i][j-1][k]);
                }
            }
        }
        if (k > 0 && DP[n][m][k] == INF)
            return k - 1;
    }
    return 20;
}

inline int SimpleLCS()
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i == 0 || j == 0)
                DP[i][j][0] = 0;
            else if (A[i] == B[j])
                DP[i][j][0] = DP[i - 1][j - 1][0] + 1;
            else
                DP[i][j][0] = max(DP[i - 1][j][0], DP[i][j - 1][0]);

            if (DP[i][j][0] > 19)
                return 20;
        }
    }
    return DP[n][m][0];
}

inline void scan(int &x)
{
    x = 0;
    for(register int c = getchar_unlocked(); c > 47 && c < 58; c = getchar_unlocked())
        x = (x << 1) + (x << 3) + c - 48;
}

int main()
{
    minVal = INF;
    maxVal = 0;

    scanf("%d %d %d", &n, &m, &range);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &A[i]);
        minVal = min(minVal, A[i]);
        maxVal = max(maxVal, A[i]);
    }

    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &B[i]);
        minVal = min(minVal, B[i]);
        maxVal = max(maxVal, B[i]);
    }

    int res;
    if (maxVal - minVal <= range)
       res = SimpleLCS(); // O(nm)
    else
       res = LCIS(); // O(nmk)

    printf("%d", res);


    return (0);
}
