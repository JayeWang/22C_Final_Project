class Solution(object):
    mid = 0
    maximum = 0
    def BinarySearch(self, start, end, nums, target):
        if start > end:
            return False
        middle = (start + end)/2
        if nums[middle] == target:
            self.mid = middle
            return True
        elif nums[middle] > target:
            return self.BinarySearch(start, middle - 1, nums, target)
        elif nums[middle] < target:
            return self.BinarySearch(middle + 1, end, nums, target)
    def getNextBigger(self, nums, target, currentIndex):
        if currentIndex == len(nums)-1:
            return currentIndex
        else:
            index = currentIndex + 1
            while nums[index] == target:
                index += 1
            return index
    def getUpperLimitIndex(self, nums, target):
        for index in range(len(nums)-1):
            if(nums[index] > target):
                return index
        return len(nums) - 1
    def twoSum(self, nums, target):
        result = []
        self.maximum = nums[len(nums)-1]+nums[0]
        ulIndex = self.getUpperLimitIndex(nums, self.maximum)
        index = 0
        while not self.BinarySearch(index, ulIndex, nums, target - nums[index]):
            index = self.getNextBigger(nums, nums[index], index)
            ulIndex = self.getUpperLimitIndex(nums, self.maximum - nums[index])
        result.append(index+1), result.append(self.mid+1)
        return result
s = Solution()
print s.twoSum([-2, -1, 1], 0)
