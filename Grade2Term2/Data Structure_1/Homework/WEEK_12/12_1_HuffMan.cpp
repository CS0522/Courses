#include <stdio.h>
#include <string.h>
#define N 50		//Ҷ�ӽ����
#define M 2*N-1		//���н������
#include <iostream>
using namespace std;

/*
TODO:����һ���ṹ��,
  ��һ����ԱΪchar�������СΪ5,����ֵ,
  �ڶ�����ԱΪint�ͱ���weight����Ȩ��,
  ��������ԱΪint�ͱ���parent����˫�׽��,
  ���ĸ���ԱΪint�ͱ���lchild�������ӽ��,
  �������ԱΪint�ͱ���rchild�����Һ��ӽ��
*/
typedef struct 
{
	//��һ����ԱΪchar�������СΪ5,����ֵ
	char data[5];
	//�ڶ�����ԱΪint�ͱ���weight����Ȩ��
	int weight = -1;
	//��������ԱΪint�ͱ���parent����˫�׽��
	int parent = -1;
	//���ĸ���ԱΪint�ͱ���lchild�������ӽ��
	int lchild = -1;
	//�������ԱΪint�ͱ���rchild�����Һ��ӽ��
	int rchild = -1;
}HTNode;

/*
TODO:����һ���ṹ��,
  ��һ����ԱΪchar������cd��СΪN,��Ź�������
  �ڶ�����ԱΪint�ͱ���start�������
*/
typedef struct 
{
	//��һ����ԱΪchar������cd��СΪN,��Ź�������
	char cd[N];
	//�ڶ�����ԱΪint�ͱ���start�������
	int start = -1;
}HCode;


/*
TODO:�����ht��Ҷ�ӽ�㹹�������Ĺ��������Ĺ���.
��������:���ý��ֵ�����жϱȽ�ÿ��Ԫ�ض�Ӧ���ݲ��������¸�ֵ���ɹ�������.
����˵��:ht-�������,n-�����.
����ֵ˵��:��.
*/
void CreateHT(HTNode ht[], int n)//�����������
{
	int i, k, lnode, rnode;
	int min1, min2;//����Ȩ����С�������ڵ�
	for (i = 0; i < 2 * n - 1; i++)//���нڵ����������ó�ʼֵΪ-1
	{
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
	}
	for (i = n; i < 2 * n - 1; i++)//�����������
	{                      //nǰ��Ŀռ�������ֵ�����������ڵ���������Ȩ�غ�
		min1 = min2 = 32767;//min1Ϊ��һ����С��Ȩ�أ�min2Ϊ�ڶ�����С��Ȩ��
		lnode = rnode = -1;//lnode��rnodeΪ��СȨ�ص������ڵ�λ��
		for (k = 0; k <= i - 1; k++)
			if (ht[k].parent == -1)//ֻ����δ����������Ľڵ��в���
			{
				if (ht[k].weight < min1)//��Ȩ����С�������ڵ�
				{
					min2 = min1; rnode = lnode;//��min1���±�ֵ����min2,ԭ���ӵ��±�lnode���Һ��ӵ��±�rnode
					min1 = ht[k].weight; lnode = k;//��Ȩ����С���±긳��lnode
				}
				else if (ht[k].weight < min2)
				{
					min2 = ht[k].weight;
					rnode = k;//��Ȩ�صڶ���С���±긳��rnode
				}
			}
		ht[lnode].parent = i; ht[rnode].parent = i;//����ǰȨ����С��������˫�׽ڵ���Ϊ�±�Ϊi�Ľڵ�
		ht[i].weight = ht[lnode].weight + ht[rnode].weight;//�±�Ϊi�Ľڵ��Ȩ��Ϊ������Ů��Ȩ�غ�
		ht[i].lchild = lnode; ht[i].rchild = rnode;//�����±�Ϊi�Ľڵ�ĺ���Ϊ�±�Ϊlnode��rnode
	}
}

/*
TODO:��ɸ��ݹ���������������Ҷ�ӽ��Ĺ���������Ĺ���.
��������:ѭ��������������,���ݹ���������������Ҷ�ӽ��Ĺ���������,
   Ƕ��ѭ��ֱ���������,�������Һ��ӽ��,������ѭ��startָ������������ʼ�ַ�.
����˵��:ht-�������,hcd-��������,n-Ҷ�ӽ����.
����ֵ˵��:��.
*/
void CreateHCode(HTNode ht[], HCode hcd[], int n)	//�ɹ�������ht�������������hcd
{
	for (int i = 0; i < n; i++)
	{
		int currentNode = i;
		int currentParent = ht[currentNode].parent;
		for (int k = n; currentParent != -1; k--)
		{
			if (ht[currentParent].lchild == currentNode)
			{
				hcd[i].cd[k] = '0';
			}
			else
			{
				hcd[i].cd[k] = '1';
			}

			hcd[i].start = k;
			currentNode = currentParent;
			currentParent = ht[currentNode].parent;
		}
	}
}


void DispHCode(HTNode ht[], HCode hcd[], int n)	//�������������
{
	int i, k;
	int sum = 0, m = 0, j;
	printf("�������������:\n");
	for (i = 0; i < n; i++)
	{
		j = 0;
		printf("      %s: ", ht[i].data);
		for (k = hcd[i].start; k <= n; k++)
		{
			printf("%c", hcd[i].cd[k]);
			j++;
		}
		m += ht[i].weight;
		sum += ht[i].weight * j;
		printf("\n");
	}
	printf("ƽ������=%g\n", 1.0 * sum / m);
}

void print(HTNode ht[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "data: " << ht[i].data << endl;
		cout << "weight: " << ht[i].weight << endl;
		cout << "parent: " << ht[i].parent << endl;
		cout << "lchild: " << ht[i].lchild << endl;
		cout << "rchild: " << ht[i].rchild << endl;
	}
}

int main()
{
	//n��Ҷ�ӽ����
	int n = 15;
	char sss1[] = "The";
	char sss2[] = "of";
	char sss3[] = "a";
	char sss4[] = "to";
	char sss5[] = "and";
	char sss6[] = "in";
	char sss7[] = "that";
	char sss8[] = "he";
	char sss9[] = "is";
	char sss10[] = "at";
	char sss11[] = "on";
	char sss12[] = "for";
	char sss13[] = "His";
	char sss14[] = "are";
	char sss15[] = "be";
	char* str[] = { sss1,sss2,sss3,sss4,sss5,sss6,sss7,sss8,sss9,sss10,sss11,sss12,sss13,sss14,sss15 };
	int fnum[] = { 1192,677,541,518,462,450,242,195,190,181,174,157,138,124,123 };
	scanf_s("%d", &fnum[14]);
	HTNode *ht = new HTNode[M];
	HCode *hcd = new HCode[N];

	/*
	TODO:forѭ��i��0��ʼ��n��i����1��,����strcpy����������ht[i].data��str[i]�������Ʋ���,
			fnum[i]����ht[i].weight,����ѭ��
	 ����CreateHT����������ht��n��������������
		 ����CreateHCode����������ht��hcd��n���ɹ�������ht�������������hcd
	 ����DispHCode����������ht��hcd��n����ʾ�����������ƽ������
	*/
	for (int i = 0; i < n; i++)
	{
		strcpy_s(ht[i].data, str[i]);
		ht[i].weight = fnum[i];
	}

	CreateHT(ht, n);
	CreateHCode(ht, hcd, n);
	DispHCode(ht, hcd, n);
	//print(ht, n);

	return 0;
}

