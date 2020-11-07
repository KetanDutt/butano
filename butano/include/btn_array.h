/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BTN_ARRAY_H
#define BTN_ARRAY_H

#include "btn_assert.h"
#include "btn_utility.h"
#include "btn_iterator.h"
#include "btn_algorithm.h"
#include "btn_array_fwd.h"

namespace btn
{

template<typename Type, int Size>
class array
{
    static_assert(Size > 0);

public:
    using value_type = Type; //!< Value type alias.
    using size_type = int; //!< Size type alias.
    using reference = Type&; //!< Reference alias.
    using const_reference = const Type&; //!< Const reference alias.
    using pointer = Type*; //!< Pointer alias.
    using const_pointer = const Type*; //!< Const pointer alias.
    using iterator = Type*; //!< Iterator alias.
    using const_iterator = const Type*; //!< Const iterator alias.
    using reverse_iterator = btn::reverse_iterator<iterator>; //!< Reverse iterator alias.
    using const_reverse_iterator = btn::reverse_iterator<const_iterator>; //!< Const reverse iterator alias.

    /**
     * @brief Returns a const pointer to the beginning of the array.
     */
    [[nodiscard]] constexpr const_pointer data() const
    {
        return &_data[0];
    }

    /**
     * @brief Returns a pointer to the beginning of the array.
     */
    [[nodiscard]] constexpr pointer data()
    {
        return &_data[0];
    }

    /**
     * @brief Returns the current elements count.
     */
    [[nodiscard]] constexpr size_type size() const
    {
        return Size;
    }

    /**
     * @brief Returns the maximum possible elements count.
     */
    [[nodiscard]] constexpr size_type max_size() const
    {
        return Size;
    }

    /**
     * @brief Returns the remaining element capacity.
     */
    [[nodiscard]] constexpr size_type available() const
    {
        return 0;
    }

    /**
     * @brief Indicates if it doesn't contain any element.
     */
    [[nodiscard]] constexpr bool empty() const
    {
        return false;
    }

    /**
     * @brief Indicates if it can't contain any more elements.
     */
    [[nodiscard]] constexpr bool full() const
    {
        return true;
    }

    /**
     * @brief Returns a const iterator to the beginning of the array.
     */
    [[nodiscard]] constexpr const_iterator begin() const
    {
        return &_data[0];
    }

    /**
     * @brief Returns an iterator to the beginning of the array.
     */
    [[nodiscard]] constexpr iterator begin()
    {
        return &_data[0];
    }

    /**
     * @brief Returns a const iterator to the end of the array.
     */
    [[nodiscard]] constexpr const_iterator end() const
    {
        return &_data[Size];
    }

    /**
     * @brief Returns an iterator to the end of the array.
     */
    [[nodiscard]] constexpr iterator end()
    {
        return &_data[Size];
    }

    /**
     * @brief Returns a const iterator to the beginning of the array.
     */
    [[nodiscard]] constexpr const_iterator cbegin() const
    {
        return begin();
    }

    /**
     * @brief Returns a const iterator to the end of the array.
     */
    [[nodiscard]] constexpr const_iterator cend() const
    {
        return &_data[Size];
    }

    /**
     * @brief Returns a const reverse iterator to the end of the array.
     */
    [[nodiscard]] constexpr const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }

