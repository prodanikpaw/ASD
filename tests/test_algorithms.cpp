#include "algorithms.h"
#include <gtest/gtest.h>

TEST(BracketCheckerTest, valid_simple_expressions) {
    EXPECT_TRUE(check_breckets("()"));
    EXPECT_TRUE(check_breckets("[]"));
    EXPECT_TRUE(check_breckets("{}"));
}
TEST(BracketCheckerTest, valid_nested_expressions) {
    EXPECT_TRUE(check_breckets("({[]})"));
    EXPECT_TRUE(check_breckets("[({})]"));
    EXPECT_TRUE(check_breckets("{([])}"));
}
TEST(BracketCheckerTest, invalid_unmatched_closing) {
    EXPECT_FALSE(check_breckets(")"));
    EXPECT_FALSE(check_breckets("())"));
}