/**
 * hopcroftkarp_test.cpp
 * Unit tests for Hopcroft-Karp algorithm
 *
 * Copyright (c) 2014 Marshall Farrier
 * license http://opensource.org/licenses/gpl-license.php GNU Public License
 *
 * Author Marshall Farrier
 * Since 2014-05-29
 */

#include <iostream>

#include "maxmatch.h"
#include "index.h"

int main() {
    /**
     * CLRS, p. 733
     */
    int graph1[] = {
        1, 0, 0, 0,
        1, 0, 1, 0,
        0, 1, 1, 1,
        0, 0, 1, 0,
        0, 0, 1, 0
    };
    const int rows = 5,
        cols = 4;
    int tests_passed = 0,
        tests_failed = 0,
        i;
    MaxMatch mm(graph1, rows, cols);
    Index index(cols);

    std::cout << "Test constructor" << std::endl;
    std::cout << "Test member graph" << std::endl;
    for (i = 0; i < rows * cols; ++i) {
        if (mm.has_edge(index.row(i), index.col(i)) && graph1[i] == 1) {
            ++tests_passed;
        } else if (!mm.has_edge(index.row(i), index.col(i)) && graph1[i] == 0) {
            ++tests_passed;
        } else {
            ++tests_failed;
            std::cout << "Test failed for index " << i << std::endl;
            if (mm.has_edge(index.row(i), index.col(i))) {
                std::cout << "Member graph has edge but not source graph" << std::endl;
            } else {
                std::cout << "Member graph doesn't have edge but source graph does" << std::endl;
            }
        }
    }
    std::cout << tests_passed << " tests passed" << std::endl;
    std::cout << tests_failed << " tests failed" << std::endl << std::endl;

    std::cout << "Test matches before running algorithm" << std::endl;
    tests_passed = 0;
    tests_failed = 0;
    for (i = 0; i < rows; ++i) {
        if (mm.match_X(i) == -1) {
            ++tests_passed;
        } else {
            ++tests_failed;
            std::cout << "X matches not initialized properly for index " << i << std::endl;
            std::cout << "expected: -1, actual: " << mm.match_X(i) << std::endl;
        }
    }
    for (i = 0; i < cols; ++i) {
        if (mm.match_Y(i) == -1) {
            ++tests_passed;
        } else {
            ++tests_failed;
            std::cout << "Y matches not initialized properly for index " << i << std::endl;
            std::cout << "expected: -1, actual: " << mm.match_Y(i) << std::endl;
        }
    }
    std::cout << tests_passed << " tests passed" << std::endl;
    std::cout << tests_failed << " tests failed" << std::endl << std::endl;

    return 0;
}
