/*2.3  ����������

	void createSearchTree();									//2.3-a ��������������
	BinarySearchTreeNode<T>* search(BinarySearchTreeNode<T>* root, T x);
																//2.3-b �����������Ĳ���ֵΪx�Ľ�㣬�����ش˽��
	void insertNode(const T& value);							//2.3-c �����������Ĳ���x��
	void deleteByCopying(BinarySearchTreeNode<T>*& node);		//2.3-d ����ɾ��

*/

#include <iostream>
using namespace std;

template <class T>
class BinarySearchTree;

template <class T>
class BinarySearchTreeNode {
	friend class BinarySearchTree<T>;

private:
	T element;
	BinarySearchTreeNode<T>* leftChild;
	BinarySearchTreeNode<T>* rightChild;

public:
	BinarySearchTreeNode()
	{

	}
	BinarySearchTreeNode(const T& ele)
	{
		element = ele;
		leftChild = NULL;
		rightChild = NULL;
	}
	BinarySearchTreeNode(const T& ele, BinarySearchTreeNode<T>* l, BinarySearchTreeNode<T>* r)
	{
		element = ele;
		leftChild = l;
		rightChild = r;
	}
	BinarySearchTreeNode<T>* getLeftChild() const
	{
		return leftChild;
	}
	BinarySearchTreeNode<T>* getRightChild() const
	{
		return rightChild;
	}
	void setLeftChild(BinarySearchTreeNode<T>* l)
	{
		leftChild = l;
	}
	void setRightChild(BinarySearchTreeNode<T>* r)
	{
		rightChild = r;
	}
	T getValue() const
	{
		return element;
	}
	void setValue(const T& val)
	{
		element = val;
	}
	bool isLeaf() const
	{
		if (leftChild == NULL && rightChild == NULL)
			return true;
		return false;
	}
};

template <class T>
class BinarySearchTree {
private:
	BinarySearchTreeNode<T>* root;

public:
	BinarySearchTree()
	{
		root = NULL;
	}
	BinarySearchTree(BinarySearchTreeNode<T>*& r)
	{
		root = r;
	}
	void createSearchTree(); //2.3-a ��������������
	void visit(BinarySearchTreeNode<T>* current);
	BinarySearchTreeNode<T>* search(BinarySearchTreeNode<T>* root, T x);
	//2.3-b �����������Ĳ���ֵΪx�Ľ�㣬�����ش˽��
	void insertNode(const T& value); //2.3-c �����������Ĳ���x��
	void deleteByCopying(BinarySearchTreeNode<T>*& node); //2.3-d ����ɾ��
	void inOrder(BinarySearchTreeNode<T>* root);
	void setRoot(BinarySearchTreeNode<T>* r);
	BinarySearchTreeNode<T>* getRoot();
	BinarySearchTreeNode<T>* getParent(BinarySearchTreeNode<T>* root, BinarySearchTreeNode<T>* current) const;
};

/*
�������ܣ�2.3-a ��������������
*/
template <class T>
void BinarySearchTree<T>::createSearchTree()
{
	int a;
	cout << "����int�ͣ���0Ϊ����" << endl;
	cin >> a;
	while (a != 0) {
		//TODO:������a���뵽�����������С�������������������
		insertNode(a);
		cin >> a;
	}
}

template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getRoot()
{
	return root;
}

template <class T>
void BinarySearchTree<T>::setRoot(BinarySearchTreeNode<T>* r)
{
	this->root = r;
}
template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::getParent(BinarySearchTreeNode<T>* root, BinarySearchTreeNode<T>* current) const
{
	if (root != NULL) {
		if (root == current) {
			cout << "�ýڵ�Ϊ����㣬�޸����" << endl;
			return NULL;
		}
		else if (root->leftChild == current || root->rightChild == current) {
			return root;
		}
		else {
			getParent(root->leftChild, current);
			getParent(root->rightChild, current);
		}
	}
}

template <class T>
void BinarySearchTree<T>::visit(BinarySearchTreeNode<T>* current)
{
	cout << current->element << " ";
}

/*
TODO:2.3-b �����������Ĳ���ֵΪx�Ľ�㣬�����ش˽��
 */
template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::search(BinarySearchTreeNode<T>* root, T x)
{
	//if binary tree is NULL
	if (root == NULL)
	{
		return NULL;
	}
	//point to the current node
	BinarySearchTreeNode<T>* currentNode = root;
	//while loop to traverse and quit if '==' or quit if not found 'x'
	while ((currentNode != NULL) && (currentNode->getValue() != x))
	{
		//smaller: go to left
		if (x < currentNode->getValue())
		{
			currentNode = currentNode->getLeftChild();
		}
		//larger: go to right
		else
		{
			currentNode = currentNode->getRightChild();
		}
	}

	return currentNode;
}

