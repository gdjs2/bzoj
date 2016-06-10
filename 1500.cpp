#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int Maxn = 5 * int(1e5) + 10;
const int oo = 0x3f3f3f3f;
int n, m, rt, cnt = 0;
int v[Maxn], ch[Maxn][2], fa[Maxn], size[Maxn], rev[Maxn], sum[Maxn], cha[Maxn];
int stack[Maxn], top = 0, lmax[Maxn], vmax[Maxn], rmax[Maxn], mmax[Maxn];
char com[10];

int read()
{
    int x = 0, k = 1; char c = getchar();
    while(c < '0' || c > '9') k = (c == '-' ? -1 : 1), c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * k;
}

void build(int l, int r, int last)
{
    if(l > r) return;
    if(l == r)
    {
        sum[l] = v[l];
        fa[l] = last; size[l] = 1;
        if(l < last) ch[last][0] = l;
        else ch[last][1] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid - 1, mid);
    build(mid + 1, r, mid);
    size[mid] = size[ch[mid][0]] + size[ch[mid][1]] + 1;
    sum[mid] = sum[ch[mid][0]] + sum[ch[mid][1]] + v[mid];
    if(mid < last) ch[last][0] = mid;
    else ch[last][1] = mid;
    fa[mid] = last;
    return ;
}

void init()
{
    memset(cha, 0x3f, sizeof(cha));
    for(int i = 2; i <= n + 1; ++i) v[i] = read();
    build(1, n + 2, 0);
    rt = (n + 3) >> 1;
    cnt = n + 2;
    return;
}

void insert(int p, int x)
{
    int now = rt, last = 0;
    while(now)
    {
        size[now] += size[x]; sum[now] += sum[x];
        if(p <= size[ch[now][0]]) { last = now; now = ch[now][0]; }
        else { p -= size[ch[now][0]] + 1; last = now; now = ch[now][1]; }
    }
    fa[x] = last;
    if(p <= size[ch[last][0]]) ch[last][0] = x;
    else ch[last][1] = x;
    return;
}

void update(int x)
{
    size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + v[x];
    lmax[x] = max(lmax[ch[x][0]], sum[ch[x][0]] + v[x] + lmax[ch[x][1]]);
    rmax[x] = max(rmax[ch[x][1]], sum[ch[x][1]] + v[x] + rmax[ch[x][0]]);
    mmax[x] = max(rmax[ch[x][0]] + v[x] + lmax[ch[x][1]], max(lmax[x], rmax[x]));
    mmax[x] = max(mmax[x], mmax[ch[x][0]], mmax[ch[x][1]]);
    vmax[x] = max(v[x], max(vmax[ch[x][0]], vmax[ch[x][1]]));
    return;
}

void dfs(int now)
{
    if(!now) return;
    if(rev[now])
    {
        swap(ch[now][0], ch[now][1]);
        rev[ch[now][0]] ^= 1;
        rev[ch[now][1]] ^= 1;
        rev[now] = 0;
        update(now);
    }
    if(cha[now] != oo)
    {
        v[now] = cha[now];
        cha[ch[now][0]] = cha[now];
        cha[ch[now][1]] = cha[now];
        cha[now] = oo;
        update(now);
    }
    dfs(ch[now][0]);
    printf("%d ", v[now]);
    dfs(ch[now][1]);
    return;
}

void rotate(int x)
{
    int y = fa[x], g = fa[y], c = (ch[y][1] == x);
    ch[y][c] = ch[x][!c]; ch[x][!c] = y; fa[y] = x;
    if(ch[y][c]) fa[ch[y][c]] = y;
    fa[x] = g;
    if(g) ch[g][ch[g][1] == y] = x;
    update(y); update(x);
    if(g) update(g);
    return;
}

void splay(int x, int p)
{
    for(int y; (y = fa[x]) != p; rotate(x))
        if(fa[y] != p) rotate( (ch[y][1] == x) == (ch[fa[y]][1] == y) ? y : x);
    if(!p) rt = x;
    return;
}

int find(int x)
{
    int now = rt;
    while(now)
    {
        if(rev[now])
        {
            swap(ch[now][0], ch[now][1]);
            rev[ch[now][0]] ^= 1;
            rev[ch[now][1]] ^= 1;
            rev[now] = 0;
            update(now);
        }
        if(cha[now] != oo)
        {
            v[now] = cha[now];
            cha[ch[now][0]] = cha[now];
            cha[ch[now][1]] = cha[now];
            cha[now] = oo;
            update(now);
        }
        if(x == size[ch[now][0]] + 1) break;
        else if(x <= size[ch[now][0]]) now = ch[now][0];
        else if(x > size[ch[now][0]] + 1) { x -= size[ch[now][0]] + 1; now = ch[now][1]; }
    }
    return now;
}

int main()
{
    freopen("1500.in", "r", stdin);
    n = read(); m = read();
    init();

    while(m--)
    {
        scanf("%s", com);
        if(*com == 'I')
        {
            int pos = read(), tot = read(), first, now, last = 0;
            for(int i = 1; i <= tot; ++i)
            {
                if(top) now = stack[top--];
                else now = ++cnt;
                scanf("%d", &v[now]);
                fa[now] = last;
                ch[last][1] = now;
                size[now] = n - i + 1;
                if(i == 1) first = now;
                last = now;
            }
            int k = now;
            while(k) sum[k] = sum[ch[k][1]] + v[k], k = fa[k];
            insert(pos + 1, first);
            splay(now, 0);
        }
        else if(*com == 'D')
        {
            int pos = read(), tot = read();
            splay(find(pos), 0);
            splay(find(pos + tot + 1), rt);
            ch[ch[rt][1]][0] = 0;
            update(ch[rt][1]); update(rt);
        }
        else if(*com == 'R')
        {
            int pos = read(), tot = read();
            splay(find(pos), 0);
            splay(find(pos + tot + 1), rt);
            rev[ch[ch[rt][1]][0]] ^= 1;
        }
        else if(*com == 'G')
        {
            int pos = read(), tot = read();
            splay(find(pos), 0);
            splay(find(pos + tot + 1), rt);
            printf("%d\n", sum[ch[ch[rt][1]][0]]);
        }
        else if(com[2] == 'K')
        {
            int pos = read(), tot = read(), c = read();
            splay(find(pos), 0);
            splay(find(pos + tot + 1), rt);
            cha[ch[ch[rt][1]][0]] = c;
        }
        else if(com[2] == 'X')
        {
            printf("%d\n", mmax[rt]);
        }
        dfs(rt);
        puts("");
    }

}
