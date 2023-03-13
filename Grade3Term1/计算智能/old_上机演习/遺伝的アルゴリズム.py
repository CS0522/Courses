import matplotlib.pyplot as plt
import numpy as np

N = 4  #遺伝子長
M = 100  #個体数
Pc = 0.30 #交叉確率
Pm = 0.50 #突然変異確率
T = 100  #世代数
G_max = [] #最良解集合
G_min = [] #最小適応度集合


#適応度計算
def evaluation(individuals):
    x1_binary = individuals[:, 0:4]
    x2_binary = individuals[:, 4:8]
    x3_binary = individuals[:, 8:12]
    #2進数から10進数
    x1 = x1_binary.dot(2 ** np.arange(N))
    x2 = x2_binary.dot(2 ** np.arange(N))
    x3 = x3_binary.dot(2 ** np.arange(N))
    # 目的関数
    pred = F(x1, x2, x3)
    # 最大適応度集合
    G_max.append(pred.max())

    return (pred - np.min(pred))

#目的関数
def F(x1, x2, x3):
	return 2*x1**2-3*x2**2-4*x1+5*x2+x3

#交叉
def crossover(individuals,Pc):
    new_individuals = []
    #個体をランダムにペアリング(親個体ia, ibを選ぶ)

    for ia in individuals:#親iaを決定
        child = ia
        if np.random.rand() < Pc:#交叉
            ib = individuals[np.random.randint(M)]#親ibを決定
            cross_points = np.random.randint(low=0, high=N*3)#交叉点
            child[cross_points:] = ib[cross_points:]
        mutation(child)#突然変異
        new_individuals.append(child)
    return new_individuals

#突然変異
def mutation(child):
    if np.random.rand() < Pm:
        mutate_point = np.random.randint(0, N)
        child[mutate_point] = child[mutate_point]^1


#ルーレット選択
def roulette_selection(individuals, fitness):

    fitness = np.square(fitness)
    idx = np.random.choice(np.arange(M), size=M, replace=True,p=(fitness)/(fitness.sum())) #ルーレット・ホイールに従って次世代を決定
    return individuals[idx]

if __name__ == "__main__":
    #0世代目生成
    individuals = np.random.randint(2, size=(M, N*3))
    # 適応度計算
    fitness = evaluation(individuals)
    #1～T世代生成
    for _ in range(T):
        #交叉,突然変異
        individuals = np.array(crossover(individuals, Pc))
        #適応度値計算
        fitness = evaluation(individuals)
        #ルーレット選択
        individuals = roulette_selection(individuals, fitness)

    #結果を示す
    plt.plot(G_max)
    plt.show()



    