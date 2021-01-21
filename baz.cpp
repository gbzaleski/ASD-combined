#include <iostream>
using namespace std;
using LL = long long;
#define MAXN 1000069
int n,t,k,tab[MAXN],
    biggestOnLeftOdd[MAXN],
    biggestOnLeftEven[MAXN],
    SmallestDiffrentOfRight[MAXN];

LL prefSum[MAXN];

inline LL getSum (int a, int b)
{
    if (a == 0)
        return prefSum[b];
    return prefSum[b] - prefSum[a-1];
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    int biggestOdd = -1, biggestEven = -1;
    for (int i=0; i < n; ++i)
    {
        cin >> tab[i];

        biggestOnLeftEven[i] = biggestEven;
        biggestOnLeftOdd[i] = biggestOdd;

        if (tab[i]%2) //odd
        {
            biggestOdd = tab[i];
        }
        else
            biggestEven = tab[i];


        if (i != 0)
            prefSum[i] = tab[i] + prefSum[i-1];
        else prefSum[i] = tab[i];
    }

    int smallestOdd = -1, smallestEven = -1;

    for (int i = n-1; i >= 0; --i)
    {
        if (tab[i]%2) //odd
        {
            SmallestDiffrentOfRight[i] = smallestEven;
            smallestOdd = tab[i];
        }
        else
        {
           SmallestDiffrentOfRight[i] = smallestOdd;
           smallestEven = tab[i];
        }
    }


    cin >> t;
    while (t--)
    {
        cin >> k;
        LL curSum = getSum(n-k, n-1);
        if (curSum%2)
            cout << curSum << "\n";
        else //wymieniamy
        {
            LL kth_out = -1;
            if (tab[n-k]%2) //odd
            {
                if (biggestOnLeftEven[n-k] != -1)
                    kth_out = curSum - tab[n-k] + biggestOnLeftEven[n-k];
            }
            else //even
            {
                if (biggestOnLeftOdd[n-k] != -1)
                    kth_out = curSum - tab[n-k] + biggestOnLeftOdd[n-k];
            }

            LL kth_in = -1;
            if (SmallestDiffrentOfRight[n-k] != -1)
            {
                if (tab[n-k]%2) //odd
                {
                    if (biggestOnLeftOdd[n-k] != -1)
                        kth_in = curSum - SmallestDiffrentOfRight[n-k] + biggestOnLeftOdd[n-k];
                }
                else //even
                {
                    if (biggestOnLeftEven[n-k] != -1)
                    {
                        kth_in = curSum - SmallestDiffrentOfRight[n-k] + biggestOnLeftEven[n-k];
                    }
                }
            }

            //cout << kth_out << " vs " << kth_in << " -> ";
            cout << max(kth_out, kth_in) << "\n";
        }
    }

    return 0;
}