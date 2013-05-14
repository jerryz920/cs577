/******************************************************************************

 @File Name : {PROJECT_DIR}/opt.cc

 @Creation Date : 04-10-2013

 @Purpose :

*******************************************************************************/

#pragma once


#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cfloat>

using namespace std;

/*
 * An optimal search tree is just something in concept: when we know the visit
 * pattern, we could construct such static structure.
 */

template <class T>
class OptimalBST {

  private:
    typedef struct OptNode {
      struct OptNode* left;
      struct OptNode* right;
      T index;
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
    OptimalBST(const std::vector<double>& p, const std::vector<T>& v)
    {
      construct(p, v);
    }

    bool exist(T t, int* level=NULL)
    {
      OptNode* cur = root;
      while (cur && cur->index != t) {
        if (level) (*level)++;
        if (cur->index < t) {
          cur = cur->right;
        } else {
          cur = cur->left;
        }
      }
      if (cur && cur->index == t) {
        if (level) (*level)++;
        return true;
      }
      if (level) (*level)++;
      return false;
    }

  private:

    void construct(const vector<double>& p, const vector<T>& keys)
    {
      double **w, **c;
      int **r;
      assert(p.size() % 2 == 1 && p.size() / 2 == keys.size());
      int num_key = p.size() / 2;
      w = (double**) malloc(sizeof(double) * (num_key + 1));
      c = (double**) malloc(sizeof(double) * (num_key + 1));
      r = (int **) malloc(sizeof(double) * (num_key + 1));
      for (int i = 0; i <= num_key; i++) {
        w[i] = (double*) malloc(sizeof(double) * (num_key + 1));
        w[i][i] = p[2 * i];
        for (int j = i + 1; j < num_key; j++) {
          w[i][j] = w[i][j-1] + p[2 * j - 1] + p[2 * j];
        }
        c[i] = (double*) malloc(sizeof(double) * (num_key + 1));
        c[i][i] = p[2 * i];
        r[i] = (int*) malloc(sizeof(double) * (num_key + 1));
      }

      for (int k = 1; k <= num_key; k++) {
        for (int i = 0; i <= num_key - k; i++) {
          int j = i + k;
          double min = DBL_MAX;
          for (int l = i; l < j; l++) {
            double tmp = c[i][l] + c[l + 1][j] + w[i][j];
            if (tmp < min) {
              min = tmp;
              r[i][j] = l;
            }
          }
          c[i][j] = min;
        }
      }
      root = build_tree(r, 0, num_key, keys);

      for (int i = 0 ; i < num_key; i++) {
        free(w[i]);
        free(c[i]);
      }
      free(w);
      free(c);
    }

    ////
    //  Construct a sub OST within range [l, r)
    //
    OptNode* build_tree(int** root, int l, int r, const vector<T>& key)
    {
      if (l >= r) {
        return NULL;
      }
      OptNode* nroot = new OptNode;
      nroot->left = build_tree(root, l, root[l][r], key);
      nroot->right = build_tree(root, root[l][r] + 1, r, key);
      nroot->index = key[root[l][r]];
      return nroot;
    }
    OptNode* root;
};

