//optimization for subsegment dynamics n^3 -> n^2
//works if and only if cut[i][j] <= cut[i][j+1] <= cur[i+1][j+1]
for (int len = 1; len < n; ++len)
{
	for (int i = 0; i < n-len; ++i)
	{
		int j = i + len - 1;
		for (int k = cut[i][j-1]; k < cur[i+1][j]; ++k)
		{
			int curres = f(dp[i][k], dp[k+1][j], i, j);
			if (curres < dp[i][j])
			{
				dp[i][j] = curres;
				cur[i][j] = k;
			}
		}
	}
}