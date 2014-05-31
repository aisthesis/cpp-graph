/**
 * hopcroftkarp.cpp
 * Implementation of Hopcroft-Karp algorithm for maximum
 * matching in a bipartite graph.
 *
 * Copyright (c) 2014 Marshall Farrier
 * license http://opensource.org/licenses/gpl-license.php GNU Public License
 *
 * Author Marshall Farrier
 * Since 2014-05-29
 */

#include <algorithm>

#include "index.h"
#include "maxmatch.h"

MaxMatch::MaxMatch(const int *graph, const int &X_size, 
        const int &Y_size) : rows_(X_size), cols_(Y_size), index_(Y_size) {
    graph_ = new int[rows_ * cols_];
    match_by_X_ = new int[rows_];
    match_by_Y_ = new int[cols_];
    visitedX_ = new int[rows_];
    visitedY_ = new int[cols_];

    set(graph);
    reset();
}

MaxMatch::~MaxMatch() {
    delete[] visitedY_;
    delete[] visitedX_;
    delete[] match_by_Y_;
    delete[] match_by_X_;
    delete[] graph_;
}

// run the algorithm to get the matching
void MaxMatch::init() {
    // TODO
}
/**
 * get the column matched to a given row.
 * return -1 if no column matches
 */
int MaxMatch::match_X(const int &x) const {
    return match_by_X_[x];
}
/**
 * get the row matched to a given column.
 * return -1 if no row matches
 */
int MaxMatch::match_Y(const int &y) const {
    return match_by_Y_[y];
}

/**
 * reset the graph on which to find a matching
 * presupposes the same number of rows and
 * columns
 */
void MaxMatch::set(const int *graph) {
    int len = rows_ * cols_;

    for (int i = 0; i < len; ++i) {
        graph_[i] = graph[i] == 0 ? 0 : 1;
    }
    reset_matches();
}

void MaxMatch::add_edge(const int &x, const int &y) {
    graph_[index_.index(x, y)] = 1;
}

void MaxMatch::delete_edge(const int &x, const int &y) {
    graph_[index_.index(x, y)] = 0;

}

bool MaxMatch::has_edge(const int &x, const int &y) {
    return graph_[index_.index(x, y)] == 1;
}

void MaxMatch::reset() {
    reset_matches();
    reset_visited();
}

void MaxMatch::reset_matches() {
    std::fill(match_by_X_, match_by_X_ + rows_, -1);
    std::fill(match_by_Y_, match_by_Y_ + cols_, -1);
}

void MaxMatch::reset_visited() {
    std::fill(visitedX_, visitedX_ + rows_, WHITE);
    std::fill(visitedY_, visitedY_ + cols_, WHITE);
}
