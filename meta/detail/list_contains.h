/**
 * This file is part of meta.
 *
 * Author(s): Jens Finkhaeuser <jens@unwesen.co.uk>
 *
 * Copyright (c) 2009-2012 Jens Finkhaeuser.
 * Copyright (c) 2013 Unwesen Ltd.
 *
 * This software is licensed under the terms of the GNU GPLv3 for personal,
 * educational and non-profit use. For all other uses, alternative license
 * options are available. Please contact the copyright holder for additional
 * information, stating your intended usage.
 *
 * You can find the full text of the GPLv3 in the COPYING file in this code
 * distribution.
 *
 * This software is distributed on an "AS IS" BASIS, WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.
 **/
#ifndef META_DETAIL_LIST_CONTAINS_H
#define META_DETAIL_LIST_CONTAINS_H

#ifndef __cplusplus
#error You are trying to include a C++ only header file
#endif

#include <meta/meta-config.h>

#include <meta/detail/typelist.h>
#include <meta/detail/classlist.h>

namespace meta {
namespace types {

/**
 * This file contains meta-programming code for handling lists of types.
 **/

/**
 * Two types representing boolean true/false respectively.
 **/
struct true_type {};
struct false_type {};


/**
 * The contains consturct returns true (contains<>::type is true_type) if the
 * type given in first template argument is part of the typelist given in the
 * second argument.
 *
 * Note that the second argument *must* be a typelist; if it's not, false_type
 * is returned.
 *
 * Example usage:
 *    contains<int, typelist<int, float, double>>::type // is true_type
 *    contains<float, typelist<int, char>>::type        // is false_type
 *
 * Bad usage:
 *    contains<int, int>::type // compiles, but is false_type
 **/

// Default to false.
template <typename, typename>
struct contains
{
  typedef false_type type;
};

// Matches if the first type in the typelist is the test type.
template <
  typename TestType,
  typename... Types
>
struct contains<
      TestType,
      typelist<TestType, Types...>
    >
{
  typedef true_type type;
};

// Matches if the first type in the typelist is not the test type, so we'll
// recursively try typelist elements until it's the first type and the above
// struct matches.
template <
  typename TestType,
  typename Head,
  typename... Tail
>
struct contains<
      TestType,
      typelist<Head, Tail...>
    >
{
  typedef typename contains<
    TestType,
    typelist<Tail...>
  >::type type;
};




// Same for classes; first element match
template <
  typename TestType,
  typename... Types
>
struct contains<
      TestType,
      classlist<TestType, Types...>
    >
{
  typedef true_type type;
};

// Same for classes; recursion
template <
  typename TestType,
  typename Head,
  typename... Tail
>
struct contains<
      TestType,
      classlist<Head, Tail...>
    >
{
  typedef typename contains<
    TestType,
    classlist<Tail...>
  >::type type;
};




}} // namespace meta::types

#endif // guard
