//AVL�㷨
#include <stdio.h>
#include <malloc.h>
typedef int KeyType;					//�ؼ�������
typedef char InfoType;

/*
TODO:����һ��ƽ��������ṹ�壬��Ա��
  KeyType���ͱ���key���洢�ؼ��֣�
  int�ͱ���bf���洢ƽ������
  InfoType�ͱ���data���洢���ݣ�
  ������ƽ��������ṹ������ָ��lchild��rchild��ָ�������Һ��ӽ��.
*/
typedef struct node               		//��¼����
{
	//key
	KeyType key;
	//data
	InfoType data;
	//balance factor
	int bf;
	//left child and right child
	node* lchild;
	node* rchild;
} BSTNode;

/*
TODO:��ɶ���ָ��p��ָ���Ϊ���Ķ���������ƽ����ת����Ĺ���.
��������:����ָ��p��ָ���Ϊ���Ķ���������ƽ����ת����ͨ���жϽ���ƽ�����ӵ�ֵ���������¸�ֵ����������ƽ�⴦��.
  ����ʵ�ֹ��̣�
	��������BSTNode���͵�ָ��p1��p2
	�ж����p��ƽ�����ӵ���0����p��ƽ��������Ϊ1�����taller��Ϊ1.
	�ж����p��ƽ�����ӵ���-1����p��ƽ��������Ϊ0�����taller��Ϊ0.
	���p��ƽ�����ӼȲ�����0��Ҳ������-1��
	  p1ָ����p�����ӽ��
	  �ж����p1��ƽ�����ӵ���1�����p�ĳ�Աlchildָ��p1�����ӽ�㣬p1�ĳ�Աrchildָ��p��㣬p��p1��ƽ��������Ϊ0����p1����p.
	  �ж����p1��ƽ�����ӵ���-1��p2ָ��p1�����ӽ�㣬p1�����ӽ��ָ��p2�����ӽ�㣬p2�����ӽ��ָ��p1��
		p�����ӽ��ָ��p2�����ӽ�㣬p2�����ӽ��ָ��p��
		�ж����p2��ƽ�����ӵ���0����p��p1��ƽ��������Ϊ0
		�ж����p2��ƽ�����ӵ���1����p1��ƽ��������Ϊ0����p��ƽ��������Ϊ-1
		���p2��ƽ�����ӼȲ�����0��Ҳ������1����p1��ƽ��������Ϊ1��p��ƽ��������Ϊ0
		��p2����p��p��ƽ��������Ϊ0
	  ���taller��Ϊ0.
����˵��:p��Ŀ��������ĸ�ָ������
		taller��������p�Ƿ񳤸ߵı��
����ֵ˵��:��.
*/
void LeftProcess(BSTNode*& p, int& taller)
{
	BSTNode* p1;
	BSTNode* p2;
	if (p->bf == 0)
	{
		p->bf = 1;
		taller = 1;
	}
	else if (p->bf == -1)
	{
		p->bf = 0;
		taller = 0;
	}
	else
	{
		p1 = p->lchild;
		if (p1->bf == 1)
		{
			p->lchild = p1->rchild;
			p1->rchild = p;
			p->bf = 0;
			p1->bf = 0;
			p = p1;
		}
		else if (p1->bf == -1)
		{
			p2 = p1->rchild;
			p1->rchild = p2->lchild;
			p2->lchild = p1; 
			p->lchild = p2->rchild; 
			p2->rchild = p;

			if (p2->bf == 0)
			{
				p->bf = 0;
				p1->bf = 0;
			}
			else if (p2->bf == 1)
			{
				p1->bf = 0;
				p->bf = -1;
			}
			else
			{
				p1->bf = 1;
				p->bf = 0;
			}
			p = p2;
			p->bf = 0;
		}
		taller = 0;
	}
}

