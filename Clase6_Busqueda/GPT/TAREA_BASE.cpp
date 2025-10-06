#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int sequentialSearch(vector<int> a, int key) {
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == key) return i;
    }
    return -1;
}

int binarySearch_Iterativa(vector<int> a, int key) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == key) return m;
        if (key < a[m]) r = m - 1;
        else l = m + 1;
    }
    return -1;
}

int binarySearch_Recursiva(vector<int> a, int key, int l, int r) {
    if (l > r) return -1;
    int m = (l + r) / 2;
    if (a[m] == key) return m;
    if (key < a[m]) return binarySearch_Recursiva(a, key, l, m - 1);
    return binarySearch_Recursiva(a, key, m + 1, r);
}

int main() {
    vector<int> v = {15, 3, 9, 20, 7, 11, 25, 30};
    vector<int> vs = v;
    sort(vs.begin(), vs.end());

    int key = 7;
    cout << "Sequential: " << sequentialSearch(v, key) << endl;
    cout << "Binaria Iterativa: " << binarySearch_Iterativa(vs, key) << endl;
    cout << "Binaria Recursiva: " << binarySearch_Recursiva(vs, key, 0, vs.size() - 1) << endl;

    return 0;
}