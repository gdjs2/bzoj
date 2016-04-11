#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
ll t;

struct big_num
{
    int num[100];
    big_num()
    { memset(num, 0, sizeof(num)); }
    big_num(char* s)
    {
        memset(num, 0, sizeof(num));
        num[0] = strlen(s);
        for(int i = 0; i < num[0]; ++i) num[num[0]-i] = s[i] - '0';
        return;
    }
    void read()
    {
        char s[101];
        memset(s, 0, sizeof(s));
        scanf("%s", s);
        num[0] = strlen(s);
        for(int i = 0; i < num[0]; ++i) num[num[0]-i] = s[i] - '0';
        return;
    }
    void out()
    {
        printf("%lld", num[num[0]]);
        for(int i = num[0]-1; i >= 1; --i) printf("%lld", num[i]);
        printf("\n");
        return;
    }
    big_num operator + (big_num b)
    {
        int len = max(num[0], b.num[0]);
        for(int i = 1; i <= len; ++i)
        {
            b.num[i] += num[i];
            b.num[i+1] += b.num[i] / 10;
            b.num[i] %= 10;
        }
        b.num[0] = len;
        if(b.num[b.num[0]+1]) ++b.num[0];
        return b;
    }
    big_num operator / (int x)
    {
        big_num ret;
        ll left = 0;
        for(int i = num[0]; i; --i)
        {
            left = left * 10 + num[i];
            ret.num[i] = left / x;
            left %= x;
        }
        ret.num[0] = num[0];
        while(!ret.num[ret.num[0]]) --ret.num[0];
        return ret;
    }
}p, q, n;

void dfs(big_num x)
{
    /*if(x.num[0] == 1 && x.num[1] == 1) return big_num("1");
    else if(x.num[0] == 1 && x.num[1] == 0) return big_num("0");
    else if(x.num[1]&1) return dfs(x/2) + dfs(x/2+big_num("1"));
    else return dfs(x/2);*/
    if(x.num[0] == 1 && x.num[1] == 1)
    { q = x; memset(p.num, 0, sizeof(p.num)); return ;}
    dfs((x+big_num("1"))/2);
    if(x.num[1]&1) q = q+p;
    else p = q+p;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("2656.in", "r", stdin);
    // freopen("2656.out", "w", stdout);
#endif
    scanf("%lld", &t);
    while(t--)
    {
        memset(n.num, 0, sizeof(n.num));
        n.read();
        dfs(n);
        q.out();
    }
    return 0;
}
