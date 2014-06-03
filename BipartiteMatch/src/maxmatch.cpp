/**
 * maxmatch.cpp
 * Find a maximum match in a bipartite graph.
 * At each step, we look for an augmenting path. If found,
 * we augment the matching. If not, we're done.
 * Differs from Hopcroft-Karp in that we augment as soon
 * as we find one augmenting path. We don't try to find all
 * minimal augmenting paths.
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
    childX_ = new int[rows_];

    set(graph);
    reset();
}

MaxMatch::~MaxMatch() {
    delete[] childX_;
    delete[] match_by_Y_;
    delete[] match_by_X_;
    delete[] graph_;
}

// run the algorithm to get the matching
void MaxMatch::init() {
    int start_index;

    while ((start_index = dfs()) != -1) {
        augment_match(start_index);
    }
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
    reset();
}

void MaxMatch::add_graph_edge(const int &x, const int &y) {
    graph_[index_.index(x, y)] = 1;
}

void MaxMatch::delete_graph_edge(const int &x, const int &y) {
    graph_[index_.index(x, y)] = 0;

}

bool MaxMatch::has_graph_edge(const int &x, const int &y) {
    return graph_[index_.index(x, y)] == 1;
}

void MaxMatch::reset() {
    reset_matches();
    reset_childX();
}

void MaxMatch::reset_matches() {
    std::fill(match_by_X_, match_by_X_ + rows_, -1);
    std::fill(match_by_Y_, match_by_Y_ + cols_, -1);
}

void MaxMatch::reset_childX() {
    std::fill(childX_, childX_ + rows_, -1);
}

int MaxMatch::dfs() {
    reset_childX();
    for (int i = 0; i < rows_; ++i) {
        if (match_by_X_[i] == -1 && dfs_visit(i)) {
            return i;
        }
    }
    return -1;
}

bool MaxMatch::dfs_visit(const int &i) {
    // vertex already visited
    if (childX_[i] >= 0) { return false; }
    for (int j = 0; j < cols_; ++j) {
        // we're only looking for unmatched edges
        if (graph_[index_.index(i, j)] == 0 || match_by_X_[i] == j) continue;
        childX_[i] = j;
        // j is unmatched, augmenting path found
        if (match_by_Y_[j] == -1) return true; 
        // j is matched, keep going
        if (dfs_visit(match_by_Y_[j])) return true;
    }
    childX_[i] = -1;
    return false;
}

void MaxMatch::augment_match(int i) {
    int nextX;

    while (i >= 0) {
        match_by_X_[i] = childX_[i];
        nextX = match_by_Y_[match_by_X_[i]];
        match_by_Y_[match_by_X_[i]] = i;
        i = nextX;
    }
}

int MaxMatch::matches() const {
    return std::count_if(match_by_X_, match_by_X_ + rows_, [](int x) { return x != -1; });
}

int MaxMatch::sizeX() const {
    return rows_;
}

int MaxMatch::sizeY() const {
    return cols_;
}
