/**
 * @file brute.cpp
 * @author Simon Zhang (simon.zhang@uwaterloo.ca)
 * @brief brute force way to solve the problem
 * @version 0.1
 * @date 2022-06-09
 * 
 * @copyright Copyright (c) 2022 belongs to Simon Zhang @ University of Waterloo
 * 
 */
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <iomanip>

using namespace std;


class Point {
    public:
    float x;
    float y;
    friend bool operator==(const Point& l, const Point& r) {
        return (l.x == r.x) && (l.y == r.y);
    }
    friend bool operator!=(const Point& l, const Point& r) {
        return !(l == r);
    }
};


float distance(Point& p1, Point& p2) {
    float dist = sqrtf((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    return dist;
}



void findClosestPair() {
    int point_num = 0;
    cin >> point_num;
    vector<Point> points;
    for (int i = 0; i < point_num; i++) {
        float x = 0;
        float y = 0;
        cin >> x;
        cin >> y;
        Point temp = {x, y};
        points.emplace_back(temp);
    }
    float min_dist = distance(points[0], points[1]);
    int first = 0;
    int second = 1;
    int size = points.size();
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            float temp = distance(points[i], points[j]);
            if (temp < min_dist && points[i] != points[j]) {
                first = i;
                second = j;
                min_dist = temp;
            }
        }
    }
    cout << fixed << setprecision(4) << min_dist << endl;
    cout << first << " " << second << endl;
}

int main() {
    int problem_num = 0;
    cin >> problem_num;
    for (int i = 0; i < problem_num; i++) {
        findClosestPair();
    }
}