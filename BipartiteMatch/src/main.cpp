/**
 * main.cpp
 * For demoing hungarian class
 * 
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

#include <iostream>

#include "hungarian.h"

// the number of rows (or cols, since matrix is square)
//size_t len;
//int *weights;
//bool has_run;

int main() {
    int len = 3;
    int scores[len * len];
    Hungarian hung(scores, len);

    std::cout << hung.get_match_total() << std::endl;
    return 0;
}
