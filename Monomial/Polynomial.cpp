#include "Polynomial.h"

#include <iostream>

Polynomial::Polynomial(int a)
{
	bases = { '\1'  };
	monomial[{0, }] = a;
	normalize();
}


Polynomial::Polynomial(const pair<const vector<int>&, int>& pair, const string& base)
	: Polynomial({pair.second, base, pair.first})
{}

Polynomial::Polynomial(const tuple<int, const string&, const vector<int>& >& monom)
	: Polynomial(0)
{
	int a = std::get<0>(monom);
	const string& bases_ = std::get<1>(monom);
	const vector<int>& powers = std::get<2>(monom);

	join_bases(bases_);
	monomial[generate_key(bases_, powers)] = a;
	normalize();
}

Polynomial::Polynomial(const vector< tuple<int, const string&, const vector<int>& > >& all)
	: Polynomial(0)
{
	for (const auto& elem : all)
		operator+=(elem);
}

string Polynomial::to_string() const
{
	vector<string> monomials;
	string res;

	for (const auto& elem : monomial)
	{
		if (elem.second == 0) continue;

		string monom;
		monom += std::to_string(elem.second);
		for (int i = 0; i < elem.first.size(); i++)
		{
			if (elem.first[i] == 1)
				monom += bases[i];
			else if (elem.first[i] != 0)	
				monom += bases[i] + ("^" + std::to_string(elem.first[i]));
		}
		monomials.push_back(monom);
	}

	if (monomials.empty())
		res = "0";
	else
	{
		for (int i = 0; i < monomials.size(); i++)
		{
			res += monomials[i];
			if (i + 1 < monomials.size() && monomials[i + 1][0] != '-')
				res += '+';
		}
	}

	return res;
}

void Polynomial::join_bases(const string& str)
{
	vector<int> positions;
	for (const auto& c : str)
	{
		if (isalpha(c))
		{
			size_t position = 0;
			while (position < bases.size() && bases[position] < c) position++;

			if (position == bases.size() || c != bases[position])
			{
				bases.insert(bases.begin() + position, c);
				positions.push_back(position);
			}
		}
	}

	vector< vector<int> > keys;

	for (const auto& elem : monomial)
		keys.push_back(elem.first);

	for (auto& key : keys)
	{
		auto node = monomial.extract(key);

		for (const auto& position : positions)
			key.insert(key.begin() + position, 0);

		node.key() = key;

		monomial.insert(std::move(node));
	}
}

vector<int> Polynomial::generate_key(const string& base, const vector<int>& powers)
{
	int position = 0;
	vector<int> key(bases.size(), 0);

	for (const auto& c : base)
	{
		size_t index = find(bases.begin(), bases.end(), c) - bases.begin();
		key[index] = powers[position];
		position++;
	}

	return key;
}

Polynomial& Polynomial::operator+=(const Polynomial& other)
{
	if (this == &other)
	{
		for (auto& item : monomial)
			item.second *= 2;
	}
	else
	{
		string otherbase(other.bases.begin(), other.bases.end());
		join_bases(otherbase);

		for (const auto& item : other.monomial)
			monomial[generate_key(otherbase, item.first)] += item.second;
	}
	normalize();
	
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other)
{
	if (this == &other)
	{
		for (auto& item : monomial)
			item.second = 0;
	}
	else
	{
		string otherbase(other.bases.begin(), other.bases.end());
		join_bases(otherbase);

		for (const auto& item : other.monomial)
			monomial[generate_key(otherbase, item.first)] -= item.second;
	}
	normalize();

	return *this;
}

vector<int> sum(const vector<int>& a, const vector<int>& b)
{
	vector<int> res = a;
	for (int i = 0; i < b.size(); i++)
		res[i] += b[i];
	return res;
}

Polynomial simple_mul(const Polynomial& a_, const Polynomial& b_)
{
	if (a_.monomial.size() != 1 || b_.monomial.size() != 1)
		throw std::runtime_error("Error");

	Polynomial a = a_, b = b_;

	a.join_bases({ b.bases.begin(), b.bases.end() });
	b.join_bases({ a.bases.begin(), a.bases.end() });

	int k = a.monomial.begin()->second * b.monomial.begin()->second;

	return Polynomial({sum(a.monomial.begin()->first, b.monomial.begin()->first), k}, {a.bases.begin(), a.bases.end()});
}

Polynomial Polynomial::operator*(const Polynomial& other) const
{
	Polynomial result;

	string other_base({ other.bases.begin(), other.bases.end() });
	string this_base({this->bases.begin(), this->bases.end()});

	for (const auto& elem: other.monomial)
		for (const auto& elem2 : this->monomial)
		{
			result += simple_mul({elem, other_base}, {elem2, this_base});
		}

	return result;
}

Polynomial& Polynomial::operator*=(const Polynomial& other)
{
	*this = other * *this;
	return *this;
}

Polynomial Polynomial::operator+(const Polynomial& other) const
{
	return (Polynomial() += other) += *this;
}

Polynomial Polynomial::operator-(const Polynomial& other) const
{
	return (Polynomial() -= other) -= *this;
}


void Polynomial::normalize()
{
	vector< vector<int> > keys;
	for (auto& elem: this->monomial)
	{
		if (elem.second == 0)
			keys.push_back(elem.first);
	}

	for (const auto& key : keys)
		this->monomial.erase(key);
}


ostream& operator<<(ostream& stream, const Polynomial& m)
{
	return stream << m.to_string();
}

int main()
{
	Polynomial m(
		{
			{ 4, "xy", {1, 1 } },
			{ -2, "x", {1,  } },
		}
	);

	Polynomial n(
		{
			{ 5, "xyz", {1, 3, 1 } },
			{ -3, "z", {4,  } },
		}
	);

	std::cout << m * n << std::endl;
}
