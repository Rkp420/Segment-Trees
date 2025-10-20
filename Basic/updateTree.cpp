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

int main()
{
    vector<int> nums = {0, 2, 3, 5};
    input = nums;
    N = nums.size();

    segment.assign(2 * N, 0);

    int idx, val;
    cin >> idx >> val;

    buildTree(0, 0, N - 1);
    display(segment);

    updateTree(idx, val, 0, 0, N - 1);
    display(segment);
    return 0;
}