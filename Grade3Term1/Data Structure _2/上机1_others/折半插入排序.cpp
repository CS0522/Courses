#include <iostream>
using namespace std;

/*
TODO:�۰��������,ʹ�������Data�е����ݰ���������
 */
template <class T>
void BinaryInsertionSort(T Data[], int n) //���������������ݺʹ�����Ԫ�ظ���
{
    for (int i = 1; i < n; ++i) {
        int l = 0, r = i - 1;
        while (l <= r) { //����Ѱ�Ҳ���λ��
            int m = (l + r) / 2;
            if (Data[m] < Data[i]) l = m + 1;
            else r = m - 1;
        }
        //����lһ������ȷ�������ǰ�Ĳ���λ��
        T temp = Data[i]; //����һ��
        //ѭ���ƶ��Ϳ�
        for (int j = i - 1; j >= l; --j) Data[j + 1] = Data[j];
        Data[l] = temp;
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

    BinaryInsertionSort<int>(a, n); //aΪ����������飬10Ϊ����Ĵ�С
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
}
