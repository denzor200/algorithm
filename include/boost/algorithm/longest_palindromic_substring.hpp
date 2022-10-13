/*
  Copyright (c) Denis Mikhailov 2022.

  Distributed under the Boost Software License, Version 1.0. (See
  accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt)

  See http://www.boost.org/ for latest version.
*/

// TODO: ссылки на источники и имена авторов алгоритмов в копирайте

/// \file  longest_palindromic_substring.hpp
/// \brief 
/// \author Denis Mikhailov

#ifndef BOOST_ALGORITHM_LONGEST_PALINDROMIC_SUBSTRING_HPP
#define BOOST_ALGORITHM_LONGEST_PALINDROMIC_SUBSTRING_HPP

#include <iterator>
#include <functional>
#include <cstring>
#include <string>
#include <algorithm> // for std::max

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range.hpp>

namespace boost {  namespace algorithm {

namespace detail {
/// \cond DOXYGEN_HIDE

    template <typename RandomAccessIterator, typename Predicate>
    typename std::iterator_traits<RandomAccessIterator>::difference_type
    expand_around_center(RandomAccessIterator begin, RandomAccessIterator end,
                         RandomAccessIterator left, RandomAccessIterator right,
                         const Predicate& p)
    {
        while (left >= begin && right < end && p(*left, *right)) {
            if (left == begin) {
                return right - left + 1; // TODO: test it
            }
            --left;
            ++right;
        }
        return right - left - 1;
    }
/// \endcond
    }

// TODO: format spaces and naming like in gather.hpp

/// \fn longest_palindromic_substring ( RandomAccessIterator begin, RandomAccessIterator end, Predicate p )
/// \return TODO: describe returns
///
/// \param begin    The start of the input sequence
/// \param end		  One past the end of the input sequence
/// \param p        A predicate used to compare the values.
///
/// \note TODO: first line note
///     TODO: second line note
///     Storage Requirements:
///
///    The algorithm will attempt to allocate temporary memory,
///    but will work in-situ if there is none available.
///
///    Time Complexity:
///
///    If there is sufficient memory available, the run time is linear in <code>N</code>.
///    If there is not any memory available, then the run time is <code>O(N^2)</code>.
template <typename RandomAccessIterator, typename Predicate>
std::pair<RandomAccessIterator, RandomAccessIterator> longest_palindromic_substring(RandomAccessIterator begin, RandomAccessIterator end, Predicate p)
{
    // TODO: O(n)
    typedef typename std::iterator_traits<RandomAccessIterator>::difference_type Diff;
    if (begin == end)
    {
        return std::make_pair(begin, end);
    }

    RandomAccessIterator front_it = begin, last_it = begin;
    for (RandomAccessIterator it = begin; it != end; ++it)
    {
        const Diff length1 = expand_around_center(begin, end, it, it, p);
        const Diff length2 = expand_around_center(begin, end, it, std::next(it), p);
        const Diff length = std::max(length1, length2);
        if (length > last_it - front_it) {
            front_it = it - (length - 1) / 2;
            last_it = it + length / 2;
        }
    }
    return std::make_pair(front_it, std::next(last_it));
}

/// \fn longest_palindromic_substring ( RandomAccessIterator begin, RandomAccessIterator end )
/// \return TODO: describe returns
///
/// \param begin    The start of the input sequence
/// \param end	    One past the end of the input sequence
///
/// \note TODO: copy note from above
template <typename RandomAccessIterator>
std::pair<RandomAccessIterator, RandomAccessIterator> longest_palindromic_substring(RandomAccessIterator begin, RandomAccessIterator end)
{
    return longest_palindromic_substring(begin, end,
                                         std::equal_to<typename std::iterator_traits<RandomAccessIterator>::value_type> ());
}

/// \fn longest_palindromic_substring ( const RandomAccessRange& range )
/// \return TODO: describe returns
///
/// \param range TODO: describe range
///
/// \note TODO: copy note from above
template <typename RandomAccessRange>
std::pair<
    typename boost::range_iterator<const RandomAccessRange>::type,
    typename boost::range_iterator<const RandomAccessRange>::type> longest_palindromic_substring(const RandomAccessRange& range)
{
    return longest_palindromic_substring(boost::begin(range), boost::end(range));
}

/// \fn longest_palindromic_substring ( const RandomAccessRange& range, Predicate p )
/// \return TODO describe returns
///
/// \param range TODO describe range
/// \param p     A predicate used to compare the values.
///
/// \note TODO copy notes from above
template <typename RandomAccessRange, typename Predicate>
std::pair<
    typename boost::range_iterator<const RandomAccessRange>::type,
    typename boost::range_iterator<const RandomAccessRange>::type> longest_palindromic_substring(const RandomAccessRange& range, Predicate p)
{
    return longest_palindromic_substring(boost::begin(range), boost::end(range), p);
}

/// \fn longest_palindromic_substring ( const char* str )
/// \return TODO describe returns
///
/// \param str TODO describe str
///
/// \note TODO copy notes from above
inline std::string longest_palindromic_substring(const char* str)
{
    std::string result;
    if(str)
      result = boost::copy_range<std::string>(longest_palindromic_substring(str, str + strlen(str)));
    return result;
}
}}

#endif // BOOST_ALGORITHM_LONGEST_PALINDROMIC_SUBSTRING_HPP
