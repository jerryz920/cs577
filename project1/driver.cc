/******************************************************************************

 @File Name : {PROJECT_DIR}/driver.cc

 @Creation Date : 05-14-2013

 @Purpose :

*******************************************************************************/

#include "splay.h"
#include "opt.h"
#include <vector>
#include <cstdio>
#include <cmath>

extern bool gen_dist(const vector<double>& dists, int size, vector<int>& key, vector<int>& workload, int type);


int main(int argc, char** argv)
{
  FILE* f = fopen("workload", "r");
  if (!f) {
    fprintf(stderr, "can not open workload file\n");
    return 1;
  }

  vector<double> dist;
  double p;
  double total = 0;
  while (fscanf(f, "%lf", &p) == 1) {
    dist.push_back(p);
    total += p;
  }

  if (fabs(total - 1) > 1E-6) {
    fprintf(stderr, "ill-formed workload file, probablity should add to 1\n");
    return 1;
  }

  fclose(f);

  int size = 1000;
  int type = 0;

  if (argc > 1) {
    type = atoi(argv[1]);
    if (type > 3 || type < 0) type = 0;
  }

  if (argc > 2) {
    size = atoi(argv[2]);
    if (size < 100) size = 100;
  }

  vector<int> keys;
  vector<int> workload;
  if (!gen_dist(dist, size, keys, workload, type)) {
    fprintf(stderr, "can not generate workload, aborting!\n");
    return 1;
  }

  OptimalBST<int>bst(dist, keys);

  int bst_level_total = 0;
  for (int i = 0; i < workload.size(); i++) {
    bst.exist(workload[i], &bst_level_total);
  }

  std::sort(keys.begin(), keys.end());

  SplayTree<int> spl;
  /*
   *  Shall we consider different method for constructing the tree
   */
  for (int i = 0; i < keys.size(); i++) {
    spl.insert(keys[i]);
  }

  int splay_level_total = 0;
  int splay_cnt = 0;
  for (int i =0 ; i < workload.size(); i++) {
    spl.find(workload[i], &splay_level_total, &splay_cnt);
  }

  printf("type %d: bst %d, splay %d %d\n", type, bst_level_total, splay_level_total, splay_cnt);

  return 0;
}
