/**
 * hungarian.cpp
 * Hungarian class implements the Hungarian
 * algorithm for finding a maximum weight matching
 * in a bipartite graph.
 * The input graph is assumed to be complete and to have partitions
 * X and Y of equal size. 
 * But it may have 0 weight edges, so incomplete graphs and
 * graphs with unequal partitions can be padded with 0 weight
 * edges to fit the algorithm.
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

Hungarian::Hungarian(const int *weights, const int &len) : 
        len_(len), len_sq_(len_ * len_), index_(len_), matcher_(weights, len_, len_) {
    int i;

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
    update_equality_graph();
    // set matcher to initial equality graph
    matcher_.set(equality_graph_);
    matcher_.init();
    // initialize S_, T_, NlS_
    S_ = new int[len_];
    T_ = new int[len_];
    NlS_ = new int[len_];
}
Hungarian::~Hungarian() {
    delete[] weights_;
    delete[] labelsX_;
    delete[] labelsY_;
    delete[] equality_graph_;
    delete[] S_;
    delete[] T_;
    delete[] NlS_;
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
    while (matcher_.matches() < len_) {
        improve_equality_graph();
        matcher_.set(equality_graph_);
        matcher_.init();
    }
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

void Hungarian::improve_equality_graph() {
    reset_path_sets();
    int free_vertex = get_free_vertex();
    S_[free_vertex] = 1;
    update_NlS(free_vertex);
    int y = nls_minus_t();
    while (y >= 0) {
        T_[y] = 1;
        S_[matcher_.match_Y(y)] = 1;
        update_NlS(matcher_.match_Y(y));
        y = nls_minus_t();
    }
    relabel();
    update_equality_graph();
}

int Hungarian::get_free_vertex() const {
    for (int i = 0; i < len_; ++i) {
        if (matcher_.match_X(i) < 0) return i; 
    }
    return -1;
}

void Hungarian::update_equality_graph() {
    int i, j;

    for (i = 0; i < len_; ++i) {
        for (j = 0; j < len_; ++j) {
            if (labelsX_[i] + labelsY_[j] == weights_[index_.index(i, j)]) {
                equality_graph_[index_.index(i, j)] = 1;
            } else {
                equality_graph_[index_.index(i, j)] = 0;
            }
        }
    }
}

int Hungarian::get_alpha() const {
    int alpha = -1,
        i,
        j;

    for (i = 0; i < len_; ++i) {
        for (j = 0; j < len_; ++j) {
            if (S_[i] == 1 && T_[j] == 0) {
                if (alpha == -1 || labelsX_[i] + labelsY_[j] - weights_[index_.index(i, j)] < alpha) {
                    alpha = labelsX_[i] + labelsY_[j] - weights_[index_.index(i, j)];
                }
            }
        }
    }
    return alpha;
}

void Hungarian::reset_path_sets() {
    std::fill(S_, S_ + len_, 0);
    std::fill(T_, T_ + len_, 0);
    std::fill(NlS_, NlS_ + len_, 0);
}

/**
 * Add the neighbors of input vertex in the equality
 * graph to NlS
 */
void Hungarian::update_NlS(const int &vertex) {
    for (int j = 0; j < len_; ++j) {
        if (equality_graph_[index_.index(vertex, j)] == 1) {
            NlS_[j] = 1;
        }
    }
}

/**
 * return some vertex in NlS that isn't in T.
 * return -1 if there is no such vertex (NlS_ == T_)
 */
int Hungarian::nls_minus_t() const {
    for (int i = 0; i < len_; ++i) {
        if (NlS_[i] == 1 && T_[i] == 0) return i;
    }
    return -1;
}

void Hungarian::relabel() {
    int alpha = get_alpha(),
        i;

    for (i = 0; i < len_; ++i) {
        if (S_[i] == 1) {
            labelsX_[i] -= alpha;
        }
        if (T_[i] == 1) {
            labelsY_[i] += alpha;
        }
    }

}
