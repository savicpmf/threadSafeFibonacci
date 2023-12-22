#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;
// ovo je drugi branch koji koristi lockguard umesto atomic rezultat

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

void posao(int pocetak,int kraj,int radPoNit,int& rezultat, mutex& m)
{
	for (int i = pocetak; i < kraj; i++)
	{
		//cout << "fibonaci [" << i << "] = " << fibonaci(i) << " ";
		lock_guard<mutex> lg(m);
		rezultat += fibonaci(i);
	}
}




int main()
{
	mutex m;
	int rezultat=0;
	int i, zbir = 0, brojNiti = 35, n = 35, start = 0, end = 0;
	vector<thread>niti(brojNiti);

	int radPoNit = (n+brojNiti-1)/brojNiti;

	

	for (i = 0; i < brojNiti-1; i++)
	{
		end = min(start + radPoNit, n);
		niti[i] = thread(posao, start, end, radPoNit, ref(rezultat),ref(m));
		start = end;
		if (start >= n)
			break;
	}
	posao(start, n+1, radPoNit, rezultat,m);

	//for_each(niti.begin(), find_if(niti.begin(), niti.end(), [](const thread& t) { return !t.joinable(); }), mem_fn(&thread::join));

	for (auto& t : niti) {
		if (t.joinable()) {
			t.join();
		}
	}

	cout << rezultat;
	

	return 0;
}