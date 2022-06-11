/**
 * @file prog1.cpp
 * @author Simon Zhang (simon.zhang@uwaterloo.ca)
 * @brief 
 * @version 0.1
 * @date 2022-06-09
 * 
 * @copyright Copyright (c) 2022 belongs to Simon Zhang @ University of Waterloo
 * 
 * STATEMENT:
 * Quicksort algo in this question is retrieved from
 * https://www.geeksforgeeks.org/cpp-program-for-quicksort/
 * since we can even use build in function.
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

class ClosestPair {
    public:
    Point p1;
    Point p2;
    float dist;
    bool exist;
};

float distance(Point& p1, Point& p2) {
    float dist = sqrtf((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    return dist;
}

/**
 * ** **************** STATEMENT *********
 * quicksort algo here is refered from https://www.geeksforgeeks.org/cpp-program-for-quicksort/
 * 
 */

/**
 * @brief partion & quicksort: used for sort the vector of points by x value
 * 
 * @param points 
 * @param start 
 * @param end 
 * @return int 
 */
int partition(vector<Point>& points, int start, int end) {
    int pivot = points.at(start).x;
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (points.at(i).x <= pivot)
            count++;
    }
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(points[pivotIndex], points[start]);
    
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (points[i].x <= pivot) {
            i++;
        }
 
        while (points[j].x > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(points[i++], points[j--]);
        }
    }
 
    return pivotIndex;
}

/**
 * @brief partion & quicksort: used for sort the vector of points by x value
 * 
 * @param points 
 * @param start 
 * @param end 
 */
void quickSort(vector<Point>& points, int start, int end) {
 
    // base case
    if (start >= end) {
        return;
    }
    // partitioning the array
    int p = partition(points, start, end);
 
    // Sorting the left part
    quickSort(points, start, p - 1);
 
    // Sorting the right part
    quickSort(points, p + 1, end);
}


/**
 * @brief partion & quicksort: used for sort the vector of points by y value
 * 
 * @param points 
 * @param start 
 * @param end 
 * @return int 
 */
int partitionY(vector<Point>& points, int start, int end) {
    int pivot = points.at(start).y;
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (points.at(i).y <= pivot)
            count++;
    }
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(points[pivotIndex], points[start]);
    
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (points[i].y <= pivot) {
            i++;
        }
 
        while (points[j].y > pivot) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(points[i++], points[j--]);
        }
    }
 
    return pivotIndex;
}

/**
 * @brief partion & quicksort: used for sort the vector of points by y value
 * 
 * @param points 
 * @param start 
 * @param end 
 */
void quickSortY(vector<Point>& points, int start, int end) {
 
    // base case
    if (start >= end) {
        return;
    }
    // partitioning the array
    int p = partitionY(points, start, end);
 
    // Sorting the left part
    quickSortY(points, start, p - 1);
 
    // Sorting the right part
    quickSortY(points, p + 1, end);
}

/**
 * @brief find closest spanning pairs
 * 
 * @param points 
 * @param delta 
 * @return ClosestPair 
 */
ClosestPair findSpanningPair(vector<Point>& points, float delta) {
    vector<Point> candidates;
    int total_size = points.size();
    int mid = total_size / 2;
    for (auto i : points) {
        if (abs(i.x - points[mid].x) <= delta) {
            candidates.emplace_back(i);
        }
    }
    int candidate_size = candidates.size();
    quickSortY(candidates, 0, candidate_size - 1);
    ClosestPair result;
    if (candidate_size < 2) {
        result.exist = false;
        return result;
    }
    result.p1 = candidates[0];
    result.p2 = candidates[1];
    result.exist = true;
    result.dist = distance(candidates[0], candidates[1]);
    for (int i = 0; i < candidate_size; i++) {
        for (int j = i; j < candidate_size; j++) {
            if (abs(candidates[j].y - candidates[i].y) > delta) {
                break;
            }
            float temp = distance(candidates[j], candidates[i]);
            if ((temp < result.dist) && (candidates[i] != candidates[j])) {
                result.p1 = candidates[i];
                result.p2 = candidates[j];
                result.dist = temp;
            }
        }
    }
    return result;
}

