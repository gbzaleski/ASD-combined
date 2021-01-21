#include <bits/stdc++.h>
long long n, m, i, x, a[40004];
int main() {
    scanf("%lld%lld", &n, &m);
    for (scanf("%lld", &x), i = n * m - 1; i >= 0; m -= !((i--) % n), scanf("%lld", &x), std::sort(a + 1, a + n * (i == 0) + 1))
            a[x] |= (1LL << m * (i % n >= n / 2));
    printf(std::adjacent_find(a + 1, a + n + 1) == (a + n + 1) ? "TAK\n" : "NIE\n");
}