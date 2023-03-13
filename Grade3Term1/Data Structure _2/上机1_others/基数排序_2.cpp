#include <iostream>
#include <math.h>

using namespace std;

// �����ģ��
template <class ElemType>
struct Node
{
    // ���ݳ�Ա:
    ElemType data;				// ������
    Node<ElemType>* next;		// ָ����

// ���캯��ģ��:
    Node();						// �޲����Ĺ��캯��ģ��
    Node(ElemType item, Node<ElemType>* link = NULL);	// ��֪����Ԫ��ֵ��ָ�뽨���ṹ
};

// �����ģ���ʵ�ֲ���
template<class ElemType>
Node<ElemType>::Node()
// �������������ָ����Ϊ�յĽ��
{
    next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType>* link)
// �������������һ��������Ϊitem��ָ����Ϊlink�Ľ��
{
    data = item;
    next = link;
}

// ����������ģ��
template <class ElemType>
class LinkList
{
protected:
    //  ����ʵ�ֵ����ݳ�Ա:
    Node<ElemType>* head;				// ͷ���ָ��
    mutable int curPosition;			// ��ǰλ�õ����
    mutable Node<ElemType>* curPtr;	// ָ��ǰλ�õ�ָ��
    int count;							// Ԫ�ظ���

// ��������ģ��:
    Node<ElemType>* GetElemPtr(int position) const;	// ����ָ���position������ָ��

public:
    //  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
    LinkList();							// �޲����Ĺ��캯��ģ��
    virtual ~LinkList();				// ��������ģ��
    int Length() const;				    // �����Ա���
    bool Empty() const;					// �ж����Ա��Ƿ�Ϊ��
    void Clear();						// �����Ա����
    void Traverse(void (*visit)(const ElemType&)) const;	// �������Ա�
    int GetCurPosition() const;								// ���ص�ǰλ��
    bool GetElem(int position, ElemType& e) const;			// ��ָ��λ�õ�Ԫ��
    bool SetElem(int position, const ElemType& e);			// ����ָ��λ�õ�Ԫ��ֵ
    bool Delete(int position, ElemType& e);					// ɾ��Ԫ��
    bool Insert(int position, const ElemType& e);			// ����Ԫ��
    LinkList(const LinkList<ElemType>& copy);				// ���ƹ��캯��ģ��
    LinkList<ElemType>& operator =(const LinkList<ElemType>& copy); // ���ظ�ֵ�����
};


// ������ģ���ʵ�ֲ���

template<class ElemType>
Node<ElemType>* LinkList<ElemType>::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
    if (curPosition > position)
    {	// ��ǰλ����������λ��֮��,ֻ�ܴӱ�ͷ��ʼ����
        curPosition = 0;
        curPtr = head;
    }

    for (; curPosition < position; curPosition++)
        curPtr = curPtr->next;			// ����λ��position

    return curPtr;
}

template <class ElemType>
LinkList<ElemType>::LinkList()
// �������������һ��������
{
    head = new Node<ElemType>;		// ����ͷָ��
    curPtr = head;	curPosition = 0;// ��ʼ����ǰλ��
    count = 0;						// ��ʼ��Ԫ�ظ���
}

template <class ElemType>
LinkList<ElemType>::~LinkList()
// ����������������Ա�
{
    Clear();			// ������Ա�
    delete head;		// �ͷ�ͷ�����ָ�ռ�
}

template <class ElemType>
int LinkList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
    return count;
}

template <class ElemType>
bool LinkList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
    return head->next == NULL;
}

template <class ElemType>
void LinkList<ElemType>::Clear()
// ���������������Ա�
{

    ElemType tmpElem;	// ��ʱԪ��ֵ
    while (!Empty())
    {	// ���Ա�ǿգ���ɾ����1��Ԫ��
        Delete(1, tmpElem);
    }
}

template <class ElemType>
void LinkList<ElemType>::Traverse(void (*visit)(const ElemType&)) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
    for (Node<ElemType>* tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
    {	// ��tmpPtr����ָ��ÿ��Ԫ��
        (*visit)(tmpPtr->data);	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
    }
}

