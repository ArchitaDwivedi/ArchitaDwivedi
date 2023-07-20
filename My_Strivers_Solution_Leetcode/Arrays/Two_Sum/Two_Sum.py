class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        i = 0
        hashmap = {}
        while(len(nums) > 0 and i < len(nums)):
            reqnum = target - nums[i]
            if (reqnum in hashmap):
                return [i, hashmap[reqnum]]
            else:
                hashmap[nums[i]] = i
                i = i + 1
        return