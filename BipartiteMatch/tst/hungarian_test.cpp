/**
 * hungarian_test.cpp
 * Test suite for implementation of Hungarian algorithm
 * For additional test cases:
 * http://www.hungarianalgorithm.com/hungarianalgorithm.php
 *
 * Copyright (c) 2014 Marshall Farrier
 * license http://opensource.org/licenses/gpl-license.php GNU Public License
 *
 * Author Marshall Farrier
 * Since 2014-05-23
 */

#include <iostream>

#include "hungarian.h"
#include "index.h"

#define RESET "\033[0m"
#define BOLDRED "\033[1m\033[31m"

void test(const char *, const int *, const int &, const int &, const int &);
void test_ctor(const int *, const Hungarian &, const int &, const int &);
void test_length(const Hungarian &, const int &, int &, int &);
void test_weights(const int *, const Hungarian &, int &, int &);
void test_match_count(const Hungarian &, const int &, int &, int &);
void test_init(const int *, Hungarian &, const int &, const int &);

int main() {
    int weights1[] = {
        1, 6, 0,
        0, 8, 6,
        4, 0, 1
    };
    int len = 3,
        first_match_count = 2,
        final_answer = 16;

    test("Test case 1", weights1, len, first_match_count, final_answer);

    int weights2[] = {
        3, 2, 3,
        1, 2, 0,
        3, 2, 1
    };
    len = 3;
    first_match_count = 3;
    final_answer = 8;
    test("Test case 2", weights2, len, first_match_count, final_answer);

    int weights3[] = {
        8, 15, 54, 32,
        50, 19, 9, 98,
        50, 79, 80, 30,
        76, 86, 85, 48
    };
    len = 4;
    first_match_count = 3;
    final_answer = 307;
    test("Test case 3", weights3, len, first_match_count, final_answer);

    int weights4[] = {
        35, 26, 56, 57, 17, 97, 27, 84, 7,
        12, 83, 89, 3, 23, 65, 34, 19, 90,
        16, 94, 80, 63, 26, 4, 15, 15, 18,
        19, 36, 47, 41, 74, 16, 19, 47, 39,
        15, 41, 40, 16, 84, 92, 54, 18, 74,
        68, 14, 21, 46, 65, 57, 19, 37, 21,
        34, 48, 59, 69, 95, 68, 19, 80, 97,
        55, 77, 31, 13, 72, 39, 52, 94, 56,
        4, 85, 25, 73, 61, 58, 80, 81, 84
    };
    len = 9;
    first_match_count = 6;
    final_answer = 745;
    test("Test case 4", weights4, len, first_match_count, final_answer);

    return 0;
}

void test(const char *msg, const int *weights, const int &len, const int &first_match_count, 
        const int &final_answer) {
    std::cout << msg << std::endl;
    Hungarian hung(weights, len);
    test_ctor(weights, hung, len, first_match_count);
    test_init(weights, hung, len, final_answer);
}

void test_ctor(const int *weights, const Hungarian &hung, const int &len, const int &first_match_count) {
    std::cout << "Test constructor" << std::endl;
    int passed = 0,
        failed = 0;

    test_length(hung, len, passed, failed); 
    test_weights(weights, hung, passed, failed);
    test_match_count(hung, first_match_count, passed, failed);

    std::cout << passed << " tests passed" << std::endl;
    std::cout << (failed > 0 ? BOLDRED : RESET) << failed << " tests failed" << RESET << std::endl << std::endl;
}

void test_length(const Hungarian &hung, const int &len, int &passed, int &failed) {
    std::cout << "Test length()" << std::endl;
    if (hung.length() == len) {
        ++passed;
    } else {
        ++failed;
        std::cerr << BOLDRED << "Incorrect length!" << std::endl;
        std::cerr << "expected: " << len << ", actual: " << hung.length() << RESET << std::endl;
    }
}

void test_weights(const int *weights, const Hungarian &hung, int &passed, int &failed) {
    std::cout << "Test correct weights" << std::endl;
    int len = hung.length(),
        i,
        j;
    Index index(len);

    for (i = 0; i < len; ++i) {
        for (j = 0; j < len; ++j) {
            if (weights[index.index(i, j)] == hung.weight(i, j)) {
                ++passed;
            } else {
                ++failed;
                std::cerr << BOLDRED << "Incorrect weight!" << std::endl;
                std::cerr << "expected: " << weights[index.index(i, j)] << 
                    ", actual: " << hung.weight(i, j) << RESET << std::endl;
            }
        }
    }
}

void test_match_count(const Hungarian &hung, const int &expected_matches, int &passed, int &failed) {
    std::cout << "Test correct match count" << std::endl;
    int actual_matches = 0;

    for (int i = 0; i < hung.length(); ++i) {
        if (hung.matchX(i) >= 0) ++actual_matches;
    }
    if (expected_matches == actual_matches) {
        ++passed;
    } else {
        ++failed;
        std::cerr << BOLDRED << "Incorrect number of matches!" << std::endl;
        std::cerr << "expected: " << expected_matches << ", actual: " << actual_matches << RESET << std::endl;
    }
}

void test_init(const int *weights, Hungarian &hung, const int &len, const int &expected) {
    std::cout << "Test init(), which executes algorithm" << std::endl;
    int passed = 0,
        failed = 0;

    hung.init();
    int actual = hung.get_match_total();
    if (actual == expected) {
        ++passed;
    } else {
        ++failed;
        std::cerr << BOLDRED << "Incorrect maximum weight for match!" << std::endl;
        std::cerr << "expected: " << expected << ", actual: " << actual << RESET << std::endl;
    }
    std::cout << passed << " tests passed" << std::endl;
    std::cout << (failed > 0 ? BOLDRED : RESET) << failed << " tests failed" << RESET << std::endl << std::endl;
}
