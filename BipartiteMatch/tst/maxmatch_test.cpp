/**
 * maxmatch_test.cpp
 * Unit tests for maximum matching in a bipartite graph. 
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

void test(const char *, const int *, const int &, const int &, const int &, 
    const int &, const int &, const int &);
void test_constructor(MaxMatch &, const int *, const int &, const int &);
void test_matches(MaxMatch &, const int *, const int &, const int &, const int &);
void test_add_edge(MaxMatch &, const int &, const int &, const int &);
void test_match_count(MaxMatch &, const int &, int &, int &);
void test_match_consistency(MaxMatch &, int &, int &);
void test_set_graph(MaxMatch &);
void test_delete_edge(MaxMatch &, const int &, const int &, const int &);

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
    int rows = 5,
        cols = 4,
        expected_matches = 3,
        addi = 3,
        addj = 3,
        expected_after = 4;

    test("Test case 1", graph1, rows, cols, expected_matches, addi, addj, expected_after);

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
    /**
     * 0 2
     * 1 0
     * 2 3
     * 3 1
     * 4 4
     * 5 5
     * is a possible full match
     */
    rows = 6;
    cols = 6;
    expected_matches = 6;
    addi = 0;
    addj = 4;
    expected_after = 6;
    test("Test case 2", graph2, rows, cols, expected_matches, addi, addj, expected_after);

    int graph3[] = {
        0, 1, 0, 0, 0,
        0, 1, 0, 0, 0,
        1, 0, 0, 0, 0,
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 0
    };
    /**
     * 0 1
     * 2 0
     * 3 2
     * is a possible match
     */
    rows = 5;
    cols = 5;
    expected_matches = 3;
    addi = 4;
    addj = 4;
    expected_after = 4;
    test("Test case 3", graph3, rows, cols, expected_matches, addi, addj, expected_after);
    

    return 0;
}

void test(const char *msg, const int *graph, const int &rows, const int &cols, const int &expected_matches,
        const int &addi, const int &addj, const int &expected_after) {
    MaxMatch mm(graph, rows, cols);

    std::cout << msg << std::endl;
    test_constructor(mm, graph, rows, cols);
    test_matches(mm, graph, rows, cols, expected_matches);
    test_add_edge(mm, addi, addj, expected_after);
    test_set_graph(mm);
}

