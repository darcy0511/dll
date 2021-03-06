//=======================================================================
// Copyright (c) 2014 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#define DLL_SVM_SUPPORT

#include "dll/rbm.hpp"
#include "dll/dbn.hpp"

template<typename DBN>
void test_dbn(){
    DBN dbn;

    dbn.display();

    std::vector<etl::dyn_vector<double>> images;
    std::vector<uint8_t> labels;

    dbn.pretrain(images, 10);
    dbn.svm_train(images, labels);
    dbn.svm_train(images.begin(), images.end(), labels.begin(), labels.end());
    dbn.svm_grid_search(images, labels);
    dbn.svm_grid_search(images.begin(), images.end(), labels.begin(), labels.end());
    dbn.svm_predict(images[1]);
}

template <typename RBM>
using pcd2_trainer_t = dll::persistent_cd_trainer<2, RBM>;

int main(){
    //Basic example

    typedef dll::dbn_desc<
        dll::dbn_layers<
        dll::rbm_desc<28 * 28, 100, dll::momentum, dll::batch_size<50>, dll::init_weights, dll::weight_decay<dll::decay_type::L2>, dll::sparsity<>>::rbm_t,
        dll::rbm_desc<100, 100, dll::momentum, dll::batch_size<50>>::rbm_t,
        dll::rbm_desc<100, 200, dll::batch_size<50>, dll::momentum, dll::weight_decay<dll::decay_type::L2_FULL>>::rbm_t
    >, dll::watcher<dll::silent_dbn_watcher>>::dbn_t dbn_1;

    //Test them all

    test_dbn<dbn_1>();

    return 0;
}