/*
TODO:2.3-c �����������Ĳ���,��value�����ȥ
 */
template <class T>
void BinarySearchTree<T>::insertNode(const T& value)
{
	//new node
	BinarySearchTreeNode<T>* newNode = new BinarySearchTreeNode<T>(value);
	//point to the current node
	BinarySearchTreeNode<T>* currentNode = this->getRoot();
	//point to the previous node
	BinarySearchTreeNode<T>* previousNode = NULL;

	while (currentNode != NULL)
	{
		//move previous node
		previousNode = currentNode;
		if (value < currentNode->getValue())
		{
			currentNode = currentNode->getLeftChild();
		}
		else
		{
			currentNode = currentNode->getRightChild();
		}
	}
	//when quit the while loop, it means that:
	//1. root is NULL.
	//2. currentNode is the position that 'value' should to be
	if (root == NULL)
	{
		root = newNode;
	}
	else if (previousNode != NULL && (value < previousNode->getValue()))
	{
		previousNode->setLeftChild(newNode);
	}
	else if (previousNode != NULL && (value >= previousNode->getValue()))
	{
		previousNode->setRightChild(newNode);
	}
}

/*
TODO:2.3-d ����ɾ��
*/
template <class T>
void BinarySearchTree<T>::deleteByCopying(BinarySearchTreeNode<T>*& node)
{
	//temp node 
	BinarySearchTreeNode<T>* tempNode = node;
	//previous node
	BinarySearchTreeNode<T>* previousNode = this->getParent(this->getRoot(), node);
	//3 cases:
	//1. only left child exists (include the case that is a leaf node)
	if (node->getRightChild() == NULL)
	{
		//set previous node's child:
		node->getValue() < previousNode->getValue() ?
			//node is left child:
			previousNode->setLeftChild(node->getLeftChild()) :
			//node is right child:
			previousNode->setRightChild(node->getLeftChild());
	}
	//2. only right child exists (include the case that is a leaf node)
	else if (node->getLeftChild() == NULL)
	{
		//set previous node's child:
		node->getValue() < previousNode->getValue() ?
			//node is left child:
			previousNode->setLeftChild(node->getRightChild()) :
			//node is right child:
			previousNode->setRightChild(node->getRightChild());
	}
	//3. both children exist
	else
	{
		//to search to largest node in the left sub tree
		previousNode = tempNode;
		tempNode = tempNode->getRightChild();

		while (tempNode->getRightChild() != NULL)
		{
			previousNode = tempNode;
			tempNode = tempNode->getRightChild();
		}
		//break when tempNode's right child == NULL, meaning tempNode is largest node in left
		//copy: 
		node->setValue(tempNode->getValue());
		//if previous node is just the target node that need to be deleted
		//���ڵ�պ���Ҫɾ���Ľ��ʱ��
		if (previousNode == node)
		{
			previousNode->setLeftChild(tempNode->getLeftChild());
		}
		else
		{
			previousNode->setRightChild(tempNode->getLeftChild());
		}
	}
	//delete the tempNode
	delete tempNode;
}

template <class T>
void BinarySearchTree<T>::inOrder(BinarySearchTreeNode<T>* root)
{
	if (root != NULL) {
		inOrder(root->leftChild);
		visit(root);
		inOrder(root->rightChild);
	}
}

int main()
{
	BinarySearchTreeNode<int>* tmp1, * tmp2;
	BinarySearchTree<int> st;
	st.createSearchTree();
	tmp1 = st.getRoot();
	st.inOrder(tmp1);
	cout << endl;
	int temp;
	cin >> temp;
	st.insertNode(temp);
	st.inOrder(tmp1);
	cout << endl;

	cout << "����һ����Ҫ���ҵ�ֵ" << endl;
	cin >> temp; // ����һ����Ҫ���ҵ�ֵ
	tmp2 = st.search(tmp1, temp); //�ҵ�ֵtemp ���ؽ�㣬�Ҳ�������NULL
	if (tmp2 != NULL) {
		cout << "���ҵ�ֵΪ: " << tmp2->getValue() << endl;
		st.deleteByCopying(tmp2);
		st.inOrder(tmp1);
	}
	else
		cout << "������ֵ" << temp;
	return 0;
}
