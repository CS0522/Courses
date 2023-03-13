#include <iostream>
using namespace std;

template <class T>
/*
TODO:����Merge������Data�Ǵ��鲢���飬���ж�Data[start,mid]��Data[mid+1, end]
  ֮������ݽ��й鲢
*/
void Merge(T Data[], int start, int mid, int end)
{
    T *temp = new T[end - start + 1]; //��ʱ����
    int i = start, j = mid + 1, p = 0; //�ֱ�ָ��ǰ��Σ����Σ���ʱ����
    while (i <= mid && j <= end) {
        if (Data[i] < Data[j]) temp[p++] = Data[i++];
        else temp[p++] = Data[j++];
    }
    while (i <= mid) temp[p++] = Data[i++];
    while (j <= end) temp[p++] = Data[j++];
    for (i = start, p = 0; i <= end; ++i, ++p) Data[i] = temp[p]; //�ƻ�Data
}

/*
TODO:��Data[start]-Data[end]֮������н��й鲢����,�����ʹ��Data��Ԫ����������
 */
template <class T>
void MergeSort(T Data[], int start, int end)
{ //��Data[start]-Data[end]֮������н��й鲢����
    if (start < end) { //���ȴ���1
        int mid = (start + end) / 2;
        MergeSort(Data, start, mid); //ǰһ��鲢����
        MergeSort(Data, mid + 1, end); //��һ��鲢����
        Merge(Data, start, mid, end); //ǰ��ϲ�
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
    MergeSort<int>(a, 0, n - 1); //aΪ����������飬0Ϊ����ĵ�һ��λ�ã�n-1Ϊ��������һ��λ��
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
