#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/problems/range-minimum-query/1

/* The functions which
builds the segment tree */
void buildTree(int i, int l, int r, int *st, int *arr)
{
    if (l == r)
    {
        st[i] = arr[l];
        return;
    }

    int mid = (l + r) / 2;

    buildTree(2 * i + 1, l, mid, st, arr);
    buildTree(2 * i + 2, mid + 1, r, st, arr);

    st[i] = min(st[2 * i + 1], st[2 * i + 2]);
}

int *constructST(int arr[], int n)
{
    int *st = new int[4 * n];
    buildTree(0, 0, n - 1, st, arr);
    return st;
}

/* The functions returns the
 min element in the range
 from a and b */
int rangeMinQuery(int *st, int a, int b, int currIdx, int low, int high)
{
    if (a > high || b < low)
        return INT_MAX;

    if (a <= low && b >= high)
        return st[currIdx];

    int mid = (low + high) / 2;
    return min(rangeMinQuery(st, a, b, 2 * currIdx + 1, low, mid), rangeMinQuery(st, a, b, 2 * currIdx + 2, mid + 1, high));
}
int RMQ(int st[], int n, int a, int b)
{
    return rangeMinQuery(st, a, b, 0, 0, n - 1);
}

int main()
{
    return 0;
}