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
// enum { UP, RIGHT, DOWN, LEFT, UP_RIGHT, DOWN_RIGHT, DOWN_LEFT, UP_LEFT };
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

// Header under development {{{

int LCM(int a, int b) {
	// FIXME
	return a * b;
}

// Fraction class {{{
// ref: http://martin-thoma.com/fractions-in-cpp/
class Fraction {
	public:
		ULL numerator;
		ULL denominator;
		Fraction(ULL _numerator, ULL _denominator) {
			assert(_denominator > 0);
			numerator = _numerator;
			denominator = _denominator;
		};

		Fraction operator*(const ULL rhs) {
			return Fraction(this->numerator * rhs, this->denominator);
		};

		Fraction operator*(const Fraction& rhs) {
			return Fraction(this->numerator * rhs.numerator, this->denominator * rhs.denominator);
		}

		Fraction operator+(const Fraction& rhs) {
			ULL lcm = LCM(this->denominator, rhs.denominator);
			ULL numer_lhs = this->numerator * (this->denominator / lcm);
			ULL numer_rhs = rhs.numerator * (rhs.numerator / lcm);
			return Fraction(numer_lhs + numer_rhs, lcm);
		}

		Fraction& operator+=(const Fraction& rhs) {
			Fraction result = (*this) + rhs;
			this->numerator = result.numerator;
			this->denominator = result.denominator;
			return *this;
		}
};

std::ostream& operator<<(std::ostream &s, const Fraction &a) {
	if (a.denominator == 1) {
		s << a.numerator;
	} else {
		s << a.numerator << "/" << a.denominator;
	}
	return s;
}

// }}}

// }}}

bool opt_debug = false;
typedef vector<VVI> VVVI;

// enum { UP, RIGHT, DOWN, LEFT, UP_RIGHT, DOWN_RIGHT, DOWN_LEFT, UP_LEFT };
enum DIRECTIONS { LEFT, FRONT, RIGHT, BACK };

class Die {
	private:
	public:
		int top, bottom, front, back, left, right;
		Die(int _top, int _front) {
			top = _top;
			front = _front;
			bottom = 7 - top;
			back = 7 - front;
			if (top == 1 || top == 6) {
				if (front == 5) { left = 4; }
				if (front == 3) { left = 5; }
				if (front == 2) { left = 3; }
				if (front == 4) { left = 2; }
			} else if (top == 2 || top == 5) {
				if (front == 1) { left = 4; }
				if (front == 3) { left = 1; }
				if (front == 6) { left = 3; }
				if (front == 4) { left = 6; }
			} else if (top == 3 || top == 4) {
				if (front == 5) { left = 1; }
				if (front == 6) { left = 5; }
				if (front == 2) { left = 6; }
				if (front == 1) { left = 2; }
			}
			if (top == 6 || top == 5 || top == 4) {
				left = 7 - left;
			}
			right = 7 - left;
		}

		Die roll(int dir) {
			if (dir == LEFT) {
				return Die(right, front);
			} else if (dir == FRONT) {
				return Die(back, top);
			} else if (dir == RIGHT) {
				return Die(left, front);
			} else {
				return Die(front, bottom);
			}
		}
};

void roll(VVVI& field, Die die, int z, int x, int y) {
	dprt("roll: (%d, %d, %d)\n", x, y, z);
	dprt("die: top:%d, bottom: %d, front:%d, back:%d, left:%d, right:%d\n", die.top, die.bottom, die.front, die.back, die.left, die.right);
	if (z == 0) {
		field[z][x][y] = die.top;
		return;
	}
	if (field[z-1][x][y] == 0) {
		roll(field, die, z-1, x, y);
		return;
	}

	vector<PII> dirs;
	dirs.PB(MP(die.front, FRONT));
	dirs.PB(MP(die.left, LEFT));
	dirs.PB(MP(die.back, BACK));
	dirs.PB(MP(die.right, RIGHT));
	RSORT(dirs);
	REP (i, 4) {
		int diced = dirs[i].F;
		int dir = dirs[i].S;
		if (diced != 4 && diced != 5 && diced != 6) {
			continue;
		}
		int nx = x + dydx4[dir].X;
		int ny = y + dydx4[dir].Y;
		dump(diced); dump(dir); dump(x); dump(y); dump(nx); dump(ny); dump(z);
		dump(field[z-1][nx][ny])
		if (field[z-1][nx][ny] == 0) {
			roll(field, die.roll(dir), z-1, nx, ny);
			return;
		}
	}
	field[z][x][y] = die.top;
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

	const int OFFSET = 100;
	// opt_debug = true;
	// input("./inputs/0.txt");
	// output("./outputs/0.txt");

	int n;
	while (cin >> n, n) {
		VVVI field(OFFSET*2, VVI(OFFSET*2, VI(OFFSET*2, 0)));
		REP (i, n) {
			int t, f; cin >> t >> f;
			Die die(t, f);
			int z = 0;
			while (field[z][OFFSET][OFFSET] != 0) {
				z++;
			}
			roll(field, die, z, OFFSET, OFFSET);
			dumpl(field[0]);
		}

		VI ans(6, 0);
		REP (x, OFFSET*2) {
			REP (y, OFFSET*2) {
				int t = 0;
				REP (z, OFFSET*2) {
					if (field[z][x][y] == 0) {
						break;
					} else {
						t = field[z][x][y];
					}
				}
				if (t != 0) {
					ans[t-1]++;
				}
			}
		}
		REP (i, 6) {
			if (i != 0) {
				cout << " ";
			}
			cout << ans[i];
		}
		cout << endl;
	}

	return 0;
}

// vim: foldmethod=marker
