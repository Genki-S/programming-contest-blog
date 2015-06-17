---
title: "HackerRank HiringSprint: Gifts"
categories: hackerrank hiringsprint
---

[Problem Statement](https://www.hackerrank.com/contests/hackerrank-hiringsprint/challenges/gifts)

# Algorithm

DP

# Explanation

Imagine that the scrolls of Bronze, Silver, and Gold techniques are stacked in 3 separated piles. In this situation, Koga can only learn each of them from either top or bottom. Effectively building 3 deque (in C++) data structures.

Let DP(i, j, k, l, m, n) be the best possible score Koga can get when he has learned i Bronze techniques from top, j Bronze techniques from bottom, k Silver techniques from top, l Silver techniques from bottom, m Gold techniques from top, n Gold techniques form bottom. The base case for this DP is `DP(0, 0, 0, 0, 0, 0) = 0`. To reach the state of DP(i, j, k, l, m, n), there are 6 possible paths, that is:

1. learn the top Bronze technique from `DP(i-1, j, k, l, m, n)` state
1. learn the bottom Bronze technique from `DP(i, j-1, k, l, m, n)` state
1. learn the top Silver technique from `DP(i, j, k-1, l, m, n)` state
1. learn the bottom Silver technique from `DP(i, j, k, l-1, m, n)` state
1. learn the top Gold technique from `DP(i, j, k, l, m-1, n)` state
1. learn the bottom Gold technique from `DP(i, j, k, l, m, n-1)` state

Regarding impossible combinations (such as `i + j > B`), we can calculate all possible DP(i, j, k, l, m, n) by looping for all variables (i.e. using 6 level nested loop!). Then, `max{ DP(i, j, k, l, m, n) | i+j+k+l+m+n = B+S+G }` (where Koga learns all the techniques) is the answer.

# Complexity

Since `1 <= B, S, G <= 10`, the 6 level nested loop takes `O(10^6)`, which is fast enough to complete. Searching answer for `max{ DP(i, j, k, l, m, n) | i+j+k+l+m+n = B+S+G }` can be performed in the same `O(10^6)` complexity.

Thus, `O(10^6)` in total.

# Code

{% highlight cpp %}
int main(int argc, char** argv) {
  ULL B, S, G; cin >> B >> S >> G;
  deque<ULL> bronze, silver, gold;
  REP (i, B) {
    ULL n; cin >> n;
    bronze.PB(n);
  }
  REP (i, S) {
    ULL n; cin >> n;
    silver.PB(n);
  }
  REP (i, G) {
    ULL n; cin >> n;
    gold.PB(n);
  }

  VI stones(B+S+G);
  REP (i, B+S+G) {
    cin >> stones[i];
  }

  typedef vector<int> VI;
  typedef vector<VI> VVI;
  typedef vector<VVI> VVVI;
  typedef vector<VVVI> VVVVI;
  typedef vector<VVVVI> VVVVVI;
  typedef vector<VVVVVI> VVVVVVI;
  VVVVVVI dp(B+1, VVVVVI(B+1, VVVVI(S+1, VVVI(S+1, VVI(G+1, VI(G+1, 0))))));

#define ASSIGN_MAX(var, val) ((var) = max((var), (val)))
  ULL ans = 0;
  REP (i, B+1) {
    REP (j, B+1) {
      if (i + j > B) { break; }
      REP (k, S+1) {
        REP (l, S+1) {
          if (k + l > S) { break; }
          REP (m, G+1) {
            REP (n, G+1) {
              if (m + n > G) { break; }
              ULL completed = i+j+k+l+m+n;
              if (i > 0) {
                ASSIGN_MAX(dp[i][j][k][l][m][n], dp[i-1][j][k][l][m][n] + bronze[i-1] * stones[completed-1]);
              }
              if (j > 0) {
                ASSIGN_MAX(dp[i][j][k][l][m][n], dp[i][j-1][k][l][m][n] + bronze[B-j] * stones[completed-1]);
              }
              if (k > 0) {
                ASSIGN_MAX(dp[i][j][k][l][m][n], dp[i][j][k-1][l][m][n] + silver[k-1] * stones[completed-1]);
              }
              if (l > 0) {
                ASSIGN_MAX(dp[i][j][k][l][m][n], dp[i][j][k][l-1][m][n] + silver[S-l] * stones[completed-1]);
              }
              if (m > 0) {
                ASSIGN_MAX(dp[i][j][k][l][m][n], dp[i][j][k][l][m-1][n] + gold[m-1] * stones[completed-1]);
              }
              if (n > 0) {
                ASSIGN_MAX(dp[i][j][k][l][m][n], dp[i][j][k][l][m][n-1] + gold[G-n] * stones[completed-1]);
              }

              if (completed == B+G+S) {
                ASSIGN_MAX(ans, dp[i][j][k][l][m][n]);
              }
            }
          }
        }
      }
    }
  }
  cout << ans << endl;

  return 0;
}
{% endhighlight %}

Full runnable code [here](https://github.com/Genki-S/programming-contest-blog/blob/master/code/hackerrank/hiringsprint/gift.cpp).
