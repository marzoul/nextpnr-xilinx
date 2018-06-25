/*
 *  nextpnr -- Next Generation Place and Route
 *
 *  Copyright (C) 2018  David Shah <david@symbioticeda.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef UTIL_H
#define UTIL_H

#include <map>
#include <string>
#include "nextpnr.h"

NEXTPNR_NAMESPACE_BEGIN

// Get a value from a map-style container, returning default if value is not
// found
template <typename Container, typename KeyType, typename ValueType>
ValueType get_or_default(const Container &ct, const KeyType &key, ValueType def = ValueType())
{
    auto found = ct.find(key);
    if (found == ct.end())
        return def;
    else
        return found->second;
};

// Get a value from a map-style container, converting to int, and returning
// default if value is not found
template <typename Container, typename KeyType> int int_or_default(const Container &ct, const KeyType &key, int def = 0)
{
    auto found = ct.find(key);
    if (found == ct.end())
        return def;
    else
        return std::stoi(found->second);
};

// As above, but convert to bool
template <typename Container, typename KeyType>
bool bool_or_default(const Container &ct, const KeyType &key, bool def = false)
{
    return bool(int_or_default(ct, key, int(def)));
};

// Wrap an unordered_map, and allow it to be iterated over sorted by key
template <typename K, typename V> std::map<K, V*> sorted(const std::unordered_map<K, std::unique_ptr<V>> &orig)
{
    std::map<K, V*> retVal;
    for(auto& item : orig)
        retVal.emplace(std::make_pair(item.first,item.second.get()));
    return retVal;
};

NEXTPNR_NAMESPACE_END

#endif