template <class ElemType>
int LinkList<ElemType>::GetCurPosition() const
// ������������ص�ǰλ��
{
    return curPosition;
}

template <class ElemType>
bool LinkList<ElemType>::GetElem(int position, ElemType& e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ������true,
//	���򷵻�false
{
    if (position < 1 || position > Length())
    {	// position��Χ��
        return false;					// Ԫ�ز�����
    }
    else
    {	// position�Ϸ�
        Node<ElemType>* tmpPtr;
        tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
        e = tmpPtr->data;				// ��e���ص�position��Ԫ�ص�ֵ
        return true;
    }
}

template <class ElemType>
bool LinkList<ElemType>::SetElem(int position, const ElemType& e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ����true,���򷵻�false
{
    if (position < 1 || position > Length())
    {	// position��Χ��
        return false;
    }
    else
    {	// position�Ϸ�
        Node<ElemType>* tmpPtr;
        tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
        tmpPtr->data = e;				// ���õ�position��Ԫ�ص�ֵ
        return true;
    }
}

template <class ElemType>
bool LinkList<ElemType>::Delete(int position, ElemType& e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ����e������ֵ, position��ȡֵ
//	��ΧΪ1��position��Length(),position�Ϸ�ʱ����true,���򷵻�false
{
    if (position < 1 || position > Length())
    {	// position��Χ��
        return false;
    }
    else
    {	// position�Ϸ�
        Node<ElemType>* tmpPtr;
        tmpPtr = GetElemPtr(position - 1);		// ȡ��ָ���position-1������ָ��
        Node<ElemType>* nextPtr = tmpPtr->next;	// nextPtrΪtmpPtr�ĺ��
        tmpPtr->next = nextPtr->next;			// ɾ�����
        e = nextPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ
        if (position == Length())
        {	// ɾ��β���,��ǰ����Ϊͷ���
            curPosition = 0;					// ���õ�ǰλ�õ����
            curPtr = head;						// ����ָ��ǰλ�õ�ָ��
        }
        else
        {	// ɾ����β���,��ǰ����Ϊ��position�����
            curPosition = position;				// ���õ�ǰλ�õ����
            curPtr = tmpPtr->next;				// ����ָ��ǰλ�õ�ָ��
        }
        count--;								// ɾ���ɹ���Ԫ�ظ�����1
        delete nextPtr;							// �ͷű�ɾ���
        return true;
    }
}

template <class ElemType>
bool LinkList<ElemType>::Insert(int position, const ElemType& e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e, position��ȡֵ��Χ
//	Ϊ1��position��Length()+1,position�Ϸ�ʱ����true, ���򷵻�false
{
    if (position < 1 || position > Length() + 1)
    {	// position��Χ��
        return false;						// λ�ò��Ϸ�
    }
    else
    {	// position�Ϸ�
        Node<ElemType>* tmpPtr;
        tmpPtr = GetElemPtr(position - 1);	// ȡ��ָ���position-1������ָ��
        Node<ElemType>* newPtr;
        newPtr = new Node<ElemType>(e, tmpPtr->next);// �����½��
        tmpPtr->next = newPtr;				// ��tmpPtr���뵽������
        curPosition = position;				// ���õ�ǰλ�õ����
        curPtr = newPtr;					// ����ָ��ǰλ�õ�ָ��
        count++;							// ����ɹ���Ԫ�ظ�����1
        return true;
    }
}

template <class ElemType>
LinkList<ElemType>::LinkList(const LinkList<ElemType>& copy)
// ��������������Ա�copy���������Ա������ƹ��캯��ģ��
{
    ElemType e;

    head = new Node<ElemType>;		// ����ͷָ��
    curPtr = head;	curPosition = 0;// ��ʼ����ǰλ��
    count = 0;						// ��ʼ��Ԫ�ظ���

    for (int pos = 1; pos <= copy.Length(); pos++)
    {	// ��������Ԫ��
        copy.GetElem(pos, e);			// ȡ����pos��Ԫ��
        Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
    }
}

template <class ElemType>
LinkList<ElemType>& LinkList<ElemType>::operator =(const LinkList<ElemType>& copy)
// ��������������Ա�copy��ֵ����ǰ���Ա������ظ�ֵ�����
{
    if (&copy != this)
    {
        ElemType e;
        Clear();							// ��յ�ǰ���Ա�

        for (int pos = 1; pos <= copy.Length(); pos++)
        {	// ��������Ԫ��
            copy.GetElem(pos, e);			// ȡ����pos��Ԫ��
            Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
        }
    }
    return *this;
}

/*
TODO:��ɷ������Ա��������Ĺ���.
��������:���ÿ⺯��pow��ֵ����ʼֵ����ѭ��,�������λ��ֵ�����ú��������Ա����.
����˵��:lem-Ԫ������,n-Ԫ�ظ���,r-����,d-�ؼ���λ��,i-ѭ������,list-���Ա�����
����ֵ˵��:��
*/
template <class ElemType>
void Distribute(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[])
// ��ʼ����: rΪ����,dΪ�ؼ���λ��,list[0 .. r - 1]Ϊ����������Ա�����
// �������: ���е�i�˷���
{
    ElemType temp;
    for (int j = 0; j < n; j++)
    {
        temp = elem[j];
        for (int k = 1; k < i; k++)
        {
            temp = elem[j] / r;
        }
        temp = temp % r;
        list[temp].Insert(list[temp].GetCurPosition() + 1, elem[j]);
    }
}

/*
TODO:��ɷ������Ա������ռ��Ĺ���.
��������:ѭ���������з���,�����Ա���ʱ���ú�������ɾ��,���¸�ֵԪ��.
����˵��:lem-Ԫ������,n-Ԫ�ظ���,r-����,d-�ؼ���λ��,i-ѭ������,list-���Ա�����
����ֵ˵��:��
*/
template <class ElemType>
void Colect(ElemType elem[], int n, int r, int d, int i, LinkList<ElemType> list[])
// ��ʼ����: rΪ����,dΪ�ؼ���λ��,list[0 .. r - 1]Ϊ����������Ա�����
// �������: ���е�i���ռ�
{
    int j = 0;
    int ith = 0;
    for (ith = 0; ith < n; NULL)
    {
        if (!list[j].Empty())
        {
            while (!list[j].Empty())
            {
                list[j].Delete(1, elem[ith]);
                ith++;
            }
        }
        else if(j < r)
        {
            j++;
        }
    }
}

/*
TODO:��ɶ�elem���л�������Ĺ���.
��������:�������ڴ洢����������Ա����鲢������Ӧ�ռ�,
ѭ���������ú������з�����ռ�,����ͷ����Ա�ռ�.
����˵��:lem-Ԫ������,n-Ԫ�ظ���,r-����,d-�ؼ���λ��
����ֵ˵��:��
*/
template <class ElemType>
void RadixSort(ElemType elem[], int n, int r, int d)
// ��ʼ����: rΪ����,dΪ�ؼ���λ��
// �������: ��elem���л�������
{
    LinkList<ElemType>* list = new LinkList<ElemType>[r];
    for (int i = 1; i <= d; i++)
    {
        Distribute(elem, n, r, d, i, list);
        Colect(elem, n, r, d, i, list);
    }
}

template<class ElemType>
void Show(ElemType elem[], int n)
// �������: ��ʾ����elem�ĸ�����Ԫ��ֵ
{
    for (int i = 0; i < n; i++)
        cout << elem[i] << "  ";	// ��ʾ����elem
    cout << endl;					// ����
}

int main(void)
{
    int a[6];

    for (int i = 0; i < 6; i++) {
        cin >> a[i];
    }
    int n = 6, r = 10, d = 2;
    cout << "����ǰ:";
    // TODO: ���ú�����ʾ����Ԫ��ֵ,Ȼ����л�����������
    Show(a, 6);
    RadixSort(a, n, r, d);
    cout << "�����:";
    // TODO: ���ú�����ʾ����Ԫ��ֵ
    Show(a, 6);
    return 0;						// ����ֵ0, ���ز���ϵͳ
}