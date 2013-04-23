/******************************************************************************

 @File Name : {PROJECT_DIR}/opt.cc

 @Creation Date : 10-04-2013

 @Created By: Zhai Yan

 @Purpose :

*******************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * An optimal search tree is just something in concept: when we know the visit
 * pattern, we could construct such static structure.
 */

class OptimalBST {

  private:
    typedef struct OptNode {
      struct OptNode* left;
      struct OptNode* right;
      int index;
    } OptNode;

  public:

    //
    //  Assume we have n keys a[0..n-1], sorting in acsending order. For generality
    //  we prepend a[-1] and append a[n] such that a[-1] < a[0] and a[n] > a[n-1].
    //
    //  Then the optimal binary search tree could be constructed using a 2*n+1 elements
    //  vector. This vector corresponds to the chance to hit or miss in the search tree.
    //
    //  for the element at 2 * i, it means the chance of the search to drop between
    //  a[i-1] and a[i]. For the element 2 * i + 1, it means the chance of the search to
    //  hit a[i]. Use dynamic programming we could construct the search tree in O(n^3)
    //  time.
    //
    OptimalBST(const std::vector<double>&& p)
    {

    }

    T* find(const T&& t)
    {


    }


  private:
    OptNode* inner_lookup(const T&& t)
    {
      return nullptr;
    }

    ////
    //  Construct a sub OST within range [l, r)
    //
    OptNode* construct(int l, int r, const vector<double>& p)
    {
      OptNode* new_node = new OptNode {NULL, NULL, l};
      if (l >= r - 1) {
        return new_node;
      }

      double mincost =
      for (int root = l; root < r; root++) {

      }

      return NULL;
    }

    OptNode* root;
};
