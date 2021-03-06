//=======================================================================
// Copyright (c) 2014 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#ifndef DLL_BASE_DBN_DESC_HPP
#define DLL_BASE_DBN_DESC_HPP

#include "base_conf.hpp"
#include "conjugate_gradient.hpp"
#include "watcher.hpp"
#include "tmp.hpp"

namespace dll {

template <typename DBN>
using default_dbn_trainer_t = cg_trainer<DBN, false>;

/*!
 * \brief Describe a DBN *
 *
 * This struct should be used to define a DBN.
 * Once configured, the ::dbn_t member returns the type of the configured DBN.
 */
template<typename Layers, template<typename> class D, typename... Parameters>
struct base_dbn_desc {
    using layers = Layers;

    static constexpr const bool Momentum = detail::is_present<momentum, Parameters...>::value;
    static constexpr const decay_type Decay = detail::get_value<weight_decay<decay_type::NONE>, Parameters...>::value;
    static constexpr const bool Concatenate = detail::is_present<concatenate, Parameters...>::value;

    /*! The type of the trainer to use to train the DBN */
    template <typename DBN>
    using trainer_t = typename detail::get_template_type<trainer<default_dbn_trainer_t>, Parameters...>::template type<DBN>;

    /*! The type of the watched to use during training */
    template <typename DBN>
    using watcher_t = typename detail::get_template_type<watcher<default_dbn_watcher>, Parameters...>::template type<DBN>;

    /*! The DBN type */
    using dbn_t = D<base_dbn_desc<Layers, D, Parameters...>>;

    //Make sure only valid types are passed to the configuration list
    static_assert(
        detail::is_valid<detail::tmp_list<trainer_id, watcher_id, momentum_id, weight_decay_id, concatenate_id>, Parameters...>::value,
        "Invalid parameters type");
};

} //end of dll namespace

#endif