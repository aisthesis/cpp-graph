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

class Hungarian {
    private:
    // the number of rows (or cols, since matrix is square)
    int len_;
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
    int *vertex_labels_;
    // We only need to run the algorithm once
    bool has_run_;

    public:
    Hungarian(const int *weights, const int &len);
    ~Hungarian();

    int get_match_total();
    int length() const;
    int get_weight(const int &, const int &) const;
    int get_eq_graph_edge(const int &, const int &) const;
    int get_label(const int &) const;
    void run();

    private:
    int row(const int &) const;
    int col(const int &) const;
    int index(const int &, const int &) const;
};

#endif
