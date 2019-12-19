class Solution {
public:
    // 用两种方法来实现，其一是基于快速排序的分割方法，其二是基于最小堆实现
    int findKthLargest1(vector<int>& nums, int k) {
        if(nums.empty() || k>nums.size() || k<1) return INT_MIN;

        priority_queue<int, vector<int>, greater<int>> q;
        for(auto num : nums)
        {
            if(q.size()<k) q.push(num);
            else {
                if(num > q.top()) {
                    q.pop();
                    q.push(num);
                }
            }
        }

        return q.top();
    }

    // 基于partition函数
    int findKthLargest(vector<int>&nums, int k)
    {
        if(nums.empty() || k>nums.size() || k<1) return INT_MIN;

        int index(-1);  // 注意, k=1时，index=0将直接输出，没有经过分割操作，因此index不能初始化为0
        int lo(0), hi(nums.size()-1);
        while(index!=k-1)
        {
            index = partition(nums,lo,hi);
            if(index==k-1) break;
            else if(index<k-1) lo = index + 1;
            else hi = index - 1;
        }

        return nums[index];
    }

private:
    void swap(int& a, int& b)
    {
        if(&a!=&b)
        {
            a ^= b;
            b ^= a;
            a ^= b;
        }
    }
    // 注意要由大到小排序
    int partition(vector<int>&nums, int lo, int hi)
    {
        if(lo>=hi || nums.size()<2) return lo;

        srand(time(0));
        int idx = (rand() % (hi - lo + 1)) + lo;
        swap(nums[lo],nums[idx]);

        int pivot = nums[lo];
        while(lo<hi)
        {
            while(lo<hi)
            {
                if(nums[hi]<pivot) {
                    --hi;
                } else{
                    nums[lo++] = nums[hi];
                    break;
                }
            }

            while(lo<hi)
            {
                if(nums[lo]>pivot) ++lo;
                else {
                    nums[hi--] = nums[lo];
                    break;
                }
            }

        }

        nums[lo] = pivot;

        return lo;
    }
};
