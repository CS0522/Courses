/*5.2  ��������

		a.	ð������
			void BubbleSort(T Data[], int n)
*/
#include <iostream>
using namespace std;

/*
TODO:ð������,�����Data��Ԫ��Ϊ��������
 */
template <class T>
void BubbleSort(T Data[], int n)
{
    bool flag;
    for (int a = 0; a < n; ++a) 
    {
        flag = false;
        for (int b = 0; b < n - a - 1; ++b) //ÿһ��ѭ������ķ������
        {
            if (Data[b + 1] < Data[b]) 
                {
                    flag = true, swap(Data[b], Data[b + 1]); //����³�
                }
        }
        if (!flag) 
        {
            break;
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
    BubbleSort<int>(a, n); //aΪ����������飬nΪ����Ĵ�С
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