/**
 * @brief recursively find closest pair
 * 
 * @param points 
 * @return ClosestPair 
 */
ClosestPair recurse(vector<Point>& points) {
    ClosestPair result;

    // base case
    if (points.size() < 4) {
        if (points.size() < 2) {
            result.exist = false;
            cerr << "ERROR: One Side has less than 2 points!" << endl;
            return result;
        }
        // float min_dist = distance(points[0], points[1]);
        result.exist = true;
        result.p1 = points[0];
        result.p2 = points[1];
        result.dist = distance(points[0], points[1]);
        for (auto i : points) {
            for (auto j : points) {
                float temp_dist = distance(i, j);
                if ((temp_dist < result.dist) && (i != j)) {
                    result.p1 = i;
                    result.p2 = j;
                    // min_dist = temp_dist;
                    result.dist = temp_dist;
                }
            }
        }
        return result;
    }

    // divide & conqure
    vector<Point> left;
    vector<Point> right;
    int total_size = points.size();
    int mid = total_size / 2;
    for (int i = 0; i < mid; i++) {
        left.emplace_back(points[i]);
    }
    for (int i = mid; i < total_size; i++) {
        right.emplace_back(points[i]);
    }
    ClosestPair pairL = recurse(left);
    ClosestPair pairR = recurse(right);

    // combine
    float delta = 0.0;
    if (pairL.exist && pairR.exist) {
        delta = min(pairL.dist, pairR.dist);
    } else if (pairL.exist && !pairR.exist) {
        delta = pairL.dist;
    } else if (!pairL.exist && pairR.exist) {
        delta = pairR.dist;
    } else {
        cerr << "ERROR: both sides does not have min points" << endl;
    }

    ClosestPair pairS = findSpanningPair(points, delta);
    // cerr << pairS.p1.x << endl;
    // cerr << pairS.p1.x << endl;
    
    result.exist = true;
    if (pairL.exist && pairR.exist && pairS.exist) {
        result = pairL;
        if (pairR.dist < result.dist) {
            result = pairR;
        }
        if (pairS.dist < result.dist) {
            result = pairS;
        }
        return result;
    }
    if (pairL.exist && pairR.exist) {
        // cerr << "impossible1" << endl;
        result = pairL;
        if (pairR.dist < result.dist) {
            result = pairR;
        }
        return result;
    }
    if (pairL.exist && pairS.exist) {
        // cerr << "impossible2" << endl;
        result = pairL;
        if (pairS.dist < result.dist) {
            result = pairS;
        }
        return result;
    }
    if (pairR.exist && pairS.exist) {
        // cerr << "impossible3" << endl;
        result = pairR;
        if (pairS.dist < result.dist) {
            result = pairS;
        }
        return result;
    }
    if (pairL.exist) {
        // cerr << "impossible4" << endl;
        return pairL;
    }
    if (pairR.exist) {
        // cerr << "impossible5" << endl;
        return pairR;
    }
    if (pairS.exist) {
        // cerr << "impossible6" << endl;
        return pairS;
    }
    cerr << "Fail to find Closest Pair" << endl;
    result.exist = false;
    return result;
}

/**
 * @brief find and print closest pair
 * 
 */
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
    vector<Point> init_points = points;

    // sort by x
    quickSort(points, 0, points.size() - 1);
    // for (auto i : points) {
    //     cout << i.x << " " << i.y << endl;
    // }
    ClosestPair result = recurse(points);

    // print result
    cout << fixed << setprecision(4) << result.dist << endl;
    int total_size = init_points.size();
    bool first = true;
    for (int i = 0; i < total_size; i++) {
        if (init_points[i] == result.p1) {
            cout << i;
            if (first) {
                cout << " ";
                first = false;
            } else {
                break;
            }
        }
        if (init_points[i] == result.p2) {
            cout << i;
            if (first) {
                cout << " ";
                first = false;
            } else {
                break;
            }
        }
    }
    cout << endl;
}

int main() {
    int problem_num = 0;
    cin >> problem_num;
    for (int i = 0; i < problem_num; i++) {
        findClosestPair();
    }
}