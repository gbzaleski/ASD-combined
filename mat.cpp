#include <iostream>
using namespace std;
string inp;
int min_dist = 1e9;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> inp;
    int posA = -1, posB = -1;
    char A,B;

    for (int i=0; i < inp.size(); ++i)
    {
        if (inp[i] == '*')
            continue;

        if (inp[i] != A)
        {
            if (posA != -1)
                min_dist = min(min_dist, i - posA);
            B = A;
            A = inp[i];
            posB = posA;
            posA = i;
        }
        else // inp[i] == A
        {
            posA = i;
        }
    }

    if (posB == -1)
        cout << 1;
    else
        cout << inp.size() - min_dist + 1;
    return 0;
}