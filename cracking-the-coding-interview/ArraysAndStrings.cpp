/**
 *  Arrays and strings
 */

#include <iostream>
#include <map>
#include <string>
#include <cstring>

using namespace std;

// ------------------------------------ 1.1 -------------------------------------- //
/** 
 *  Implement an algorithm to determine if string has all unique characters.
 *  What if we can't use map?
 *
 *  Good questions:
 *      1. Do we care about the case of chars (e.g. are "DoG" and "dOg" the same)?
 *      2. Is string ASCII or Unicode string?
 */

/** Solution with map
 *
 *  1. Case is important
 *  2. Doesn't matter
 */
bool hasUniqueChars(string s)
{
    map<char, int> occs;    // Count occurences of each letter

    for (int i = 0; i < s.size(); i++)
    {
        if (occs[s[i]] > 0)
            return false;       // There must not be the 2 same chars
        else
            occs[s[i]]++;       // Remember the visited char
    }
    return true;
}

/** Solution without map - use ASCII value as key
 *
 *  1. Case matters
 *  2. String is the (extended) ASCII string - 256 different characters
 */
bool hasUniqueChars_noMap(string s)
{
    // Slight optimization - there are only 256 unique characters in ASCII charset
    if (s.size() > 256) return false;

    bool occs[256];
    memset(occs, 0, sizeof(occs));

    for (int i = 0; i < s.size(); i++)
    {
        int key = s[i];
        if (occs[key] == true)
            return false;
        else
            occs[key] = true;
    }
    return true;
}

/** Possible solution - using bit vector
 *  Int is 32/64 bits big, so we could use it at least for only lowercase letters
 */

// ------------------------------------ 1.2 -------------------------------------- //
/**
 *  Implement a function which reverses a null-terminated string
 *
 *  Good questions:
 *      1. Do it in place?
 */

/** In-place solution.
 */
char* reverseString(char* s, int size)
{
    int lo = 0;
    int hi = size - 1;

    while (lo < hi)
    {
        char tmp = s[lo];
        s[lo] = s[hi];
        s[hi] = tmp;

        lo++; hi--;
    }
    return s;
}

// ------------------------------------ 1.3 -------------------------------------- //
/**
 *  Given two strings, write a method to decide if one is a permutation of another.
 *
 *  Good questions:
 *      1. Do we care about char case?
 *      2. Is whitespace significant (e.g. are "dog    " and "g o d" the same)?
 *      3. If answer to 2. is "No", what about multiple blanks in a row (e.g. "d    og" and "d og")?
 */

/** Solution using char count - must be same for a and b
 *
 *  1. Case matters
 *  2. & 3. Whitespace is significant
 */
bool isPermutation(string a, string b)
{
    if (a.size() != b.size()) return false;

    // Count char appearances in a
    map<char, int> aChars;
    for (int i = 0; i < a.size(); i++)
        aChars[a[i]]++;

    // Check b with a
    for (int i = 0; i < b.size(); i++)
    {
        aChars[b[i]]--;
        if (aChars[b[i]] < 0) return false;
    }
    return true;
}

/** Main, for testing
 */
int main(int argc, char const *argv[])
{
    cout << "// ------------------------------- 1.1 ------------------------------- //" << endl;

    cout << "With map: " << endl;
    cout << "matija " << hasUniqueChars("matija") << endl;
    cout << "ivan " << hasUniqueChars("ivan") << endl;
    
    cout << "Without map: " << endl;
    cout << "matija " << hasUniqueChars_noMap("matija") << endl;
    cout << "ivan " << hasUniqueChars_noMap("ivan") << endl;

    cout << "// ------------------------------- 1.2 ------------------------------- //" << endl;

    char s1_2[] = "coding";
    cout << reverseString(s1_2, 6) << endl;

    cout << "// ------------------------------- 1.3 ------------------------------- //" << endl;

    cout << "coding, interview -> " << isPermutation("coding", "interview") << endl;
    cout << "coding, gincod -> " << isPermutation("coding", "gincod") << endl;

    return 0;
}
