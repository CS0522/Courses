#include <iostream>
using namespace std;

/*
TODO:����ֱ�Ӳ������򷨣���Data������в���������
 */
template <class T>
void InsertionSort(T Data[], int n)
{ //
    for (int i = 1, j; i < n; ++i) { //1~n-1������ǰ����ͬʱ�ƶ�
        T temp = Data[i];
        for (j = i - 1; j >= 0; --j) {
            if (Data[j] > temp) Data[j + 1] = Data[j]; //������
            else break;
        }
        Data[j + 1] = temp;
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
    InsertionSort<int>(a, n); //aΪ����������飬10Ϊ����Ĵ�С
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
}
