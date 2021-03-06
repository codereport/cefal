/* Copyright 2020, Dennis Kormalev
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, this list of
 * conditions and the following disclaimer in the documentation and/or other materials provided
 * with the distribution.
 *     * Neither the name of the copyright holders nor the names of its contributors may be used to
 * endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once

#include <concepts>
#include <utility>

namespace cefal {
namespace detail {
template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;
}
template <typename...>
struct InnerType;
template <template <typename...> typename C, typename T, typename... Ts>
struct InnerType<C<T, Ts...>> {
    using type = T;
};
template <typename T>
using InnerType_T = InnerType<T>::type;

template <typename...>
struct WithInnerType;
template <template <typename...> typename C, typename T, typename... Ts, typename NewT>
struct WithInnerType<C<T, Ts...>, NewT> {
    using type = C<NewT>;
};
template <typename... Ts>
using WithInnerType_T = WithInnerType<Ts...>::type;

template <detail::Arithmetic T>
struct Sum {
    Sum(T x = T()) : value(x) {}
    T value;
    operator T() const { return value; }
};

template <detail::Arithmetic T>
struct Product {
    Product(T x = T()) : value(x) {}
    T value;
    operator T() const { return value; }
};

namespace ops {
template <typename Left, typename Op>
inline auto operator|(Left&& left, Op&& op) {
    return std::forward<Op>(op)(std::forward<Left>(left));
}
} // namespace ops
} // namespace cefal
