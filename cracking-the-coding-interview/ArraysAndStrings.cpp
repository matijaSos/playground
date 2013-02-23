/**
 *  Arrays and strings
 */

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

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
    map<char, int> aChars;                  // Maybe better to use array instead of map, its faster!
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

/** Solution with sorting
 *  Sort each array - see if they are the same
 */

// ------------------------------------ 1.4 -------------------------------------- //
/**
 *  Write a method to replace all spaces in string with "%20". There is enough space at the end of the string.
 *  Do it in place.
 *
 *  Good questions:
 *      1. What about multiple spaces? (e.g. "first     second        third")
 *
 */

/** Solution - Move each word for 2 places for each space ahead of it
 *  
 *  1. There are no multiple spaces
 */
char* replaceSpaces(char* s, int size)
{
    // Count spaces (only those between words)
    int spaceNum = 0;
    for(int i = 0; i < size - 1; i++)
        if (s[i] == ' ' && s[i + 1] != ' ')
            spaceNum++;
    
    // Move each word, starting from last one
    int wordLength = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        if (s[i] == ' ' && wordLength > 0) 
        {
            // Move word
            int curr = i + wordLength; // Last char in word
            int offset = 2 * spaceNum;
            while (wordLength > 0)
            {
                s[curr + offset] = s[curr];

                curr--;
                wordLength--;
            }
            // Add space
            strncpy(s + curr + offset - 2, "%20", 3);

            spaceNum--;
        }
        if (s[i] != ' ')
            wordLength++;
    }
    return s;
}

// ------------------------------------ 1.5 -------------------------------------- //
/**
 *  Compress string -> "aaabb" becomes "a3b2"
 *  If compressed string is bigger than original, return original
 */
string compress(string s)
{
    string comp = "";
    for (int i = 0 ; i < s.size(); i++)
    {
        int rep = 1;
        while(i + 1 < s.size() && s[i + 1] == s[i])
        {
            rep++; i++;
        }
        stringstream ss;
        ss << rep;
        
        // (+) causes new buffer for each element, so it's better to do (+=) twice
        comp += s[i]; 
        comp += ss.str();           
    }

    return (comp.size() < s.size()) ? comp : s;
}

// ------------------------------------ 1.6 -------------------------------------- //
/**
 *  Rotate the square matrix by 90 degrees left - in place.
 *
 *  Good questions:
 *      1. Don't have any right now. Something regarding constraints?
 */

int** rotateMatrix(int** m, int size)
{
    for (int layer = 0; layer < (size / 2); layer++)
    {
        int first = layer;
        int last = size - 1 - layer;
        for (int i = first; i < last; i++)
        {
            int offset = i;

            int top = m[first][i];

            // Right -> top
            m[first][i] = m[first + offset][last];

            // Bottom -> right
            m[first + offset][last] = m[last][last - offset];

            // Left -> bottom
            m[last][last - offset] = m[last - offset][first];
            
            // Top -> left
            m[last - offset][first] = top;
        }
    }
    return m;
}

/** Main, for testing
 */
int main(int argc, char const *argv[])
{

    string str = "ab";
    cout << compress(str) << endl;



    return 0;
}
