class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        minn = maxn = prices[0]
        maxP = 0
        for i in range(1,len(prices)):
            if (prices[i] < minn ):
                maxn = minn = prices[i]

            elif (prices[i] > maxn or maxP == 0):
                maxn = prices[i]
                if (maxP < maxn - minn):
                    maxP = maxn - minn

        return maxP
