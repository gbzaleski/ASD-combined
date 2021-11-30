#include <iostream>
#include <vector>
using namespace std;

#define MP make_pair

int timekr = 1;
class Tree
{
    public:
    Tree(int n)
    {
        int x = 1;
        while (x < n)
            x <<= 1;

        this->n = x;
        this->d.resize(2*x);
        this->sum.resize(2*x);
    }

    void maluj(int l, int r, int val)
    {
        _maluj(l, r, val, 1, 1, this->n);
    }

    int suma_biala()
    {
        return this->sum[1];
    }

    private:
    int n;
    // time - val
    vector <pair<int,int>> d;
    vector <int> sum;

    void _maluj(int l, int r, int kolor, int v, int vl, int vr)
    {
        if (r < vl || l > vr)
            return;
        else if (l <= vl && vr <= r)
        {
            this->d[v] = MP(kolor, timekr);
            this->sum[v] = (vr - vl + 1) * kolor;
        }
        else
        {
            int m = (vl + vr)/2;

            if (this->d[v].second > 0)
            {
                pair <int,int> cur_down = this->d[v];

                if (cur_down.second > this->d[2*v].second)
                {
                    this->d[2*v] = cur_down;
                    this->sum[2*v] = cur_down.first * (vr - vl + 1)/2;
                }

                if (cur_down.second > this->d[2*v + 1].second)
                {
                    this->d[2*v + 1] = cur_down;
                    this->sum[2*v + 1] = cur_down.first * (vr - vl + 1)/2;
                }

                this->d[v] = MP(0,0);
            }

            _maluj(l, r, kolor, 2*v, vl, m);
            _maluj(l, r, kolor, 2*v + 1, m + 1, vr);

            this->sum[v] = this->sum[2*v] + this->sum[2*v + 1];
        }
    }
};


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int a,b,n,t;
    char c;

    cin >> n >> t;
    Tree myTree(n);

    while (t--)
    {
        timekr++;
        cin >> a >> b >> c;

       myTree.maluj(a, b, c == 'B');
       cout <<  myTree.suma_biala() << "\n";

    }

    return 0;
}

/*
12
4
1 5 C
2 10 B
4 6 B
4 7 C
--
0
9
7
4
*/
