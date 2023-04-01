#include<bits/stdc++.h>
using namespace std;

bool fail = 0;

// random number from 0 to 2^64-1 (be careful about it taking unsigned int / long long!)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// random number from a to b
long long randint(long long a, long long b)
{
	return uniform_int_distribution<long long>(a, b)(rng);
}


// put constraints under here
const int maxn = 1e5;
const int mod = 1e9 + 7;
int h[maxn];
long long dp[maxn + 1];

long long powm(long long b, long long e) {
	b %= mod;

	long long ans = 1;

	while (e) {
		if (e & 1) {
			ans = (ans * b) % mod;
		}

		e >>= 1;
		b = (b * b) % mod;
	}

	return ans;
}


// print test case to stdout
void generate_test(int test_num)
{
	vector<string> test_cases;
	int tot_n = 0;
	while (1)
	{
		int n = randint(1, pow(10,1+(test_num-1)/10));

		if (tot_n + n > maxn) break;

		tot_n += n;

		int k = randint(2, 10 + (1e5 * randint(0, 1))); // some small and some big k (sometimes k < n is important)

		test_cases.push_back(to_string(n) + ' ' + to_string(k) + '\n');
		
		for (int i = 0; i < n; i++)
		{
			test_cases.back() += to_string(randint(1, n)) + ' ';
		}
		test_cases.back() += '\n';
	}

	cout << test_cases.size() << '\n';
	for (auto& test_case : test_cases) 
	{
		cout << test_case;
	}

}

// read test case from stdin and print solution to stdout
void model_sol()
{
	// O(n)

	cin.tie(0)->sync_with_stdio(0);

	int t; cin >> t;

	while (t--)
	{
		// read in input
		int n, k; cin >> n >> k;

		for (int i = 0; i < n; i++)
		{
			cin >> h[i];
		}

		// precompute helpful inverses
		long long inv_k = powm(k, mod - 2);
		long long inv_k_mi_1 = powm(k - 1, mod - 2);
		long long inv_k_mi_1_sq = powm(inv_k_mi_1, 2);

		// compute dp
		dp[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			long long e = 0; // expected moves assuming Rengoku chooses F != 1

			for (int f = 2; f * f <= i and f <= k; f++)
			{
				if ((i / f) * (i / f) >= i)
				{ // edge case where if N < sqrt(n) * (sqrt(n) + 1), new health < sqrt(i) for f = floor(sqrt(i))
					e = (e + dp[i / f]) % mod; // new health >= sqrt(i)
				}
			}

			for (int j = 1; j * j < i; j++)
			{
				int f_largest = i / j; // largest f such that i/f = j
				int f_smallest = i / (j + 1) + 1; // smallest f such that i/f = j

				if (f_smallest <= k)
				{
					// get intersection between possible forms (1..k) and forms that reach health j
					e = (e + (min(f_largest, k) - f_smallest + 1) * dp[i / f_largest]) % mod; // new health < sqrt(i)
				}
			}

			// new health = 0 takes 0 extra forms

			e = ((k - 1 + e) * inv_k) % mod;

			// arithmetico geometric series formula
			dp[i] = (((k * e % mod) * inv_k_mi_1 % mod) + (k * inv_k_mi_1_sq % mod)) % mod;
		}

		long long ans = 0;

		for (int i = 0; i < n; i++)
		{
			ans += dp[h[i]];
		}

		cout << ans % mod << '\n';
	}
}

// read test case from stin and print solution to stdout
void brute_sol()
{
	// O(n^2/2)

	cin.tie(0)->sync_with_stdio(0);

	int t; cin >> t;

	while (t--)
	{
		// read in input
		int n, k; cin >> n >> k;

		for (int i = 0; i < n; i++)
		{
			cin >> h[i];
		}

		// precompute helpful inverses
		long long inv_k = powm(k, mod - 2);
		long long inv_k_mi_1 = powm(k - 1, mod - 2);
		long long inv_k_mi_1_sq = powm(inv_k_mi_1, 2);

		// compute dp
		dp[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			long long e = 0; // expected moves assuming Rengoku chooses F != 1

			for (int f = 2; f <= i and f <= k; f++) {
				e = (e + dp[i / f]) % mod;
			}

			// new health = 0 takes 0 extra forms

			e = ((k - 1 + e) * inv_k) % mod;

			// arithmetico geometric series formula
			dp[i] = (((k * e % mod) * inv_k_mi_1 % mod) + (k * inv_k_mi_1_sq % mod)) % mod;
		}

		long long ans = 0;

		for (int i = 0; i < n; i++)
		{
			ans += dp[h[i]];
		}

		cout << ans % mod << '\n';
	}
}

// for checking tests look right
void read_and_print_file(string directory, string name)
{
	freopen((directory + name).c_str(), "r", stdin);

	string a;
	while (getline(cin, a))
	{
		cout << a << '\n';
	}

	exit(0);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int num_tests = 40;

	string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Rengoku's Flame Breathing\Checking Model with Brute Tests\)";

	// read_and_print_file(directory, "1.in"); 

	for (int test_num = 1; test_num <= num_tests; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test(test_num);

		// generate the output for the model
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + "model" + ".out").c_str(), "w", stdout);
		model_sol();
		fflush(stdout); // because otherwise when reading output for model/brute last line might still be in the buffer
		// generate the output for the brute
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + "brute" + ".out").c_str(), "w", stdout);
		brute_sol();
		fflush(stdout); // because otherwise when reading output for model/brute last line might still be in the buffer

		vector<string> model_output, brute_output;
		string temp;

		// read output for the model
		ifstream fin((directory + to_string(test_num) + "model" + ".out").c_str());
		while (fin >> temp)
		{
			model_output.push_back(temp);
		}
		fin.close();
		// read output for the brute
		fin.open((directory + to_string(test_num) + "brute" + ".out").c_str());
		while (fin >> temp)
		{
			brute_output.push_back(temp);
		}
		fin.close();

		// compare outputs
		cerr << "model and brute sizes: " << model_output.size() << ' ' << brute_output.size() << '\n';
		for (int i = 0; i < min(model_output.size(), brute_output.size()); i++)
		{

			if (model_output[i] != brute_output[i])
			{
				cerr << "The model and the brute do not agree!\n";
				cerr << "Differ Test: " << test_num << '\n';
				cerr << "Differ Index: " << i << '\n';
				cerr << "Differ Values: " << model_output[i] << ' ' << brute_output[i] << '\n';
				fail = 1;
			}
		}
	}

	if (!fail) {
		cerr << "The model and the brute agree!\n";
	}
}