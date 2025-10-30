#include <iostream>
using namespace std;

// https://leetcode.com/problems/range-sum-query-mutable/

class NumArray
{
    vector<int> st;
    int n;

private:
    void buildTree(vector<int> &st, vector<int> &nums, int i, int l, int r)
    {
        if (l == r)
        {
            st[i] = nums[l];
            return;
        }

        int mid = (l + r) / 2;

        buildTree(st, nums, 2 * i + 1, l, mid);
        buildTree(st, nums, 2 * i + 2, mid + 1, r);

        st[i] = st[2 * i + 1] + st[2 * i + 2];
    }

    void updateAtidx(vector<int> &st, int idx, int val, int l, int r,
                     int currIdx)
    {
        if (idx < l || idx > r)
            return;

        if (l == r)
        {
            if (idx == l)
                st[currIdx] = val;
            return;
        }

        int mid = (l + r) / 2;
        updateAtidx(st, idx, val, l, mid, currIdx * 2 + 1);
        updateAtidx(st, idx, val, mid + 1, r, currIdx * 2 + 2);

        st[currIdx] = st[2 * currIdx + 1] + st[2 * currIdx + 2];
    }

    int getSumInRange(vector<int> &st, int a, int b, int i, int l, int r)
    {
        if (b < l || a > r)
            return 0;

        if (a <= l && b >= r)
            return st[i];

        int mid = (l + r) / 2;

        return getSumInRange(st, a, b, 2 * i + 1, l, mid) +
               getSumInRange(st, a, b, 2 * i + 2, mid + 1, r);
    }

public:
    NumArray(vector<int> &nums)
    {
        n = nums.size();
        st.resize(4 * n, 0);
        buildTree(st, nums, 0, 0, n - 1);
    }

    void update(int index, int val)
    {
        updateAtidx(st, index, val, 0, n - 1, 0);
    }

    int sumRange(int left, int right)
    {
        return getSumInRange(st, left, right, 0, 0, n - 1);
    }
};

int main()
{
    return 0;
}

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */