
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

class HungryCowsEasy
{
public:
	vector <int> findFood(vector <int> cowPositions, vector <int> barnPositions)
	{
            vector<int> cowChoice;

            // Process each cow separately.
            for (int cowIdx = 0; cowIdx < cowPositions.size(); cowIdx++) {
                int cowPosition = cowPositions[cowIdx];

                // Find the nearest barn.
                int nearestBarnIdx = 0;
                for (int barnIdx = 0; barnIdx < barnPositions.size(); barnIdx++) {
                    int dist = abs(cowPosition - barnPositions[barnIdx]);
                    if (dist < abs(cowPosition - barnPositions[nearestBarnIdx])) {
                        nearestBarnIdx = barnIdx;
                    } else if (dist == abs(cowPosition - barnPositions[nearestBarnIdx])) {
                        if (barnPositions[barnIdx] < barnPositions[nearestBarnIdx]) {
                            nearestBarnIdx = barnIdx;
                        }
                    }
                }

                cowChoice.push_back(nearestBarnIdx);
            }

	    return cowChoice;
	}
};

