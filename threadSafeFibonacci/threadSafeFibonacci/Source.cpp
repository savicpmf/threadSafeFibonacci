#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;


int fibonaci(int n)
{
	if (n <= 1)
	{
		return n;
	}

	else
	{
		return fibonaci(n - 1) + fibonaci(n-2);
	}
}

void posao(int pocetak,int kraj,int radPoNit,atomic<int>& rezultat)
{
	for (int i = pocetak; i < kraj; i++)
	{
		//cout << "fibonaci [" << i << "] = " << fibonaci(i) << " ";
		rezultat += fibonaci(i);
	}
}

// ovo je drugi branch


int main()
{
	atomic<int> rezultat;
	int i, zbir = 0, brojNiti = 8, n = 10, start = 0, end = 0;
	vector<thread>niti(brojNiti);

	int radPoNit = (n+brojNiti-1)/brojNiti;

	

	for (i = 0; i < brojNiti-1; i++)
	{
		end = min(start + radPoNit, n);
		niti[i] = thread(posao, start, end, radPoNit, ref(rezultat));
		start = end;
		if (start >= n)
			break;
	}
	posao(start, n+1, radPoNit, rezultat);

	//for_each(niti.begin(), find_if(niti.begin(), niti.end(), [](const thread& t) { return !t.joinable(); }), mem_fn(&thread::join));

	for (auto& t : niti) {
		if (t.joinable()) {
			t.join();
		}
	}

	cout << rezultat;
	

	return 0;
}