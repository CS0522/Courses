import numpy as np
import matplotlib.pyplot as plt

POP_SIZE = 100  #每次迭代的种群总个数
N_GENERATIONS = 100  #迭代的总次数
C1 = 2  #自身最优解学习率
C2 = 2  #全局最优解学习率
W = 0.6 #惯性权重
X_MIN = 0 #解空间最小值
X_MAX = 15 #解空间最大值
BEST_ANSWERS = []

def F(x1, x2, x3):
	return 2*x1**2-3*x2**2-4*x1+5*x2+x3

def clamp(n, minn, maxn):
    n = np.maximum(n, minn)
    n = np.minimum(n, maxn)
    return n

class PSO(object):
    def __init__(self, population_size=POP_SIZE, max_steps=N_GENERATIONS):
        self.population_size = population_size  # 粒子群数量
        self.dim = 3  # 搜索空间的维度
        self.max_steps = max_steps  # 迭代次数
        self.x_bound = [X_MIN, X_MAX]  # 解空间范围 
        self.x = np.random.randint(self.x_bound[0],self.x_bound[1]+1, size=(POP_SIZE, self.dim)) #每一行就是一个3维度的向量，对应上x1，x2，x3
        self.v = np.random.rand(self.population_size, self.dim)  # 初始化粒子群速度
        fitness = self.calculate_fitness(self.x)
        self.p = self.x  # 个体的最佳位置
        self.pg = self.x[np.argmin(fitness)]  # 全局最佳位置
        self.individual_best_fitness = fitness  # 个体的最优适应度
        self.global_best_fitness = np.min(fitness)  # 全局最佳适应度
        BEST_ANSWERS.append(self.global_best_fitness)

    def calculate_fitness(self, x):
        x1 = x[:,0]
        x2 = x[:,1]
        x3 = x[:,2] 
        pred = F(x1, x2, x3)
        return pred

    def evolve(self):
        for _ in range(self.max_steps):
            r1 = np.random.rand(self.population_size, self.dim)
            r2 = np.random.rand(self.population_size, self.dim)
            # 更新速度和权重
            self.v = W*self.v+C1*r1*(self.p-self.x)+C2*r2*(self.pg-self.x)
            minn = [[self.x_bound[0]]*self.dim]*self.population_size
            maxn = [[self.x_bound[1]]*self.dim]*self.population_size
            self.x = clamp(self.v + self.x, minn, maxn)
            fitness = self.calculate_fitness(self.x)
            # 需要更新的个体
            update_id = np.greater(self.individual_best_fitness, fitness)
            self.p[update_id] = self.x[update_id]
            self.individual_best_fitness[update_id] = fitness[update_id]
            # 新一代出现了更小的fitness，所以更新全局最优fitness和位置
            if np.min(fitness) > self.global_best_fitness:
                self.pg = self.x[np.argmin(fitness)]
                self.global_best_fitness = np.min(fitness)
            print('best fitness: %.5f, mean fitness: %.5f' % (self.global_best_fitness, np.mean(fitness)))
            BEST_ANSWERS.append(np.min(fitness))
 
pso = PSO()
pso.evolve()
plt.plot(BEST_ANSWERS)
plt.show()
