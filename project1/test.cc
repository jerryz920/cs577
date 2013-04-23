/******************************************************************************

 @File Name : {PROJECT_DIR}/test.cc

 @Creation Date : 09-04-2013

 @Created By: Zhai Yan

 @Purpose :

*******************************************************************************/
#include <cstdio>
#include <string>
#include <vector>
using namespace std;


class N 
{
  public:
  N() :msg("123") {
    printf("original %p\n", this);
  }

  N(const N& o): msg(o.msg)
  {
    printf("lfs %p %p\n", this, &o);
  }

  N(const N&&o) 
  {
    msg = std::move(o.msg);
    printf("rfs %s %d %p %p\n", o.msg.c_str(), o.msg.size(), this, &o);
  }
  ~N()
  {
    printf("need this? %p\n", this);
  }
  string msg;
};

N test(N& v)
{
  printf("fff1\n");
  N tmp = std::move(v);
  printf("fff\n");
  return tmp;
}

N test(N&& v)
{
  printf("fff1\n");
  N tmp = v;
  printf("fff\n");
  return tmp;
}

#include <iostream>
int main()
{
  //int x = 1;
  //test(x);
  //test(2);

  string a = "123";
  string b = std::move(a);
  printf("%s\n", a.c_str());

  N v;
  N y = test(v);
  //v.msg.push_back('1');
  printf("v msg %p\n", v.msg.c_str());
  printf("y msg %p\n", y.msg.c_str());
  printf("ooo\n");
  N x = test(N());
  printf("ooo\n");

  vector<int> m;

  return 0;
}



