#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

template<class T>
class BinaryTree;

template<class T>
class BinaryTreeNode
{
private:
	T  element;			                     //����������
	BinaryTreeNode<T>* leftChild;            //�������ӽ��
	BinaryTreeNode<T>* rightChild;           //�����Һ��ӽ��
public:
	friend class BinaryTree<T>;              //������������Ϊ��������Ԫ�࣬�Ա����˽�����ݳ�Ա
	//Ĭ�Ϲ��캯��
	BinaryTreeNode()
	{
		element = 0;
		leftChild = NULL;
		rightChild = NULL;
	}
	//�������ݵĹ��캯��
	BinaryTreeNode(const T& ele)
	{
		element = ele;
		leftChild = NULL;
		rightChild = NULL;
	}
	//��������ֵ�����Һ��ӽ��Ĺ��캯��
	BinaryTreeNode(const T& ele, BinaryTreeNode<T>* l, BinaryTreeNode<T>* r)
	{
		element = ele;
		leftChild = l;
		rightChild = r;
	}
	//���ظý������ӽ��
	BinaryTreeNode<T>* getLeftChild() const
	{
		return leftChild;
	}
	//���ظý����Һ��ӽ��
	BinaryTreeNode<T>* getRightChild() const
	{
		return rightChild;
	}
	//���øý������ӽ��
	void setleftChild(BinaryTreeNode<T>* l)
	{
		leftChild = l;
	}
	//���øý����Һ��ӽ��
	void setrightChild(BinaryTreeNode<T>* r)
	{
		rightChild = r;
	}
	//���ظý�������ֵ
	T getValue(const T& val)
	{
		val = element;
		return val;
	}
	//���øý����������ֵ
	void setValue(const T& val)
	{
		element = val;
	}
	//�жϸý���Ƿ���Ҷ�ӽ�㣬���ǣ��򷵻�true
	bool isLeaf() const
	{
		if (rightChild == NULL && leftChild == NULL)
			return true;
		else
			return false;
	}
	void showEle()
	{
		cout << element << ' ';
	}
};

template <class T>

class BinaryTree
{
public:
	BinaryTreeNode<T>* root;      	           //�����������
	BinaryTree()             		           //Ĭ�Ϲ��캯��
	{
		root = NULL;
	}
	~BinaryTree()                              //��������
	{
		deleteBinaryTree(root);
	}
	bool isEmpty() const 	                   //�ж��������Ƿ�Ϊ����
	{
		if (root == NULL)
			return true;
		else
			return false;
	}
	BinaryTreeNode<T>* Root()                   //���ض������ĸ����
	{
		return root;
	}

	BinaryTreeNode<T>* buildPreAndIn(string prestr, string instr);			  //2.1-a ʵ���������������й�����������㷨
	BinaryTreeNode<T>* buildPostAndIn(string poststr, string instr);		  //2.1-b ʵ���ɺ����������й�����������㷨
	void levelOrder(BinaryTreeNode<T>* root);                                 //2.1-c ������ȱ�����rootΪ����������
	void inOrder(BinaryTreeNode<T>* root);                                    //2.1-d ���������rootΪ����������
	void InOrderWithoutRecusion(BinaryTreeNode<T>* root);                     //2.1-e �ǵݹ����������������������
	void deleteBinaryTree(BinaryTreeNode<T>* root);                           //ɾ����rootΪ����������                                                          

	void visit(BinaryTreeNode<T>* p)										  //����һ����ʵ��
	{
		p->showEle();
	}
	BinaryTreeNode<T>* setTree()
	{
		T ch;
		cin >> ch;
		BinaryTreeNode<T>* treeroot = NULL;
		if (ch == 0 || ch == '0')
			return NULL;
		else
		{
			treeroot = new BinaryTreeNode<T>;
			treeroot->element = ch;
			treeroot->leftChild = setTree();
			treeroot->rightChild = setTree();
			return treeroot;
		}
	}
};

/*
TODO��2.1-a ʵ���������������й�����������㷨
	  return ���ĸ����root
 */
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::buildPreAndIn(string prestr, string instr)
{
	//if preOrder or inOrder string is ""
	if (prestr.length() == 0 || instr.length() == 0)
	{
		return NULL;
	}
	//the first char in preOrder is the root node
	int rootIndex = instr.find(prestr[0]);
	//inOrder string is divided into two parts
	//left child tree and right child tree
	string leftInstr = instr.substr(0, rootIndex);
	string rightInstr = instr.substr(rootIndex + 1);
	//preOrder string is divided according to the length of substring
	string leftPrestr = prestr.substr(1, leftInstr.length());
	string rightPrestr = prestr.substr(prestr.length() - rightInstr.length());

	BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>((char)prestr[0]);

	if (root == NULL)
	{
		root = newNode;
	}

	newNode->setleftChild(buildPreAndIn(leftPrestr, leftInstr));
	newNode->setrightChild(buildPreAndIn(rightPrestr, rightInstr));

	return newNode;
}

