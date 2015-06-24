// Header {{{
// includes {{{
#include <algorithm>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
// }}}
using namespace std;
// consts {{{
static const int INF = 1e9;
static const double PI = acos(-1.0);
static const double EPS = 1e-10;
// }}}
// typedefs {{{
typedef long long int LL;
typedef unsigned long long int ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<ULL> VULL;
typedef vector<VULL> VVULL;
typedef vector<double> VD;
typedef vector<VD> VVD;
typedef vector<bool> VB;
typedef vector<VB> VVB;
typedef vector<char> VC;
typedef vector<VC> VVC;
typedef vector<string> VS;
typedef vector<VS> VVS;
typedef pair<int, int> PII;
typedef complex<int> P;
#define PQ(type) priority_queue<type>
// priority queue reverse
#define PQR(type) priority_queue< type, vector<type>, greater<type> >
// }}}
// macros & inline functions {{{
// syntax sugars {{{
#define FOR(i, b, e) for (typeof(e) i = (b); i < (e); ++i)
#define FORI(i, b, e) for (typeof(e) i = (b); i <= (e); ++i)
#define REP(i, n) FOR(i, 0, n)
#define REPI(i, n) FORI(i, 0, n)
#define OPOVER(_op, _type) inline bool operator _op (const _type &t) const
#define ASSIGN_MAX(var, val) ((var) = max((var), (val)))
#define ASSIGN_MIN(var, val) ((var) = min((var), (val)))
// }}}
// conversion {{{
inline int toInt(string s) { int v; istringstream sin(s); sin>>v; return v; }
template<class T> inline string toString(T x) { ostringstream sout; sout<<x; return sout.str(); }
// }}}
// array and STL {{{
#define ARRSIZE(a) ( sizeof(a) / sizeof(a[0]) )
#define ZERO(a, v) ( assert(v == 0 || v == -1), memset(a, v, sizeof(a)) )
#define F first
#define S second
#define MP(a, b) make_pair(a, b)
#define SIZE(a) ((LL)a.size())
#define PB(e) push_back(e)
#define SORT(v) sort((v).begin(), (v).end())
#define RSORT(v) sort((v).rbegin(), (v).rend())
#define ALL(a) (a).begin(), (a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define EACH(c, it) for(typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)
#define REACH(c, it) for(typeof((c).rbegin()) it=(c).rbegin(); it!=(c).rend(); ++it)
#define EXIST(s, e) ((s).find(e) != (s).end())
// }}}
// bit manipulation {{{
// singed integers are not for bitwise operations, specifically arithmetic shifts ('>>', and maybe not good for '<<' too)
#define IS_UNSIGNED(n) (!numeric_limits<typeof(n)>::is_signed)
#define BIT(n) (assert(IS_UNSIGNED(n)), assert(n < 64), (1ULL << (n)))
#define BITOF(n, m) (assert(IS_UNSIGNED(n)), assert(m < 64), ((ULL)(n) >> (m) & 1))
inline int BITS_COUNT(ULL b) { int c = 0; while(b != 0) { c += (b & 1); b >>= 1; } return c; }
inline int MSB(ULL b) { int c = 0; while(b != 0) { ++c; b >>= 1; } return c-1; }
inline int MAKE_MASK(ULL upper, ULL lower) { assert(lower < 64 && upper < 64 && lower <= upper); return (BIT(upper) - 1) ^ (BIT(lower) - 1); }
// }}}
// for readable code {{{
#define EVEN(n) (n % 2 == 0)
#define ODD(n) (!EVEN(n))
// }}}
// debug {{{
#define arrsz(a) ( sizeof(a) / sizeof(a[0]) )
#define dprt(fmt, ...) if (opt_debug) { fprintf(stderr, fmt, ##__VA_ARGS__); }
#define darr(a) if (opt_debug) { copy( (a), (a) + arrsz(a), ostream_iterator<int>(cerr, " ") ); cerr << endl; }
#define darr_range(a, f, t) if (opt_debug) { copy( (a) + (f), (a) + (t), ostream_iterator<int>(cerr, " ") ); cerr << endl; }
#define dvec(v) if (opt_debug) { copy( ALL(v), ostream_iterator<int>(cerr, " ") ); cerr << endl; }
#define darr2(a) if (opt_debug) { FOR(__i, 0, (arrsz(a))){ darr( (a)[__i] ); } }
#define WAIT() if (opt_debug) { string _wait_; cerr << "(hit return to continue)" << endl; getline(cin, _wait_); }
#define dump(x) if (opt_debug) { cerr << " [L" << __LINE__ << "] " << #x << " = " << (x) << endl; }
// dump vector elements in [s, e)
#define dumpv(v, s, e) if (opt_debug) { cerr << " [L" << __LINE__ << "] " << #v << " = "; FOR(__i, s, e) { cerr << v[__i] << "\t"; } cerr << endl; }
#define dumpl(x) if (opt_debug) { cerr << " [L" << __LINE__ << "] " << #x << endl << (x) << endl; }
#define dumpf() if (opt_debug) { cerr << __PRETTY_FUNCTION__ << endl; }
#define where() if (opt_debug) { cerr << __FILE__ << ": " << __PRETTY_FUNCTION__ << " [L: " << __LINE__ << "]" << endl; }
#define show_bits(b, s) if(opt_debug) { REP(i, s) { cerr << BITOF(b, s-1-i); if(i%4 == 3) cerr << ' '; } cerr << endl; }