    /**
     * @brief Returns a reverse iterator to the end of the array.
     */
    [[nodiscard]] constexpr reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }

    /**
     * @brief Returns a const reverse iterator to the beginning of the array.
     */
    [[nodiscard]] constexpr const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

    /**
     * @brief Returns a reverse iterator to the beginning of the array.
     */
    [[nodiscard]] constexpr reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }

    /**
     * @brief Returns a const reverse iterator to the end of the array.
     */
    [[nodiscard]] constexpr const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator(end());
    }

    /**
     * @brief Returns a const reverse iterator to the beginning of the array.
     */
    [[nodiscard]] constexpr const_reverse_iterator crend() const
    {
        return const_reverse_iterator(begin());
    }

    /**
     * @brief Returns a const reference to the value stored at the specified index.
     */
    [[nodiscard]] constexpr const_reference operator[](size_type index) const
    {
        BTN_ASSERT(index >= 0 && index < Size, "Invalid index: ", index);

        return _data[index];
    }

    /**
     * @brief Returns a reference to the value stored at the specified index.
     */
    [[nodiscard]] constexpr reference operator[](size_type index)
    {
        BTN_ASSERT(index >= 0 && index < Size, "Invalid index: ", index);

        return _data[index];
    }

    /**
     * @brief Returns a const reference to the value stored at the specified index.
     */
    [[nodiscard]] constexpr const_reference at(size_type index) const
    {
        BTN_ASSERT(index >= 0 && index < Size, "Invalid index: ", index);

        return _data[index];
    }

    /**
     * @brief Returns a reference to the value stored at the specified index.
     */
    [[nodiscard]] constexpr reference at(size_type index)
    {
        BTN_ASSERT(index >= 0 && index < Size, "Invalid index: ", index);

        return _data[index];
    }

    /**
     * @brief Returns a const reference to the first element.
     */
    [[nodiscard]] constexpr const_reference front() const
    {
        return _data[0];
    }

    /**
     * @brief Returns a reference to the first element.
     */
    [[nodiscard]] constexpr reference front()
    {
        return _data[0];
    }

    /**
     * @brief Returns a const reference to the last element.
     */
    [[nodiscard]] constexpr const_reference back() const
    {
        return _data[Size - 1];
    }

    /**
     * @brief Returns a reference to the last element.
     */
    [[nodiscard]] constexpr reference back()
    {
        return _data[Size - 1];
    }

    /**
     * @brief Fills the array with the given value.
     */
    constexpr void fill(const_reference value)
    {
        btn::fill(begin(), end(), value);
    }

    /**
     * @brief Exchanges the contents of this array with those of the other one.
     * @param other array to exchange the contents with.
     */
    constexpr void swap(array& other)
    {
        pointer data = _data;
        pointer other_data = other._data;

        for(size_type index = 0; index < Size; ++index)
        {
            btn::swap(data[index], other_data[index]);
        }
    }

    /**
     * @brief Exchanges the contents of an array with those of another one.
     * @param a First array to exchange the contents with.
     * @param b Second array to exchange the contents with.
     */
    constexpr friend void swap(array& a, array& b)
    {
        a.swap(b);
    }

    /**
     * @brief Equal operator.
     * @param a First array to compare.
     * @param b Second array to compare.
     * @return <b>true</b> if the first array is equal to the second one, otherwise <b>false</b>.
     */
    [[nodiscard]] constexpr friend bool operator==(const array& a, const array& b)
    {
        if(a.size() != b.size())
        {
            return false;
        }

        return equal(a.begin(), a.end(), b.begin());
    }

    /**
     * @brief Not equal operator.
     * @param a First array to compare.
     * @param b Second array to compare.
     * @return <b>true</b> if the first array is not equal to the second one, otherwise <b>false</b>.
     */
    [[nodiscard]] constexpr friend bool operator!=(const array& a, const array& b)
    {
        return ! (a == b);
    }

    /**
     * @brief Less than operator.
     * @param a First array to compare.
     * @param b Second array to compare.
     * @return <b>true</b> if the first array is lexicographically less than the second one, otherwise <b>false</b>.
     */
    [[nodiscard]] constexpr friend bool operator<(const array& a, const array& b)
    {
        return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    /**
     * @brief Greater than operator.
     * @param a First array to compare.
     * @param b Second array to compare.
     * @return <b>true</b> if the first array is lexicographically greater than the second one,
     * otherwise <b>false</b>.
     */
    [[nodiscard]] constexpr friend bool operator>(const array& a, const array& b)
    {
        return b < a;
    }

    /**
     * @brief Less than or equal operator.
     * @param a First array to compare.
     * @param b Second array to compare.
     * @return <b>true</b> if the first array is lexicographically less than or equal to the second one,
     * otherwise <b>false</b>.
     */
    [[nodiscard]] constexpr friend bool operator<=(const array& a, const array& b)
    {
        return ! (a > b);
    }

    /**
     * @brief Greater than or equal operator.
     * @param a First array to compare.
     * @param b Second array to compare.
     * @return <b>true</b> if the first array is lexicographically greater than or equal to the second one,
     * otherwise <b>false</b>.
     */
    [[nodiscard]] constexpr friend bool operator>=(const array& a, const array& b)
    {
        return ! (a < b);
    }

    Type _data[Size]; //!< (Not so) internal data.
};


/**
 * @brief Creates a btn::array object from the given built-in array.
 *
 * @ingroup array
 */
template<typename Type, int Size>
constexpr array<remove_cv_t<Type>, Size> to_array(Type (&base_array)[Size])
{
    return array(base_array);
}

}

#endif
