#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

Point p0;

/* ab x ac */
int cross(Point& a, Point& b, Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

/* distance(a, b)^2 */
int distance2(Point& a, Point& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool cmp(Point& a, Point& b) {
    int cross_ab = cross(p0, a, b);
    int distance_a = distance2(p0, a);
    int distance_b = distance2(p0, b);

    return cross_ab > 0 || (cross_ab == 0 && distance_a < distance_b);
}

vector<Point> graham_scan(vector<Point> p) {
    int n = p.size();

    /* find the buttom left point */
    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if (p[i].y < p[min_idx].y ||
                p[i].y == p[min_idx].y && p[i].x < p[min_idx].x)
            min_idx = i;
    }
    swap(p[0], p[min_idx]);
    p0 = p[0];

    /* sort by angle */
    sort(p.begin() + 1, p.end(), cmp);

    /* remove the point if the points has the same angle but leave the farthest one */
    int m = 1;
    for (int i = 1; i < n; i++) {
        while (i < n-1 && cross(p0, p[i], p[i+1]) == 0)
            i++;

        p[m] = p[i];
        m++;
    }

    /* start to add the point and check */
    vector<Point> stk;

    for (int i = 0; i < m; i++) {
        while (stk.size() >= 2 &&
                cross(*(stk.end() - 2), *(stk.end() - 1), p[i]) < 0)
            stk.pop_back();
        stk.push_back(p[i]);
    }

    return stk;
}

#endif // GRAHAM_SCAN_H
