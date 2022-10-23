#include <iostream>
#include "1.5.cc"

struct TestCase {
    std::vector<int> citations;
    int hindex;
};
      
const std::vector<TestCase> cases{
    {{1, 2, 1}, 1},
    {{}, 0},
    {{0}, 0},
    {{1, 2, 3, 4, 5, 6, 7, 8, 9}, 5},
    {{1, 2, 3, 4, 5, 6, 7, 8, 9, 9}, 5},
    {{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9}, 6},
};
      
int main()
{
    int i = 0;
    for (const auto testcase : cases)
    {
        auto res = HIndex(testcase.citations.size(), testcase.citations.data());
        if (res != testcase.hindex)
            std::cout << "error for " << i << ": " << res << " vs " << testcase.hindex << std::endl;
        i++;
    }
}