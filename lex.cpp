#include <iostream>
using namespace std;
using LL = long long;
const LL q = 29;
const LL MOD = 1e9 + 696969;
const int MAXN = 3 * 1e5 + 69;
LL W[MAXN];
LL pow[MAXN];
LL hashd[MAXN];
int n,t;
char c;

inline LL getHash(int a, int b)
{
    return ((hashd[b] - hashd[a-1] * pow[b-a+1]) % MOD + MOD) % MOD;
}

int binsearch(int a, int b, int low, int high)
{
    while (low + 1 < high)
    {
        int mid = (low+high)/2;
        if (getHash(a, a + mid) == getHash(b, b + mid))
            low = mid;
        else
            high = mid;
    }
    if (W[a + low] != W[b + low])
        return low;
    else if (W[a + low + 1] != W[b + low + 1])
        return low + 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> t;
    pow[0] = 1;
    for (int i = 1; i <= n; ++i)
        pow[i] = (pow[i-1] * q) % MOD;
    for (int i = 1; i <= n; ++i)
    {
        cin >> c;
        W[i] = c - 'a' + 1;
    }

    hashd[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        hashd[i] = (hashd[i - 1] * q + W[i]) % MOD;
    }

    int a1, a2, b1, b2;
    while (t--)
    {
        cin >> a1 >> a2 >> b1 >> b2;
        int len = min(a2 - a1, b2 - b1);

        if (a1 - a2 == b1 - b2 && getHash(a1, a2) == getHash(b1, b2))
        {
            cout << "=\n";
            continue;
        }

        if (getHash(a1, a1 + len) == getHash(b1, b1 + len))
        {
            if (a2 - a1 < b2 - b1)
                cout << "<\n";
            else
                cout << ">\n";
            continue;
        }

        if (W[a1] != W[b1])
        {
            if (W[a1] > W[b1])
                cout <<">\n";
            else
                cout << "<\n";
            continue;
        }

        int r = binsearch(a1, b1, 0, len);

        if (W[a1 + r] != W[b1 + r])
        {
            if (W[a1 + r] > W[b1 + r])
                cout <<">\n";
            else
                cout << "<\n";
        }
    }

    return 0;
}

/*
6 3
aaaaaa
-----
13 3
abaababaabaab
8 13 7 7
6 11 4 6
3 5 11 13
*/
