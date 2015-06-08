#include <iostream>
#include <string>
#include <vector>
using namespace std;
static const double EPS = 1e-10;
#define FOR(i, b, e) for (int i = (b); i < (e); ++i)
#define REP(i, n) FOR(i, 0, n)
#define dump(x) cerr << " [L" << __LINE__ << "] " << #x << " = " << (x) << endl;
#define dumpv(x) cerr << " [L:" << __LINE__ << "] " << #x << " = "; REP(q, (x).size()) cerr << (x)[q] << " "; cerr << endl;

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
		cout << "Testing Privateparty (500.0 points)" << endl << endl;
		for (int i = 0; i < 100; i++)
		{
			ostringstream s; s << argv[0] << " " << i << " " << rand();
			int exitCode = system(s.str().c_str());
			if (exitCode)
				cout << "#" << i << ": Runtime Error" << endl;
		}
		int T = time(NULL)-1433558918;
		double PT = T/60.0, TT = 75.0;
		cout.setf(ios::fixed,ios::floatfield);
		cout.precision(2);
		cout << endl;
		cout << "Time  : " << T/60 << " minutes " << T%60 << " secs" << endl;
		cout << "Score : " << 500.0*(.3+(.7*TT*TT)/(10.0*PT*PT+TT*TT)) << " points" << endl;
	}
	else
	{
		int _tc; istringstream(argv[1]) >> _tc;
		int _seed; istringstream(argv[2]) >> _seed;
		srand(_seed);
		Privateparty _obj;
		double _expected, _received;
		time_t _start = clock();
		switch (_tc)
		{
			case 0:
			{
				int a[] = {0,1};
				_expected = 2.0;
				_received = _obj.getexp(vector <int>(a, a+sizeof(a)/sizeof(int))); break;
			}
			case 1:
			{
				int a[] = {0,0};
				_expected = 1.5;
				_received = _obj.getexp(vector <int>(a, a+sizeof(a)/sizeof(int))); break;
			}
			case 2:
			{
				int a[] = {0,1,1};
				_expected = 2.5;
				_received = _obj.getexp(vector <int>(a, a+sizeof(a)/sizeof(int))); break;
			}
			case 3:
			{
				int a[] = {0,1,1,2};
				_expected = 3.166666666666667;
				_received = _obj.getexp(vector <int>(a, a+sizeof(a)/sizeof(int))); break;
			}
			case 4:
			{
				int a[] = {3,2,1,0};
				_expected = 2.0;
				_received = _obj.getexp(vector <int>(a, a+sizeof(a)/sizeof(int))); break;
			}
			case 5:
			{
				int a[] = {0};
				_expected = 1.0;
				_received = _obj.getexp(vector <int>(a, a+sizeof(a)/sizeof(int))); break;
			}
			case 6:
			{
				int a[] = {0, 4, 5, 1, 8, 1, 0, 0, 2, 8, 6, 0, 9};
				_expected = 8.229365079365078;
				_received = _obj.getexp(vector <int>(a, a+sizeof(a)/sizeof(int))); break;
			}
/*
			case 7:
			{
				int a[] = ;
				_expected = ;
				_received = _obj.getexp(vector <int>(a, a+sizeof(a)/sizeof(int))); break;
			}
*/
			default:
				return 0;
			/*
			{
			cout << "seed of this test is: " << _seed << endl;
			// implement test generation code
				int a[] = ;
				_expected = ;
				_received = _obj.getexp(vector <int>(a, a+sizeof(a)/sizeof(int)));
			}
			*/
		}
		cout.setf(ios::fixed,ios::floatfield);
		cout.precision(2);
		double _elapsed = (double)(clock()-_start)/CLOCKS_PER_SEC;
		if (abs(_expected-_received) < 1e-9 || (_received > min(_expected*(1.0-1e-9), _expected*(1.0+1e-9)) && _received < max(_expected*(1.0-1e-9), _expected*(1.0+1e-9))))
			cout << "#" << _tc << ": Passed (" << _elapsed << " secs)" << endl;
		else
		{
			cout << "#" << _tc << ": Failed (" << _elapsed << " secs)" << endl;
			cout.precision(10);
			cout << "           Expected: " << _expected << endl;
			cout << "           Received: " << _received << endl;
		}
	}
}

// END CUT HERE
