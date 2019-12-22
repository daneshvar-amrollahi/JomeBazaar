#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <string>
#include <vector>

using namespace std;

class Product
{
protected:
	int product_id;
	vector < pair<string, string> > comments;
public:
	Product(int _product_id);
	int getProductId() {return product_id;}
	void addComment(string username, string s) {comments.push_back(make_pair(username, s));}

	vector < pair<string, string> > getComments() {return comments;}
};

#endif