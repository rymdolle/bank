#include <gtest/gtest.h>

// This is a sample test to ensure the testing framework is working.
TEST(BankSanityCheck, BasicMath) {
    EXPECT_EQ(2 + 2, 4);
}

// Once you share your Bank class code, you can write tests like this:
/*
TEST(BankAccountTest, DepositIncreasesBalance) {
    // Arrange
    BankAccount account;
    
    // Act
    account.deposit(100.0);

    // Assert
    EXPECT_EQ(account.getBalance(), 100.0);
}
*/