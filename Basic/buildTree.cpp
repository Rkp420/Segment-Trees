#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> segement;
vector<int> input;

void buildTree(int i, int low, int high)
{
    if (low == high)
    {
        segement[i] = input[low];
        return;
    }

    int mid = (low + high) / 2;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    buildTree(left, low, mid);
    buildTree(right, mid + 1, high);

    segement[i] = segement[left] + segement[right];
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

    // ✅ Allocate segment tree now that N is known
    segement.assign(2 * N, 0);

    buildTree(0, 0, N - 1);
    display(segement);
    return 0;
}