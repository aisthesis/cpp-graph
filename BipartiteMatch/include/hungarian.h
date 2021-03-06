/**
 * hungarian.h
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

#ifndef HUNGARIAN_H
#define HUNGARIAN_H

#include <cstddef>

#include "maxmatch.h"
#include "index.h"

class Hungarian {
private:
    // the number of rows (or cols, since matrix is square)
    const int len_;
    const int len_sq_;
    /**
     * the graph is bipartite, but edges may have weight 0
     * to deal with the case where the sets to match have different
     * sizes
     */
    int *weights_;
    /**
     * edges will just be 0 or 1.
     * Edges in this graph may be 1 for 0 weight edges (to
     * padded vertices) in main graph
     */
    int *equality_graph_;
    int *labelsX_;
    int *labelsY_;
    // 1 for members of S, 0 for non-members
    int *S_;
    // 1 for members of T, 0 for non-members
    int *T_;
    // 1 for members of NlS, 0 for non-members
    int *NlS_;
    Index index_;
    MaxMatch matcher_;

public:
    Hungarian(const int *weights, const int &len);
    ~Hungarian();

    int get_match_total();
    int matchX(const int &) const;
    int matchY(const int &) const;
    int length() const;
    int weight(const int &, const int &) const;
    void init();

private:
    void improve_equality_graph();
    int get_free_vertex() const;
    void update_equality_graph();
    int get_alpha() const;
    // S_, T_, NlS_
    void reset_path_sets();
    void update_NlS(const int &);
    int nls_minus_t() const;
    void relabel();
};

#endif
