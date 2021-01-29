#include <bits/stdc++.h>

using namespace std;
const int s = 11;
long long n;
inline void scan(long long &x)
{
    x = 0;
    register long long c = getchar_unlocked();
    for(;c > 47 && c < 58;
         c = getchar_unlocked())
        x = (x << 1) + (x << 3) + c - 48;
}

int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);

    
    vector <long long> _cnt(s, 0);
    vector <long long> _p(s, 0);
    scan(n);
    
    vector <vector<long long>> cnt(n, _cnt);
    vector <vector<long long>> p(n, _p);
    vector <long long> tab(n);
    
    for (int i = 0; i < n; ++i)
       scan(tab[i]);
        
    p[n-1][tab[n-1]] ++;
    for (int i = n - 2; i >= 0; --i)
    {
        p[i] = p[i+1];
        p[i][tab[i]] ++;
    }
    
    long long ans = 0;
    cnt[0][tab[0]] = 1;
    for (int i = 1; i < n; ++i)
    {
       cnt[i] = cnt[i-1];
       int v = tab[i];
       
       for (int a = 0; a < s; ++a)
       {
            int sum = v + a;
            if (sum < s)
            {
                ans += cnt[i][a] * p[i][sum];
            }
          
       }
       
       
       cnt[i][v] ++;
    }
    
    cout << ans;
    
    return 0;
}
