---
title: "TopCoder SRM 660 Div1 Medium: Privateparty"
categories: topcoder srm
---

[Problem Statement](http://community.topcoder.com/stat?c=problem_statement&pm=13804)

# Algorithm

DP

# Explanation

## Key No.1: Influence Chain

Say we want to know whether or not Alice accepts invitation when she comes. What factors influence the attendance of Alice? When Alice likes everyone, she obviously accepts invitation regardless of other people's attendances, so we do not consider this case here. When Alice hates Bob, if and only if Bob comes before Alice **and** Bob accepts the invitation, Alice declines the invitation. So, Alice's attendance is influenced by (1) whether Bob comes before Alice and (2) (when Bob comes before Alice) whether Bob accepts the invitation or not. Here, what factors influence Bob's attendance? When Bob hates Carol, under the same argument, Bob's attendance is influenced by (1) whether Carol comes before Bob and (2) (when Carol comes before Bob) whether Carol accepts the invitation or not. Since Carol's attendance influences Bob's attendance and Bob's attendance influences Alice's attendance, Carol's attendance effectively influences Alice's attendance. So, if we create a chain starting from Alice by connecting the hatred relations, all people in the chain influence Alice's attendance. We call it an influence chain.

## Key No.2: Number of Bob's influencers is number of Alice's influencers - 1

Since one person can only hate one person, this is obvious.

## Summary of key points

- If we know Alice's order, we can calculate the probability Bob comes before Alice
- When Bob comes before Alice, if we know Bob's probability to attend we can calculate the probability of Alice's attendance (1 - probability that Bob attends)

This means that if we know Bob's probability to attend for each order Bob comes, we can calculate Alice's probability to attend for each order Alice comes. And to do that we want to know Carol's (whom Bob hates) probability to attend for each order Carol comes. And if Carol likes everyone, she comes 100%. DP chance!

## Implementation

Let `dp[i][o]` the probability that the person who has i influencers comes as o-th person in i + 1 people (influencers and the person himself). When a person likes everyone (`i = 0`) he/she will come 100%, so `dp[0][1] = 1`, this is the base case.

We can calculate `dp[i][o]` for `1 <= i <= n - 1`, `1 <= o <= i + 1` as follows (using Alice and Bob example above):

$$
dp[i][o] = P(\text{Bob comes after Alice}) + \sum\limits_{k=1}^{o-1} P(\text{Bob comes as k-th person}) * (1 - dp[i-1][k])
$$

where P(x) is the probability that the condition x suffices.

Here, `dp[i-1][k]` represents the probability that a person (here we are calling him Bob) having i-1 influencers attends the party when comes as k-th person. This `dp` calculation is done in O(n * n * n) = O(50^3).

Having all `dp[i][o]` calculated, we can calculate the probability for a given person to accept the invitation. First we have to know how long the influence chain for this person is (when doing this, you don't want to get into infinite loop -- multiple instance of the same person does not influence the attendance of given person, so simply stop adding up the influence chain when you find a loop). Let the length of a given person $$ I $$, then the probability this person accepts the invitation is:

$$
\sum\limits_{o=1}^{I+1} dp[I][o]
$$

Note that the order of people who are not in the influence chain does not affect the person's attendance, so we just have to think the order the person comes in people who are in the influence chain.

# Code

{% highlight cpp %}
#include <iostream>
#include <string>
#include <vector>
using namespace std;
static const double EPS = 1e-10;
#define FOR(i, b, e) for (int i = (b); i < (e); ++i)
#define REP(i, n) FOR(i, 0, n)

class Privateparty {
  public:
  double getexp(vector <int> a) {
    const int n = a.size();
    typedef vector<double> VD;
    // dp[i][j] = probability of a man to come to the party when the man's
    //            participation is influenced by i people, and when the man
    //            has come as the j-th person among those i people (+ himself).
    vector<VD> dp(n, VD(n+1, 0));
    // if a person is not influenced by anyone, he will come.
    dp[0][1] = 1;

    FOR (i, 1, n) {
      FOR (j, 1, n + 1) { // Let the line (people coming to the party) 1 indexed.
        // Let's say Alice has come to the line as j-th person
        // and Alice hates Bob
        // there are i people and Alice
        if (j > i + 1) { break; } // line has only i+1 people (including Alice)
        dp[i][j] += (i - j + 1) / (double)i; // probability that Bob comes after Alice
        FOR (k, 1, j) {
          // When Bob came before Alice
          // Add the probability that:
          //   - Bob comes as k-th person and
          //   - Bob declined the invitation
          dp[i][j] += (1 / (double)i) * (1 - dp[i-1][k]);
        }
      }
    }

    double ans = 0;
    REP (i, n) {
      int n_influencer = 0;
      int parent = i;
      vector<bool> visited(n, false);
      visited[parent] = true;
      while (parent != a[parent]) {
        parent = a[parent];
        if (visited[parent]) { // loop
          break;
        }
        visited[parent] = true;
        n_influencer++;
      }

      FOR (j, 1, n + 1) {
        if (j > n_influencer + 1) { break; }
        // add probability that:
        //   - Alice comes as j-th person (among n_influencer + 1 people) and
        //   - the probability that Alice accepts when she comes as j-th person
        ans += (1 / (double)(n_influencer + 1)) * dp[n_influencer][j];
      }
    }

    return ans;
  }
};
{% endhighlight %}

Full runnable code with test cases [here](https://github.com/Genki-S/programming-contest-blog/blob/master/code/topcoder/srm/660/div1/Privateparty.cpp).

# Credit

- [TopCoder SRM 660 Div1 Medium Privateparty - kmjp's blog](http://kmjp.hatenablog.jp/entry/2015/06/04/1030)
