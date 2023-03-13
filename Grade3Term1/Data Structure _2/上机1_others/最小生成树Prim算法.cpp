#include <iostream>
using namespace std;
const int inf = 0x3f3f3f3f;
/*
 * TODO:���帨���ṹ��Element�洢��̱߼�
 * �ýṹ�庬����������Ԫ�ش�����̱ߵ�Ȩֵlowcost���ڽӵ�adjvex
 *
 */
struct Element {
    Element() : lowcost(inf), adjvex(0) {} //��ʼ��Ϊ���ֵ
    Element(int a, int b) : lowcost(a), adjvex(b) {}
    int lowcost, adjvex;
};

/*
 * TODO����С������Prim�㷨
 * ������������ G= ( V, E) ��һ��������ͨ��,��G����С��������Ӧ�����������Ե�
 *          ̰�ķ���Prim�㷨����⡣���������k�Ͷ�Ӧ��Ȩֵ�����¸�ʽ��
 *             cout<<shortEdge[k].adjvex<<"--"<<k<<endl;
 * ����˵����       arc: �洢ͼ�и��ߵĴ��۶�ά���飬int**����
 *                   w: ���㣬int����
 *                   n: �����С��int����
 * ����ֵ˵������
*/
void Prim(int** arc, int w, int n)
{
    int *vertex = new int[n], cnt = 0; 
    Element *edge = new Element[n]; 

    for (int v = 0; v < n; ++v) vertex[v] = 0;
    vertex[w] = 1, ++cnt; 
    for (int v = 0; v < n; ++v) 
        if (arc[w][v] != 0) edge[v] = Element(arc[w][v], w);

    while (cnt < n){ // ���������Ϊn��ѭ��
        int minp = 0; // ��С�ߵ��±�
        for (int v = 0; v < n; ++v) { // Ѱ����С��
            if (vertex[v]) continue; 
            if (vertex[edge[v].adjvex] && edge[v].lowcost < edge[minp].lowcost) // ������ڶ��㼯����С��
                minp = v;
        }
        cout << edge[minp].adjvex << "--" << minp << endl; 
        for (int v = 0; v < n; ++v) {
            if (vertex[v]) continue; 
            if (arc[minp][v] < edge[v].lowcost) 
                edge[v] = Element(arc[minp][v], minp);
        }
        vertex[minp] = 1, ++cnt; // ���붥�㼯
    }
}

int main( )
{
    //����: arc[n][n] �洢ͼ�и��ߵĴ���
    int n;
    cout<<"�������άnxn�����С n:"<<endl;
    cin>>n;
    int **arc;
    arc = new int *[n];
    for (int i = 0; i < n; i++)
    {
        arc[i] = new int[n];
    }
    //ͼ�и��ߵĴ���, 100����������
    cout<<"������ͼ�и��ߵĴ���, 100����������:"<<endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin>>arc[i][j];
        }
    }
    //���: ��С������
    cout<<"��С�������Ľ�Ϊ:"<<endl;
    Prim(arc, 0, n);
    //�ͷ��ڴ棺
    for(int i = 0; i < n; ++i)
        delete[] arc[i];
    delete[] arc;
    return 0;
}
