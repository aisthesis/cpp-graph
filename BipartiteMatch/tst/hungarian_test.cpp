/**
 * hungarian_test.cpp
 * Test suite for implementation of Hungarian algorithm
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
    return 0;
}

void test(const char *msg, const int *weights, const int &len, const int &first_match_count, 
        const int &final_answer) {
    std::cout << msg << std::endl;
    Hungarian hung(weights, len);
    test_ctor(weights, hung, len, first_match_count);
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
