#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>
#include "point.h"

using namespace std;


vector<point> parseString(vector<string> stroki) {
    vector<point> points;
    bool isFound;
    int endStroki, amount, x, y;
    amount = stroki.size() - 1;
    // string stroka = "", example = "{:}", bufStr;

    regex coordRegex(R"([()\[\]{}<>]\s*([+-]?\d+)\s*[;,:.]\s*([+-]?\d+)\s*[()\[\]{}<>])");
    
    for (const string& line : stroki) {
        string::const_iterator searchStart(line.cbegin());
        smatch match;

        while(regex_search(searchStart, line.cend(), match, coordRegex)) {
            if (match[0].first == match[0].second) {
                ++searchStart;
                if (searchStart == line.cend()) break;
                continue;
            }
            cout << line << endl;
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
    bool isFound;
    int endStroki, amount, x, y;
    string stroka = "", example = "{:}", bufStr;
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--input" && i + 1 < argc) {
            inputFileName = argv[++i];
        }
    }
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
    else {
        cout << "number of lines: ";
        cin >> amount;
        for (int n = 0; n <= amount; n++) {
            getline(cin, bufStr);
            stroki.push_back(bufStr);
        }
        // Ввод строк:
    }
    // Отлов точек из строк:
    points = parseString(stroki);
    // Вывод точек и расстояний до первой:
    for (int i = 0; i < points.size(); i++) {
        cout << "point " << i + 1 << ": ";
        points.at(i).output();
    }
    for (int i = 1; i < points.size(); i++) {
        cout << "distance between point1 and point" << points.at(i).getNumber() << " = " << points.at(i).getDistance() << endl;
    }
    // Сортировка
    if (!points.empty()) {
        cout << "Sorted distances: " << endl;
        sort(points.begin(), points.end(),
     [](const point& a, const point& b) {
         return a.getDistance() < b.getDistance();
     });
        for (int i = 0; i < points.size() - 1; i++) {
            cout << "distance between point1 and point" << points.at(i).getNumber() << " = " << points.at(i).getDistance() << endl;
        }
    }
    // Границы координатной плоскости: 
    int maxX = 0, minX = 0, maxY = 0, minY = 0;
    for (int i = 0; i < points.size(); i++) {
        if (points.at(i).getX() > maxX) {
            maxX = points.at(i).getX();
        }
        if (points.at(i).getX() < minX) {
            minX = points.at(i).getX();
        }
        if (points.at(i).getY() > maxY) {
            maxY = points.at(i).getY();
        }
        if (points.at(i).getY() < minY) {
            minY = points.at(i).getY();
        }
    }
    // Если точки не помещаются:
    if (minX >= 0) {
        if (maxX > 206) { maxX = 206; }
    }
    else if (maxX == 0) {
        if (minX < 206) { minX = -205; }
    }
    else if (maxX - minX > 206) {
        maxX = 103;
        minX = -103;
    }
    // Рисуем координатную плоскость:
    cout << "draw: " << endl;
    for (y = maxY + 1; y >= minY - 1; y--) {
        for (x = minX - 1; x <= maxX + 1; x++) {
            isFound = false;
            for (int i = 0; i < points.size(); i++) { // Проверяем, нужно ли ставить точку
                if ((points.at(i).getX() == x) && (points.at(i).getY() == y)) {
                    cout << "*";
                    isFound = true;
                }
            }
            if (!isFound) { // Если точки нет
                if ((x == 0) && (y != 0)) { // Проверяем нужно ли рисовать Oy
                    cout << "|";
                }
                else if ((x != 0) && (y == 0)) { // Проверяем нужно ли рисовать Ox
                    cout << "-";
                }
                else if ((x == 0) && (y == 0)) { // Проверяем нужно ли рисовать центр
                    cout << "+";
                }
                else { // Если ничего нет, ставим пробел
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