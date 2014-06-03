/**
 * maxmatch.h
 * Maximum matching of a bipartite graph.
 *
 * Copyright (c) 2014 Marshall Farrier
 * license http://opensource.org/licenses/gpl-license.php GNU Public License
 *
 * Author Marshall Farrier
 * Since 2014-05-29
 */

#ifndef MAXMATCH_H
#define MAXMATCH_H

#include "index.h"

class MaxMatch {
private:
    const int rows_;
    const int cols_;
    const Index index_;
    int *graph_,
        *match_by_X_,
        *match_by_Y_,
        *childX_;
public:
    MaxMatch(const int *, const int &, const int &);
    ~MaxMatch();
    // run the algorithm to get the matching
    void init();
    /**
     * get the Y element matching a given X element.
     * return -1 if no element matches
     */
    int match_X(const int &) const;
    /**
     * get the X element matching a given Y element
     * return -1 if no element matches
     */
    int match_Y(const int &) const;
    /**
     * return the number of matches found
     */
    int matches() const;
    /**
     * reset the graph on which to find a matching.
     * presupposes the same number of rows and
     * columns.
     * Also resets match_by_row_ and match_by_col_ to 0s
     */
    void set(const int *);
    /**
     * Does not reset matchings to avoid unnecessary repetition
     */
    void add_graph_edge(const int &, const int &);
    void delete_graph_edge(const int &, const int &);
    bool has_graph_edge(const int &, const int &);
    int sizeX() const;
    int sizeY() const;
    void reset();
private:
    void reset_matches();
    void reset_childX();
    /**
     * Return the start of an augmenting path, if there
     * is one. Otherwise, return -1.
     */
    int dfs();
    /**
     * recursive search starting at a given X vertex.
     */
    bool dfs_visit(const int &);
    void augment_match(int);
};
#endif
