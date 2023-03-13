/*�κ�ϰ��1.8-b
    b.	����һ������ͷ���ĵ�����д���������õ��㷨
        Node* Reverse(Node* first)
*/
#include <iostream>
using namespace std;

struct Node {
    Node(int x)
    {
        value = x;
        next = NULL;
    }
    int value;
    Node* next;
};

/*
TODO:�����õ��㷨
 */
Node* Reverse(Node* first)
{
    Node* tempList = first;
    Node* tempNode(0);
    Node* headNode = tempList;

    //insert current node at the first position while traverse
    while (tempList->next != NULL)
    {
        tempNode = tempList->next;
        
        if (tempNode->next != NULL)
        {
            tempList->next = tempNode->next;
            tempNode->next = headNode;
            headNode = tempNode;

            //tempList = tempList->next;
        }
        else
        {
            tempList->next = NULL;
            tempNode->next = headNode;
            headNode = tempNode;
        }
    }

    return headNode;
}

void print(Node* node)
{
    while (NULL != node) {
        cout << node->value << " ";
        node = node->next;
    }
}

int main()
{
    int iNum;
    cin >> iNum;
    Node* a = NULL;
    Node* pTemp(0);

    for (int i = 0; i < iNum; i++) {
        int tmp;
        cin >> tmp;
        if (i == 0) {
            a = new Node(tmp);
            pTemp = a;
        }
        else {
            pTemp->next = new Node(tmp);
            pTemp = pTemp->next;
        }
    }

    cout << "����ǰΪ��";
    print(a);
    cout << endl;
    Node* r = Reverse(a);
    cout << "���ú�Ϊ��";
    print(r);
    cout << endl;
    return 0;
}
