#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
#define MAXN 100000
#define NUM_CASES 10

//inclusive
int rand(int a, int b)
{
	return (rand() % (b - a + 1) + a);
}

//easy version

int main() {
	srand(time(NULL));
	ofstream cout;

	for (int i = 1; i <= NUM_CASES; i++)
	{
		string format = ".in";
		string test_data = "";
		int N = 0;

		if (i == 1)
			test_data = "9\nABBCCCBAB";
		else if (i == 2 || i == 3)
			N = rand(20, 100);
		else if (i == 8 || i == 10)
			N = MAXN;
		else
			N = rand(75000, MAXN);

		if (i != 1)
		{
			test_data += to_string(N) + "\n";
			string letters[3] = { "A", "B", "C" };
			for (int i = 0; i < N; i++)
				test_data += letters[rand(0, 2)];
		}

		cout.open(to_string(i) + format);
		if (cout)
		{
			cout << test_data << "\n";
			cout.close();
		}
	}
}
