#include <limits.h>

int* sortRev2(int num, const int* values) {
    // This function implements a reverse sorting thanks to a frequency table,
    // so its complexity is O(n).

    long long max = INT_MIN;  // long long because of future calculation below
    long long min = INT_MAX;

    for (int i = 0; i < num; i++) {  // This for boucle to find the minimal
        if (values[i] > max) {       // value and the greatest one
            max = values[i];
        }
        if (values[i] < min) {
            min = values[i];
        }
    }

    int* freq = new int[max - min + 1];  // the long long type is necessary here
                                         // because adding 2 ints can result
                                         // in greater-than-an-int value

    for (long long i = 0; i < max - min + 1; i++) {
        freq[i] = 0;  // First put 0 for all the frequencies
    }
    for (int i = 0; i < num; i++) {
        freq[max - (long long)values[i]] +=
            1;  // Casted it as a long long for the same reason. Also :
                // - if values[i] == max; then it adds 1 to freq[0]
                // - if values[i] == min; then it adds 1 to
                // freq[max - min ] == freq[-1]
    }

    int* sorted = new int[num];
    int inserted = 0;

    for (long long i = 0; i < max - min + 1; i++) {
        // This boucle to fill the resulted reverse sorted array
        if (freq[i] != 0) {
            for (int j = 0; j < freq[i]; j++) {
                sorted[inserted] = (int)max - i;
                inserted++;
            }
        }
    }
    return sorted;
}

int HIndex(int num_articles, const int* num_citations) {
    // Same HIndex function as before but uses the sortRev2 function
    if (num_articles == 0) return 0;
    int h = 0;
    int* sorted = sortRev2(num_articles, num_citations);
    for (int i = 0; i < num_articles; ++i) {
        if (sorted[i] >= i + 1) {
            h = i + 1;
        } else
            break;
    }
    return h;
}