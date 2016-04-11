#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int oo = 0x3f3f3f3f;
const int Maxn = 200010;
int n, m;
int RMX[Maxn], f[Maxn], RMN[Maxn];
int Bit[Maxn * 4];

void insert(int x, int k, int node = 1, int L = 0, int R = n + 1)
{
    if(L == R) { Bit[node] = k; return; }
    int mid = (L+R) >> 1;
    if(x <= mid) insert(x, k, node << 1, L, mid);
    else insert(x, k, node << 1 | 1, mid+1, R);
    Bit[node] = max(Bit[node << 1], Bit[node << 1 | 1]);
    return;
}

int query(int l, int r, int node = 1, int L = 0, int R = n + 1)
{
    if(l <= L && R <= r) return Bit[node];
    int mid = (L+R) >> 1, ret = -oo;
    if(l <= mid) ret = max(ret, query(l, r, node << 1, L, mid));
    if(r > mid) ret = max(ret, query(l, r, node << 1 | 1, mid + 1, R));
    return ret;
}

int main()
{
    freopen("3126.in", "r", stdin);
    freopen("3126.out", "w", stdout);

    scanf("%d %d", &n, &m);
    memset(Bit, -0x3f, sizeof(Bit));
    fill(RMN, RMN+1+n, n+2);

    for(int i = 1; i <= m; ++i)
    {
        int le, ri;
        scanf("%d %d", &le, &ri);
        RMX[le] = max(RMX[le], ri + 1);
        RMN[le] = min(RMN[le], ri + 1);
    }

    RMN[n + 1] = n + 2;
    for(int i = 1; i <= n; ++i)
        RMX[i] = max(RMX[i-1], RMX[i]);
    for(int i = n-1; i >= 0; --i)
        RMN[i] = min(RMN[i+1], RMN[i]);

    // for(int i = 1; i <= n; ++i) printf("%d ", RMX[i]);
    // puts("");
    // for(int i = 1; i <= n; ++i) printf("%d ", RMN[i]);
    // puts("");

    f[n + 1] = 0;
    insert(n+1, 0);
    for(int i = n; i >= 0; --i)
    {
        int r_least = max(i + 1, RMX[i]);
        int r_most = RMN[i + 1];
        // printf("%d %d\n", r_least, r_most);
        if(r_least >= r_most) f[i] = -1;
        else f[i] = query(r_least, r_most - 1);
        if(i && f[i] != -1) ++f[i];
        insert(i, f[i]);
        // printf("dp[%d] = %d\n", i, f[i]);
    }

    printf("%d\n", f[0]);

    return 0;
}
