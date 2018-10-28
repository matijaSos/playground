
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

typedef pair<int, int> Point;
#define x first
#define y second

typedef pair<Point, Point> Segment;

class CheckPolygon
{
public:
        int orientation(Point a, Point b, Point c) {
            long long o = (long long)(b.y - a.y) * (c.x - b.x) - (long long)(c.y - b.y) * (b.x - a.x);

            if (o > 0) return 1;
            if (o < 0) return 2;
            return 0;
        }

        bool areCollinear(Point a, Point b, Point c) {
            // If area of a triangle is 0 -> points are collinear
            return orientation(a, b, c) == 0;
        }

        bool isPointOnSegment(Point point, Segment segment) {
            Point sA = segment.first;
            Point sB = segment.second;

            // Must be collinear and within the bounding rectangle of
            // the segment.
            return orientation(point, sA, sB) == 0
                && (point.x <= max(sA.x, sB.x) && point.x >= min(sA.x, sB.x))
                && (point.y <= max(sA.y, sB.y) && point.y >= min(sA.y, sB.y));
        }

        bool doSegmentsIntersect(Segment a, Segment b) {
            // NOTE(matija): what if segments are colinear?

            return orientation(a.first, a.second, b.first) != orientation(a.first, a.second, b.second) &&
                orientation(b.first, b.second, a.first) != orientation(b.first, b.second, a.second);
        }

        long long getPolygonArea(vector<Segment> segments) {
            long long area = 0;
            for (int i = 0; i < segments.size(); i++) {
                Point sA = segments[i].first;
                Point sB = segments[i].second;

                area += (long long)sA.x * sB.y - (long long)sB.x * sA.y;
            }
            return area;
        }

	string check(vector <int> X, vector <int> Y)
	{
            // Create segments of a polygon.
            vector<pair<Point, Point> > segments;
            for (int pointIdx = 0; pointIdx < X.size(); pointIdx++) {
                Point a = {X[pointIdx], Y[pointIdx]};
                Point b = {X[(pointIdx + 1) % X.size()], Y[(pointIdx + 1) % X.size()]};
                segments.push_back({a, b});
            }

            // Check every segment.
            for (int segmentIdx = 0; segmentIdx < segments.size(); segmentIdx++) {
                // Has positive length?
                // Is non-colinear with the next segment?
                // Does not intersect with other non-neighbouring segments?
                
                Segment s = segments[segmentIdx];
                int nextSegmentIdx = (segmentIdx + 1) % segments.size();
                int prevSegmentIdx = (segmentIdx - 1) < 0 ? segments.size() - 1 : segmentIdx - 1; 

                if (areCollinear(s.first, s.second, segments[nextSegmentIdx].second)) {
                    return "Not simple";
                }

                // Check with all non-neighbour segments.
                for (int i = 0; i < segments.size(); i++) {
                    if (i == segmentIdx || i == nextSegmentIdx || i == prevSegmentIdx) 
                        continue;

                    if (doSegmentsIntersect(s, segments[i])) {
                        return "Not simple";
                    }
                }
            }

            long long area = abs(getPolygonArea(segments));
            stringstream s;
            s << area/2 << '.' << "05"[area % 2];

            return s.str();
	}
};

