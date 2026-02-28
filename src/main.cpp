#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "point.h"

using namespace std;


vector<point> parseString(vector<string> stroki) {
    vector<point> points;
    bool isFound;
    int endStroki, amount, x, y;
    amount = stroki.size() - 1;
    string stroka = "", example = "{:}", bufStr;
    for (int n = 0; n <= amount; n++) {
        stroka = stroki.at(n);
        endStroki = stroka.length() - 1;
        while (true) {
            isFound = false;
            for (int i = 0; i <= endStroki; i++) {
                if (stroka[i] == example[0]) {
                    for (int j = i + 1; j <= endStroki; j++) {
                        if (stroka[j] == example[1]) {
                            for (int k = j; k <= endStroki; k++) {
                                if (stroka[k] == example[2]) {
                                    isFound = true;
                                    try {
                                        x = stoi(stroka.substr(i + 1, j - i - 1));
                                        y = stoi(stroka.substr(j + 1, k - j - 1));
                                        if (points.empty()) {
                                            points.push_back(point(x, y, 1));
                                        }
                                        else {
                                            points.push_back(point(x, y, points.front(), points.back().getNumber() + 1));
                                        }
                                    }
                                    catch (...) {}
                                    stroka.erase(i, k - i + 1);
                                    endStroki -= k - i + 1;
                                    i = endStroki;
                                    j = endStroki;
                                    k = endStroki;
                                }
                                else if (stroka[k] == example[0]) {
                                    isFound = true;
                                    stroka.erase(i, k - i);
                                    endStroki -= k - i;
                                    i = endStroki;
                                    j = endStroki;
                                    k = endStroki;
                                }
                            }
                        }
                        else if (stroka[j] == example[0]) {
                            stroka.erase(i, j - i);
                            endStroki -= j - i;
                            isFound = true;
                            i = endStroki;
                            j = endStroki;
                        }
                        /*else if (stroka[j] == example[2]) {
                            stroka.erase(i, j - i + 1);
                            endStroki -= j - i+1;
                            cout << "find } : " << stroka << endl;
                        }*/
                    }
                }
            }
            if (!isFound) { break; }
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