/*
TODO:��ɶ���ָ��p��ָ���Ϊ���Ķ���������ƽ����ת����Ĺ���.
��������:����ָ��p��ָ���Ϊ���Ķ���������ƽ����ת����ͨ���жϽ���ƽ�����ӵ�ֵ���������¸�ֵ����������ƽ�⴦��.
  ����ʵ�ֹ��̣�
	��������BSTNode���͵�ָ��p1��p2
	�ж����p��ƽ�����ӵ���0����p��ƽ��������Ϊ-1�����taller��Ϊ1.
	�ж����p��ƽ�����ӵ���1����p��ƽ��������Ϊ0�����taller��Ϊ0.
	���p��ƽ�����ӼȲ�����0��Ҳ������1��
	  p1ָ����p�����ӽ��
	  �ж����p1��ƽ�����ӵ���-1��p�����ӽ��ָ��p1�����ӽ�㣬p1�����ӽ��ָ��p��p��p1��ƽ��������Ϊ0����p1����p.
	  �ж����p1��ƽ�����ӵ���1��p2ָ��p1�����ӽ�㣬p1�����ӽ��ָ��p2�����ӽڵ㣬p2�����ӽڵ�ָ��p1,
		p�����ӽ��ָ��p2�����ӽ�㣬p2�����ӽ��ָ��p��
		�ж����p2��ƽ�����ӵ���0����p��p1��ƽ��������Ϊ0
		�ж����p2��ƽ�����ӵ���-1����p1��ƽ��������Ϊ0��p��ƽ��������Ϊ1
		���p2��ƽ�����ӼȲ�����0��Ҳ������-1����p1��ƽ��������Ϊ-1��p��ƽ��������Ϊ0
		��p2����p��p��ƽ��������Ϊ0
	���taller��Ϊ0
����˵��:p��Ŀ��������ĸ�ָ������
		taller��������p�Ƿ񳤸ߵı��
����ֵ˵��:��.
*/
void RightProcess(BSTNode*& p, int& taller)
{
	BSTNode* p1;
	BSTNode* p2;
	if (p->bf == 0)
	{
		p->bf = -1;
		taller = 1;
	}
	else if (p->bf == 1)
	{
		p->bf = 0;
		taller = 0;
	}
	else
	{
		p1 = p->rchild;
		if (p1->bf == -1)
		{
			p->rchild = p1->lchild;
			p1->lchild = p;
			p->bf = 0;
			p1->bf = 0;
			p = p1;
		}
		else if (p1->bf == 1)
		{
			p2 = p1->lchild;
			p1->lchild = p2->rchild;
			p2->rchild = p1;
			p->rchild = p2->lchild;
			p2->lchild = p;
			if (p2->bf == 0)
			{
				p->bf = 0;
				p1->bf = 0;
			}
			else if (p2->bf == -1)
			{
				p1->bf = 0;
				p->bf = 1;
			}
			else
			{
				p1->bf = -1;
				p->bf = 0;
			}
			p = p2;
			p->bf = 0;
		}
		taller = 0;
	}
}

/*
TODO:��ɲ�����Ĺ���.
��������:��ƽ�������b�в���һ���ؼ���Ϊe�Ľ�㣬���õݹ鷽ʽ�����㣬����ɹ�����1�����򷵻�0.
  ����ʵ�ֹ��̣�
	�ж϶�����b�Ƿ�ΪNULL��
	  ���������bΪNULL�������½�㣬���½�����洢�ռ䣬�½���key��Ϊe�����Һ��ӽ��ΪNULL��bf��Ϊ0�����taller��Ϊ1������1.
	  ���������b��ΪNULL���жϽ��b�е�key�Ƿ����e��
		������b�е�key����e�������taller��Ϊ0������0.
		������b�е�key������e���ж�e�Ƿ�С�ڽ��b�е�key��
		  ���eС�ڽ��b�е�key�����ú���InsertAVL()��������b������ӽ�㡢���e�����taller���жϺ���InsertAVL()����ֵ�Ƿ����0��
			�������InsertAVL()����ֵ����0������0.
			�������InsertAVL()����ֵ������0���ж����taller�Ƿ����1��������taller����1������ú���LeftProcess()���������Ϊ���b�����taller.
		  ���e��С�ڽ��b�е�key�����ú���InsertAVL()��������b���Ҳ��ӽ�㡢���e�����taller���жϺ���InsertAVL()����ֵ�Ƿ����0��
			�������InsertAVL()����ֵ����0������0.
			�������InsertAVL()����ֵ������0���ж����taller�Ƿ����1��������taller����1������ú���RightProcess()���������Ϊ���b�����taller.
����˵��:b��Ŀ�������ָ������
		e���ؼ���
		taller��������b�Ƿ񳤸ߵı��.
����ֵ˵��:������ɹ�����1�����򷵻�0.
*/
int InsertAVL(BSTNode*& b, KeyType e, int& taller)
{
	if (b == NULL)
	{
		BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
		//check if null pointer
		if (newNode == NULL)
		{
			return 0;
		}
		newNode->key = e;
		newNode->lchild = NULL;
		newNode->rchild = NULL;
		newNode->bf = 0;
		taller = 1;
		b = newNode;
		return 1;
	}
	//b != NULL
	if (b->key == e)
	{
		taller = 0;
		return 0;
	}
	else
	{
		if (e < b->key)
		{
			if (InsertAVL(b->lchild, e, taller) == 0)
			{
				return 0;
			}
			else
			{
				if (taller == 1)
				{
					LeftProcess(b, taller);
				}
			}
		}
		else
		{
			if (InsertAVL(b->rchild, e, taller) == 0)
			{
				return 0;
			}
			else
			{
				if (taller == 1)
				{
					RightProcess(b, taller);
				}
			}
		}
	}

	return 1;
}

