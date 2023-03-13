/*5.1  ��������
	
	c.	ϣ������
		void ShellSort(T Data[], int n)
		
*/
#include <iostream>
using namespace std;

/*
TODO:ϣ������,�����ʹ��Data��Ԫ��Ϊ��������
 */
template <class T>
void ShellSort(T Data[], int n)
{
    for (int step = n / 2; step >= 1; step >>= 1) 
    { //����
        for (int a = step, b; a < n; ++a) 
        {
            T temp = Data[a]; //��һ��
            for (b = a - step; b >= 0; b -= step) 
            { //����ֱ�Ӳ��������˵��Ǽ��Ϊstep
                if (Data[b] > temp) 
                {
                    Data[b + step] = Data[b];
                }
                else break;
            }
            Data[b + step] = temp;
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
