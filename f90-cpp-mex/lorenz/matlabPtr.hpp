#ifndef MATLABPTR_HPP
#define MATLABPTR_HPP

#include "MatlabDataArray.hpp"

// Answer by Mathworks user dhyun March 18 2022
// https://ch.mathworks.com/matlabcentral/answers/1573713-c-mex-data-api-how-can-i-get-the-raw-pointer-of-an-array-input-without-copying-it#answer_920804

template <typename T>
const T* getDataPtr(matlab::data::Array arr){
	const matlab::data::TypedArray<T> arr_t = arr;
	matlab::data::TypedIterator<const T> it(arr_t.begin());
	return it.operator->();
}

#endif // MATLABPTR_HPP
