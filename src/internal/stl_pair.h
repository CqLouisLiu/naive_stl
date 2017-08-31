//
// Created by Shuai on 2017/8/20.
//

#ifndef NAIVE_STL_PAIR_H
#define NAIVE_STL_PAIR_H

#include "stl_move.h"


namespace naive {

	/*
	* naive::pair is a struct template that provides a way to store two heterogeneous objects as a single unit.
	*/
	template <typename T1, typename T2>
	struct pair {

		typedef T1 first_type;
		typedef T2 second_type;

		T1  first;
		T2 second;

		pair() :first(), second() {}

		pair(const T1& _first, const T2& _second) :first(_first), second(_second) {}

		explicit pair(const T1& _first) :first(_first), second() {}


		pair(const pair& _p) = default;

		pair(pair&& _p) noexcept = default;

		template< class U1, class U2>
		explicit pair(const pair<U1, U2>& _p) :first(_p.first), second(_p.second) {};

		template< class U1, class U2>
		explicit pair(pair<U1, U2>&& _p) noexcept :first(naive::move(_p.first)), second(naive::move(_p.second)) {}

		pair& operator=(const pair& _other) {

			first = _other.first;
			second = _other.second;

			return *this;
		}

		pair& operator=(pair&& _other) noexcept {
			first = naive::move(_other.first);
			second = naive::move(_other.second);
			return *this;
		}

		~pair() = default;

	};

	template <typename _T1, typename _T2>
	inline bool operator==(const pair<_T1, _T2>& _p1, const pair<_T1, _T2>& _p2) {

		return (_p1.first == _p2.first) && (_p1.second == _p2.second);
	}

	template <typename _T1, typename _T2>
	inline bool operator!=(const pair<_T1, _T2>& _p1, const pair<_T1, _T2>& _p2) {

		return !(_p1 == _p2);
	}

	// expression p1<p2;
	template <typename _T1, typename _T2>
	inline bool operator<(const pair<_T1, _T2>& _p1, const pair<_T1, _T2>& _p2) {

		return (_p1.first<_p2.first) || (!(_p2.first<_p1.first) && (_p1.second<_p2.second));
	}

	// expression p1>p2 equal to p2<p1;
	template <typename _T1, typename _T2>
	inline bool operator>(const pair<_T1, _T2>& _p1, const pair<_T1, _T2>& _p2) {

		return _p2<_p1;
	}

	// expression p1>=p2 equal to !(p1<p2)
	template <typename _T1, typename _T2>
	inline bool operator>=(const pair<_T1, _T2>& _p1, const pair<_T1, _T2>& _p2) {

		return !(_p1<_p2);
	}

	// expression p1<=p2 equal to !(p2<p1)
	template <typename _T1, typename _T2>
	inline bool operator<=(const pair<_T1, _T2>& _p1, const pair<_T1, _T2>& _p2) {

		return !(_p2<_p1);
	}


	template <typename _T1, typename _T2>
	inline pair<_T1, _T2> Make_Pair(const _T1& _p1, const _T2& _p2) {

		return pair<_T1, _T2>(_p1, _p2);
	}

}



#endif //NAIVE_STL_PAIR_H

