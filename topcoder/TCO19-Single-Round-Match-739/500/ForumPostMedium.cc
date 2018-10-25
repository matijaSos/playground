
// {{{ VimCoder 0.3.5 <-----------------------------------------------------
// vim:filetype=cpp:foldmethod=marker:foldmarker={{{,}}}

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

// }}}

class ForumPostMedium
{
public:
        int getTimeInSeconds(string time) {

            string delimiter = ":";
            string token;
            int pos = 0;
            vector<int> tokens;
            while ((pos = time.find(delimiter)) != string::npos) {
                token = time.substr(0, pos);
                tokens.push_back(stoi(token));

                time.erase(0, pos + delimiter.length());
            }
            tokens.push_back(stoi(time));

            return tokens[0] * 3600 + tokens[1] * 60 + tokens[2];
        }

	string getShownPostTime(string currentTime, string exactPostTime)
	{
            int currentTimeInSec = getTimeInSeconds(currentTime);
            int postTimeInSec = getTimeInSeconds(exactPostTime);

            int totalSecDiff = currentTimeInSec - postTimeInSec;
            if (postTimeInSec > currentTimeInSec) {
                totalSecDiff = 24 * 3600 - (postTimeInSec - currentTimeInSec);
            }

            // Get hour, min, and sec diff from sec diff.
            int hourDiff = totalSecDiff / 3600;
            int minDiff = (totalSecDiff % 3600) / 60;

            if (hourDiff == 0 && minDiff == 0) {
                return "few seconds ago";
            }
            if (hourDiff == 0) {
                return to_string(minDiff) + " minutes ago";
            }
            return to_string(hourDiff) + " hours ago";
	}
};

