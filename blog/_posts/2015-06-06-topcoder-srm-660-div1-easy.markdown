---
title: "TopCoder SRM 660 Div1 Easy: Coversta"
categories: topcoder srm
---

[Problem Statement](http://community.topcoder.com/stat?c=problem_statement&pm=13807)

# Algorithm

Greedy

# Explanation

1. For each cell, calculate the score regarding a station is placed on the cell (ignoring the second station). Let's call the array of these `scores`.
    - (in implementation, you also have to store cell position information for later use)
2. If you try all combinations, that would give you O(n * m * n * m * k * k) = O(10^10)
    - where:
        - k = number of elements in `x` (= number of elements in `y`) (1 <= k <= 10)
    - with calculations:
        - \#scores * #scores for selecting all combinations
        - k * k for removing overlaps (first station covers k cells, and second station as well. so for each cell covered by first station, we have to check if it's covered by one of the cells covered by the second station)
3. You can get a little greedy here
4. Sort `scores`, maximum first.
5. If you take i-th element of `scores`, you just have to try i+1, i+2, ... i+k^2+1 -th elements because:
    - since a station can have at most k^2 cells covered by itself and by the other station, if we try k^2+1 combinations one of which will contain at least one pair which has no overlap in covered cells
        - reason for "a station can have at most k^2 cells covered by itself and by the other station": let the first station placed on (p, q), and let (x[i], y[i]) combinations includes (0, 0), then second station can have overlap if it is placed on either:
            - a cell coverd by the first station (k cells possible)
            - a cell from which it is possible to move on to a cell covered by the first station using one of (x[i], y[i]) (k-1 cells for each of k cells above)
    - because you sorted `scores` maximum first, there are no better cases with combination i-th and (i+k^2+1 + m)-th where m >= 1
6. So you take one station as the first station for all cells, and search for the best second station choice for only k^2+1 cells (from better score)
    - which gives you O(n * m * k^2 * k * k) = O(10^8)
    - you can reduce this to O(n * m * k^2 * k * log(k)) if you use binary search when detecting overlaps (or hashmap to even remove log(k))
        - to achieve this, you have to store the information of which cells are covered by a station alonside with `scores`

# Code

{% highlight cpp %}
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
#define FOR(i, b, e) for (int i = (b); i < (e); ++i)
#define REP(i, n) FOR(i, 0, n)

typedef pair<int, int> PII;

class CellStat {
  public:
    int score;
    set<PII> covers;
    CellStat();
};
CellStat::CellStat() {
  score = 0;
  covers = set<PII>();
}

bool sorter(CellStat a, CellStat b) {
  return a.score < b.score;
}

class Coversta {
  public:
  int place(vector <string> a, vector <int> x, vector <int> y) {
    int n = a.size(), m = a[0].size();
    vector<CellStat> stats(n * m, CellStat());
    REP (i, n) {
      REP (j, m) {
        REP (k, x.size()) {
          int ti = i + x[k], tj = j + y[k];
          if (! (0 <= ti && ti < n && 0 <= tj && tj < m) ) { continue; }
          stats[i*m + j].score += a[ti][tj] - '0';
          stats[i*m + j].covers.insert(make_pair(ti, tj));
        }
      }
    }

    sort(stats.rbegin(), stats.rend(), sorter);

    int ans = 0;
    int K = x.size() * x.size();
    REP (i, n * m) { // n*m == stats.size()
      // place first station on cell of stats[i]
      CellStat &first = stats[i];
      FOR (j, 1, K + 2) {
        if (i + j >= stats.size()) { break; }
        // search at most K+1 cells cuz one of 1st..K+1-th cell is certainly the one which does not have overlap
        CellStat &second = stats[i + j];
        int score = first.score + second.score;
        // subtract the overlap
        for(set<PII>::iterator itr = first.covers.begin(); itr != first.covers.end(); ++itr) {
          if (second.covers.find(*itr) != second.covers.end()) {
            const PII &p = *itr;
            score -= a[p.first][p.second] - '0';
          }
        }
        ans = max(ans, score);
      }
    }

    return ans;
  }
};
{% endhighlight %}

Full runnable code with test cases [here](https://github.com/Genki-S/programming-contest-blog/blob/master/code/topcoder/srm/660/div1/Coversta.cpp).

# Credit

- [SRM 660 div1 easy:Coversta - mayoko’s diary](http://mayokoex.hatenablog.com/entry/2015/06/05/081145)
- [TopCoder SRM 660 Div1 Easy: Coversta - roiti46's blog](http://roiti46.hatenablog.com/entry/2015/06/04/233104)