//�����ű�ʾ�����AVL
void DispBSTree(BSTNode* b)
{
	if (b != NULL)
	{
		printf("%d", b->key);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DispBSTree(b->lchild);
			if (b->rchild != NULL) printf(",");
			DispBSTree(b->rchild);
			printf(")");
		}
	}
}

/*
TODO:�������ƽ��������Ĺ���.
��������:���õݹ鷽ʽ�ͷ�ƽ�������ÿһ�����������Ŀռ�.
  ����ʵ�ֹ��̣�
	�ж�bָ���Ƿ�ΪNULL�������ΪNULL������ú���DestroyAVL()���ֱ�����b�������ӽ�㣻
	���ú���free()�ͷ�b
����˵��:b��Ŀ��ƽ���������ָ������.
����ֵ˵��:��.
*/
void DestroyAVL(BSTNode*& b)
{
	if (b != NULL)
	{
		DestroyAVL(b->lchild);
		DestroyAVL(b->rchild);
		free(b);
	}
}

/*
TODO:�����ɾ�����ʱ��������Ĺ���.
��������:�ж�ƽ�����ӵ�ֵ���ı���ֵ����ı����Һ�����������.
  ����ʵ�ֹ���:
	��������BSTNode�͵�ָ�����p1��p2
	�ж����p��ƽ�����ӵ���1����p��ƽ��������Ϊ0��taller��Ϊ1
	�ж����p��ƽ�����ӵ���0����p��ƽ��������Ϊ-1��taller��Ϊ0
	���p��ƽ�����ӼȲ�����1��Ҳ������0��
	  p1ָ��p�����ӽ��
	  �ж����p1��ƽ�����ӵ���0����p�����ӽ��ָ��p1�����ӽ�㣬p1�����ӽ��ָ��p��p1��ƽ��������Ϊ1��
		p��ƽ��������Ϊ-1��p1����p��taller��Ϊ0
	  �ж����p1��ƽ�����ӵ���-1����p�����ӽ��ָ��p1�����ӽ�㣬p1�����ӽ��ָ��p��p��p1��ƽ��������Ϊ0��
		p1����p��taller��Ϊ1
	  ���p1��ƽ�����ӼȲ�����0��Ҳ������-1��
		��p2ָ��p1�����ӽ�㣬p1�����ӽ��ָ��p2�����ӽ�㣬p2�����ӽ��ָ��p1��
		p�����ӽ��ָ��p2�����ӽ�㣬p2�����ӽ��ָ��p,
		�ж����p2��ƽ�����ӵ���0����p��p1��ƽ��������Ϊ0
		�ж����p2��ƽ�����ӵ���-1����p��ƽ��������Ϊ1��p1��ƽ��������Ϊ0
		���p2��ƽ�����ӼȲ�����0��Ҳ������-1����p��ƽ��������Ϊ0��p1��ƽ��������Ϊ-1
		p2��ƽ��������Ϊ0��p2����p��taller��Ϊ1
����˵��:p��Ŀ��������ĸ�ָ������
		taller�����Ҹ߶ȱȽϱ��.
����ֵ˵��:��.
*/
void LeftProcess1(BSTNode*& p, int& taller)
{
	BSTNode* p1;
	BSTNode* p2;
	if (p->bf == 1)
	{
		p->bf = 0;
		taller = 1;
	}
	else if (p->bf == 0)
	{
		p->bf = -1;
		taller = 0;
	}
	else
	{
		p1 = p->rchild;
		if (p1->bf == 0)
		{
			p->rchild = p1->lchild;
			p1->lchild = p;
			p1->bf = 1;
			p->bf = -1;
			p = p1;
			taller = 0;
		}
		else if (p1->bf == -1)
		{
			p->rchild = p1->lchild;
			p1->lchild = p;
			p->bf = 0;
			p1->bf = 0;
			p = p1;
			taller = 1;
		}
		else
		{
			p2 = p1->lchild;
			p1->lchild = p2->rchild;
			p2->rchild = p1;
			p->rchild = p2->lchild;
			p2->rchild = p;
			if (p2->bf == 0)
			{
				p->bf = 0;
				p1->bf = 0;
			}
			else if (p2->bf == -1)
			{
				p->bf = 1;
				p1->bf = 0;
			}
			else
			{
				p->bf = 0;
				p1->bf = -1;
			}
			p2->bf = 0;
			p = p2;
			taller = 1;
		}
	}
}

