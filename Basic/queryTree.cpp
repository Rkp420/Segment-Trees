#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> segment;
vector<int> input;

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

void updateTree(int idx, int val, int i, int low, int high)
{
    if (low == high)
    {
        segment[i] = val;
        return;
    }

    int mid = (low + high) / 2;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (idx <= mid)
    {
        updateTree(idx, val, left, low, mid);
    }
    else
    {
        updateTree(idx, val, right, mid + 1, high);
    }

    segment[i] = segment[left] + segment[right];
}

void display(const vector<int> &nums)
{
    for (int num : nums)
        cout << num << " ";
    cout << endl;
}

int queryInRange(int i, int j, int currIdx, int low, int high){
    // Case 1: Out of Bound
    if(i > high || j < low) return 0;

    // Case 2 : in Range
    if(i <= low && j >= high) return segment[currIdx];

    // Case 3: Overlapping
    int mid = (low + high) / 2;
    return queryInRange(i, j, 2 * currIdx + 1, low, mid) + queryInRange(i, j, 2 * currIdx + 2, mid + 1, high);
}

int main()
{
    vector<int> nums = {0, 2, 3, 5};
    input = nums;
    N = nums.size();

    segment.assign(2 * N, 0);

    buildTree(0, 0, N - 1);
    display(segment);

    cout << queryInRange(0, 2, 0, 0, N - 1);
    return 0;
}