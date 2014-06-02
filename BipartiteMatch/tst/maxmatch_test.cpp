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
        i,
        actuali,
        expectedi;
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
    actuali = mm.matches();
    if (actuali == 0) {
        ++tests_passed;
    } else {
        ++tests_failed;
        std::cout << "Incorrect number of initial matches!" << std::endl;
        std::cout << "expected: 0, actual: " << actuali << std::endl;
    }
    std::cout << tests_passed << " tests passed" << std::endl;
    std::cout << tests_failed << " tests failed" << std::endl << std::endl;

    std::cout << "Test matches after running algorithm" << std::endl;
    tests_passed = 0;
    tests_failed = 0;
    mm.init();
    actuali = mm.matches();
    if (actuali == 3) {
        ++tests_passed;
    } else {
        ++tests_failed;
        std::cout << "Incorrect number of matches!" << std::endl;
        std::cout << "expected: 3, actual: " << actuali << std::endl;
    }
    std::cout << tests_passed << " tests passed" << std::endl;
    std::cout << tests_failed << " tests failed" << std::endl << std::endl;

    std::cout << "Add edge to allow an additional match" << std::endl;
    tests_passed = 0;
    tests_failed = 0;
    mm.add_edge(3, 3);
    mm.reset();
    mm.init();
    actuali = mm.matches();
    expectedi = 4;
    if (actuali == expectedi) {
        ++tests_passed;
    } else {
        ++tests_failed;
        std::cout << "Incorrect number of matches!" << std::endl;
        std::cout << "expected: " << expectedi << ", actual: " << actuali << std::endl;
    }
    for (i = 0; i < rows; ++i) {
        if (mm.match_X(i) == -1 || mm.match_Y(mm.match_X(i)) == i) {
            ++tests_passed;
        } else {
            ++tests_failed;
            std::cout << "Match X and Match Y inconsistent for value " << i << std::endl;
            std::cout << "match_X: " << mm.match_X(i) << ", match_Y of this value: " << mm.match_Y(mm.match_X(i)) << std::endl;
        }
    }
    for (i = 0; i < cols; ++i) {
        if (mm.match_X(i) == -1 || mm.match_X(mm.match_Y(i)) == i) {
            ++tests_passed;
        } else {
            ++tests_failed;
            std::cout << "Match Y and Match X inconsistent for value " << i << std::endl;
            std::cout << "match_Y: " << mm.match_Y(i) << ", match_X of this value: " << mm.match_X(mm.match_Y(i)) << std::endl;
        }
    }

    std::cout << tests_passed << " tests passed" << std::endl;
    std::cout << tests_failed << " tests failed" << std::endl << std::endl;

    /**
     * Sedgewick, Algorithms in C, vol. 2, p. 420
     */
    int graph2[] = {
        1, 1, 1, 0, 0, 0,
        1, 1, 0, 0, 0, 1,
        0, 0, 1, 1, 1, 0,
        1, 1, 0, 0, 0, 0,
        0, 0, 0, 1, 1, 1,
        0, 0, 1, 0, 1, 1
    };
    const int rows2 = 6,
        cols2 = 6;
    MaxMatch mm2(graph2, rows2, cols2);
    mm2.init();
    tests_passed = 0;
    tests_failed = 0;
    actuali = mm2.matches();
    expectedi = 6;
    if (actuali == expectedi) {
        ++tests_passed;
    } else {
        ++tests_failed;
        std::cout << "Incorrect number of matches!" << std::endl;
        std::cout << "expected: " << expectedi << ", actual: " << actuali << std::endl;
    }
    std::cout << std::endl;
    std::cout << tests_passed << " tests passed" << std::endl;
    std::cout << tests_failed << " tests failed" << std::endl << std::endl;

    std::cout << "Run after deleting edge" << std::endl;
    tests_passed = 0;
    tests_failed = 0;
    mm2.delete_edge(0, 0);
    if (mm2.has_edge(0, 0)) {
        ++tests_failed;
        std::cout << "Edge present after deletion!" << std::endl;
    } else {
        ++tests_passed;
    }
    mm2.reset();
    mm2.init();
    /**
     * 0 2
     * 1 0
     * 2 3
     * 3 1
     * 4 4
     * 5 5
     * is a possible full match
     */
    actuali = mm2.matches();
    expectedi = 6;
    if (actuali == expectedi) {
        ++tests_passed;
    } else {
        ++tests_failed;
        std::cout << "Incorrect number of matches!" << std::endl;
        std::cout << "expected: " << expectedi << ", actual: " << actuali << std::endl;
    }
    std::cout << tests_passed << " tests passed" << std::endl;
    std::cout << tests_failed << " tests failed" << std::endl << std::endl;

    std::cout << "Test set() by replacing graph" << std::endl;
    int graph3[] = {
        1, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0
    };
    tests_passed = 0;
    tests_failed = 0;
    mm2.set(graph3);
    mm2.init();
    actuali = mm2.matches();
    expectedi = 5;
    if (actuali == expectedi) {
        ++tests_passed;
    } else {
        ++tests_failed;
        std::cout << "Incorrect number of matches!" << std::endl;
        std::cout << "expected: " << expectedi << ", actual: " << actuali << std::endl;
    }
    std::cout << tests_passed << " tests passed" << std::endl;
    std::cout << tests_failed << " tests failed" << std::endl << std::endl;
    
    return 0;
}
