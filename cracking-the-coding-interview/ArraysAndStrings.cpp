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
 */
bool hasUniqueChars(string s)
{
    map<char, int> occs;    // Count occurences of each letter

    for (int i = 0; i < s.size(); i++)
    {
        if (occs[s[i]] > 0)
            return false;
        else
            occs[s[i]]++;
    }
    return true;
}

// If we can't use map, we can just use ASCII codes as keys
// Works only for lowercase letters
int abcSize = 26;
bool hasUniqueChars_noMap(string s)
{
   int occs[abcSize];
   memset(occs, 0, sizeof(occs));

   for (int i = 0; i < s.size(); i++)
   {
        int key = s[i] % abcSize;
        if (occs[key] > 0)
            return false;
        else
            occs[key]++;
   }
   return true;
}

// ------------------------------------ 1.2 -------------------------------------- //

/**
 *  Implement a function which reverses a null-terminated string
 *  In-place solution.
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
