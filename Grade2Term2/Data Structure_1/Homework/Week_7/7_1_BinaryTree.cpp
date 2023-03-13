#include <stdio.h>
#include <stack>
#include <malloc.h>
#define MaxSize 100
using namespace std;

typedef char ElemType;

/*
TODO:����һ���ṹ��,��Ա��
  ElemType���ͱ���data���洢����Ԫ��ֵ��
  �ýṹ��ָ��lchild��ָ�����ӽ�㣻
  �ýṹ��ָ��rchild��ָ���Һ��ӽ��
*/
typedef struct node
{
	ElemType data;
	node* lchild;
	node* rchild;
	//to check if is right child
	bool toRightChild;
	node()
	{
		lchild = NULL;
		rchild = NULL;
		toRightChild = false;
	}
} BTNode;

/*
TODO:��������ض���ʽ�ַ������ɶ������Ĺ���.
��������:����һ���ַ������ɶ�����������ֵ������ʽ�洢�ṹ�Ķ�������ָ��.
	  ����ָ��������Ϊ˳��ջ���ڸ���,ѭ���ж��ַ�����ÿ���ַ�,����'\0'�˳�,
	  ������������ţ��������ӽ�㿪ʼ����ǰ����ջ,
	  ������������ţ���������˺��ӽ�����У���ջ��
	  �������','���������ӽ�㿪ʼ��ջ���������ӽ�㣬
	  �����ַ�������ͨ������ֵ�����ָ�������Ӧ�ռ�,����ֵ���ֵ,���к��ӽ�㸳��,
	  ������գ����㸳����ָ�룬��������Ϊջ������һ�����ӣ����������ӽ���ʶ������Ӧ�ӽ��ָ��.
����˵��:b-Ҫ��ֵ���ɵĶ�������ָ������,str-Ŀ���ַ�����ָ��.
����ֵ˵��:��.
����˵��:����ַ�����"A(B,C)",�������A�Ǹ�,A��������������B,C
		����ַ�����"A(B(C)",�������A�Ǹ�,A��һ������B,B��һ������C
*/
void CreateBTree(BTNode*& b, char* str)	//����������
{
	if (str == NULL)
	{
		return;
	}
	BTNode* currentNode = (BTNode *)malloc(sizeof(BTNode));
	//����ָ��������Ϊ˳��ջ���ڸ���
	std::stack<BTNode *> tempStack;
	//ѭ���ж��ַ�����ÿ���ַ�,����'\0'�˳�
	for (int i = 0; str[i] != '\0'; i++)
	{
		//������������ţ��������ӽ�㿪ʼ����ǰ����ջ
		if (str[i] == '(')
		{
			tempStack.push(currentNode);
		}
		//������������ţ���������˺��ӽ�����У���ջ
		else if (str[i] == ')')
		{
			tempStack.pop();
		}
		//�������','���������ӽ�㿪ʼ��ջ���������ӽ��
		else if (str[i] == ',')
		{
			tempStack.top()->toRightChild = true;
		}
		//�����ַ�������ͨ������ֵ�����ָ�������Ӧ�ռ�, ����ֵ���ֵ, ���к��ӽ�㸳��
		else
		{
			BTNode* newNode = (BTNode *)malloc(sizeof(BTNode));

			newNode->data = str[i];
			newNode->lchild = NULL;
			newNode->rchild = NULL;
			newNode->toRightChild = false;

			//temp pointer points to the current node
			currentNode = newNode;

			//������գ����㸳����ָ�룬��������Ϊջ������һ�����ӣ����������ӽ���ʶ������Ӧ�ӽ��ָ��
			if (b == NULL)
			{
				b = currentNode;
			}
			else
			{
				if (tempStack.empty() == false)
				{
					//to left child
					if (tempStack.top()->toRightChild == false)
					{
						tempStack.top()->lchild = newNode;
					}
					//to right child
					else
					{
						tempStack.top()->rchild = newNode;
					}
				}
			}
		}
		
	}
}

/*
TODO:������ٶ������Ĺ���.
��������:���õݹ鷽ʽ�ͷŶ�����ÿһ�����������Ŀռ�.
����˵��:b-Ŀ���������ָ������.
����ֵ˵��:��.
*/
void DestroyBTree(BTNode* b)	//���ٶ�����
{
	if (b == NULL)
	{
		return;
	}
	DestroyBTree(b->lchild);
	DestroyBTree(b->rchild);
	free(b);
	return;
}

