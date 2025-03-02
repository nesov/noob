#include <gtest/gtest.h>

#include "proc/TaskProcessorFactory.h"
#include "proc/ITaskProcessor.h"

class TaskProcessor_2_Tests : public testing::Test {
    protected:
        ITaskProcessor* processor;
        TaskProcessor_2_Tests() {}
         ~TaskProcessor_2_Tests() override {}
       
         void SetUp() override {
            processor = (new TaskProcessorFactory) -> createTaskProcessor(2);
         }
       
        void TearDown() override {
           delete processor;
         }

};

TEST_F(TaskProcessor_2_Tests, Check_int_values) {
    std::string expected = "The Sum (first two found numbers) is: 10.000000";
    std::string actual =  processor -> execute("5 5");
    EXPECT_EQ(actual, expected);
}

TEST_F(TaskProcessor_2_Tests, Check_float_values) {
    std::string expected = "The Sum (first two found numbers) is: 14.110000";
    std::string actual =  processor -> execute("5.12 8.99");
    EXPECT_EQ(actual, expected);
}

TEST_F(TaskProcessor_2_Tests, Check_finding_two_values_within_array_of_values) {
    std::string expected = "The Sum (first two found numbers) is: 9.000000";
    std::string actual =  processor -> execute("4, 5, 299, 22, 21.0001");
    EXPECT_EQ(actual, expected);
}

TEST_F(TaskProcessor_2_Tests, Check_finding_two_values_within_message) {
    std::string expected = "The Sum (first two found numbers) is: 97.000000";
    std::string actual =  processor -> execute("7 jahsdk sakasdjdsa d 90dsad");
    EXPECT_EQ(actual, expected);
}

TEST_F(TaskProcessor_2_Tests, Empty_message) {
    std::string expected = "There should be at least two numbers to make it happen.";
    std::string actual =  processor -> execute(" ");
    EXPECT_NE(actual, expected);
}

TEST_F(TaskProcessor_2_Tests, Check_error_message) {
    std::string expected = "There should be at least two numbers to make it happen.";
    std::string actual =  processor -> execute("Niesov");
    EXPECT_NE(actual, expected);
}
