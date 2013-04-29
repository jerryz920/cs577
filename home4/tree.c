
extern int t[n][n];
search(r)
{
  tmp[N][n] = {MAX}; // N is the max children count, n is number of all tree nodes
  tmp[0][0] = 0;
  for (i = 1; i < descendants_count(c); i++) {
    // we have defined cost before
    t[0][i] = cost(i,r,0);
  }
  for c in r.child[1..] { // foreach group
    search(c);
    tmp[c][0] = 0;
    for (v = 1; v <= n; v++)
      for (i = 0; i <= descendants_count(c); i++) // for each item
	tmp[c][v] = min(tmp[c-1][v], tmp[c-1][v - i] + cost(i, r, c))
  }
  t[r] = copy_array(tmp[r.child_count - 1]);
}