/*
TODO:���Ҷ������н������ֵ����x�Ľ��
�������������õݹ鷽ʽ�Ӷ������ĸ���㿪ʼ�����ҽ������ֵ����x�Ľ��
		 ������Ľ��bΪ��ʱ������NULL��������Ľ��b������ֵ����xʱ������ָ��ý���ָ��
����˵����b-Ŀ���������ָ������
		 x-���ҵĽ������ֵ
����ֵ˵�������bΪ��ʱ������NULL�����b������ֵ����xʱ�����ظý���ָ��
*/
BTNode* FindNode(BTNode* b, ElemType x) //����ֵΪx�Ľ��
{
	//������Ľ��bΪ��ʱ������NULL
	if (b == NULL)
	{
		return NULL;
	}
	//���õݹ鷽ʽ�Ӷ������ĸ���㿪ʼ�����ҽ������ֵ����x�Ľ��
	//visit the node
	if (b->data == x)
	{
		return b;
	}

	if (FindNode(b->lchild, x) != NULL)
	{
		return FindNode(b->lchild, x);
	}
	else if (FindNode(b->rchild, x) != NULL)
	{
		return FindNode(b->rchild, x);
	}
	else
	{
		return NULL;
	}
}

BTNode* LchildNode(BTNode* p)
{
	return p->lchild;
}

BTNode* RchildNode(BTNode* p)
{
	return p->rchild;
}

/*
TODO:�����������ĸ߶ȵĹ���.
��������:���õݹ鷽ʽȡ���Һ��Ӹ������ֵ.
  ������bΪ�գ����Ϊ�գ��򷵻�0
  ������b��Ϊ�գ����ú���BTHeight()������b�����ӽ�㣬�����������ĸ߶�
  ȡ���������߶ȵ����ֵ��1���з���
����˵��:b-Ŀ���������ָ��.
����ֵ˵��:�������߶���ֵ,����Ϊ��ʱ,����0.
*/
int BTHeight(BTNode* b)		//�������b�ĸ߶�
{
	if (b == NULL)
	{
		return 0;
	}
	else
	{
		return (max(BTHeight(b->lchild), BTHeight(b->rchild)) + 1);
	}
}

void DispBTree(BTNode* b)  //�����ű�ʾ�����������
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");						//�к��ӽ��ʱ�����(
			DispBTree(b->lchild);				//�ݹ鴦��������
			if (b->rchild != NULL) printf(",");	//���Һ��ӽ��ʱ�����,
			DispBTree(b->rchild);				//�ݹ鴦��������
			printf(")");						//�к��ӽ��ʱ�����)
		}
	}
}

int main()
{
	BTNode* b = NULL, * p, * lp, * rp;
	printf("�������Ļ�����������:\n");
	printf("  (1)����������\n");
	char str[40] = "";
	scanf("%s", str);
	str[39] = '\0';

	/*
	TODO:���ú���CreateBTree()���������b��str������������
	*/
	CreateBTree(b, str);

	printf("  (2)���������:");

	/*
	TODO:���ú���DispBTree()���������b�����������
	*/
	DispBTree(b);

	printf("\n");
	printf("  (3)H���:");
	/*
	TODO:���ú���FindNode()���������b��'H'�����Ҷ������н�������ֵ����'H'�Ľ�㣬���������ؽ������p
	*/
	p = FindNode(b, 'H');

	if (p != NULL)
	{

		/*
		TODO:���ú���LchildNode()���������p����ȡp�����ӽ�㣬���������ؽ������lp
		*/
		lp = LchildNode(p);

		if (lp != NULL)
			printf("����Ϊ%c ", lp->data);
		else
			printf("������ ");

		/*
		TODO:���ú���RchildNode()���������p����ȡp�����ӽ�㣬���������ؽ������rp
		*/
		rp = RchildNode(p);

		if (rp != NULL)
			printf("�Һ���Ϊ%c", rp->data);
		else
			printf("���Һ��� ");
	}
	printf("\n");

	printf("  (4)������b�ĸ߶�:%d\n", BTHeight(b));
	printf("  (5)�ͷŶ�����b\n");

	/*
	TODO:���ú���DestroyBTree()���������b�����ٶ�����
	*/
	DestroyBTree(b);

	return 0;
}
