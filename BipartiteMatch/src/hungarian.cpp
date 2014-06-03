/**
 * hungarian.cpp
 * Hungarian class implements the Hungarian
 * algorithm for finding a maximum weight matching
 * in a bipartite graph.
 *
 * Copyright (c) 2014 Marshall Farrier
 * license http://opensource.org/licenses/gpl-license.php GNU Public License
 *
 * Author Marshall Farrier
 * Since 2014-05-23
 */

#include <algorithm>
// TODO remove after debugging
#include <iostream>

#include "hungarian.h"
#include "maxmatch.h"
#include "index.h"

// the number of rows (or cols, since matrix is square)
//int len;
//int *weights;
//bool has_run;

Hungarian::Hungarian(const int *weights, const int &len) : 
        len_(len), len_sq_(len_ * len_), index_(len_), matcher_(weights, len_, len_) {
    int i, j;

    std::cout << "Initializing weights" << std::endl;
    // initialize weights
    weights_ = new int[len_sq_];
    for (i = 0; i < len_sq_; ++i) {
        weights_[i] = weights[i];
    }
    // initialize vertex labels
    labelsX_ = new int[len_];
    labelsY_ = new int[len_];
    for (i = 0; i < len_; ++i) {
        labelsX_[i] = *std::max_element(weights_ + index_.index(i, 0), 
                weights_ + index_.index(i + 1, 0));
        labelsY_[i] = 0;
    }
    //initialize equality graph to starting values
    equality_graph_ = new int[len_sq_];
    for (i = 0; i < len_; ++i) {
        for (j = 0; j < len_; ++j) {
            if (labelsX_[i] + labelsY_[j] == weights_[index_.index(i, j)]) {
                equality_graph_[index_.index(i, j)] = 1;
            } else {
                equality_graph_[index_.index(i, j)] = 0;
            }
        }
    }
    // set matcher to initial equality graph
    matcher_.set(equality_graph_);
    matcher_.init();
}
Hungarian::~Hungarian() {
    delete[] weights_;
    delete[] labelsX_;
    delete[] labelsY_;
    delete[] equality_graph_;
}

int Hungarian::get_match_total() {
    int total = 0;

    for (int i = 0; i < len_; ++i) {
        if (matcher_.match_X(i) >= 0) {
            total += weights_[index_.index(i, matcher_.match_X(i))];
        }
    }
    return total;
}

void Hungarian::init() {
    // TODO
}

int Hungarian::length() const {
    return len_;
}

int Hungarian::weight(const int &x, const int &y) const {
    return weights_[index_.index(x, y)];
}

int Hungarian::matchX(const int &x) const {
    return matcher_.match_X(x);
}

int Hungarian::matchY(const int &y) const {
    return matcher_.match_Y(y);
}
