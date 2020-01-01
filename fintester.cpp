#include <bits/stdc++.h>
using namespace std;


int main()
{
	string boz = "mobile.csv";
	ifstream fin(boz.c_str());
	string line;
	getline(fin, line);
	while (getline(fin, line))
	{
		cout << "line is " << line << endl;
	}	
	return 0;
}