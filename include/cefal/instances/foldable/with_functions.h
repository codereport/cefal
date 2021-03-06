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

#include "cefal/common.h"
#include "cefal/foldable.h"

#include <algorithm>
#include <type_traits>

namespace cefal::instances {
namespace detail {
template <typename T>
struct FoldableFromFunctionsExists {
    using type = T;
};
} // namespace detail
template <detail::HasFoldableMethods T>
struct Foldable<T> {
    template <typename Input, typename Result, typename Func>
    // clang-format off
    requires std::same_as<std::remove_cvref_t<Input>, T>
        // clang-format on
        static std::remove_cvref_t<Result> foldLeft(Input&& src, Result&& initial, Func&& func) {
        return std::forward<Input>(src).foldLeft(std::forward<Result>(initial), std::forward<Func>(func));
    }
};

template <detail::HasFoldableSnakeCaseMethods T>
struct Foldable<T> {
    template <typename Input, typename Result, typename Func>
    // clang-format off
    requires std::same_as<std::remove_cvref_t<Input>, T>
        // clang-format on
        static std::remove_cvref_t<Result> foldLeft(Input&& src, Result&& initial, Func&& func) {
        return std::forward<Input>(src).fold_left(std::forward<Result>(initial), std::forward<Func>(func));
    }
};
} // namespace cefal::instances
