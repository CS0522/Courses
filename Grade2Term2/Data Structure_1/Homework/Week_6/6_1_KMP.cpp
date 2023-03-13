/*1.7-b,c KMPģʽƥ���㷨

	//1.7-b.	�����ַ��������������㷨�������������������顣
	int* next(string P)

	//1.7-c.	KMPģʽƥ���㷨�������Ӵ���һ�γ��ֵ�λ�ã��������ڣ�����-1
	int KMPStrMatching(string T, string P, int* N, int startIndex)

*/
#include <assert.h>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

/*
TODO:�����ַ���p�������������㷨�������������������顣
��������������int�ͱ���m����ʼֵΪP�ĳ��ȣ�
		 ���ú���assert���� m>0 �жϣ�
		 ����int��ָ�����N����ʼ��Ϊint�����飬����Ϊm;
		 ���ú���assert���� N != 0 �жϣ�
		 N[0]��ֵ0��
		 forѭ����ѭ������i��1��ʼ��С��m�ĳ��Ƚ�����
		   ����int�ͱ���k����ʼֵΪN[i - 1]
		   whileѭ����ѭ��������k������0 ���� P[i]������P[k]
					  ѭ���壺k = next[k - 1]
		   whileѭ��������
		   �������i����0 ���� P[i]����P[k] ʱ��N[i]��ֵΪk+1��
		   ����N[i]��ֵΪ0
		forѭ�������󣬷���N
����˵����P-Ҫ���������������ַ���
����ֵ˵����ָ������������ָ��
 */
int* next(string P)
{
	//���ú���assert���� m > 0 �ж�
	assert(P.length());
	//����int��ָ�����next����ʼ��Ϊint�����飬����Ϊm
	int* next = new int[P.length()];
	//���ú���assert���� next != 0 �ж�
	assert(next != 0);

	next[0] = 0;
	/*forѭ����ѭ������i��1��ʼ��С��m�ĳ��Ƚ�����
		   ����int�ͱ���k����ʼֵΪN[i - 1]
		   whileѭ����ѭ��������k������0 ���� P[i]������P[k]
					  ѭ���壺k = next[k - 1]
		   whileѭ��������
		   �������i����0 ���� P[i]����P[k] ʱ��N[i]��ֵΪk+1��
		   ����N[i]��ֵΪ0
		forѭ�������󣬷���N
	*/
	for (int i = 1; i < P.length(); i++)
	{
		int k = next[i - 1];
		
		while (k != 0 && P[i] != P[k])
		{
			k = next[k - 1];
		}
		
		if (i > 0 && P[i] == P[k])
		{
			next[i] = k + 1;
		}
		else
		{
			next[i] = 0;
		}
	}

	return next;
}

/*
TODO:KMPģʽƥ���㷨�������Ӵ���һ�γ��ֵ�λ��
��������������int�ͱ���lastIndex����ʼֵΪT�ĳ��ȼ�P�ĳ��ȣ�
		���lastIndex��startIndex С�� 0������-1��
		����int�ͱ���i������int�ͱ���j����ʼֵΪ0��
		forѭ����ѭ������i��0��ʼ��С��T�ĳ��Ƚ�����
		  whileѭ����ѭ��������P[j]������T[i] ���� j����0��
			  ѭ���壺j��ֵΪN[j - 1]
		  whileѭ��������
		  ���P[j]����T[i]��j�ۼ�1��
		  ���j����P�ĳ��ȣ�����(i - j + 1)��
		forѭ�������󣬷���-1
����˵����T-ԭʼ�ַ�����P-�Ӵ���N-�ַ���P����������
����ֵ˵�������ҵ��򷵻��Ӵ���һ�γ��ֵ�λ�ã�û�в��ҵ�������-1
*/
int KMPStrMatching(string T, string P, int* N, int startIndex)
{
	int lastIndex = T.length() - P.length();
	
	if (lastIndex < startIndex)
	{
		return -1;
	}

	int i = 0;
	int j = 0;

	for (; i < T.length(); i++)
	{
		while (j > 0 && T[i] != P[j])
		{
			j = N[j - 1];
		}

		if (P[j] == T[i])
		{
			j++;
		}

		if (j == P.length())
		{
			return (i - j + 1);
		}
	}

	return -1;
}

int main()
{
	string p; //Ҫ���ҵ��ַ���
	string q; //ԭʼ�ַ���
	getline(cin, p);
	getline(cin, q);
	int* N;
	N = next(p);
	for (int i = 0; i < p.length(); i++)
		cout << N[i] << " ";
	cout << endl;
	cout << KMPStrMatching(q, p, N, 0) << endl;
}
