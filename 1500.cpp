#include <cstdio>

const int Maxn = 5 * int(1e5) + 10;
int n, m;
int v[Maxn], ch[Maxn][2], fa[Maxn], size[Maxn];
int stack[Maxn], top = 0;

int read()
{
    int x = 0, k = 1; char c = getchar();
    while(c < '0' || c > '9') k = (c == '-' ? -1 : 1), c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * k;
}

void build(int l, int r)
{

}
void init()
{
    for(int i = 2; i <= n + 1; ++i) v[i] = read();
    build(1, n + 2);
}

int main()
{
    n = read(); m = read();
    init();

}
