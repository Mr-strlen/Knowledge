/*
��N����Ʒ��һ������ΪV�ı�������i����Ʒ�ķ�����w[i]����ֵ��v[i]������Щ��Ʒװ�뱳����ʹ��ֵ�ܺ����
�����������⣬�Ż��߲���
f[i][j]=max(f[i-1][j],f[i-1][j-w[i]]+v[i])
ʱ�临�Ӷ�ΪO(V*N)
�ռ临�Ӷ��Ż���O(N) 
*/ 
//O(N)���Ӷ�
for (int i = 1; i <= n; i++)
    for (int j = V; j >= 0; j--)
        f[j] = max(f[j], f[j - w[i]] + v[i]); 
//�Ż����һ����Ʒ 
for (int i = 1; i <= n; i++)
    for (int j = V; j >= w[i]; j--)
        f[j] = max(f[j], f[j - w[i]] + v[i]);
//Luogu 2925 �ɲݳ��� https://www.luogu.org/problemnew/show/P2925
