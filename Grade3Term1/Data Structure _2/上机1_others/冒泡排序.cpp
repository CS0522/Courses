#include <iostream>
using namespace std;

/*
TODO:ð������,�����Data��Ԫ��Ϊ��������
 */
template <class T>
void BubbleSort(T Data[], int n)
{
    bool flag;
    for (int i = 0; i < n; ++i) {
        flag = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (Data[j + 1] < Data[j]) flag = true, swap(Data[j], Data[j + 1]); //����³�
        }
        if (!flag) break;
    }
}

int main()
{
    int n, num;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> num;
        a[i] = num;
    }
    BubbleSort<int>(a, n); //aΪ����������飬nΪ����Ĵ�С
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
