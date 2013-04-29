
group_knapsack(int costs[N][V], Group g[N], int V)
{
  set costs to MAX
  for (i = 0; i < g[0].item_count; i++)
    costs[0][g[0].weight[i]] = g[0].cost[i];
  for (i = 1; i < N; i++) {
    costs[i][0] = 0;
    for (v = 1; v <= V; v++) {
      for (j = 0; j < g[i].item_count; j++) {
        if (g[i].weight[j] <= v)
          costs[i][v] = min(costs[i-1][v], costs[i-1][v-g[i].weight[j]] + g[i].cost[j]);
      }
    }
  }
  return costs[N+1][V]; // this value is minimum cost, if able to fill exactly capacity V.
}


