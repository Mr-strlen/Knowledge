/*
有N种物品和一个容量为V的背包。
第i种物品最多有p[i]件可用，每件费用是w[i]，价值是v[i]。
求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。

转换成01背包
状态转移方程 f[i][j]=max(f[i-1][j-k*w[i]]+k*v[i]) | 0<=k<=p[i] 
*/
//优化 二进制拆分
for (int i = 1; i <= n; i++) {
    int num = min(p[i], V / w[i]);
    for (int k = 1; num > 0; k <<= 1) {
        if (k > num) k = num;
        num -= k;
        for (int j = V; j >= w[i] * k; j--)
            f[j] = max(f[j], f[j - w[i] * k] + v[i] * k);
    }
} 
//O(VN)算法 单调队列 使用mod 

