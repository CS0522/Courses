//开放地址法构造的哈希表的运算算法
#include <iostream>
using namespace std;

#define MaxSize 100         //定义最大哈希表长度
#define NULLKEY -1          //定义空关键字值
#define DELKEY -2           //定义被删关键字值
typedef int KeyType;        //关键字类型

/*
TODO:定义一个哈希表开放结构体,第一个为KeyType类型变量key存关键字域,
第二个为int型变量count存探测次数域
*/
typedef struct
{
    KeyType key;
    int count;
} HashTable;                //哈希表类型

/*
TODO:完成将关键字k插入到哈希表中的功能.
函数功能:计算哈希函数值,判断哈希表状态进行插入或者循环探测插入.
参数说明:ha-哈希表,n-总关键字数,m-基数,p-计算哈希分母,k-插入关键字.
返回值说明:无.
*/
void InsertHT(HashTable ha[], int &n, int m, int p, KeyType k)  //将关键字k插入到哈希表中
{
    int i = 1, adr = k % p; 
    while (ha[adr].key != NULLKEY) ++i, adr = (adr + 1) % m; 
    ha[adr].key = k, ha[adr].count = i; 
}

/*
TODO:完成创建哈希表的功能.
函数功能:循环初始化哈希表元素值然后循环调用函数插入关键字.
参数说明:ha-哈希表,n-总关键字数,m-基数,p-计算哈希分母,keys-关键字组,n1-初始关键字数.
返回值说明:无.
*/
void CreateHT(HashTable ha[], int &n, int m, int p, KeyType keys[], int n1)  //创建哈希表
{
    for (int i = 0; i < m; ++i) ha[i].key = NULLKEY; 
    for (int i = 0; i < n1; ++i) InsertHT(ha, n, m, p, keys[i]); 
}
void SearchHT(HashTable ha[], int m, int p, KeyType k)  //在哈希表中查找关键字k
{
    
    int i = 1, adr = k % p;
    while (ha[adr].key != NULLKEY && ha[adr].key != k) ++i, adr = (adr + 1) % m;
    if (ha[adr].key == k)           //查找成功
        cout << "查找成功：关键字" << k << "，比较" << i << "次" << endl;
    else                        //查找失败
        cout << "查找失败：关键字" << k << "，比较" << i << "次" << endl;
}

/*
TODO:完成删除哈希表中关键字k的功能.
函数功能:计算哈希函数值,循环探测查找,根据查找结果进行删除并返回成功或者返回失败，把删除的位置的关键字赋值为DELKEY.
参数说明:ha-哈希表,n-总关键字数,m-基数,p-计算哈希分母,k-目标关键字.
返回值说明:查找失败返回false,查找删除成功返回true.
*/
bool DeleteHT(HashTable ha[], int &n, int m, int p, KeyType k)  //删除哈希表中关键字k
{
    int i = 1, adr = k % p;
    while (ha[adr].key != NULLKEY && ha[adr].key != k) ++i, adr = (adr + 1) % m;
    if (ha[adr].key == NULLKEY) return false; 
    ha[adr].key = DELKEY; 
    return true;
}


void DispHT(HashTable ha[], int n, int m, int p)  //输出哈希表
{
    int i, j;
    cout << "哈希表:" << endl;
    cout << "哈希表地址:    ";
    for (i = 0; i < m; i++)
        cout << i << "  ";
    cout << endl;
    cout << "哈希表关键字: ";
    for (i = 0; i < m; i++)
        if (ha[i].key == NULLKEY)
            cout << "   ";      //输出3个空格
        else
            cout << ha[i].key << ' ';
    cout << endl;
    cout << "探测次数:       ";
    for (i = 0; i < m; i++)
        if (ha[i].key == NULLKEY)
            cout << "   ";      //输出3个空格
        else
            cout << ha[i].count << "   ";
    cout << endl;
}

int main()
{
    int keys[] = { 16,74,60,43,54,90,46,31,29,88,77 };
    int n, m = 13, p = 13, k;
    HashTable ha[MaxSize];
    cin >> k;
    CreateHT(ha, n, m, p, keys, 11);
    cout << "显示哈希表:" << endl;
    DispHT(ha, n, m, p);
    if (DeleteHT(ha, n, m, p, k)) {
        cout << "\n删除之后:\n";
        DispHT(ha, n, m, p);
    }
    else {
        cout << "\n删除失败!\n";
    }

    return 0;
}
