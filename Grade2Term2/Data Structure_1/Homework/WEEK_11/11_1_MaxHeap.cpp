/*2.4����
 *
 * void BuildHeap();	//2.4-a ���ѹ���
 * void SiftDown(int left);	//2.4-b SiftDown������left���µ����ѣ�ʹ���г�Ϊ��
 * void SiftUp(int pos);	//2.4-c SiftUp������position���ϵ����ѣ�ʹ���г�Ϊ��
 * bool Remove(int pos, T& node);	//2.4-d ɾ�������±��Ԫ��
 * bool Insert(const T& newNode);	//2.4-e �Ӷ��в�����Ԫ��newNode
 *
 */

#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class MaxHeap {
private:
	T* heapArray;
	int CurrentSize; /* ��ǰ��Ԫ�ظ��� */
	int MaxSize; /* �����ܴ�ŵ����Ԫ�ظ��� */
public:
	MaxHeap(T* array, int num, int max)
	{
		this->heapArray = array;
		this->CurrentSize = num;
		this->MaxSize = max;
	}

	virtual ~MaxHeap() {};
	bool isLeaf(int pos) const;
	int leftchild(int pos) const;
	int rightchild(int pos) const;
	int parent(int pos) const;
	void BuildHeap(); /* 2.4-a ���ѹ��� */
	void SiftDown(int left); /* 2.4-b SiftDown������left���µ����ѣ�ʹ���г�Ϊ�� */
	void SiftUp(int pos); /* 2.4-c SiftUp������position���ϵ����ѣ�ʹ���г�Ϊ�� */
	bool Remove(int pos, T& node); /* 2.4-d ɾ�������±��Ԫ�� */
	bool Insert(const T& newNode); /* 2.4-e �Ӷ��в�����Ԫ��newNode */
	T& RemoveMax(); /* 2.4-f �ӶѶ�ɾ�����ֵ */
	void visit();
};

/*
 * TODO:2.4-a ���ѹ���
 */
template <class T>
void MaxHeap<T>::BuildHeap()
{
	//start from index'0'
	for (int i = this->CurrentSize / 2 - 1; i >= 0; i--)
	{
		SiftDown(i);
	}
}

template <class T>
bool MaxHeap<T>::isLeaf(int pos) const
{
	if (pos >= CurrentSize) {
		cout << "Խ��" << endl;
		return (false);
	}
	else if (pos > (CurrentSize - 1) / 2)
		return (true);
	else
		return (false);
}

template <class T>
int MaxHeap<T>::leftchild(int pos) const
{
	return (2 * pos + 1);
}

template <class T>
int MaxHeap<T>::rightchild(int pos) const
{
	return (2 * pos + 2);
}

template <class T>
int MaxHeap<T>::parent(int pos) const
{
	return ((pos - 1) / 2);
}

/*
 * TODO:2.4-d ɾ�������±��Ԫ�أ�������Ԫ�ص�ֵ��ֵ��node������
 * ����ֵ˵�������ɾ���ɹ����򷵻�true�����򷵻�false
 * ��Ҫ˵���������ǰ��Ϊ�գ��������ӡcout << "�ն�" << endl;������false
 */

template <class T>
bool MaxHeap<T>::Remove(int pos, T& node)
{
	//�����ǰ��Ϊ�գ��������ӡcout << "�ն�" << endl;������false
	if (this->CurrentSize == 0)
	{
		cout << "�ն�" << endl;
		return false;
	}
	//����Ԫ�ص�ֵ��ֵ��node����
	node = this->heapArray[pos];
	//����ĩβnode����λ�ã���ɾ��
	this->heapArray[pos] = this->heapArray[this->CurrentSize - 1];

	this->CurrentSize--;

	//���½��е���
	if (this->CurrentSize > 1)
	{
		SiftDown(pos);
	}

	return true;
}

/*
 * TODO:2.4 - b SiftDown������left���µ����ѣ�ʹ���г�Ϊ��
 */
template <class T>
void MaxHeap<T>::SiftDown(int left)
{
	//parent node's index
	int parentIndex = left;
	//child's index
	int childIndex = parentIndex * 2 + 1;
	//store parent''s node
	T parentValue = this->heapArray[parentIndex];

	//< heap's current size
	while (childIndex < this->CurrentSize)
	{
		//if right child > left child
		if ((childIndex < this->CurrentSize - 1) && (
			this->heapArray[childIndex + 1] > this->heapArray[childIndex]))
		{
			//point to the right child
			childIndex++;
		}
		//parent node < child node
		if (parentValue < this->heapArray[childIndex])
		{
			//exchange the values
			this->heapArray[parentIndex] = this->heapArray[childIndex];
			//move index
			parentIndex = childIndex;
			childIndex = parentIndex * 2 + 1;
		}
		//if parent node >= child node, then is satisfied with max heap
		else
		{
			//����Ķ����㡣��Ϊ�������ṹ���������ϣ�������㣬���������
			break;
		}
	}
	//current child index's value = former parent index's value
	this->heapArray[parentIndex] = parentValue;
}

