#include <cstdio>
#include <cmath>
#include <set>
using namespace std;

const int Maxn = int(1e5)+10;
int n, a[Maxn], size, num, q;
int l[201], r[201], g[Maxn], bel[Maxn], Xor[Maxn];
char com[Maxn];
set <int> s[201];

int gcd(int a, int b)
{
    while(b)
    { int t = a; a = b; b = t%b; }
    return a;
}

void build(int x)
{
    s[x].clear();
    l[x] = (x-1)*num+1;
    r[x] = x*num;
    g[l[x]] = a[l[x]]; Xor[l[x]] = a[l[x]];
    s[x].insert(Xor[l[x]]);
    for(int i = l[x]+1; i <= r[x]; ++i)
    { g[i] = gcd(g[l[x]], a[i]); bel[i] = x;
    Xor[i] = Xor[i-1] ^ a[i]; s[x].insert(Xor[i]); }
    return;
}

int main()
{
    freopen("4028.in", "r", stdin);
    freopen("4028.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", a+i);
    size = (int)sqrt(n+0.5);
    num = n / size;
    if(n % size) ++num;
    for(int i = 1; i <= num; ++i) build(i);
    scanf("%d", &q);
    for(int i = 1; i <= q; ++i)
    {
        int ans = 0;
        scanf("%s", com);
        if(*com == 'M')
        {
            int x, b;
            scanf("%d %d", &x, &b);
            a[x] = b;  build(bel[x]);
        }
        else if(*com == 'Q')
        {
            int lastgcd = 0, lastxor = 0, x;
            bool flg = false;
            scanf("%d", &x);
            for(int j = 1; j <= num; ++j)
            {
                int T = gcd(lastgcd, g[r[j]]);
                if(flg)
                if(x % T == 0 && lastgcd == T)
                {
                    if(s[j].count((x/T) xor lastxor))
                    {
                        flg = true;
                        for(int k = l[j]; k <= r[j]; ++k)
                        {
                            if(Xor[k] == (x/T) xor lastxor)
                            {
                                ans = k;
                                break;
                            }
                        }
                    }
                }
                else if(lastgcd != T)
                {
                    for(int k = l[j]; k <= r[j]; ++k)
                    if(gcd(lastgcd, g[k]) * (lastxor xor Xor[k]) == x)
                    {
                        ans = k;
                        flg = true;
                        break;
                    }
                }
                if(flg) printf("d\n", ans);
                else printf("no\n");
                lastgcd = T; lastxor ^= Xor[r[j]];
            }
        }
    }
    return 0;
}
