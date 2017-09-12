/*
 * NOTE: This is an internal header file, included by other C++ headers.
 * You should not attempt to use it directly.
 *
*/

#ifndef _NAIVE_STL_ALLOC_H
#define _NAIVE_STL_ALLOC_H

#include <cstddef>
#include <climits>
#include <cstdlib>
#include "stl_construct.h"
#include <utility>
#include <memory>

/*
* @Author: Shuai Liu
* @Email: cqutliushuai@gmail.com
* @Time 2017-6-24
*/
namespace naive
{

	template <typename _T>
	class allocator{

	public:
		typedef _T value_type;
		typedef _T *pointer;
		typedef const _T *const_pointer;
		typedef _T &reference;
		typedef const _T &const_reference;
		typedef std::size_t size_type;
		typedef ptrdiff_t difference_type;
		//typedef 
		typedef std::true_type propagate_on_container_move_assignment;
		typedef std::true_type is_always_equal;

	public:
		/*
		* The inside template rebind is used when value_type/T need to
		* transform to another defined inside a _container, for example, std::List<int,naive::Allocate<int>> should
		* transform int to List<int>::node defined in class List, and we can use Allocate<int>::rebind<node> inside
		* the List;
		*
		*/
		template <typename U>
		struct rebind{
			using other=allocator<U>;
		};

		//Default constructor;
		allocator()= default;

		//Default copying constructor;
		allocator(const allocator& _alloc)= default;

		allocator(allocator<_T>&& _alloc) noexcept = default;

		// Convert to related Allocator;
		template <typename U>
		allocator(const allocator<U>& _alloc){}

		allocator& operator=(const allocator&) = default;
		allocator& operator=(allocator&&)= default;

		~allocator() {}

		// Allocate arrary of _n*sizeof(T) size;
		pointer allocate(size_type _n, const void *hint = nullptr){
			std::set_new_handler(nullptr);

			if (_n == 0)
				return nullptr;

			pointer temp = static_cast<pointer>(::operator new((size_t)(_n * sizeof(_T))));

			if (temp == nullptr){

				throw std::out_of_range("Out of memory..");
			}

			return temp;
		}

		// Deallocate object at _p and ignore size because it was allocated by allocate();
		void deallocate(pointer _p, size_type _n){
			::operator delete(_p);
		}

		void construct(pointer _p, const_reference _value){
			//new (_p) value_type(_value);
			::construct(_p, _value);
		}

		void destroy(pointer _p){
			::destroy(_p);
		}

		/*
		* return the address of object x;
		* @param a reference of input value;
		* @return the address of input value;
		* */
		pointer address(reference _x) const noexcept{
			return static_cast<pointer>(&_x);
		}

		const_pointer const_address(const_reference _x) const noexcept{
			return static_cast<const_pointer>(&_x);
		}

		size_type max_size() const{
			return static_cast<size_type>(UINT_MAX / sizeof(_T));
		}
	};

	template <>
	class allocator<void>
	{
	public:
		typedef void value_type;
		typedef void *pointer;
		typedef const void *const_pointer;

		template <typename U>
		allocator(const allocator<U> &) {}

		template <typename U>
		struct rebind{
			using other= allocator<U>;
		};
	};

	//According to C++ standard, there are two non-menber functions for comparing two
	//Allocator instances;
	template <typename _T>
	inline bool operator==(const allocator<_T>& _alloc1, const allocator<_T>& _alloc2){
		return true;
	}

	template <typename _T>
	inline bool operator!=(const allocator<_T>& _alloc1, const allocator<_T>& _alloc2){
		return false;
	}




};
#endif