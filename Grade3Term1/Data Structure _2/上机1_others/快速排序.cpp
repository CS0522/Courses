#include <iostream>
using namespace std;

/*
TODO:ʵ�ֶ�data[left]��data[right]�ķָ�����������ػ��ֺ���Ԫ�ض�Ӧ��λ��,������Ԫ�ص��λ�ã�ʵ�ַ��?
*/
template <class T>
int Partition1(T Data[], int left, int right)
{
    swap(Data[left], Data[rand() % (right - left + 1) + left]); //���ѡ��Ԫ��
    T temp = Data[left]; //��һ��
    int i = left, j = right;
    while (i < j) {
        while (i < j && Data[j] >= temp) --j;
        Data[i] = Data[j]; //�ҵ�С�Ľ���
        while (i < j && Data[i] <= temp) ++i;
        Data[j] = Data[i]; //�ҵ���Ľ���
    }
    Data[i] = temp; //�Ž�ȥ
    return i;
}

/*
TODO:�÷��η�ʵ�ֿ��������㷨,�����Data��Ԫ�ذ���������
 */
template <class T>
void QuickSort(T Data[], int left, int right)
{
    if (left < right) { //����1
        int mid = Partition1(Data, left, right); //��ȡλ��
        QuickSort(Data, left, mid - 1); //���ҿ���
        QuickSort(Data, mid + 1, right);
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
    QuickSort<int>(a, 0, n - 1); //aΪ����������飬0Ϊ����ĵ�һ��λ�ã�n-1Ϊ��������һ��λ��
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
