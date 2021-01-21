#include <iostream>

using namespace std;
#define MAXN 40007
int lead[MAXN];
int second_ld[MAXN];
int whichTeam[MAXN];

int n,m,player;
int main()
{
    ios_base::sync_with_stdio(0);

    for (int i=1; i<MAXN; ++i)
        lead[i] = 1;


    cin >> n >> m;

    while (m--)
    {
        for (int i=1; i<MAXN; ++i)
        second_ld[i] = -1;

        int t = n/2;
        while (t--)
        {
            cin >> player;
            whichTeam[player] = 0;
        }
        t = n/2;
        while (t--)
        {
            cin >> player;
            whichTeam[player] = 1;
        }

        for (int p = 1; p <= n; ++p)
        {
            int leader = lead[p];
            if (whichTeam[leader] != whichTeam[p])
            {
                if (second_ld[leader] != -1)
                {
                    lead[p] = second_ld[leader];
                }
                else
                {
                    lead[p] = p;
                    second_ld[leader] = p;
                }
            }
        }
    }

    for (int p = 1; p <= n; ++p)
    {
       if (lead[p] != p)
       {
           cout << "NIE";
           return 0;
       }
    }
    cout << "TAK";

    return 0;
}