#include <unity.h>
#include "scale.h"

// scaleSearch
void test_scaleSearch_note_not_found() {
    int scaleTest[]  = {-1, 1, 2, 3};
    TEST_ASSERT_EQUAL_INT(3, scaleSearch(5, scaleTest, 3));
}

void test_scaleSearch_note_found() {
    int scaleTest[]  = {-1, 1, 2, 3};
    TEST_ASSERT_EQUAL_INT(2, scaleSearch(2, scaleTest, 3));
}

void test_scaleSearch_nearest_note_found() {
    int scaleTest[]  = {-1, 1, 2, 3, 7};
    TEST_ASSERT_EQUAL_INT(7, scaleSearch(5, scaleTest, 4));
}

void test_scaleSearch_scale_size() {
    int scaleTest[]  = {-1, 1, 2, 3, 4, 5};
    TEST_ASSERT_EQUAL_INT(5, scaleSearch(5, scaleTest, 5));
}

void test_scaleSearch_ignores_first_element() {
    int scaleTest[] = {-1, 9};
    TEST_ASSERT_EQUAL_INT(9, scaleSearch(5, scaleTest, 2));
}

// scaleNote
// When note is not found it is mapped to the highest note in the scale
void test_scaleNote_not_found() {
    int scaleTest[4]  = {3, 1, 2, 3};
    TEST_ASSERT_EQUAL_INT(3, scaleNote(5, scaleTest, 0));
}

// When note > 1 octave and not found
// It is then scaled by 17/12 octaves
void test_scaleNote_not_found_octave() {
    int scaleTest[4]  = {3, 1, 2, 3};
    TEST_ASSERT_EQUAL_INT(15, scaleNote(17, scaleTest, 0));
}

void test_scaleNote_found() {
    int scaleTest[4]  = {3, 1, 2, 3};
    TEST_ASSERT_EQUAL_INT(2, scaleNote(2, scaleTest, 0));
}

void test_scaleNote_octave_found() {
    int scaleTest[4]  = {3, 1, 2, 3};
    TEST_ASSERT_EQUAL_INT(26, scaleNote(26, scaleTest, 0));
}

void test_scaleNote_found_root() {
    int scaleTest[4]  = {3, 1, 2, 3};
    TEST_ASSERT_EQUAL_INT(5, scaleNote(2, scaleTest, 3));
}

void test_scaleNote_major_next_octave() {
    int scaleMajor[] = {7, 0, 2, 4, 5, 7, 9, 11};
    TEST_ASSERT_EQUAL_INT(12, scaleNote(12, scaleMajor, 0));
}

void test_scaleNote_major_octave() {
    int scaleMajor[] = {7, 0, 2, 4, 5, 7, 9, 11};
    int expected[12] = { 0, 2, 2, 4, 4, 5, 7, 7, 9, 9, 11, 11 };
    int actual[12];
    for (int note = 0; note < 12; note++) {
        actual[note] = scaleNote(note, scaleMajor, 0);
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, 12);
}


int main( int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_scaleSearch_note_not_found);
    RUN_TEST(test_scaleSearch_note_found);
    RUN_TEST(test_scaleSearch_nearest_note_found);
    RUN_TEST(test_scaleSearch_scale_size);
    RUN_TEST(test_scaleSearch_ignores_first_element);

    RUN_TEST(test_scaleNote_not_found);
    RUN_TEST(test_scaleNote_found);
    RUN_TEST(test_scaleNote_octave_found);
    RUN_TEST(test_scaleNote_found_root);

    // Bugs/weirdness to fix
    RUN_TEST(test_scaleNote_not_found_octave);
    RUN_TEST(test_scaleNote_major_next_octave);
    RUN_TEST(test_scaleNote_major_octave);
    UNITY_END();
}
