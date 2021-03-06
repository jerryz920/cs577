/******************************************************************************

 @File Name : {PROJECT_DIR}/splay.cc

 @Creation Date : 04-08-2013

 @Purpose : This is a simple implementation of a splay tree.

*******************************************************************************/

#pragma once

#include <cstdio>
#include <cstdlib>
#include <utility>

//
//TODO:
//  Here we simplify things: T should only be value type, rather than pointer,
//  or reference. In future should use standard facilities to make this template
//  more usable.
//
template <typename T>
class SplayTree {

  private:

    typedef struct SplayNode {
      SplayNode* parent;
      SplayNode* left;
      SplayNode* right;
      T val;

      SplayNode(SplayNode* p, SplayNode* l, SplayNode* r, T v):
        parent(p), left(l), right(r), val(v)
      { }
    } SplayNode;

  public:

    /*
     *  Constructors
     */
    SplayTree():
      sentinel(&sentinel, &sentinel, &sentinel, T()),
      root_(&sentinel)
    {
    }

    void debug()
    {
      dodebug(root_, 0);
    }

    void dodebug(SplayNode* root, int tab)
    {
      if (!is_nil(root)) {
        printf("%*d\n", tab, root->val);
        printf("%*sleft\n", tab, " ");
        dodebug(root->left, tab + 2);
        printf("%*sright\n", tab, " ");
        dodebug(root->right, tab + 2);
      }
    }

    /*
     *  Interfaces
     */
    void insert(T v)
    {
      if (is_nil(root_)) {
        root_ = new SplayNode(&sentinel, &sentinel, &sentinel, v);
        root_->val = v;
      } else {
        do_insert(v);
      }
    }

    void remove(T v)
    {
      SplayNode* target = bin_find(v).second;
      if (is_nil(target)) {
        return ;
      }

      splay(target);
      do_remove(target);
    }

    T* find(T v, int*level = NULL, int* splay_cnt = NULL)
    {
      std::pair<SplayNode*,SplayNode*> target = bin_find(v, level);
      if (is_nil(target.second)) {
        int tmp = splay(target.first);
        if (splay_cnt) *splay_cnt += tmp;
        return NULL;
      } else {
        int tmp = splay(target.second);
        if (splay_cnt) *splay_cnt += tmp;
        return &target.second->val;
      }
    }

    bool contains(T v)
    {
      return find(v) != NULL;
    }

  private:

    /*
     *  Inner implementation of splay, insert, and delete
     */
    ////
    // Zig operation applies when rotating p and its left child
    //
    void zig(SplayNode* p)
    {
      SplayNode* x = p->left;
      p->left = x->right;
      x->right->parent = p;
      x->right = p;
      x->parent = p->parent;
      if (!is_nil(p->parent)) {
        if (p->parent->left == p)
          p->parent->left = x;
        else
          p->parent->right = x;
      }
      p->parent = x;
    }

    ////
    // Zag operation applies when rotating p and its right child
    //
    void zag(SplayNode* p)
    {
      SplayNode* x = p->right;
      p->right = x->left;
      x->left->parent = p;
      x->left = p;
      x->parent = p->parent;
      if (!is_nil(p->parent)) {
        if (p->parent->left == p)
          p->parent->left = x;
        else
          p->parent->right = x;
      }
      p->parent = x;
    }

    int splay(SplayNode* x)
    {
      SplayNode* p = x->parent;
      int splay_cnt = 0;

      while (!is_nil(p)) {
        SplayNode* pp = p->parent;
        if (is_nil(pp)) {
          if (p->left == x) {
            zig(p);
          } else {
            zag(p);
          }
        } else if (pp->left == p && p->left == x) {
          zig(pp);
          zig(p);
        } else if (pp->left == p && p->right == x) {
          zag(p);
          //
          //  Important: after this x->parent != p
          //
          zig(x->parent);
        } else if (pp->right == p && p->left == x) {
          zig(p);
          //
          //  Important: after this x->parent != p
          //
          zag(x->parent);
        } else {
          zag(pp);
          zag(p);
        }
        p = x->parent;
        splay_cnt++;
      }
      //
      //  now root should point at x.
      //
      root_ = x;
      return splay_cnt;
    }

    std::pair<SplayNode*,SplayNode*> bin_find(const T& v, int* level = NULL)
    {
      sentinel.val = v;
      SplayNode* cur = root_;
      SplayNode* par = &sentinel;
      //
      // We just require T to implement '<' method, so we
      // should not write cur->v != v, rather, we rely on
      // the fact if !(a < b) && !(b < a) then a == b.
      //
      while (true) {
        if (cur->val < v) {
          par = cur;
          cur = cur->right;
          if (level) (*level)++;
        } else if (v < cur->val) {
          par = cur;
          cur = cur->left;
          if (level) (*level)++;
        } else {
          if (level) (*level)++;
          break;
        }
      }
      return std::make_pair(par, cur);
    }

    void do_insert(const T& v)
    {
      std::pair<SplayNode*,SplayNode*>  ins_point = bin_find(v);
      SplayNode* par = ins_point.first;
      SplayNode* ins = ins_point.second;

      if (is_nil(ins)) {
        if (v < par->val) {
          par->left = new SplayNode(par, &sentinel, &sentinel, v);
          ins = par->left;
        } else {
          par->right = new SplayNode(par, &sentinel, &sentinel, v);
          ins = par->right;
        }
      }
      splay(ins);
    }

    void do_remove(SplayNode* oldroot)
    {
      SplayNode* lmax = max(oldroot->left);
      if (is_nil(lmax)) {
        root_ = oldroot->right;
        oldroot->right->parent = &sentinel;
        delete oldroot;
        return;
      }
      //
      //  assert(is_nil(lmax->right));
      //
      std::swap(oldroot->val, lmax->val);
      if (lmax->parent->right == lmax) {
        lmax->parent->right = lmax->left;
      }
      if (lmax->parent->left == lmax) {
        lmax->parent->left = lmax->left;
      }
      if (!is_nil(lmax->left)) {
        lmax->left->parent = lmax->parent;
      }
      delete lmax;
    }

    /*
     *  Utilities
     */
    SplayNode* max(SplayNode* t)
    {
      while (!is_nil(t) && !is_nil(t->right)) {
        t = t->right;
      }
      return t;
    }
    bool is_nil(const SplayNode* n) const
    {
      return n == &sentinel;
    }
    bool is_nil(SplayNode* n)
    {
      return n == &sentinel;
    }

    SplayNode* root_;
    SplayNode sentinel;
};


//
//  Test code
//
//int main()
//{
//  SplayTree<int> t;
//
//  for (int i = 6; i > 0; i--)
//    t.insert(i);
//  t.insert(6);
//  t.remove(5);
//  t.remove(5);
//  t.remove(4);
//  t.remove(3);
//  t.remove(1);
//  t.debug();
//
//  return 0;
//}
