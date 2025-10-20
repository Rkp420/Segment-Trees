// https://www.geeksforgeeks.org/problems/sum-of-query-ii5310/1

#include <iostream>
using namespace std;

class Solution
{
public:
    vector<int> segment;
    int *input;

    void buildTree(int i, int low, int high)
    {
        if (low == high)
        {
            segment[i] = input[low];
            return;
        }

        int mid = (low + high) / 2;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        buildTree(left, low, mid);
        buildTree(right, mid + 1, high);

        segment[i] = segment[left] + segment[right];
    }

    int queryInRange(int i, int j, int currIdx, int low, int high)
    {
        // Case 1: Out of range
        if (i > high || j < low)
            return 0;

        // Case 2: Completely inside range
        if (i <= low && j >= high)
            return segment[currIdx];

        // Case 3: Partial overlap
        int mid = (low + high) / 2;
        return queryInRange(i, j, 2 * currIdx + 1, low, mid) + queryInRange(i, j, 2 * currIdx + 2, mid + 1, high);
    }

    vector<int> querySum(int n, int arr[], int q, int queries[])
    {
        vector<int> ans;
        input = arr;
        segment.assign(4 * n, 0);

        // Build the segment tree once
        buildTree(0, 0, n - 1);

        for (int i = 0; i < 2 * q; i += 2)
        {
            int l = queries[i] - 1;
            int r = queries[i + 1] - 1;
            ans.push_back(queryInRange(l, r, 0, 0, n - 1));
        }

        return ans;
    }
};

int main()
{
    return 0;
}