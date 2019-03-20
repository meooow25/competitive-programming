// Manacher's algorithm
// Finds all palindromic substrings
// O(n)

// Implementation by me, intended to be similar to the Z-algorithm
// implementation on cp-algorithms.

// Refs:
// https://en.wikipedia.org/wiki/Longest_palindromic_substring
// https://codeforces.com/blog/entry/12143

// Problems:
// https://cses.fi/problemset/task/1111

// 
//      0   1   2   3   <--- odd palindrome centers in len1
//    +---+---+---+---+
//  s | 0 | 1 | 2 | 3 |
//    +---+---+---+---+
//
//        0   1   2     <--- even palindrome centers in len2
//    +---+---+---+---+
//  s | 0 | 1 | 2 | 3 |
//    +---+---+---+---+
//

int l = 0, r = 0;
for (int i = 0; i < n; i++) {
    if (i < r) len1[i] = min(len1[l + r - i], r - i);
    int l2 = i - len1[i], r2 = i + len1[i];
    while (0 <= l2 && r2 < n && s[l2] == s[r2]) l2--, r2++;
    if (r2 > r) len1[i] = r2 - i, l = l2, r = r2;
}
l = 0, r = 0;
for (int i = 0; i < n - 1; i++) {
    if (i < r) len2[i] = min(len2[l + r - i], r - i);
    int l2 = i - len2[i], r2 = i + len2[i] + 1;
    while (0 <= l2 && r2 < n && s[l2] == s[r2]) l2--, r2++;
    if (r2 > r) len2[i] = i - l2, l = l2, r = r2 - 1;
}
