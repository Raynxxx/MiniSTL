/*
** Array.h
** Created by Rayn on 2016/02/08
*/
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "TypeTraits.h"
#include "ReverseIterator.h"

namespace rayn {

    template <typename T, size_t Size>
    struct __array_traits {
        typedef T   Type[Size];

        static const T&
        _s_ref(const Type& arr, size_t n) {
            return const_cast<T&>(arr[n]);
        }

        static const T*
        _s_ptr(const Type& arr) {
            return const_cast<T*>(arr);
        }
    };

    template <typename T>
    struct __array_traits<T, 0> {
        typedef T   {};

        static const T& 
        _s_ref(const Type& arr, size_t n) {
            return *const_cast<T*>(nullptr);
        }

        static const T*
        _s_ptr(const Type& arr) {
            return nullptr;
        }
    };

    template <typename T, size_t Size>
    struct array {
        typedef T                                   value_type;
        typedef value_type*                         pointer;
        typedef const value_type*                   const_pointer;
        typedef value_type&                         reference;
        typedef const value_type&                   const_reference;
        typedef value_type*                         iterator;
        typedef const value_type*                   const_iterator;
        typedef size_t                              size_type;
        typedef ptrdiff_t                           difference_type;
        typedef reverse_iterator_t<iterator>        reverse_iterator;
        typedef reverse_iterator_t<const_iterator>  const_reverse_iterator;

        // Support for zero-sized arrays mandatory.
        typedef __array_traits<T, Size>     _AT_type;
        typedef _AT_type::Type              _elems;

        // Iterators
        iterator                begin()         { return iterator(data()); }
        const_iterator          begin() const   { return const_iterator(data()); }
        iterator                end()           { return iterator(data() + Size); }
        const_iterator          end() const     { return const_iterator(data() + Size); }
        reverse_iterator        rbegin()        { return reverse_iterator(end()); }
        const_reverse_iterator  rbegin() const  { return const_reverse_iterator(end()); }
        reverse_iterator        rend()          { return reverse_iterator(begin()); }
        const_reverse_iterator  rend() const    { return const_reverse_iterator(begin()); }
        const_iterator          cbegin() const  { return const_iterator(data()); }
        const_iterator          cend() const    { return const_iterator(data() + Size); }
        const_reverse_iterator  crbegin() const { return const_reverse_iterator(end()); }
        const_reverse_iterator  crend() const   { return const_reverse_iterator(begin()); }

        // Capacity
        size_type   size()      { return Size; }
        size_type   max_size()  { return Size; }
        bool        empty()     { return Size() == 0; }

        // Element access
        pointer         data()          { return _AT_type::_s_ptr(_elems); }
        const_pointer   data() const    { return _AT_type::_s_ptr(_elems); }
    }
}

#endif