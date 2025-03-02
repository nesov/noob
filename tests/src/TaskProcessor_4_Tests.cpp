#include <gtest/gtest.h>

#include "proc/TaskProcessorFactory.h"
#include "proc/ITaskProcessor.h"


class TaskProcessor_4_Tests : public testing::Test {
    protected:
        ITaskProcessor* processor;
        TaskProcessor_4_Tests() {}
         ~TaskProcessor_4_Tests() override {}
       
         void SetUp() override {
            processor = (new TaskProcessorFactory) -> createTaskProcessor(4);
         }
       
        void TearDown() override {
           delete processor;
         }
};


TEST_F(TaskProcessor_4_Tests, Pair_of_numbers) {
    std::string expected = "Maximum element is: 3.000000";
    std::string actual =  processor->execute("1,3");
    EXPECT_EQ(actual, expected);
}

TEST_F(TaskProcessor_4_Tests, Normal_array_elements) {
    std::string expected = "Maximum element is: 90.000000";
    std::string actual =  processor -> execute("10.3 2 4 90 87 71 0");
    EXPECT_EQ(actual, expected);
}

TEST_F(TaskProcessor_4_Tests, Negative_numbers_only) {
    std::string expected = "Maximum element is: -1.000000";
    std::string actual =  processor -> execute("-99 -3 -1");
    EXPECT_EQ(actual, expected);
}

TEST_F(TaskProcessor_4_Tests, Mixed_numbers_array) {
    std::string expected = "Maximum element is: 7.324500";
    std::string actual =  processor -> execute("-99 -3 2 -1 -111.123 7.3245");
    EXPECT_EQ(actual, expected);
}

TEST_F(TaskProcessor_4_Tests, Text_instead_of_arr) {
    std::string expected = "Array is 2 and more elements.";
    std::string actual =  processor -> execute("No numbers at all");
    EXPECT_EQ(actual, expected);
}

TEST_F(TaskProcessor_4_Tests, Single_number) {
    std::string expected = "Array is 2 and more elements.";
    std::string actual =  processor -> execute("4");
    EXPECT_EQ(actual, expected);
}







