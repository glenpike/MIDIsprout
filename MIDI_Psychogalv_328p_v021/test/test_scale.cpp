#include <unity.h>
#include "scale.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_scaleSearch() {
    int scaleTest[3]  = {1, 2, 3};
    TEST_ASSERT_TRUE(scaleSearch(5, scaleTest, 3) == 6);
}

int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_scaleSearch);
    UNITY_END();
}
