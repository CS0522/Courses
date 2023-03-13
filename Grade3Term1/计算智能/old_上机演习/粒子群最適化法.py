import numpy as np
import matplotlib.pyplot as plt

M = 100  #個体数
T = 100  #世代数
C1 = 2  #学習係数c1
C2 = 2  #学習係数c2
W = 0.6 #慣性定数
X_MIN = 0 #最小値
X_MAX = 15 #最大値
G_max = [] #最良解集合


#目的関数
def F(x1, x2, x3):
	return 2*x1**2-3*x2**2-4*x1+5*x2+x3

def clamp(n, minn, maxn):
    n = np.maximum(n, minn)
    n = np.minimum(n, maxn)
    return n

class PSO(object):
    def __init__(self, individual_size=M, max_steps=T):
        self.individual_size = individual_size  # 粒子群数
        self.dim = 3  # 空間次元
        self.max_steps = max_steps  # 世代数
        self.x_bound = [X_MIN, X_MAX]  # 解集団の範囲
        self.x = np.random.randint(self.x_bound[0],self.x_bound[1]+1, size=(M, self.dim))
        self.v = np.random.rand(self.individual_size, self.dim)  # 探索個体の速度
        fitness = self.calculate_fitness(self.x)
        self.p = self.x  # 探索個体の最良位置
        self.pg = self.x[np.argmax(fitness)]  # 個体群全体での最良位置
        self.individual_best_fitness = fitness  # 個体の最良適応度
        self.global_best_fitness = np.max(fitness)  # 個体群全体での最良適応度
        G_max.append(self.global_best_fitness)

    def calculate_fitness(self, x):
        x1 = x[:,0]
        x2 = x[:,1]
        x3 = x[:,2] 
        pred = F(x1, x2, x3)
        return pred

    def evolve(self):
        for _ in range(self.max_steps):
            r1 = np.random.rand(self.individual_size, self.dim)
            r2 = np.random.rand(self.individual_size, self.dim)
            # 学習係数と速度の更新
            self.v = W*self.v+C1*r1*(self.p-self.x)+C2*r2*(self.pg-self.x)
            minn = [[self.x_bound[0]]*self.dim]*self.individual_size
            maxn = [[self.x_bound[1]]*self.dim]*self.individual_size
            self.x = clamp(self.v + self.x, minn, maxn)
            fitness = self.calculate_fitness(self.x)
            # 個体の更新
            update_id = np.greater(self.individual_best_fitness, fitness)
            self.p[update_id] = self.x[update_id]
            self.individual_best_fitness[update_id] = fitness[update_id]
            # 個体群全体での最良適応度と最良位置の更新
            if np.max(fitness) > self.global_best_fitness:
                self.pg = self.x[np.argmax(fitness)]
                self.global_best_fitness = np.max(fitness)
            print('best fitness: %.5f, mean fitness: %.5f' % (self.global_best_fitness, np.mean(fitness)))
            G_max.append(np.max(fitness))
 
pso = PSO()
pso.evolve()
plt.plot(G_max)
plt.show()
