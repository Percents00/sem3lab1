#include "Tests/StartTests.h"
#include "GUI.h"

int main() {
    runLinkedListTest();
    runListSequenceTest();
    runUniquePtrTest();
    runSharedPtrTest();
    runGUI();

    return 0;
}