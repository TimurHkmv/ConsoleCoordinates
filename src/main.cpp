#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>
#include "point.h"

using namespace std;

/**
 * @brief function to find point [x:y] in string vector
 * @param stroki string vector with lines containing points
 * @return vector of points in order of detection
 */
vector<point> parseString(vector<string> stroki) {
    vector<point> points;
    int amount;
    amount = (int)stroki.size() - 1;
    regex coordRegex(R"([()\[\]{}<>]\s*([+-]?\d+)\s*[;,:.]\s*([+-]?\d+)\s*[()\[\]{}<>])");
    for (const string& line : stroki) {
        string::const_iterator searchStart(line.cbegin());
        smatch match;

        while(regex_search(searchStart, line.cend(), match, coordRegex)) {
            // dead end check
            if (match[0].first == match[0].second) {
                ++searchStart;
                if (searchStart == line.cend()) break;
                continue;
            }
            int x = stoi(match[1].str());
            int y = stoi(match[2].str());

            if (points.empty()) {
                points.emplace_back(x,y,1);
            } else {
                points.emplace_back(x, y, points.front(), points.back().getNumber()+1);
            }
            searchStart = match[0].second;
        }
    }
    return points;
}

int main(int argc, char* argv[]) {
    vector<string> stroki;
    vector<point> points;
    string inputFileName;
    int amount, x, y;
    string bufStr;
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--input" && i + 1 < argc) {
            inputFileName = argv[++i];
        }
    }
    // Input from file
    if (!inputFileName.empty()) {
        ifstream in(inputFileName);
        if (!in) {
            cerr << "Cannot open file " << inputFileName << endl;
            return 1;
        }
        string line;
        while (getline(in, line)) {
            stroki.push_back(line);
        }
    }
    // Terminal input
    else {
        cout << "number of lines: ";
        cin >> amount;
        for (int n = 0; n <= amount; n++) {
            getline(cin, bufStr);
            stroki.push_back(bufStr);
        }
    }
    // Find points in input lines
    points = parseString(stroki);
    // Output of points
    for (int i = 0; i < points.size(); i++) {
        cout << "point " << i + 1 << ": ";
        points.at(i).output();
    }
    // Output of distances between all points and first point
    for (int i = 1; i < points.size(); i++) {
        cout << "distance between point1 and point" << points.at(i).getNumber() << " = " << points.at(i).getDistance() << endl;
    }
    // Sort points by distances to first point
    if (!points.empty()) {
        cout << "Sorted distances: " << endl;
        sort(points.begin(), points.end(),
     [](const point& a, const point& b) {
         return a.getDistance() < b.getDistance();
     });
        // Output sorted distances
        for (int i = 0; i < points.size() - 1; i++) {
            cout << "distance between point1 and point" << points.at(i).getNumber() << " = " << points.at(i).getDistance() << endl;
        }
    }
    // Output of coordinate plane
    int maxX = 0, minX = 0, maxY = 0, minY = 0;
    for (int i = 0; i < points.size(); i++) {
        if ((points.at(i).getX() > maxX) && (points.at(i).getX() < 103)) {
            maxX = points.at(i).getX();
        }
        if (points.at(i).getX() < minX  && (points.at(i).getX() > -103)) {
            minX = points.at(i).getX();
        }
        if (points.at(i).getY() > maxY) {
            maxY = points.at(i).getY();
        }
        if (points.at(i).getY() < minY) {
            minY = points.at(i).getY();
        }
    }
    // if (minX >= 0) {
    //     if (maxX > 206) { maxX = 206; }
    // }
    // else if (maxX == 0) {
    //     if (minX > 206) { minX = 206; }
    // }
    // else if (maxX - minX > 206) {
    //     maxX = 103;
    //     minX = -103;
    // }
    cout << "draw: " << endl;
    bool isFound;
    for (y = maxY + 1; y >= minY - 1; y--) {
        for (x = minX - 1; x <= maxX + 1; x++) {
            isFound = false;
            // Print point
            for (int i = 0; i < points.size(); i++) { 
                if ((points.at(i).getX() == x) && (points.at(i).getY() == y)) {
                    cout << "*";
                    isFound = true;
                    break;
                }
            }
            if (!isFound) { 
                // Print axis
                if ((x == 0) && (y != 0)) { 
                    cout << "|";
                }
                else if ((x != 0) && (y == 0)) { 
                    cout << "-";
                }
                else if ((x == 0) && (y == 0)) { 
                    cout << "+";
                }
                else {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    stroki.~vector<string>();
    points.~vector<point>();
    cout << "Press Enter to exit...";
}