// ostreams {{{
// complex
template<typename T> ostream& operator<<(ostream& s, const complex<T>& d) {return s << "(" << d.real() << ", " << d.imag() << ")";}

// pair
template<typename T1, typename T2> ostream& operator<<(ostream& s, const pair<T1, T2>& d) {return s << "(" << d.first << ", " << d.second << ")";}

// vector
template<typename T> ostream& operator<<(ostream& s, const vector<T>& d) {
	int len = d.size();
	REP (i, len) {
		s << d[i]; if (i < len - 1) s << "\t";
	}
	return s;
}

// 2 dimentional vector
template<typename T> ostream& operator<<(ostream& s, const vector< vector<T> >& d) {
	int len = d.size();
	REP (i, len) {
		s << d[i] << endl;
	}
	return s;
}

// map
template<typename T1, typename T2> ostream& operator<<(ostream& s, const map<T1, T2>& m) {
	s << "{" << endl;
	for (typeof(m.begin()) itr = m.begin(); itr != m.end(); ++itr) {
		s << "\t" << (*itr).first << " : " << (*itr).second << endl;
	}
	s << "}" << endl;
	return s;
}
// }}}
// }}}
// }}}
// time {{{
inline double now(){ struct timeval tv; gettimeofday(&tv, NULL); return (static_cast<double>(tv.tv_sec) + static_cast<double>(tv.tv_usec) * 1e-6); }
// }}}
// string manipulation {{{
inline VS split(string s, char delimiter) { VS v; string t; REP(i, s.length()) { if(s[i] == delimiter) v.PB(t), t = ""; else t += s[i]; } v.PB(t); return v; }
inline string join(VS s, string j) { string t; REP(i, s.size()) { t += s[i] + j; } return t; }
// }}}
// geometry {{{
#define Y real()
#define X imag()
// }}}
// 2 dimentional array {{{
enum { UP, RIGHT, DOWN, LEFT, UP_RIGHT, DOWN_RIGHT, DOWN_LEFT, UP_LEFT };
P dydx4[4] = { P(-1, 0), P(0, 1), P(1, 0), P(0, -1) };
P dydx8[8] = { P(-1, 0), P(0, 1), P(1, 0), P(0, -1), P(-1, 1), P(1, 1), P(1, -1), P(-1, -1) };
bool in_field(int H, int W, P p) {
	return (0 <= p.Y && p.Y < H) && (0 <= p.X && p.X < W);
}
// }}}
// input and output {{{
inline void input(string filename) {
	freopen(filename.c_str(), "r", stdin);
}
inline void output(string filename) {
	freopen(filename.c_str(), "w", stdout);
}
// }}}
// }}}

bool opt_debug = false;

// Could not come up with the solution.
// Saw http://kenkoooo.hatenablog.com/entry/2015/02/16/161201

int MOD;
VVI operator*(const VVI& lhs, const VVI& rhs) {
	// N x M * P x Q matrices => returns N x Q matrix
	int N = lhs.size(), M = lhs[0].size(), P = rhs.size(), Q = rhs[0].size();
	assert(M == P);
	VVI ret(N, VI(Q, 0));
	REP (i, N) {
		REP (j, Q) {
			REP (k, M) {
				ret[i][j] += lhs[i][k] * rhs[k][j];
				ret[i][j] %= MOD;
			}
		}
	}
	return ret;
}

int main(int argc, char** argv) {
	std::ios_base::sync_with_stdio(false);
	// set options {{{
	int __c;
	while ( (__c = getopt(argc, argv, "d")) != -1 ) {
		switch (__c) {
			case 'd':
				opt_debug = true;
				break;
			default:
				abort();
		}
	}
	// }}}

	// opt_debug = true;
	// input("./inputs/0.txt");
	// output("./outputs/0.txt");

	int N, A, B, C, T;
	while (cin >> N >> MOD >> A >> B >> C >> T, N | MOD | A | B | C | T) {
		VVI cells(N, VI(1, 0));
		REP (i, N) {
			cin >> cells[i][0];
		}

		int abc[] = {A, B, C};
		VVI matrix(N, VI(N, 0));
		REP (i, N) {
			int j = i-1;
			REP (k, 3) {
				if (0 <= j && j < N) {
					matrix[i][j] = abc[k];
				}
				j++;
			}
		}

		VVI D(N, VI(N, 0));
		REP (i, N) {
			REP (j, N) {
				if (i == j) {
					D[i][j] = 1;
				}
			}
		}

		// S_T = D^T * S_0
		int power = T;
		VVI _mat = matrix;
		while (power > 0) {
			if (power & 1) {
				D = D * _mat;
			}
			_mat = _mat * _mat;
			power >>= 1;
		}

		VVI ans = D * cells;
		REP (i, N) {
			if (i != 0) {
				cout << " ";
			}
			cout << ans[i][0];
		}
		cout << endl;
	}

	return 0;
}

// vim: foldmethod=marker