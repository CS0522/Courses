/*5.1  ��������

		b.	�۰��������
			void BinaryInsertionSort(T Data[], int n)
			
*/
#include <iostream>
using namespace std;

/*
TODO:�۰��������,ʹ�������Data�е����ݰ���������
 */
template <class T>
void BinaryInsertionSort(T Data[], int n) //���������������ݺʹ�����Ԫ
    //�ظ���
{
    for (int a = 1; a < n; ++a) 
    {
        int l = 0, r = a - 1;
        while (l <= r) 
        { //����Ѱ�Ҳ���λ��
            int m = (l + r) / 2;
            if (Data[m] < Data[a]) l = m + 1;
            else r = m - 1;
        }
        //����lһ������ȷ�������ǰ�Ĳ���λ��
        T temp = Data[a]; //����һ��
        //ѭ���ƶ��Ϳ�
        for (int b = a - 1; b >= l; --b) 
        {
            Data[b + 1] = Data[b];
        }
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