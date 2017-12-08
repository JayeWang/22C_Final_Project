class Solution(object):
    def maxProfit(self, prices, k):
        Profit = [[0, 0] for x in range(10000000)]
        firstBuy, firstSell = -1e9, 0
        for i in range(len(prices)):
            if firstBuy < -prices[i]: firstBuy = -prices[i]
            if firstSell < prices[i] + firstBuy: firstSell = prices[i] + firstBuy
        Profit[1][0] = firstBuy
        Profit[1][1] = firstSell
        print Profit
        for i in range(2, 10):
            for j in range(len(prices)):
                if Profit[i][0] < Profit[i-1][1] - prices[j]: Profit[i][0] = Profit[i-1][1] - prices[j]
                if Profit[i][1] < prices[j] + Profit[i-1][0]: Profit[i][1] = prices[j] + Profit[i-1][0]
        print Profit[k][1]
s = Solution()
print s.maxProfit([6, 3, 4, 7, 1], 5)
