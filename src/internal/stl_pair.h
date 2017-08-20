//
// Created by Shuai on 2017/8/20.
//

#ifndef NAIVE_STL_PAIR_H
#define NAIVE_STL_PAIR_H
#include<utility>

namespace naive{

	/*
	* naive::Pair is a struct template that provides a way to store two heterogeneous objects as a single unit.
	*/
	template <typename T1,typename T2>
	struct Pair{

		typedef T1 first_type;
		typedef T2 second_type;

		T1  first;
		T2 second;

		Pair():first(),second(){}

		Pair(const T1& _first,const T2& _second):first(_first),second(_second){}

		explicit Pair(const T1& _first):first(_first),second(){}


		Pair(const Pair& _p)= default;

		Pair(Pair&& _p) noexcept= default;

		template< class U1, class U2>
		explicit Pair(const Pair<U1, U2>& _p):first(_p.first),second(_p.second){};

		template< class U1, class U2>
		explicit Pair(Pair<U1, U2>&& _p) noexcept :first(std::move(_p.first)),second(std::move(_p.second)){}

		Pair& operator=(const Pair& _other){

			first=_other.first;
			second=_other.second;

			return *this;
		}

		Pair& operator=(Pair&& _other) noexcept{
			first=std::move(_other.first);
			second=std::move(_other.second);
			return *this;
		}

		~Pair()= default;

	};

	template <typename _T1,typename _T2>
	inline bool operator==(const Pair<_T1,_T2>& _p1,const Pair<_T1,_T2>& _p2){

		return (_p1.first==_p2.first)&&(_p1.second==_p2.second);
	}

	template <typename _T1,typename _T2>
	inline bool operator!=(const Pair<_T1,_T2>& _p1,const Pair<_T1,_T2>& _p2){

		return !(_p1==_p2);
	}

	// expression p1<p2;
	template <typename _T1,typename _T2>
	inline bool operator<(const Pair<_T1,_T2>& _p1,const Pair<_T1,_T2>& _p2){

		return (_p1.first<_p2.first)||(!(_p2.first<_p1.first)&&(_p1.second<_p2.second));
	}

	// expression p1>p2 equal to p2<p1;
	template <typename _T1,typename _T2>
	inline bool operator>(const Pair<_T1,_T2>& _p1,const Pair<_T1,_T2>& _p2){

		return _p2<_p1;
	}

	// expression p1>=p2 equal to !(p1<p2)
	template <typename _T1,typename _T2>
	inline bool operator>=(const Pair<_T1,_T2>& _p1,const Pair<_T1,_T2>& _p2){

		return !(_p1<_p2);
	}

	// expression p1<=p2 equal to !(p2<p1)
	template <typename _T1,typename _T2>
	inline bool operator<=(const Pair<_T1,_T2>& _p1,const Pair<_T1,_T2>& _p2){

		return !(_p2<_p1);
	}


	template <typename _T1, typename _T2>
	inline Pair<_T1, _T2> Make_Pair(const _T1& _p1, const _T2& _p2) {

		return Pair<_T1, _T2>(_p1, _p2);
	}

}



#endif //NAIVE_STL_PAIR_H

