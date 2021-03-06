//=======================================================================
// Copyright (c) 2014 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#ifndef DLL_DBN_COMMON_HPP
#define DLL_DBN_COMMON_HPP

namespace dll {

namespace dbn_detail {

template<typename W, typename Enable = void>
struct rbm_watcher_t {
    using type = void;
};

template<typename W>
struct rbm_watcher_t<W, std::enable_if_t<W::replace_sub> > {
    using type = W;
};

} //end of namespace dbn_detail

} //end of namespace dll

#endif
