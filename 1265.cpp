#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;

struct big_num
{
    ll num[2010];
    big_num()
    { memset(num, 0, sizeof(num)); }
    big_num(char* s)
    {
        memset(num, 0, sizeof(num));
        int len = strlen(s);
        num[0] = len / 7;
        if(len % 7) ++num[0];
        for(int i = 0, j = num[0]; i < len; ++i)
        {
            num[j] = num[j]*10 + s[i] - '0';
            if(num[j] >= 1000000) --j;
        }
        return;
    }
    void read()
    {
        char s[6010];
        memset(s, 0, sizeof(s));
        scanf("%s", s);
        int len = strlen(s);
        num[0] = len / 7;
        if(len % 7) ++num[0];
        for(int i = 0, j = num[0]; i < len; ++i)
        {
            num[j] = num[j]*10 + s[i] - '0';
            if(num[j] >= 1000000) --j;
        }
        return;
    }
    void out()
    {
        for(int i = num[0]; i > 1; --i) printf("%07d", num[i]);
        printf("%d", num[1]);
        printf("\n");
        return;
    }
    big_num operator + (big_num b)
    {
        int len = max(num[0], b.num[0]);
        for(int i = 1; i <= len; ++i)
        {
            b.num[i] += num[i];
            b.num[i+1] += b.num[i] / 10000000;
            b.num[i] %= 10000000;
        }
        b.num[0] = len;
        if(b.num[b.num[0]+1]) ++b.num[0];
        return b;
    }
    big_num operator * (big_num b)
    {
        big_num ret;
        for(int i = 1; i <= num[0]; ++i)
            for(int j = 1; j <= b.num[0]; ++j)
                ret.num[i+j-1] += num[i] * b.num[j];
        ret.num[0] = num[0] + b.num[0] - 1;
        for(int i = 1; i <= ret.num[0]; ++i)
            ret.num[i+1] += ret.num[i] / 10000000;
        while(ret.num[ret.num[0]+1]) ++ret.num[0];
        return ret;
    }
    void operator = (char* s)
    {
        int len = strlen(s);
        num[0] = len / 7;
        if(len % 7) ++num[0];
        for(int i = 0, j = num[0]; i < len; ++i)
        {
            num[j] = num[j]*10 + s[i] - '0';
            if(num[j] >= 1000000) --j;
        }
        return;
    }
    big_num operator - (big_num b)
    {
        big_num c;
        int len = max(num[0], b.num[0]);
        c.num[0] = b.num[0];
        for(int i = 1; i <= b.num[0]; ++i) c.num[i] = -b.num[i];
        return *this + c;
    }
    bool operator < (big_num b)
    {
        if(num[0] != b.num[0]) return num[0] < b.num[0];
        for(int i = num[0]; i; --i)
            if(num[i] != b.num[i]) return num[i] < b.num[i];
    }
    bool operator <= (big_num b)
    {
        if(num[0] != b.num[0]) return num[0] < b.num[0];
        for(int i = num[0]; i; --i)
            if(num[i] != b.num[i]) return num[i] < b.num[i];
        if(num[1] == b.num[1]) return true;
    }
    big_num operator / (big_num b)
    {
        big_num ans; ans = "0";
        while(b <= *this)
        {
            big_num c, tmp, te;
            c = b; tmp = "1"; te = "0";
            while(c * big_num("10") < b)
            {
                c = c * big_num("10");
                tmp = tmp * big_num("10");
            }
            while(big_num("0") <= *this - c)
            {
                *this = *this - c;
                te = te + big_num("1");
            }
            ans = ans + tmp * te;
        }
        if(big_num("0") < *this) ++ans.num[1];
        return ans;
    }
};

big_num a, b, c, k;
big_num dp[4];
int m;
bool flg = false;

int main()
{
    // freopen("1265.in", "r", stdin);
    // freopen("1265.out", "w", stdout);
    a.read(); b.read(); c.read();
    scanf("%d", &m);
    // solve dp
    dp[0].num[0] = dp[0].num[1] = 1;
    dp[1] = dp[0]+a*dp[0]; dp[2] = dp[1]+ (dp[1]-dp[0])*a + dp[0]*b;
    dp[3] = dp[2] + (dp[2]-dp[1])*a + (dp[1]-dp[0])*b + dp[0]*c;
    for(int i = 4; i <= m; ++i)
    {
        dp[i%4] = dp[(i-3)%4]*c + (dp[(i-2)%4]-dp[(i-3)%4])*b + (dp[(i-1)%4]-dp[(i-2)%4])*a + dp[(i-1)%4];
    }
    dp[m%4].out();
    // solve max
    big_num div;
    div.read();
    big_num left = div / dp[m%4];
    left.out();
    return 0;
}
