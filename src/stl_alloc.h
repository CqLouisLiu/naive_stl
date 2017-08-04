#ifndef _NAIVE_STL_ALLOC_H
#define _NAIVE_STL_ALLOC_H

#include <cstddef>
#include <climits>
#include <cstdlib>
#include "stl_construct.h"
using std::size_t;
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
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		//typedef 
		typedef std::true_type propagate_on_container_move_assignment;
		typedef std::true_type is_always_equal;

	public:
		/*
		* The inside template rebind is used when value_type/T need to
		* transform to another defined inside a container, for example, std::list<int,naive::Allocate<int>> should		* transform int to list<int>::node defined in class list, and we can use Allocate<int>::rebind<node> inside
		* the list;
		*
		*/
		template <typename U>
		struct rebind{
			using other=allocator<U>;
		};

		//Default constructor;
		allocator() noexcept{
			//Nothing to do;
		}

		//Default copying constructor;
		allocator(const allocator<_T> &) noexcept{
			//Nothing to do;
		}

		// Convert to related Allocator;
		template <typename U>
		allocator(const allocator<U> &){
			//Nothing to do, because Allocator has any member fileds.
		}

		~allocator() {}

		allocator<_T> &operator=(const allocator &) = delete;

		// Allocate arrary of _n*sizeof(T) size;
		pointer allocate(size_type _n, const void *hint = nullptr){
			std::set_new_handler(nullptr); //暂时不抛出异常;

			if (_n == 0)
				return nullptr;

			pointer temp = static_cast<pointer>(::operator new((size_t)(_n * sizeof(_T))));

			if (temp == nullptr){

				throw std::out_of_range("Out of memory..");
				exit(1);
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
	inline bool operator==(const allocator<_T> &, const allocator<_T> &){
		return true;
	}

	template <typename _T>
	inline bool operator!=(const allocator<_T> &, const allocator<_T> &){
		return false;
	}


	template<typename P>
	struct pointer_traits {

	};

	template<typename P>
	struct pointer_traits<P*> {

		typedef P* pointer;
		typedef P element_type;
		typedef ptrdiff_t difference_type;

		template<typename U>
		using rebind = U*;

		//Constructs a dereferenceable pointer or pointer-like object ("fancy pointer") to its argument;
		static pointer pointer_to(element_type& x) noexcept {
			return std::addressof(x);
		}
	};

	//The allocator_traits class template provides the standardized way to access various properties of Allocators. 
	template<typename _Alloc>
	struct allocator_traits {
		typedef _Alloc allocator_type;
		typedef typename _Alloc::value_type value_type;
		typedef typename _Alloc::pointer pointer;
		//typedef typename Alloc::const_pointer;

	};

};
#endif