/*
TODO��2.1-b ʵ���ɺ����������й�����������㷨
	  return ���ĸ����root
 */
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::buildPostAndIn(string poststr, string instr)
{
	if (poststr.length() == 0 || instr.length() == 0)
	{
		return NULL;
	}
	//the last char of post string is the root node
	int rootIndex = instr.find(poststr[poststr.length() - 1]);

	string leftInstr = instr.substr(0, rootIndex);
	string rightInstr = instr.substr(rootIndex + 1);

	string leftPoststr = poststr.substr(0, leftInstr.length());
	string rightPoststr = poststr.substr(leftInstr.length(), rightInstr.length());

	BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>((char)poststr[poststr.length() - 1]);

	if (root == NULL)
	{
		root = newNode;
	}

	newNode->setleftChild(buildPostAndIn(leftPoststr, leftInstr));
	newNode->setrightChild(buildPostAndIn(rightPoststr, rightInstr));

	return newNode;
}

/*
TODO��2.1-c ������ȱ�����rootΪ����������
 */
template<class T>
void BinaryTree<T>::levelOrder(BinaryTreeNode<T>* root)
{
	if (root == NULL)
	{
		return;
	}
	//initialize an assistant queue
	queue<BinaryTreeNode<T>*> treeNodeQueue;
	//a pointer to point to current node
	BinaryTreeNode<T>* currentNode = root;
	//enqueue
	treeNodeQueue.push(currentNode);
	//loop if the queue is not empty
	while (!treeNodeQueue.empty())
	{
		//dequeue and visit
		currentNode = treeNodeQueue.front();
		treeNodeQueue.pop();

		this->visit(currentNode);

		//recursion: left child and right child
		if (currentNode->getLeftChild() != NULL)
		{
			treeNodeQueue.push(currentNode->getLeftChild());
		}
		if (currentNode->getRightChild() != NULL)
		{
			treeNodeQueue.push(currentNode->getRightChild());
		}
	}

}

/*
TODO��2.1-d �ݹ����������rootΪ����������
 */
template<class T>
void BinaryTree<T>::inOrder(BinaryTreeNode<T>* root)
{
	if (root != NULL)
	{
		inOrder(root->getLeftChild());
		this->visit(root);
		inOrder(root->getRightChild());
	}
}

/*
TODO��2.1-e �ǵݹ����������������������
 */
template<class T>
void BinaryTree<T>::InOrderWithoutRecusion(BinaryTreeNode<T>* root)
{
	if (root == NULL)
	{
		return;
	}
	//initialize an assistant stack
	stack<BinaryTreeNode<T>*> treeNodeStack;
	//a pointer points to current node
	BinaryTreeNode<T>* currentNode = root;

	while (!treeNodeStack.empty() || currentNode != NULL)
	{
		if (currentNode != NULL)
		{
			//push current node into stack
			treeNodeStack.push(currentNode);
			//turn to its left child 
			currentNode = currentNode->getLeftChild();
		}
		//left sub tree has been visited
		else
		{
			currentNode = treeNodeStack.top();
			treeNodeStack.pop();

			this->visit(currentNode);
			//turn to its right child
			currentNode = currentNode->getRightChild();
		}
	}
}

template<class T>

void BinaryTree<T>::deleteBinaryTree(BinaryTreeNode<T>* root)
{
	if (root == NULL)
		return;
	BinaryTreeNode<T>* temp = NULL;
	queue<BinaryTreeNode<T>*> node_queue;
	if (root->leftChild)
		node_queue.push(root->leftChild);
	if (root->rightChild)
		node_queue.push(root->rightChild);
	delete root;
	while (!node_queue.empty())
	{
		temp = node_queue.front();
		node_queue.pop();
		if (temp->leftChild != NULL)
			node_queue.push(temp->leftChild);
		if (temp->rightChild != NULL)
			node_queue.push(temp->rightChild);
		delete temp;
	}
	root = NULL;
}

int main()
{
	BinaryTree<char> test;
	BinaryTreeNode<char>* root = NULL, * root2 = NULL;
	string prestr, instr, poststr;
	getline(cin, prestr);
	getline(cin, instr);
	getline(cin, poststr);
	root = test.buildPreAndIn(prestr, instr);	//2.1-a ʵ���������������й�����������㷨
	root2 = test.buildPostAndIn(poststr, instr);//2.1-b ʵ���ɺ����������й�����������㷨

	cout << "PreAndIn:" << endl;
	cout << "inOrder: ";
	test.inOrder(root);
	cout << endl;

	cout << "levelOrder: ";
	test.levelOrder(root);
	cout << endl;

	cout << "InOrderWithoutRecusion: ";
	test.InOrderWithoutRecusion(root);
	cout << endl;

	cout << "PostAndIn:" << endl;
	cout << "inOrder: ";
	test.inOrder(root2);
	cout << endl;

	cout << "levelOrder: ";
	test.levelOrder(root2);
	cout << endl;

	cout << "InOrderWithoutRecusion: ";
	test.InOrderWithoutRecusion(root2);
	cout << endl;
	return 0;
}
