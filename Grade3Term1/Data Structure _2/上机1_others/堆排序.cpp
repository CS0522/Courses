#include <iostream>
using namespace std;

/*
TODO:���������Խ��iΪ�������ѵ����ʣ�n������Ԫ�صĸ���,�ҵ�i�����������ӵ�ϱ?
�����ӽ����бȽ�;�����ӽ����бȽ�;�ж��Ƿ���Ҫ���е���;�ݹ���ӽ����е���
 */
template <class T>
void SiftDown(T Data[], int i, int n)
{
    T temp = Data[i]; //��һ��
    int p = i, son = 2 * i + 1; //p�ǵ�ǰ�ڵ㣬son��p�������
    while (son < n) { //������ӵĻ�
        if (son + 1 < n && Data[son + 1] > Data[son]) ++son; //�Ҷ��Ӹ����ѡ�Ҷ���
        if (temp < Data[son]) Data[p] = Data[son]; //���������С���³���Ҳ���Ƕ��ӽڵ㸳ֵ�����ڵ�
        else break; //�����˳�ѭ��
        p = son; //p������
        son = 2 * p + 1; //ȡ�����
    }
    Data[p] = temp; //temp��ֵ������λ��
}
/*
TODO:����һ�����ѣ������Ҷ�ӽ������ϱ?ѭ������SiftDown�������������ѵ�����
 */
template <class T>
void BuildHeap(T Data[], int n)
{
    //���һ�����ն˽�㵹���³�
    for (int i = (n + 1) / 2 - 1; i >= 0; --i)
        SiftDown(Data, i, n);
}

/*
TODO: ���ж��������Ƚ���һ�����ѣ�����ѭ������ȡ�����Ԫ�غ󲻶ϵ�������
 ������ɺ�ʹ��Data��Ԫ�ذ���������
 */
template <class T>
void HeapSort(T Data[], int n)
{
    BuildHeap(Data, n); //����
    for (int i = n - 1; i > 0; --i) {
        swap(Data[0], Data[i]); //���ĸ����һ��λ�ý���
        SiftDown(Data, 0, i); //�ѵĴ�С��һ�����ڵ��³�
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
    HeapSort<int>(a, n); //aΪ����������飬nΪ����Ĵ�С
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
