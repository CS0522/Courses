#include <iostream>
using namespace std;

template <class T>
class Edge {
public:
    int start, end, weight;
    Edge()
    {
        start = 0;
        end = 0;
        weight = 0;
    }
    Edge(int st, int en, int w)
    {
        start = st;
        end = en;
        weight = w;
    }
    void showEdge()
    {
        cout << "start: " << start << " end:" << end << " weight:" << weight << endl;
    }
};

template <class T>
class Graph {
public:
    int vertexNum; //ͼ�Ķ�����Ŀ
    int edgeNum; //ͼ�ı���Ŀ
    int* Mark;
    Graph()
    {
        vertexNum = 0;
        edgeNum = 0;
        Mark = NULL;
    }
    Graph(int verticesNum)
    {
        vertexNum = verticesNum;
        edgeNum = 0;
        Mark = new int[vertexNum];
        for (int i = 0; i < vertexNum; i++)
            Mark[i] = 0;
    }
    ~Graph()
    {
        delete[] Mark;
    }
    virtual Edge<T> FirstEdge(int oneVertex) = 0;
    virtual Edge<T> NextEdge(Edge<T> oneEdge) = 0;
    int VerticesNum() { return vertexNum; }
    int EdgesNum() { return edgeNum; }
    int StartVertex(Edge<T> oneEdge) { return oneEdge.start; }
    int EndVertex(Edge<T> oneEdge) { return oneEdge.end; }
    int Weight(Edge<T> oneEdge) { return oneEdge.weight; }
    virtual void setEdge(int start, int end, int weight) = 0;
    virtual void delEdge(int start, int end) = 0;
};

template <class T>
class AdjGraph : public Graph<T> {
private:
    int** matrix; //ָ���ڽӾ����ָ��
public:
    AdjGraph(int verticesNum)
    {
        int i, j;
        this->vertexNum = verticesNum;
        this->edgeNum = 0;
        this->Mark = new int[verticesNum];
        for (int i = 0; i < verticesNum; i++)
            this->Mark[i] = 0;
        matrix = (int**)new int*[this->vertexNum]; //����vertexNum��С��matrix����
        for (i = 0; i < this->vertexNum; i++) //����matrix�����еĴ洢�ռ�
            matrix[i] = new int[this->vertexNum];
        for (i = 0; i < this->vertexNum; i++) //��ʼ���ڽӾ����Ԫ��
            for (j = 0; j < this->vertexNum; j++)
                matrix[i][j] = 0;
    }
    ~AdjGraph()
    {
        for (int i = 0; i < this->vertexNum; i++) //�ͷ�ÿ��matrix[i]����Ŀռ�
            delete[] matrix[i];
        delete[] matrix; //�ͷ�matrixָ��ָ��Ŀռ�
    }

    bool isEdge(Edge<T> oneEdge)
    {
        if (oneEdge.weight > 0 && oneEdge.end >= 0)
            return true;
        else
            return false;
    }
    /*
    TODO:b. �����붥��oneVertex������ĵ�һ����
    ����ֵ˵�������ҵ����򷵻��ҵ��ı���Ϣ�����򣬷��صı�����Ϣ�����ΪoneVertex���յ��Ȩ�ؾ�Ϊ0��
    */
    Edge<T> FirstEdge(int oneVertex)
    {
        for (int j = 0; j < this->vertexNum; j++) 
            if (matrix[oneVertex][j] != 0) 
                return Edge<T>(oneVertex, j, matrix[oneVertex][j]);
        return Edge<T>(oneVertex, 0, 0); 
    }

    /*
    TODO:c. 
    ����ֵ˵�������ҵ����򷵻��ҵ��ı���Ϣ�����򣬷��صı�����Ϣ�����ΪoneEdge����㣬�յ��Ȩ�ؾ�Ϊ0��
    */
    Edge<T> NextEdge(Edge<T> oneEdge)
    {
        for (int j = oneEdge.end + 1; j < this->vertexNum; j++) 
            if (matrix[oneEdge.start][j] != 0) 
                return Edge<T>(oneEdge.start, j, matrix[oneEdge.start][j]);
        return Edge<T>(oneEdge.start, 0, 0); 
    }
    /*
    TODO:a. 
    ����˵����start:Ϊ�ߵ���㣬
             end:Ϊ�ߵ��յ�,
             weight:Ϊ�ߵ�Ȩ�ء�
    ��Ҫ˵���������������Ƿ����������ӡcout << "�Ƿ�����" << endl;
     */
    void setEdge(int start, int end, int weight)
    {
       
        if (start < 0 || start >= this->vertexNum || end < 0 || end >= this->vertexNum || weight < 0)
            cout << "�Ƿ�����" << endl;
        else {
            
            if (matrix[start][end] == 0 && weight != 0) ++this->edgeNum;
            matrix[start][end] = weight;
        }
    }
    /*
    TODO��d.ɾ��һ����ʼ��Ϊstart����ֹ��Ϊend�ı�
    ��Ҫ˵���������������ַǷ��������ӡcout << "�Ƿ�����" << endl;
    */
    void delEdge(int start, int end)
    {
        
        if (start < 0 || start >= this->vertexNum || end < 0 || end >= this->vertexNum)
            cout << "�Ƿ�����" << endl;
       
        else if (matrix[start][end] != 0) --this->edgeNum, matrix[start][end] = 0;
    }

    void showGraph()
    {
        cout << "����" << this->edgeNum << "����" << endl;
        cout << "ͼ����ϢΪ:" << endl;
        for (int i = 0; i < this->vertexNum; i++) {
            for (int j = 0; j < this->vertexNum; j++)
                cout << matrix[i][j] << " ";
            cout << endl;
        }
    }
};

int main()
{
    Edge<int> tempEdge;
    int num; //ͼ�Ķ�����Ŀ
    int start, end, weight;
    cin >> num;
    AdjGraph<int> adp(num); //numΪͼ�Ķ�����Ŀ
    // adp.setEdge(1, 0, 2); //1,0,2  ����1Ϊ�ߵ���㣬0Ϊ�ߵ��յ㣬2Ϊ�ߵ�Ȩ�ء�
    for (size_t i = 0; i < num; i++) {

        cin >> start >> end >> weight;
        adp.setEdge(start, end, weight);
    }
    // adp.setEdge(0, 2, 1);
    // adp.setEdge(0, 3, 3);
    // adp.setEdge(3, 2, 1);
    // adp.setEdge(3, 4, 1);
    adp.showGraph();
    int oneVertex; // һ�ߵĿ�ʼλ��
    cin >> oneVertex;
    tempEdge = adp.FirstEdge(oneVertex);
    tempEdge.showEdge();
    tempEdge = adp.NextEdge(tempEdge);
    tempEdge.showEdge();
    cin >> start >> end;
    adp.delEdge(start, end);
    adp.showGraph();
    return 0;
}
