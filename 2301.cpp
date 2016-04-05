#include <cstdio>

typedef long long ll;

const int Maxn = 50010;
ll N, mu[Maxn], prime[Maxn], s[Maxn];
bool vis[Maxn];

ll min(ll a, ll b)
{
    return a < b ? a : b;
}

void get_prime()
{
    mu[1] = 1;
    for(int i = 2; i <= Maxn; ++i)
    {
        if(!vis[i])
        { mu[i] = -1; prime[++prime[0]] = i; }
        for(int j = 1; j <= prime[0] && prime[j] * i <= Maxn; ++j)
        {
            vis[i*prime[j]] = true;
            mu[i*prime[j]] = -mu[i];
            if(i % prime[j] == 0)
            {
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
    for(int i = 1; i <= Maxn; ++i)
        s[i] = s[i-1] + mu[i];
    return;
}

void swap(ll& a, ll& b)
{ a ^= b; b ^= a; a ^= b; }

ll solve(ll n, ll m)
{
    ll ret = 0;
    if(n > m) swap(n, m);
    for(int i = 1, la = 0; i <= n; i = la + 1)
    {
        ll j1 = n / (n / i), j2 = m / (m / i);
        la = min(j1, j2);
        ret += (s[la] - s[i-1]) * (n / i) * (m / i);
    }
    return ret;
}

int main()
{
    get_prime();
    scanf("%lld", &N);
    for(int i = 1; i <= N; ++i)
    {
        ll a, b, c, d, k;
        scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &d, &k);
        printf("%lld\n", solve(b / k, d / k) - solve((a-1) / k, d / k) - solve( (c-1) / k, b / k) + solve((a-1) / k, (c-1) / k));
    }
    return 0;
}
