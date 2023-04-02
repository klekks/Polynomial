#pragma once

#include <map>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

class Polynomial
{
public:
	Polynomial() : Polynomial(0) {}
	Polynomial(int a);
	Polynomial(const tuple<int, const string&, const vector<int>& >&);
	Polynomial(const vector<tuple<int, const string&, const vector<int>& >>&);

	Polynomial(const pair<const vector<int>&, int>&, const string& base);

	Polynomial& operator+=(const Polynomial&);
	Polynomial& operator-=(const Polynomial&);
	Polynomial& operator*=(const Polynomial&);
	Polynomial operator*(const Polynomial&) const;
	Polynomial operator+(const Polynomial&) const;
	Polynomial operator-(const Polynomial&) const;

	string to_string() const;

	friend ostream& operator<<(ostream&, const Polynomial&);
	friend Polynomial simple_mul(const Polynomial& a, const Polynomial& b);

private:
	void join_bases(const string&);
	vector<int> generate_key(const string&, const vector<int>&);
	void normalize();
	

	vector<char> bases;
	map < vector<int>, int> monomial;
};