/*
TODO:�����ɾ�����ʱ�����Ҵ���Ĺ���.
��������:�ж�ƽ�����ӵ�ֵ���ı���ֵ����ı����Һ��������Ҵ���.
  ����ʵ�ֹ���:
	��������BSTNode�͵�ָ�����p1��p2
	�ж����p��ƽ�����ӵ���-1����p��ƽ��������Ϊ0��taller��Ϊ-1
	�ж����p��ƽ�����ӵ���0����p��ƽ��������Ϊ1��taller��Ϊ0
	���p��ƽ�����ӼȲ�����-1��Ҳ������0��
	  p1ָ��p�����ӽ��
	  �ж����p1��ƽ�����ӵ���0����p�����ӽ��ָ��p1�����ӽ�㣬p1�����ӽ��ָ��p��p1��ƽ��������Ϊ-1��
		p��ƽ��������Ϊ1��p1����p��taller��Ϊ0
	  �ж����p1��ƽ�����ӵ���1����p�����ӽ��ָ��p1�����ӽ�㣬p1�����ӽ��ָ��p��p��p1��ƽ��������Ϊ0��
		p1����p��taller��Ϊ1
	  ���p1��ƽ�����ӼȲ�����0��Ҳ������1��
		��p2ָ��p1�����ӽ�㣬p1�����ӽ��ָ��p2�����ӽ�㣬p2�����ӽ��ָ��p1��
		p�����ӽ��ָ��p2�����ӽ�㣬p2�����ӽ��ָ��p,
		�ж����p2��ƽ�����ӵ���0����p��p1��ƽ��������Ϊ0
		�ж����p2��ƽ�����ӵ���1����p��ƽ��������Ϊ-1��p1��ƽ��������Ϊ0
		���p2��ƽ�����ӼȲ�����0��Ҳ������1����p��ƽ��������Ϊ0��p1��ƽ��������Ϊ1
		p2��ƽ��������Ϊ0��p2����p��taller��Ϊ1
����˵��:p��Ŀ��������ĸ�ָ������
		taller�����Ҹ߶ȱȽϱ��.
����ֵ˵��:��.
*/
void RightProcess1(BSTNode*& p, int& taller)
{
	BSTNode* p1;
	BSTNode* p2;
	if (p->bf == -1)
	{
		p->bf = 0;
		taller = -1;
	}
	else if (p->bf == 0)
	{
		p->bf = 1;
		taller = 0;
	}
	else
	{
		p1 = p->lchild;
		if (p1->bf == 0)
		{
			p->lchild = p1->rchild;
			p1->rchild = p;
			p1->bf = -1;
			p->bf = 1;
			p = p1;
			taller = 0;
		}
		else if (p1->bf == 1)
		{
			p->lchild = p1->rchild;
			p1->rchild = p;
			p->bf = 0;
			p1->bf = 0;
			p = p1;
			taller = 1;
		}
		else
		{
			p2 = p1->rchild;
			p1->rchild = p2->lchild;
			p2->lchild = p1;
			p->lchild = p2->rchild;
			p2->rchild = p;
			if (p2->bf == 0)
			{
				p->bf = 0;
				p1->bf = 0;
			}
			else if (p2->bf == 1)
			{
				p->bf = -1;
				p1->bf = 0;
			}
			else
			{
				p->bf = 0;
				p1->bf = 1;
			}
			p2->bf = 0;
			p = p2;
			taller = 1;
		}
	}
}

/*
TODO:������ڴ���ɾ����������������յ�����Ĺ���.
��������:�жϽ���Һ���ָ��ֵ���ͷſռ���ߵݹ���ú������Ҵ���.
  ����ʵ�ֹ��̣�
	�ж����r�����ӽ�����NULL��r�Ĺؼ��ָ���q�Ĺؼ��֣�r����q��rָ��r�����ӽ�㣬���ú���free()�ͷ�q��taller��Ϊ1
	���r�����ӽ�㲻����NULL�����ú���Delete2()����������ֱ�Ϊq��r�����ӽ�㡢taller��
	  �ж����taller����1�����ú���RightProcess1()����������ֱ�Ϊr��taller
����˵��:q�����ָ��
		r�������ָ������
		taller�����Ҹ߶ȱȽϱ��.
����ֵ˵��:��.
*/
void Delete2(BSTNode* q, BSTNode*& r, int& taller)
//��DeleteAVL()����,���ڴ���ɾ����������������յ����
{
	if (r->rchild == NULL)
	{
		q->key = r->key;
		q = r;
		r = r->lchild;
		free(q);
		taller = 1;
	}
	else
	{
		Delete2(q, r->rchild, taller);
		if (taller == 1)
		{
			RightProcess1(r, taller);
		}
	}
}

