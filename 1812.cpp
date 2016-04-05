#include <cstdio>
#include <memory.h>

const int oo = 0x3f3f3f3f;
int n, K, dp[101][101][51], dist[101][101], w[101];
int fir[101], nxt[101], to[101], cnt = 0;
int read()
{
    int x = 0, k = 1; char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar(), ch == '-' ? k = -1 : k = 1;
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x * k;
}

void add(int a, int b)
{
    nxt[++cnt] = fir[a]; fir[a] = cnt; to[cnt] = b;
    return;
}

int min(int a, int b) { return a < b ? a : b; }

namespace Ntree
{
    int fa[101], d[101];
    int q[101], l = 1, r = 0;
    void input()
    {
        n = read(); K = read();
        for(int i = 1; i <= n; ++i)
        {
            scanf("%d %d %d", &w[i], &fa[i], &d[i]);
            add(fa[i], i);
        }
        return;
    }
    void bfs()
    {
        fa[0] = -1;
        q[++r] = 0;
        while(l <= r)
        {
            int now = q[l++], tmp = now;
            while(tmp != 0)
            { dist[now][fa[tmp]] = dist[now][tmp] + d[tmp]; tmp = fa[tmp]; }
            for(int i = fir[now]; i; i = nxt[i])
                if(to[i] != fa[now]) q[++r] = to[i];
        }
        return;
    }
}

namespace FBTree
{
    int q[101], l = 1, r = 0, suk = 0;
    int ch[101][2], fa[101];
    void insert(int now, int dx, int node)
    {
        if(ch[now][dx])
        { insert(ch[now][dx], dx, node); return; }
        fa[node] = now;
        ch[now][dx] = node;
        return;
    }
    void build(int now = 0)
    {
        int i = fir[now];
        if(i)
        {
            insert(now, 0, to[i]);
            for(i = nxt[i]; i; i = nxt[i])
                insert(ch[now][0], 1, to[i]);
        }
        for(i = fir[now]; i; i = nxt[i]) build(to[i]);
    }
    void solve(int now = 0)
    {
        if(!ch[now][0] && !ch[now][1])
        {
            int tmp = now;
            while(tmp >= 0)
            {
                dp[now][tmp][1] = 0;
                if(tmp != now) dp[now][tmp][0] = dist[now][tmp] * w[now];
                tmp = Ntree::fa[tmp];
            }
            return;
        }
        if(ch[now][0]) solve(ch[now][0]);
        if(ch[now][1]) solve(ch[now][1]);
/*        if(now == 0)
        {
            int j = 0;
            for(int k = 0; k <= K; ++k)
            {
                if(ch[now][0] && !ch[now][1])
                {
                    dp[now][j][k] = min(dp[ch[now][0]][j][k] + w[now]*dist[now][j], dp[ch[now][0]][now][k]);
                }
                else if(!ch[now][0] && ch[now][1])
                {
                    dp[now][j][k] = min(dp[ch[now][1]][j][k] + w[now]*dist[now][j],0 + dp[ch[now][1]][j][k]);
                }
                else for(int k1 = 0; k1 <= k; ++k1)
                {
                    if(ch[now][0] && ch[now][1])
                    dp[now][j][k] = min(dp[ch[now][0]][j][k1] + dp[ch[now][1]][j][k-k1] + w[now]*dist[now][j],dp[ch[now][0]][now][k1] + dp[ch[now][1]][j][k-k1]);
                }
            }
        }
*/
        for(int j = Ntree::fa[now]; j >= 0; j = Ntree::fa[j])
        {

            for(int k = 0; k <= K; ++k)
            {
                if(ch[now][0] && !ch[now][1])
                {
                    if(k >= 1) dp[now][j][k] = min(dp[ch[now][0]][j][k] + w[now]*dist[now][j], dp[ch[now][0]][now][k-1]);
                    else dp[now][j][k] = dp[ch[now][0]][j][k] + w[now]*dist[now][j];
                }
                else if(!ch[now][0] && ch[now][1])
                {
                    if(k >= 1) dp[now][j][k] = min(dp[ch[now][1]][j][k] + w[now]*dist[now][j],0 + dp[ch[now][1]][j][k-1]);
                    else dp[now][j][k] = dp[ch[now][1]][j][k] + w[now]*dist[now][j];
                }
                else for(int k1 = 0; k1 <= k; ++k1)
                {
                    if(ch[now][0] && ch[now][1])
                    dp[now][j][k] = min(dp[now][j][k], min(dp[ch[now][0]][j][k1] + dp[ch[now][1]][j][k-k1] + w[now]*dist[now][j],dp[ch[now][0]][now][k1] + dp[ch[now][1]][j][k-k1-1]));

                }
            }
        }
    }
}


int main()
{
    freopen("1812.in", "r", stdin);
    Ntree::input();
    // printf("input                          [OK]\n");
    Ntree::bfs();
    // printf("BFS                          [OK]\n");
    FBTree::fa[0] = -1;
    FBTree::build();
    // for(int i = 0; i <= n; ++i) printf("now = %d lch = %d rch = %d\n", i, FBTree::ch[i][0], FBTree::ch[i][1]);
    memset(dp, 0x3f, sizeof(dp));
    FBTree::solve();
    printf("%d\n", dp[FBTree::ch[0][0]][0][K]);
    return 0;
}
