/*4.1  �۰�����㷨*/

#include <iostream>
using namespace std;

/*
TODO:�۰�����㷨,�۰���ҹ��̣�Array[0,��,n-1]Ϊ�����ҵ��������ݼ�¼��keyΪ���ҵļ�¼
���ҳɹ������ظ�Ԫ������λ��,���Ҳ��ɹ�������-1

 */
template <class T>
int BiSearch(T Array[], T key, int n)
{ 
    int l = 0, r = n - 1; 
    while (l <= r) {
        int mid = (l + r) / 2; 
        if (key < Array[mid]) r = mid - 1; 
        else if (key > Array[mid]) l = mid + 1; 
        else return mid;
    }
    return -1; 
}

int main()
{
    int n, num;
    cin >> n;
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    } //����ӦΪ�����˳���
    cin >> num;
    int index = BiSearch<int>(A, num, n);
    if (index == -1) {
        cout << "���Ҳ��ɹ�" << endl;
    } else {
        cout << num << " ��λ��Ϊ�� " << index;
    }
    return 0;
}
