#include <cstdio>

const int Maxn = 100010;
const int oo = 0x3f3f3f3f;
int n, rt, cnt = 0;
int val[Maxn], ch[Maxn][2], fa[Maxn], num[Maxn], size[Maxn];

int read()
{
    int x = 0, k = 1; char c = getchar();
    while(c < '0' || c > '9') k = (c == '-' ? -1 : 1), c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * k;
}

int newnode(int x, int f)
{
    val[++cnt] = x;
    num[cnt] = size[cnt] = 1;
    fa[cnt] = f;
    return cnt;
}

void init()
{
    rt = newnode(-oo, 0);
    newnode(oo, 1);
    ch[1][1] = 2;
    size[1] = 2;
    return;
}

void dfs(int now)
{
    if(now == 0) return;
    dfs(ch[now][0]);
    printf("%d ", val[now]);
    dfs(ch[now][1]);
    return;
}

void update(int x)
{
    size[x] = size[ch[x][1]] + size[ch[x][0]] + num[x];
    return ;
}

void insert(int x)
{
    int now = rt, last = 0;
    while(now)
    {
        ++size[now];
        if(x < val[now]) last = now, now = ch[now][0];
        else if(x > val[now]) last = now, now = ch[now][1];
        else if(x == val[now]) break;
    }
    if(now) ++num[now];
    else if(x < val[last]) ch[last][0] = newnode(x, last);
    else ch[last][1] = newnode(x, last);
    return ;
}

int find(int x)
{
    int now = rt;
    while(now)
    {
        if(x < val[now]) now = ch[now][0];
        else if(x > val[now]) now = ch[now][1];
        else if(x == val[now]) break;
    }
    return now;
}


void rotate(int x)
{
    int y = fa[x], g = fa[y], c = (ch[y][1] == x);
    ch[y][c] = ch[x][!c];
    if(ch[y][c]) fa[ch[y][c]] = y;
    fa[y] = x; ch[x][!c] = y;
    fa[x] = g;
    if(g) ch[g][ch[g][1] == y] = x;
    update(y); update(x); update(g);
    return;
}

// void rotate(int x)
// {
//     int y = fa[x], g = fa[y], c = (x == ch[y][1]);
//     ch[y][c] = ch[x][!c]; ch[x][!c] = y; fa[y] = x;
//     if(ch[y][c]) fa[ch[y][c]] = y;
//     fa[x] = g;
//     if(g) ch[g][ch[g][1] == y] = x;
//     update(y); update(x);
//     return ;
// }

void splay(int x, int p)
{
    for(int y; (y = fa[x]) != p; rotate(x))
        if(fa[y] != p)
        {
            rotate( (x == ch[y][1]) == (y == ch[fa[y]][1]) ? y : x);
            // printf("%d ", y);
        }
    if(p == 0) rt = x;
    return;
}

int find_rank(int x)
{
    int now = rt;
    while(now)
    {
        if(size[ch[now][0]] < x && x <= size[ch[now][0]] + num[now]) break;
        else if(x <= size[ch[now][0]]) now = ch[now][0];
        else {x = x - size[ch[now][0]] - num[now]; now = ch[now][1];}
    }
    return val[now];
}

void del(int x)
{
    splay(x, 0);
    int now = ch[rt][0], last = rt, pre, suf;
    while(now)
    {
        last = now;
        now = ch[now][1];
    }
    pre = last; now = ch[rt][1]; last = rt;
    while(now)
    {
        last = now;
        now = ch[now][0];
    }
    suf = last;
    splay(pre, 0);
    // printf("%d OKOKOKOKOKOKOK\n", suf);
    splay(suf, rt);
    if(num[x]) --num[x];

    if(!num[x])
    {
        ch[fa[x]][0] = 0;
        // fa[x] = 0;
    }
    else update(x);
    update(suf); update(pre);
    return;
}

int find_pre(int x)
{
    insert(x);
    int p = find(x);
    splay(p, 0);
    int now = ch[rt][0], last = rt;
    while(now)
    {
        last = now;
        now = ch[now][1];
    }
    del(p);
    return val[last];
}

int find_suf(int x)
{
    insert(x);
    int p = find(x);
    splay(p, 0);
    int now = ch[rt][1], last = rt;
    while(now)
    {
        last = now;
        now = ch[now][0];
    }
    del(p);
    return val[last];
}

int main()
{
    freopen("3224.in", "r", stdin);
    freopen("3224.out", "w", stdout);
    n = read();
    init();
    // dfs(rt);
    for(int i = 1; i <= n; ++i)
    {
        // printf("oo %d oo\n", num[find(964673)]);
        int opt = read(), x = read();
        if(opt == 1) insert(x), splay(find(x), 0);
        else if(opt == 2) del(find(x));
        else if(opt == 3)
        {
            splay(find(x), 0);
            printf("%d\n", size[ch[rt][0]]);
        }
        else if(opt == 4) printf("%d\n", find_rank(x + 1));
        else if(opt == 5) printf("%d\n", find_pre(x));
        else if(opt == 6) printf("%d\n", find_suf(x));
        // dfs(rt);
        // printf("\n");
    }
    // for(int i = 1; i <= n; ++i)
    // {
    //     // printf("oo %d oo\n", num[find(964673)]);
    //     int opt = read(), x = read();
    //     if(opt == 1) insert(x), splay(find(x), 0);
    //     else if(opt == 2) del(find(x));
    //     else if(opt == 3)
    //     {
    //         splay(find(x), 0);
    //         printf("%d:%d\n", i, size[ch[rt][0]]);
    //     }
    //     else if(opt == 4) printf("%d %d\n", i, find_rank(x + 1));
    //     else if(opt == 5) printf("%d %d\n", i, find_pre(x));
    //     else if(opt == 6) printf("%d %d\n", i, find_suf(x));
    //     // dfs(rt);
    //     // printf("\n");
    // }
    // dfs(rt);
    return 0;
}