/*
 * TODO:2.4-c SiftUp������pos���ϵ����ѣ�ʹ���г�Ϊ��
 */
template <class T>
void MaxHeap<T>::SiftUp(int pos)
{
	//current node's index
	int childIndex = pos;
	//parent node's index (��0��ʼ�洢)
	int parentIndex = (childIndex - 1) / 2;
	//store current node's value
	T childValue = this->heapArray[childIndex];

	while (parentIndex >= 0 && childIndex != 0)
	{
		if (childValue > this->heapArray[parentIndex])
		{
			//exchange
			this->heapArray[childIndex] = this->heapArray[parentIndex];
			
			childIndex = parentIndex;
			parentIndex = (childIndex - 1) / 2;
		}
		else
		{
			break;
		}
	}
	this->heapArray[childIndex] = childValue;
}

/*
 * TODO:2.4-e �Ӷ��в�����Ԫ��newNode, �������ɹ�������true�����򷵻�false��
 * ��Ҫ˵�����������Ԫ�س�������Ԫ��������ֵ���������ӡcout << "����" << endl;������false
 */
template <class T>
bool MaxHeap<T>::Insert(const T& newNode)
{
	//�������Ԫ�س�������Ԫ��������ֵ���������ӡcout << "����" << endl;������false
	if (this->CurrentSize >= this->MaxSize)
	{
		cout << "����" << endl;
		return false;
	}
	//insert a new node
	this->heapArray[this->CurrentSize ++] = newNode;
	//���Ͻ��е���
	if (this->CurrentSize > 1)
	{
		SiftUp(this->CurrentSize - 1);
	}
	
	return true;
}

template <class T>
void MaxHeap<T>::visit()
{
	for (int i = 0; i < CurrentSize; i++)
		cout << heapArray[i] << " ";
	cout << endl;
}

/*
 * TODO:2.4-f �ӶѶ�ɾ�����ֵ. �����ջΪ�նѣ��������ӡcout << "�ն�" << endl;Ȼ���˳������˳���Ϊ1.
 * ���򣬴ӶѶ�ɾ�����ֵ����������Ϊ����ֵ���з��ء�
 */
template <class T>
T& MaxHeap<T>::RemoveMax()
{
	if (this->CurrentSize == 0)
	{
		cout << "�ն�" << endl;
		exit(1);
	}

	T maxNode;
	if (Remove(0, maxNode) == true)
	{
		return maxNode;
	}
}

int main()
{
	/* int a[10] = { 20,12,35,15,10,80,30,17,2,1 }; */
	int count, maxSize; /* ��ʼ������Ԫ�ظ��� */
	cin >> count >> maxSize;
	int iValue;
	int* a = new int[count];
	//start from index'0'
	for (int i = 0; i < count; i++) {
		cin >> iValue;
		a[i] = iValue;
	}

	/* MaxHeap<int> maxheap(a, 10, 20); */
	MaxHeap<int> maxheap(a, count, maxSize);
	int temp;
	maxheap.BuildHeap();
	cout << "�����Ѻ�Ϊ:";
	maxheap.visit();
	cin >> iValue; /* ����һ���������ж����Ƿ��Ƕ��ϵ�Ҷ�ӽڵ� */
	if (maxheap.isLeaf(iValue))
		cout << "λ��" << iValue << "��Ҷ���" << endl;
	else
		cout << "λ��" << iValue << "����Ҷ���" << endl;
	maxheap.visit();
	maxheap.RemoveMax();
	cout << "�Ƴ����ֵ��:";
	maxheap.visit();
	cin >> iValue; /* ����һ���������Ƴ����±����ڵ�Ԫ�� */
	maxheap.Remove(iValue, temp);
	cout << "ɾ���±�Ϊ" << iValue << "��Ԫ��֮��Ϊ:";
	maxheap.visit();
	cout << "ɾ���±�Ϊ" << iValue << "��Ԫ��Ϊ" << temp << endl;
	cin >> iValue; /* ����һ���������Ƴ����±����ڵ�Ԫ�� */
	maxheap.Insert(iValue);
	cout << "����" << iValue << "��Ϊ:";
	maxheap.visit();
	return (0);
}
