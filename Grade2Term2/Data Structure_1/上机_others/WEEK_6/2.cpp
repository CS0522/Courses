#include <stdio.h>
//#include <malloc.h>
#include <stdlib.h>
#include <stack>
#define MaxSize 100
using namespace std;
typedef char ElemType;

/*
TODO:定义一个结构体,成员：
  ElemType类型变量data，存储数据元素值；
  该结构体指针lchild，指向左孩子结点；
  该结构体指针rchild，指向右孩子结点
*/
typedef struct node
{
    char data;
    node* lchild;
    node* rchild;
    node()
    {
        lchild=NULL;
        rchild=NULL;
        data='\0';
    }

} BTNode;

/*
TODO:完成利用特定格式字符串生成二叉树的功能.
功能描述:利用一个字符串生成二叉树树并赋值给由链式存储结构的二叉树的指针.
    定义指针数组作为顺序栈用于辅助,循环判断字符串中每个字符,遇到'\0'退出,
      如果遇到左括号，代表左子结点开始，则当前结点进栈,
      如果遇到右括号，代表结束了孩子结点排列，退栈，
      如果遇到','，代表右子结点开始，栈顶结点的右子结点，
      其他字符代表普通具体结点值，结点指针分配相应空间,并赋值结点值,所有孩子结点赋空,
      如果树空，则结点赋给树指针，否则将其作为栈顶结点的一个孩子，根据左右子结点标识赋给对应子结点指针.
参数说明:b-要赋值生成的二叉树的指针引用,str-目标字符串的指针.
返回值说明:无.
举例说明:如果字符串是"A(B,C)",则代表树A是根,A有左右两个孩子B,C
        如果字符串是"A(B(C)",则代表树A是根,A有一个左孩子B,B有一个左孩子C
*/
void CreateBTree(BTNode * &b,char *str)    //创建二叉树
{
    stack<BTNode*> st;
    BTNode *p;
    int i=0,k;
    b=NULL;
    while(str[i]!='\0')
    {
        if(str[i]=='(')
        {
            st.push(p);
            k=1;
        }
        else if(str[i]==')') st.pop();
        else if(str[i]==',') k=2;
        else
        {
            p=new BTNode;
            p->data=str[i];
            if(b==NULL) b=p;
            else
            {
                if(k==1) st.top()->lchild=p;
                else if(k==2) st.top()->rchild=p;
            }
        }
        i++;
    }
}

/*
TODO:完成销毁二叉树的功能.
功能描述:利用递归方式释放二叉树每一个结点所分配的空间.
参数说明:b-目标二叉树的指针引用.
返回值说明:无.
*/
void DestroyBTree(BTNode *&b)    //销毁二叉树
{
    if(b==NULL) return;
    DestroyBTree(b->lchild);
    DestroyBTree(b->rchild);
    delete b;
}

BTNode *LchildNode(BTNode *p)
{
    return p->lchild;
}
BTNode *RchildNode(BTNode *p)
{
    return p->rchild;
}

/*
TODO:完成求二叉树的高度的功能.
功能描述:利用递归方式取左右孩子个数最大值.
  如果结点b为空，如果为空，则返回0
  如果结点b不为空，调用函数BTHeight()，传入b左右子结点，求左右子树的高度
  取左右子树高度的最大值加1进行返回
参数说明:b-目标二叉树的指针.
返回值说明:二叉树高度数值,当树为空时,返回0.
*/
int BTHeight(BTNode *b)
{
    if(b==NULL) return 0;
    return fmax(BTHeight(b->lchild)+1,BTHeight(b->rchild)+1);
}

int main()
{
    BTNode *b;
        char str[40] = "";
        scanf("%s", str);
        str[39] = '\0';

        /*
        TODO:调用函数CreateBTree()，传入参数b、str，创建二叉树
        */
    
        CreateBTree(b, str);


        printf("二叉树b的高度:%d\n",BTHeight(b));

        /*
        TODO:调用函数DestroyBTree()，传入参数b，销毁二叉树
        */
    
        DestroyBTree(b);
        return 0;
}