/*
TODO:�����AVL��p��ɾ���ؼ���Ϊx�Ľ��Ĺ���.
��������:�жϽ��Ĺؼ��ֵ�ֵ���ݹ���ò��������Ҵ�����ߵ��ú����ͷſռ�.
  ����ʵ�ֹ��̣�
	����int�ͱ���k��BSTNode��ָ��q
	�ж����p����NULL������0.
	�ж����xС�ڽ��p�Ĺؼ��֣����ú���DeleteAVL()������Ĳ����ֱ�Ϊp�����ӽ��ָ�������x��taller��������DeleteAVL()�ķ���ֵ��������k��
	  �ж����taller����1�����ú���LeftProcess1()������Ĳ����ֱ�Ϊp��taller
	  ����k��ֵ.
	�ж����x���ڽ��P�Ĺؼ��֣����ú���DeleteAVL()������Ĳ����ֱ�Ϊp�����ӽ��ָ�������x��taller��������DeleteAVL()�ķ���ֵ��������k��
	  �ж����taller����1�����ú���RightProcess1()������Ĳ����ֱ�Ϊp��taller
	  ����k��ֵ.
	���x����p�Ĺؼ��֣�p����q��
	  �ж����p�����ӽ�����NULL��pָ��p�����ӽ�㣬���ú���free()�ͷ�q��taller��Ϊ1
	  �ж����p�����ӽ�����NULL��pָ��p�����ӽ�㣬���ú���free()�ͷ�q��taller��Ϊ1
	  ���p�������ӽ������գ����ú���Delete2()����������ֱ�Ϊq��q�����ӽ�㡢taller��
		�ж����taller����1�����ú���LeftProcess1()����������ֱ�Ϊq��taller
		q����p
	  ����1.
����˵��:p�������ָ������
		x��Ŀ��ؼ���
		taller�����Ҹ߶ȱȽϱ��.
����ֵ˵��:ɾ��ʧ�ܷ���0,ɾ���ɹ�����1.
*/
int DeleteAVL(BSTNode*& p, KeyType x, int& taller)
{
	int k;
	BSTNode* q;
	if (p == NULL)
	{
		return 0;
	}
	if (x < p->key)
	{
		k = DeleteAVL(p->lchild, x, taller);
		if (taller == 1)
		{
			LeftProcess1(p, taller);
		}
		return k;
	}
	else if (x > p->key)
	{
		k = DeleteAVL(p->rchild, x, taller);
		if (taller == 1)
		{
			RightProcess1(p, taller);
		}
		return k;
	}
	else
	{
		q = p;
		if (p->rchild == NULL)
		{
			p = p->lchild;
			free(q);
			taller = 1;
		}
		else if (p->lchild == NULL)
		{
			p = p->rchild;
			free(q);
			taller = 1;
		}
		else if (p->rchild != NULL && p->lchild != NULL)
		{
			Delete2(q, q->lchild, taller);
			if (taller == 1)
			{
				LeftProcess1(q, taller);
			}
			p = q;
		}
		return 1;
	}
}

int main()
{
	BSTNode* b = NULL;
	int i, j, k;
	scanf_s("%d", &k);
	KeyType a[] = { 16,3,7,11,9,26,18,14,15 }, n = 9;
	for (i = 0; i < n; i++)
	{
		/*
		TODO:���ú���InsertAVL()����ƽ�������b�в���һ���ؼ���Ϊa[i]�Ľ�㣬
		����Ĳ����ֱ�Ϊָ�����ĸ����b������Ԫ��a[i]�ͱ���j
		*/
		InsertAVL(b, a[i], j);

	}
	printf("   AVL:");
	/*
	TODO:���ú���DispBSTree()�����bָ���ƽ�������
	*/
	DispBSTree(b);

	printf("   ɾ���ؼ���%d:", k);
	/*
	TODO:���ú���DeleteAVL()��ɾ��ƽ����b�е��ڹؼ���k��һ����㣬
	����Ĳ����ֱ�Ϊָ�����ĸ����b������k�ͱ���j
	*/
	DeleteAVL(b, k, j);

	printf("   AVL:");
	/*
	TODO:���ú���DispBSTree()�����bָ���ƽ�������
		 ���ú���DestroyAVL()������bָ���ƽ�������
	*/
	DispBSTree(b);
	DestroyAVL(b);

	return 0;
}
