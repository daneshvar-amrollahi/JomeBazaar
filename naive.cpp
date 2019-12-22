#include <iostream>
#include <fstream>

#include <vector>
#include <unordered_map>
#include <math.h>

using namespace std;

vector <string> split_by_comma(string line)
{
	vector <string> ans;
	string cur = "";
	for (int i = 0 ; i < line.size() ; i++)
	{
		if (line[i] == ',')
		{
			ans.push_back(cur);
			cur = "";
			continue;
		}
		cur += line[i];
	}				
	ans.push_back(cur);
	return ans;
}

unordered_map<string, double> getGoods()
{
	unordered_map <string, double> good;
	ifstream fin("train.csv");
	string line;
	getline(fin, line);
	while (getline(fin, line))
	{
		if (line[0] - '0' >= 0 && line[0] - '0' < 10)
			continue;
		vector <string> q = split_by_comma(line);
		string word = q[0];
		double p_good = stod(q[1]);

		good[word] = p_good;
	}	
	return good;
}

unordered_map<string, double> getBads()
{
	unordered_map <string, double> bad;
	ifstream fin("train.csv");
	string line;
	getline(fin, line);
	while (getline(fin, line))
	{
		if (line[0] - '0' >= 0 && line[0] - '0' < 10)
			continue;
		vector <string> q = split_by_comma(line);
		string word = q[0];
		double p_bad = stod(q[2]);
		bad[word] = p_bad;
	}	
	return bad;
}

vector < pair<string, int> > readComments()
{
	ifstream fin("test.csv");
	string line;
	vector < pair<string, int> > ans;
	getline(fin, line);
	while (getline(fin, line))
	{
		int last = line[line.size() - 1] - '0';
		line.resize(line.size() - 1);
		ans.push_back(make_pair(line, last));
	}
	return ans;
} 

vector <string> split_by_space(string line)
{
	vector <string> ans;
	string cur = "";
	for (int i = 0 ; i < line.size() ; i++)
	{
		if (line[i] == ' ')
		{
			if (cur != "")
				ans.push_back(cur);
			cur = "";
			continue;
		}
		cur += line[i];
	}			
	if (cur != "")	
		ans.push_back(cur);
	return ans;
}

int isBad(string comment, unordered_map<string, double> good, unordered_map<string, double> bad)
{
	long double spam = 0, ham = 0;
	vector <string> words = split_by_space(comment);
	for (int i = 0 ; i < words.size() ; i++)
	{
		string word = words[i];
		if (good.find(word) != good.end())
		{
			ham += (long double)(log(good[word]));
			spam += (long double)(log(bad[word]));
		}
		
	}
	return (spam > ham);
}

void evaluate(vector < pair<string, int> > comments, unordered_map<string, double> good, unordered_map<string, double> bad)
{
	int correct_detected_appropriate = 0, all_appropriate = 0;
	int detected_appropriate = 0, correct_detected = 0;
	for (int i = 0 ; i < 20 ; i++)
	{
		if (i % 100 == 0)
			cout << i << endl;
		string comment = comments[i].first;
		int is_bad = comments[i].second;
		int detected_bad = isBad(comment, good, bad);
		correct_detected_appropriate += ( (!is_bad) && (!detected_bad) );
		all_appropriate += (!is_bad);

		detected_appropriate += (!detected_bad);

		correct_detected += (is_bad == detected_bad);
	}

	cout << "Recall: " << (double(correct_detected_appropriate) / double(all_appropriate)) * 100.0 << endl;
	cout << "Precision: " << (double(correct_detected_appropriate) / double(detected_appropriate)) * 100.0 << endl;
	cout << "Accuracy: " << (double(correct_detected) / double(comments.size())) * 100.0 << endl;
}

int main()
{
	unordered_map<string, double> good = getGoods();
	unordered_map<string, double> bad = getBads();
	vector < pair<string, int> > comments = readComments();
	evaluate(comments, good, bad);
	return 0;
}