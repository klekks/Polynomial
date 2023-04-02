#pragma once

template <typename Type>
Type create_polynomial(Type value);

template <typename Type>
Type  create_polynomial(Type letter, Type power);

template <typename Type>
Type multiply_polynomial(Type polynomial, const Type Polynomial2);

template <typename Type>
Type add_polynomial(Type polynomial, const Type Polynomial2);

template <typename Type>
Type sub_polynomial(Type polynomial, const Type Polynomial2);

template <typename Type>
Type create_key(Type c);

template <typename Type>
Type update_key(Type key_, Type c);

template <typename Type>
void delete_key(Type key);

template <typename Type>
Type get_variable(Type key_);

template <typename Type>
Type set_variable(Type key_, Type value_);