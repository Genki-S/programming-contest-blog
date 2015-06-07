#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
static const double EPS = 1e-10;
#define FOR(i, b, e) for (int i = (b); i < (e); ++i)
#define REP(i, n) FOR(i, 0, n)
#define dump(x) cerr << " [L" << __LINE__ << "] " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << " [L:" << __LINE__ << "] " << #x << " = "; REP(q, (x).size()) cerr << (x)[q] << " "; cerr << endl;

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

// BEGIN CUT HERE
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1) 
	{
		srand(time(0));
		cout << "Testing Coversta (250.0 points)" << endl << endl;
		for (int i = 0; i < 100; i++)
		{
			ostringstream s; s << argv[0] << " " << i << " " << rand();
			int exitCode = system(s.str().c_str());
			if (exitCode)
				cout << "#" << i << ": Runtime Error" << endl;
		}
		int T = time(NULL)-1433550867;
		double PT = T/60.0, TT = 75.0;
		cout.setf(ios::fixed,ios::floatfield);
		cout.precision(2);
		cout << endl;
		cout << "Time  : " << T/60 << " minutes " << T%60 << " secs" << endl;
		cout << "Score : " << 250.0*(.3+(.7*TT*TT)/(10.0*PT*PT+TT*TT)) << " points" << endl;
	}
	else
	{
		int _tc; istringstream(argv[1]) >> _tc;
		int _seed; istringstream(argv[2]) >> _seed;
		srand(_seed);
		Coversta _obj;
		int _expected, _received;
		time_t _start = clock();
		switch (_tc)
		{
			case 0:
			{
				string a[] = {"11",
				              "11"};
				int x[] = {0,0};
				int y[] = {0,1};
				_expected = 4;
				_received = _obj.place(vector <string>(a, a+sizeof(a)/sizeof(string)), vector <int>(x, x+sizeof(x)/sizeof(int)), vector <int>(y, y+sizeof(y)/sizeof(int))); break;
			}
			case 1:
			{
				string a[] = {"11",
				              "11"};
				int x[] = {0,1};
				int y[] = {0,1};
				_expected = 3;
				_received = _obj.place(vector <string>(a, a+sizeof(a)/sizeof(string)), vector <int>(x, x+sizeof(x)/sizeof(int)), vector <int>(y, y+sizeof(y)/sizeof(int))); break;
			}
			case 2:
			{
				string a[] = {"15",
				              "61"};
				int x[] = {0};
				int y[] = {0};
				_expected = 11;
				_received = _obj.place(vector <string>(a, a+sizeof(a)/sizeof(string)), vector <int>(x, x+sizeof(x)/sizeof(int)), vector <int>(y, y+sizeof(y)/sizeof(int))); break;
			}
			case 3:
			{
				string a[] = {"151",
				              "655",
				              "661"};
				int x[] = {0,0,-1};
				int y[] = {0,1,0};
				_expected = 33;
				_received = _obj.place(vector <string>(a, a+sizeof(a)/sizeof(string)), vector <int>(x, x+sizeof(x)/sizeof(int)), vector <int>(y, y+sizeof(y)/sizeof(int))); break;
			}
			case 4:
			{
				string a[] = {"303",
				              "333",
				              "000"};
				int x[] = {-1,-1};
				int y[] = {-1,1};
				_expected = 12;
				_received = _obj.place(vector <string>(a, a+sizeof(a)/sizeof(string)), vector <int>(x, x+sizeof(x)/sizeof(int)), vector <int>(y, y+sizeof(y)/sizeof(int))); break;
			}
			case 5:
			{
				string a[] = {"0000000",
				              "1010101"};
				int x[] = {-1,-1};
				int y[] = {-1,1};
				_expected = 0;
				_received = _obj.place(vector <string>(a, a+sizeof(a)/sizeof(string)), vector <int>(x, x+sizeof(x)/sizeof(int)), vector <int>(y, y+sizeof(y)/sizeof(int))); break;
			}
/*
			case 6:
			{
				string a[] = ;
				int x[] = ;
				int y[] = ;
				_expected = ;
				_received = _obj.place(vector <string>(a, a+sizeof(a)/sizeof(string)), vector <int>(x, x+sizeof(x)/sizeof(int)), vector <int>(y, y+sizeof(y)/sizeof(int))); break;
			}
*/
/*
			case 7:
			{
				string a[] = ;
				int x[] = ;
				int y[] = ;
				_expected = ;
				_received = _obj.place(vector <string>(a, a+sizeof(a)/sizeof(string)), vector <int>(x, x+sizeof(x)/sizeof(int)), vector <int>(y, y+sizeof(y)/sizeof(int))); break;
			}
*/
/*
			case 8:
			{
				string a[] = ;
				int x[] = ;
				int y[] = ;
				_expected = ;
				_received = _obj.place(vector <string>(a, a+sizeof(a)/sizeof(string)), vector <int>(x, x+sizeof(x)/sizeof(int)), vector <int>(y, y+sizeof(y)/sizeof(int))); break;
			}
*/
			default:
				return 0;
			/*
			{
			cout << "seed of this test is: " << _seed << endl;
			// implement test generation code
				string a[] = ;
				int x[] = ;
				int y[] = ;
				_expected = ;
				_received = _obj.place(vector <string>(a, a+sizeof(a)/sizeof(string)), vector <int>(x, x+sizeof(x)/sizeof(int)), vector <int>(y, y+sizeof(y)/sizeof(int)));
			}
			*/
		}
		cout.setf(ios::fixed,ios::floatfield);
		cout.precision(2);
		double _elapsed = (double)(clock()-_start)/CLOCKS_PER_SEC;
		if (_received == _expected)
			cout << "#" << _tc << ": Passed (" << _elapsed << " secs)" << endl;
		else
		{
			cout << "#" << _tc << ": Failed (" << _elapsed << " secs)" << endl;
			cout << "           Expected: " << _expected << endl;
			cout << "           Received: " << _received << endl;
		}
	}
}

// END CUT HERE
