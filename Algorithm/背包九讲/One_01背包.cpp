/*
有N件物品和一个容量为V的背包。第i件物品的费用是w[i]，价值是v[i]，求将哪些物品装入背包可使价值总和最大
基础背包问题，放或者不放
f[i][j]=max(f[i-1][j],f[i-1][j-w[i]]+v[i])
时间复杂度为O(V*N)
空间复杂度优化到O(N) 
*/ 
//O(N)复杂度
for (int i = 1; i <= n; i++)
    for (int j = V; j >= 0; j--)
        f[j] = max(f[j], f[j - w[i]] + v[i]); 
//优化最后一个物品 
for (int i = 1; i <= n; i++)
    for (int j = V; j >= w[i]; j--)
        f[j] = max(f[j], f[j - w[i]] + v[i]);
//Luogu 2925 干草出售 https://www.luogu.org/problemnew/show/P2925
