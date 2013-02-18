/**
 *  Arrays and strings
 */

#include <iostream>
#include <map>
#include <string>
#include <cstring>

using namespace std;

/** 1.1
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

// If we can't use map, we can just use ascii codes as keys
int abcSize = 26;
bool hasUniqueChars_noMap(string s)
{
   int occs[abcSize];
   memset(occs, 0, sizeof(occs));

   for (int i = 0; i < s.size(); i++)
   {
        int pos = s[i] % abcSize;
        if (occs[pos] > 0)
            return false;
        else
            occs[pos]++;
   }
   return true;
}

/** Main, for testing
 */
int main(int argc, char const *argv[])
{
    cout << "With map: " << endl;
    cout << "matija " << hasUniqueChars("matija") << endl;
    cout << "ivan " << hasUniqueChars("ivan") << endl;
    
    cout << "Without map: " << endl;
    cout << "matija " << hasUniqueChars_noMap("matija") << endl;
    cout << "ivan " << hasUniqueChars_noMap("ivan") << endl;

    return 0;
}
