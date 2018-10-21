//
// Created by Shuai on 2017/9/11.
//

#ifndef NAIVE_STL_HASH_BASE_H
#define NAIVE_STL_HASH_BASE_H

#include "../algorithm.h"

enum { _G_single_node = 1 };

enum { _G_num_primes = 28 };

static const unsigned long _G_prime_array[_G_num_primes] =
		{
				53ul,         97ul,         193ul,       389ul,       769ul,
				1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
				49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
				1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
				50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
				1610612741ul, 3221225473ul, 4294967291ul
		};

inline unsigned long _G_get_next_prime(unsigned long prime){

	const unsigned long* _t_first=_G_prime_array;
	const unsigned long* _t_last=_G_prime_array+_G_num_primes;
	const unsigned long* pos=naive::lower_bound(_t_first,_t_last,prime);

	return pos==_t_last? *(_t_last-1):*pos;
}




#endif //NAIVE_STL_STL_HASH_BASE_H
