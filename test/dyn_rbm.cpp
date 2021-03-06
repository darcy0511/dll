//=======================================================================
// Copyright (c) 2014 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#include "catch.hpp"

#include "dll/dyn_rbm.hpp"

#include "mnist/mnist_reader.hpp"
#include "mnist/mnist_utils.hpp"

TEST_CASE( "dyn_rbm/mnist_1", "rbm::simple" ) {
    dll::dyn_rbm_desc<>::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 100);

    REQUIRE(error < 1e-2);
}

TEST_CASE( "dyn_rbm/mnist_2", "rbm::momentum" ) {
    dll::dyn_rbm_desc<dll::momentum>::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 100);

    REQUIRE(error < 1e-2);
}

TEST_CASE( "dyn_rbm/mnist_3", "rbm::pcd_trainer" ) {
    dll::dyn_rbm_desc<
        dll::momentum,
        dll::trainer<dll::pcd1_trainer_t>
    >::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 100);

    REQUIRE(error < 1e-1);
}

TEST_CASE( "dyn_rbm/mnist_4", "rbm::decay_l1" ) {
    dll::dyn_rbm_desc<
       dll::weight_decay<dll::decay_type::L1>
    >::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 100);

    REQUIRE(error < 1e-2);
}

TEST_CASE( "dyn_rbm/mnist_5", "rbm::decay_l2" ) {
    dll::dyn_rbm_desc<
       dll::weight_decay<dll::decay_type::L2>
    >::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 100);

    REQUIRE(error < 1e-2);
}

TEST_CASE( "dyn_rbm/mnist_60", "rbm::global_sparsity" ) {
    using rbm_type = dll::dyn_rbm_desc<
       dll::sparsity<>
    >::rbm_t;

    rbm_type rbm(28 * 28, 100);

    REQUIRE(dll::rbm_traits<rbm_type>::sparsity_method() == dll::sparsity_method::GLOBAL_TARGET);

    //0.01 (default) is way too low for 100 hidden units
    rbm.sparsity_target = 0.1;

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 100);

    REQUIRE(error < 1e-2);
}

TEST_CASE( "dyn_rbm/mnist_61", "rbm::local_sparsity" ) {
    dll::dyn_rbm_desc<
       dll::sparsity<dll::sparsity_method::LOCAL_TARGET>
    >::rbm_t rbm(28 * 28, 100);

    //0.01 (default) is way too low for 100 hidden units
    rbm.sparsity_target = 0.1;

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 100);

    REQUIRE(error < 1e-2);
}

TEST_CASE( "dyn_rbm/mnist_7", "rbm::gaussian" ) {
    dll::dyn_rbm_desc<
       dll::visible<dll::unit_type::GAUSSIAN>
    >::rbm_t rbm(28 * 28, 100);

    rbm.learning_rate *= 10;

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::normalize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 200);

    REQUIRE(error < 1e-2);
}

TEST_CASE( "dyn_rbm/mnist_8", "rbm::softmax" ) {
    dll::dyn_rbm_desc<
       dll::hidden<dll::unit_type::SOFTMAX>
    >::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>(100);

    REQUIRE(!dataset.training_images.empty());

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 100);

    REQUIRE(error < 1e-2);
}

TEST_CASE( "dyn_rbm/mnist_9", "rbm::relu" ) {
    dll::dyn_rbm_desc<
       dll::hidden<dll::unit_type::RELU>
    >::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 200);

    REQUIRE(error < 1e-1);
}

TEST_CASE( "dyn_rbm/mnist_10", "rbm::relu1" ) {
    dll::dyn_rbm_desc<
       dll::hidden<dll::unit_type::RELU1>
    >::rbm_t rbm(28 * 28, 100);

    rbm.learning_rate *= 2.0;

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 200);

    REQUIRE(error < 1e-1);
}

TEST_CASE( "dyn_rbm/mnist_11", "rbm::relu6" ) {
    dll::dyn_rbm_desc<
       dll::hidden<dll::unit_type::RELU6>
    >::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 200);

    REQUIRE(error < 1e-1);
}

TEST_CASE( "dyn_rbm/mnist_12", "rbm::init_weights" ) {
    dll::dyn_rbm_desc<
       dll::init_weights
    >::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 200);

    REQUIRE(error < 1e-3);
}

//Only here for benchmarking purposes
TEST_CASE( "dyn_rbm/mnist_14", "rbm::slow" ) {
    dll::dyn_rbm_desc<>::rbm_t rbm(28 * 28, 400);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>(1000);

    REQUIRE(!dataset.training_images.empty());

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 10);

    REQUIRE(error < 5e-2);
}

//Only here for debugging purposes
TEST_CASE( "dyn_rbm/mnist_15", "rbm::fast" ) {
    dll::dyn_rbm_desc<>::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>(25);

    REQUIRE(!dataset.training_images.empty());

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 5);

    REQUIRE(error < 5e-1);
}

TEST_CASE( "dyn_rbm/mnist_16", "rbm::parallel" ) {
    dll::dyn_rbm_desc<dll::parallel, dll::momentum>::rbm_t rbm(28 * 28, 100);

    auto dataset = mnist::read_dataset<std::vector, std::vector, double>();

    REQUIRE(!dataset.training_images.empty());
    dataset.training_images.resize(100);

    mnist::binarize_dataset(dataset);

    auto error = rbm.train(dataset.training_images, 100);

    REQUIRE(error < 1e-3);
}
