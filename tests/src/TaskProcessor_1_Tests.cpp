#include <gtest/gtest.h>

#include "proc/TaskProcessorFactory.h"
#include "proc/ITaskProcessor.h"


class TaskProcessor_1_Tests : public testing::Test {
    protected:
        ITaskProcessor* processor;
        TaskProcessor_1_Tests() {}
         ~TaskProcessor_1_Tests() override {}
       
         void SetUp() override {
            processor = (new TaskProcessorFactory) -> createTaskProcessor(1);
         }
       
        void TearDown() override {
           delete processor;
         }

};


TEST_F(TaskProcessor_1_Tests, CheckHappyCase) {
    std::string expected = "Oleksandr Niesov";
    std::string actual =  processor->execute("Oleksandr");
    EXPECT_EQ(actual, expected);
}


TEST_F(TaskProcessor_1_Tests, Last_name) {
    std::string expected = "Oleksandr Niesov";
    std::string actual =  processor->execute("Niesov");
    EXPECT_NE(actual, expected);
}


TEST_F(TaskProcessor_1_Tests, Space_Instead_of_data) {
    std::string expected = "Oleksandr Niesov";
    std::string actual =  processor->execute(" ");
    EXPECT_NE(actual, expected);
}
