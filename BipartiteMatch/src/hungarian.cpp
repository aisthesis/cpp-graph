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

#include "hungarian.h"

// the number of rows (or cols, since matrix is square)
//int len;
//int *weights;
//bool has_run;

Hungarian::Hungarian(const int *weights, const int &len) {
    const int len_sq = len * len;
    const int vertex_count = len + len;
    int i, j;

    len_ = len;
    has_run_ = false;

    // initialize weights
    weights_ = new int[len_sq];
    for (i = 0; i < len_sq; ++i) {
        weights_[i] = weights[i];
        equality_graph_[i] = 0;
    }
    // initialize vertex labels
    vertex_labels_ = new int[vertex_count];
    for (i = 0; i < len; ++i) {
        vertex_labels_[i] = *std::max_element(weights_ + i * len, 
                weights_ + i * len + len);
    }
    for (; i < vertex_count; ++i) {
        vertex_labels_[i] = 0;
    }
    //initialize equality graph to starting values
    equality_graph_ = new int[len_sq];
    for (i = 0; i < len; ++i) {
        for (j = 0; j < len; ++j) {
            if (vertex_labels_[i] + vertex_labels_[len + j] == weights_[index(i, j)]) {
                equality_graph_[index(i, j)] = 1;
            } else {
                equality_graph_[index(i, j)] = 0;
            }
        }
    }
}
Hungarian::~Hungarian() {
    delete[] weights_;
    delete[] vertex_labels_;
    delete[] equality_graph_;
}

int Hungarian::get_match_total() {
    // TODO
    return 0;
}

void Hungarian::run() {
    // TODO
}

int Hungarian::row(const int &index) const {
    return index / len_;
}

int Hungarian::col(const int &index) const {
    return index % len_;
}

int Hungarian::index(const int &row, const int &col) const {
    return len_ * row + col;
}
