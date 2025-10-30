#include <iostream>
#include <vector>
using namespace std;

class NumArray
{
    vector<int> st, lazy;
    int n;

public:
    NumArray(vector<int> &nums)
    {
        n = nums.size();
        st.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        buildTree(nums, 0, 0, n - 1);
    }

private:
    void buildTree(vector<int> &nums, int i, int l, int r)
    {
        if (l == r)
        {
            st[i] = nums[l];
            return;
        }

        int mid = (l + r) / 2;

        buildTree(nums, 2 * i + 1, l, mid);
        buildTree(nums, 2 * i + 2, mid + 1, r);

        st[i] = st[2 * i + 1] + st[2 * i + 2];
    }

    void pushDown(int i, int l, int r)
    {
        if (lazy[i] != 0)
        {
            st[i] += (r - l + 1) * lazy[i];

            if (l != r)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }

            lazy[i] = 0;
        }
    }
    void updateInRange(int i, int l, int r, int ql, int qr, int val)
    {
        pushDown(i, l, r);

        if (l > qr || r < ql)
            return;

        if (l >= ql && r <= qr)
        {
            lazy[i] = val;
            pushDown(i, l, r);
            return;
        }

        int mid = (l + r) / 2;
        updateInRange(2 * i + 1, l, mid, ql, qr, val);
        updateInRange(2 * i + 2, mid + 1, r, ql, qr, val);

        st[i] = st[2 * i + 1] + st[2 * i + 2];
    }

    int queryInRange(int i, int l, int r, int ql, int qr)
    {
        pushDown(i, l, r);

        if (l > qr || r < ql)
            return 0;

        if (ql <= l && r <= qr)
            return st[i];

        int mid = (l + r) / 2;
        return queryInRange(2 * i + 1, l, mid, ql, qr) + queryInRange(2 * i + 2, mid + 1, r, ql, qr);
    }

public:
    void update(int idx, int val)
    {
        int currVal = queryInRange(0, 0, n - 1, idx, idx);
        int diff = val - currVal;

        updateInRange(0, 0, n - 1, idx, idx, diff);
    }

    void updateRange(int l, int r, int val)
    {
        updateInRange(0, 0, n - 1, l, r, val);
    }

    int sumRange(int l, int r)
    {
        return queryInRange(0, 0, n - 1, l, r);
    }
};

int main()
{
    vector<int> nums = {1, 3, 5};
    NumArray obj(nums);

    cout << obj.sumRange(0, 2) << endl; // 9
    obj.updateRange(0, 1, 2);           // add +2 to first two elements
    cout << obj.sumRange(0, 2) << endl; // (3+5+5) = 13
    return 0;
}