void test_constructor(MaxMatch &mm, const int *graph, const int &rows, const int &cols) {
    int tests_passed = 0,
        tests_failed = 0,
        i,
        actuali;
    Index index(cols);

    std::cout << "Test constructor" << std::endl;
    std::cout << "Test member graph" << std::endl;
    for (i = 0; i < rows * cols; ++i) {
        if (mm.has_graph_edge(index.row(i), index.col(i)) && graph[i] == 1) {
            ++tests_passed;
        } else if (!mm.has_graph_edge(index.row(i), index.col(i)) && graph[i] == 0) {
            ++tests_passed;
        } else {
            ++tests_failed;
            std::cout << "Test failed for index " << i << std::endl;
            if (mm.has_graph_edge(index.row(i), index.col(i))) {
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
}

void test_matches(MaxMatch &mm, const int *graph, const int &rows, const int &cols, const int &expected) {
    std::cout << "Test matches after running algorithm" << std::endl;

    int tests_passed = 0,
        tests_failed = 0,
        i;
    Index index(cols);

    mm.init();
    test_match_count(mm, expected, tests_passed, tests_failed);

    std::cout << "Matches belong to graph" << std::endl;
    for (i = 0; i < rows; ++i) {
        if (mm.match_X(i) >= 0) {
            if (graph[index.index(i, mm.match_X(i))] != 0) {
                ++tests_passed;
            } else {
                ++tests_failed;
                std::cout << "Match does not belong to graph for value " << i << std::endl;
                std::cout << "Value matched: " << mm.match_X(i) << std::endl;
            }
        }
    }
    test_match_consistency(mm, tests_passed, tests_failed);
    std::cout << tests_passed << " tests passed" << std::endl;
    std::cout << tests_failed << " tests failed" << std::endl << std::endl;
}

void test_add_edge(MaxMatch &mm, const int &from, const int &to, const int &expected) {
    std::cout << "Add edge and test matches" << std::endl;
    int tests_passed = 0,
        tests_failed = 0;
    mm.add_graph_edge(from, to);
    mm.reset();
    mm.init();
    test_match_count(mm, expected, tests_passed, tests_failed);
    test_match_consistency(mm, tests_passed, tests_failed);
    std::cout << "Edge present in graph" << std::endl;
    if (mm.has_graph_edge(from, to)) {
        ++tests_passed;
    } else {
        ++tests_failed;
        std::cout << "Added edge (" << from << ", " << to << ") not present in graph" << std::endl;
    }

    std::cout << tests_passed << " tests passed" << std::endl;
    std::cout << tests_failed << " tests failed" << std::endl << std::endl;
}

void test_match_count(MaxMatch &mm, const int &expected, int &passed, int &failed) {
    std::cout << "Test correct number of matches" << std::endl;
    int actuali = mm.matches();
    if (actuali == expected) {
        ++passed;
    } else {
        ++failed;
        std::cout << "Incorrect number of matches!" << std::endl;
        std::cout << "expected: " << expected << ", actual: " << actuali << std::endl;
    }
}

void test_match_consistency(MaxMatch &mm, int &passed, int &failed) {
    std::cout << "Matches by X and by Y are consistent" << std::endl;
    for (int i = 0; i < mm.sizeX(); ++i) {
        if (mm.match_X(i) == -1 || mm.match_Y(mm.match_X(i)) == i) {
            ++passed;
        } else {
            ++failed;
            std::cout << "Match X and Match Y inconsistent for value " << i << std::endl;
            std::cout << "match_X: " << mm.match_X(i) << ", match_Y of this value: " << mm.match_Y(mm.match_X(i)) << std::endl;
        }
    }
    for (int i = 0; i < mm.sizeY(); ++i) {
        if (mm.match_Y(i) == -1 || mm.match_X(mm.match_Y(i)) == i) {
            ++passed;
        } else {
            ++failed;
            std::cout << "Match Y and Match X inconsistent for value " << i << std::endl;
            std::cout << "match_Y: " << mm.match_Y(i) << ", match_X of this value: " << mm.match_X(mm.match_Y(i)) << std::endl;
        }
    }
}

void test_set_graph(MaxMatch &mm) {
    std::cout << "Test resetting graph" << std::endl;
    int *graph = new int[mm.sizeX() * mm.sizeY()];
    int i, j, matches;
    Index index(mm.sizeY());

    for (i = 0; i < mm.sizeX(); ++i) {
        for (j = 0; j < mm.sizeY(); ++j) {
            if (i == j) {
                graph[index.index(i, j)] = 1;
            } else {
                graph[index.index(i, j)] = 0;
            }
        }
    }
    mm.set(graph);
    matches = mm.sizeX() <= mm.sizeY() ? mm.sizeX() : mm.sizeY();
    test_matches(mm, graph, mm.sizeX(), mm.sizeY(), matches);
    test_delete_edge(mm, 0, 0, matches - 1);
    delete[] graph;
}

void test_delete_edge(MaxMatch &mm, const int &from, const int &to, const int &expected) {
    std::cout << "Test delete edge" << std::endl;
    int passed = 0,
        failed = 0;
    mm.delete_graph_edge(from, to);
    mm.delete_graph_edge(from, to);
    if (mm.has_graph_edge(from, to)) {
        ++failed;
        std::cout << "Edge present after deletion!" << std::endl;
    } else {
        ++passed;
    }
    mm.reset();
    mm.init();
    test_match_count(mm, expected, passed, failed);
    test_match_consistency(mm, passed, failed);
    std::cout << passed << " tests passed" << std::endl;
    std::cout << failed << " tests failed" << std::endl << std::endl;
}
