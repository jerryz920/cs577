/******************************************************************************

 @File Name : {PROJECT_DIR}/dist.cc

 @Creation Date : 05-14-2013

 @Purpose :

*******************************************************************************/

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <time.h>
using std::vector;
using std::random_shuffle;

int myrandom (int i) { return std::rand()%i;}
/*
 *  Given a distribution, generate the workload,
 *  the dists vector contain 2n + 1 elements:
 *    2 * ith element means the probability of 
 */
bool gen_dist(const vector<double>& dists, int size, vector<int>& key, vector<int>& workload, int type)
{
  if (dists.size() % 2 != 1)
    return false;
  vector<int> elem_count;
  for (int i = 0; i < dists.size(); i++) {
    elem_count.push_back((int) (size * dists[i]));
    if (i % 2 == 1)
      key.push_back(i);
  }

  switch(type) {
    case 0: /* Sequential workload (high locality) */
      workload.reserve(size);
      for (int i = 0; i < elem_count.size(); i++) {
        for (int j = 0; j < elem_count[i]; j++)
          workload.push_back(i);
      }
      break;
    case 1: /* Random workload (partial locality) */
      srand(time(NULL));
      workload.reserve(size);
      for (int i = 0; i < elem_count.size(); i++) {
        for (int j = 0; j < elem_count[i]; j++)
          workload.push_back(i);
      }
      std::random_shuffle(workload.begin(), workload.end(), myrandom);
      break;
    case 2: /* Cyclic workload (no locality) */
      bool flag = true;
      while (flag) {
        flag = false;
        for (int i = 0; i < elem_count.size(); i++) {
          if (elem_count[i] > 0) {
            workload.push_back(i);
            elem_count[i]--;
            flag = true;
          }
        }
      }
      break;
  }
  return true;
}


