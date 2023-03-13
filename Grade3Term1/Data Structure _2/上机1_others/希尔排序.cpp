#include <iostream>
using namespace std;

/*
TODO:ϣ������,�����ʹ��Data��Ԫ��Ϊ��������
 */
template <class T>
void ShellSort(T Data[], int n)
{
    for (int step = n / 2; step >= 1; step >>= 1) { //����
        for (int i = step, j; i < n; ++i) {
            T temp = Data[i]; //��һ��
            for (j = i - step; j >= 0; j -= step) { //����ֱ�Ӳ��������˵��Ǽ��Ϊstep
                if (Data[j] > temp) Data[j + step] = Data[j];
                else break;
            }
            Data[j + step] = temp;
        }
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

    ShellSort<int>(a, n); //aΪ����������飬nΪ����Ĵ�С
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}
