#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h> /* time */

#define N 12    // 遺伝子長
#define M 100   // 個体数
#define T 100   // 世代数
#define Pc 0.30 // 交叉確率
#define Pm 0.10 // 突然変異確率

// 遺伝子型の定義
struct genotype
{
  int gene[N];   // 遺伝子
  float fitness; // 適応度
};

float evaluation(int *a);
void one_point_crossover(struct genotype *ind);
void mutation(struct genotype *ind);
void roulette_selection(struct genotype *ind);
int flip(float prob);
void print_process(struct genotype *ind, int generation, FILE *fp);

int main(int argc, char *argv[])
{
  FILE *fp = fopen("./test.txt", "a+"); // outputfilename
  int i;                                // 個体インデックス
  int j;                                // 遺伝子座インデックス
  int t;                                // 世代インデックス
  struct genotype individual[M];        // 個体

  // 乱数seedの設定
  srand((unsigned)time(NULL));

  // ステップ1 (0世代目)
  for (i = 0; i < M; i++)
  {
    for (j = 0; j < N; j++)
    {
      individual[i].gene[j] = flip(0.5);
    }
    individual[i].fitness = evaluation(individual[i].gene); // 個体の適応度計算
  }
  print_process(individual, 0, fp); // 初期世代の個体群を表示

  // ステップ2 (1～T世代)
  for (t = 1; t <= T; t++)
  {
    // 交叉
    one_point_crossover(individual);
    // 突然変異
    mutation(individual);
    // 子個体の適応度値計算
    for (i = 0; i < M; i++)
    {
      individual[i].fitness = evaluation(individual[i].gene);
    }
    // ルーレット選択
    roulette_selection(individual);
    print_process(individual, t, fp);
  }
  fclose(fp); //关闭文件
  return (0);
} // End of main()

// 個体の適応度計算
float evaluation(int *a)
{
  int j; // 遺伝子座インデックス

  //j:0-3 --- x1
  //  4-7 --- x2
  //  8-11 --- x3

  int count = 0; //適応度
  int x1 = 0;
  int x2 = 0;
  int x3 = 0;

  //Binary to decimal
  for (j = 3; j >= 0; j--)
  {
    x1 = a[j] * pow(2, j) + x1;
  }

  for (j = 7; j >= 4; j--)
  {
    x2 = a[j] * pow(2, j - 4) + x2;
  }

  for (j = 11; j >= 8; j--)
  {
    x3 = a[j] * pow(2, j - 8) + x3;
  }

  count = 2 * pow(x1, 2) - 3 * pow(x2, 2) - 4 * x1 + 5 * x2 + x3;

  return ((float)count);
} // End of evaluation()

// 一点交叉
void one_point_crossover(struct genotype *ind)
{
  int i, ia, ib; // 個体インデックス
  int j;         // 遺伝子座インデックス
  int c;         // 交叉点
  int test[M];   // 個体の利用フラグ
  int temp[N];   // 遺伝子を入れ替えるための仮変数
  int r;         // 乱数値

  for (i = 0; i < M; i++)
    test[i] = 0;

  ia = ib = 0;
  for (i = 0; i < M / 2; i++)
  {
    // 個体をランダムにペアリング (親個体ia,ibを選ぶ)
    // 親iaを決定
    for (; test[ia] == 1; ia = (ia + 1) % M)
      ;
    test[ia] = 1;
    r = rand() % (M - 2 * i) + 1;
    // (iaとは異なる)親ibを決定
    while (r > 0)
    {
      ib = (ib + 1) % M;
      for (; test[ib] == 1; ib = (ib + 1) % M)
        ;
      r--;
    }
    test[ib] = 1;
    // 個体iaとibの遺伝子を入れ替える
    if (flip(Pc))
    {
      c = rand() % N;
      for (j = 0; j < c; j++)
      {
        temp[j] = ind[ia].gene[j];
        ind[ia].gene[j] = ind[ib].gene[j];
        ind[ib].gene[j] = temp[j];
      }
    }
  }
} // End of one_point_crossover()

// 突然変異
void mutation(struct genotype *ind)
{
  int i; // 個体インデックス
  int j; // 遺伝子座インデックス

  for (i = 0; i < M; i++)
    for (j = 0; j < N; j++)
      if (flip(Pm))
      {
        ind[i].gene[j] = (ind[i].gene[j] + 1) % 2;
      }

} // End of mutation()

// ルーレット選択
void roulette_selection(struct genotype *ind)
{
  int h, i;                   // 個体インデックス
  float total_fitness;        // 適応度の合計値
  float dart;                 // 矢
  float wheel;                // ルーレット・ホイール
  struct genotype ind_new[M]; // 選択操作後の個体集合

  // 適応度の合計値を計算
  total_fitness = 0;
  for (i = 0; i < M; i++)
    total_fitness += ind[i].fitness;

  // ルーレット・ホイールに従って次世代(ind_new[])を決定
  for (i = 0; i < M; i++)
  {
    dart = (float)rand() / RAND_MAX;
    h = 0;
    wheel = ind[h].fitness / total_fitness;
    while (dart > wheel && h < M - 1)
    {
      h++;
      wheel += ind[h].fitness / total_fitness;
    }
    ind_new[i] = ind[h];
  }

  // 個体集合の更新
  for (i = 0; i < M; i++)
  {
    ind[i] = ind_new[i];
  }

} // End of roulette_selection()

// 引数`prob'の確率で1を返す
int flip(float prob)
{
  float x = (float)rand() / RAND_MAX;

  if (x < prob)
    return (1);
  else
    return (0);
} // End of flip()

// 個体の中身や適応度値を画面に出力
void print_process(struct genotype *ind, int generation, FILE *fp)
{
  int i;                           // 個体インデックス
  int j;                           // 遺伝子座インデックス
  float max_fit, min_fit, avg_fit; // 最大，最小，平均適応度

  // 各個体の中身を出力
  fprintf(fp, "\nGeneration: %d\n", generation);
  for (i = 0; i < M; i++)
  {
    // printf("%d: ", i);
    fprintf(fp, "%d: ", i);
    for (j = 0; j < N; j++)
    {
      if (ind[i].gene[j] == 0)
        // printf("%c", ' ');
        fprintf(fp, "%c", ' ');
      else
        // printf("%c", '*');
        fprintf(fp, "%c", '*');
    }
    fprintf(fp, " : %.0f\n", ind[i].fitness);
  }

  // 個体集団の最大，最小，平均適応度を求める
  max_fit = min_fit = ind[0].fitness;
  avg_fit = ind[0].fitness / M;
  for (i = 1; i < M; i++)
  {
    if (max_fit < ind[i].fitness)
      max_fit = ind[i].fitness;
    if (min_fit > ind[i].fitness)
      min_fit = ind[i].fitness;
    avg_fit += ind[i].fitness / M;
  }
  fprintf(fp, "max: %.2f  min: %.2f  avg: %.2f\n", max_fit, min_fit, avg_fit);

} // End of print_process()
