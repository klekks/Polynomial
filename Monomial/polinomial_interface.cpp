#include "polinomial_interface.h"

#include "Polynomial.h"

#include <string>
#include <unordered_map>


static std::unordered_map<std::string, Polynomial*> storage;

template <typename Type>
Type create_polynomial(Type value)
{
	Polynomial* polynomial = new Polynomial(value);
	return static_cast<Type>(polynomial);
}

template <typename Type>
Type  create_polynomial(Type letter, Type power)
{
	Polynomial* polynomial = new Polynomial({ 1, {letter, 0}, {power, } });
	return static_cast<Type>(polynomial);
}

template <typename Type>
Type multiply_polynomial(Type polynomial, const Type Polynomial2)
{
	const Polynomial* donor = static_cast<const Polynomial*>(Polynomial2);
	Polynomial* polynomus = static_cast<Polynomial*>(polynomial);
	polynomus->operator*=(donor);
	delete donor;
	return static_cast<Type>(polynomus);
}

template <typename Type>
Type add_polynomial(Type polynomial, const Type Polynomial2)
{
	const Polynomial* donor = static_cast<const Polynomial*>(Polynomial2);
	Polynomial* polynomus = static_cast<Polynomial*>(polynomial);
	polynomus->operator+=(donor);
	delete donor;
	return static_cast<Type>(polynomus);
}

template <typename Type>
Type sub_polynomial(Type polynomial, const Type Polynomial2)
{
	const Polynomial* donor = static_cast<const Polynomial*>(Polynomial2);
	Polynomial* polynomus = static_cast<Polynomial*>(polynomial);
	polynomus->operator-=(donor);
	delete donor;
	return static_cast<Type>(polynomus);
}

template <typename Type>
Type create_key(Type c)
{
	return static_cast<Type>( new std::string(1, (char)c) );
}

template <typename Type>
Type update_key(Type key_, Type c)
{
	std::string* key = static_cast<std::string*>(key_);
	key->operator+=(c);
	return static_cast<Type>( key );
}

template <typename Type>
void delete_key(Type key)
{
	delete static_cast<std::string*>(key);
}

template <typename Type>
Type get_variable(Type key_)
{
	std::string* key = static_cast<std::string*>(key_);
	return storage[*key];
}

template <typename Type>
Type set_variable(Type key_, Type value_)
{
	std::string* key = static_cast<std::string*>(key_);
	Polynomial* polynomial = static_cast<Polynomial*>(value_);
	return static_cast<Type>(polynomial);
}
