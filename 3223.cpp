#include <cstdio>
#include <algorithm>
using namespace std;

const int Maxn = int(1e5) + 10;

int n, m, sz = 0, rt;
int fa[Maxn], ch[Maxn][2], id[Maxn], size[Maxn], rev[Maxn];

int read()
{
    int x = 0, k = 1; char c = getchar();
    while(c < '0' || c > '9') k = (c == '-' ? -1 : 1), c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * k;
}

void pushup(int now)
{
    size[now] = size[ch[now][0]] + size[ch[now][1]] + 1;
    return;
}

void build(int l, int r, int f)
{
    if(l > r) return;
    if(l == r)
    {
        fa[l] = f;
        if(l < f) ch[f][0] = l;
        else ch[f][1] = l;
        size[l] = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid - 1, mid);
    build(mid + 1, r, mid);
    pushup(mid);
    fa[mid] = f;
    if(mid < f) ch[f][0] = mid;
    else ch[f][1] = mid;
}

void dfs(int now)
{
    if(now == 0) return;
    dfs(ch[now][0]);
    printf("%d ", now);
    dfs(ch[now][1]);
    return;
}

void rotate(int x)
{
    int y = fa[x], g = fa[y], c = (ch[y][1] == x);
    ch[y][c] = ch[x][!c];
    if(ch[y][c]) fa[ch[y][c]] = y;
    fa[y] = x; ch[x][!c] = y;
    fa[x] = g;
    if(g) ch[g][ch[g][1] == y] = x;
    pushup(y); pushup(x);
    return;
}

void splay(int x, int k)
{
    for(int y; (y = fa[x]) != k; rotate(x))
        if(fa[y] != k) rotate( (ch[fa[y]][1] == y) == (ch[y][1] == x) ? y : x);
    if(k == 0) rt = x;
    return;
}

int find(int now, int x)
{
    if(rev[now])
    {
        swap(ch[now][0], ch[now][1]);
        rev[ch[now][0]] ^= 1;
        rev[ch[now][1]] ^= 1;
        rev[now] = 0;
    }
    if(size[ch[now][0]] + 1 == x) return now;
    if(x <= size[ch[now][0]]) return find(ch[now][0], x);
    else return find(ch[now][1], x - size[ch[now][0]] - 1);
}

int main()
{
    n = read(); m = read();
    for(int i = 1; i <= n + 2; ++i) id[i] = i;

    build(1, n + 2, 0); rt = (n + 3) >> 1;
    for(int i = 1; i <= m; ++i)
    {
        int l = read(), r = read();
        splay(find(rt, l), 0);
        splay(find(rt, r + 2), rt);
        rev[ch[ch[rt][1]][0]] ^= 1;
    }
    for(int i = 2; i <= n + 1; ++i) printf("%d ", find(rt, i) - 1);
    return 0;
    return 0;
}
