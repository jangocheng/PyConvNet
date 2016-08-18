//
// Created by xie on 16-8-3.
//

#ifndef PYCONVNET_TENSOR_HPP
#define PYCONVNET_TENSOR_HPP

# include <iostream>
# include <cstring>
# include <vector>
# include <boost/shared_array.hpp>

# include "blas_function.hpp"

class Tensor {
public:
    Tensor(int n, int c, int h, int w) : data(new float[n * c * h * w]){
        N = n;
        C = c;
        H = h;
        W = w;
    }
    Tensor(const Tensor& T) {
        N = T.get_N();
        C = T.get_C();
        H = T.get_H();
        W = T.get_W();
        data = T.get_data();
    }
    boost::shared_array<float>  get_data() const {
        return data;
    }
    void set_data(boost::shared_array<float> data_input) {
        data = data_input;
    }
    int  get_N() const {
        return N;
    }
    int  get_C() const {
        return C;
    }
    int  get_H() const {
        return H;
    }
    int  get_W() const {
        return W;
    }
    int get_size() const {
        return N * C * H * W;
    }
    std::vector<float> get_data_vector() const {
        std::vector<float> data_vector;
        std::copy(data.get(), data.get() + N*C*H*W, data_vector.begin());
        return data_vector;
    }
    bool operator==( Tensor const& t ) const {
        return std::equal(this->get_data().get(), this->get_data().get() + N * C * H * W,
           t.get_data().get());
    }
    bool operator!=( Tensor const& t ) const {
        return std::equal(this->get_data().get(), this->get_data().get() + N * C * H * W,
                          t.get_data().get());
    }
    Tensor operator+(Tensor& t) {
        vector_add(this->get_data().get(), t.get_data().get(), this->get_data().get(),
                   this->get_size());
        return *this;
    }
    Tensor operator-(Tensor& t) {
        vector_sub(this->get_data().get(), t.get_data().get(), this->get_data().get(),
                   this->get_size());
        return *this;
    }
    Tensor operator*(float mul) {
        vector_mul_scalar(this->get_data().get(), mul, this->get_size());
        return *this;
    }
private:
    boost::shared_array<float> data;
    int N, C, H, W;
};
#endif //PYCONVNET_TENSOR_HPP