#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <windows.h>

class Bideque
{
private:
    std::deque<std::deque<int>> grid;
    int nRow;
    int nCol;
    int xorigine;
    int yorigine;
    int initValue;
    int best;

public:
    std::deque<int>& operator[](int i)
    {
        return grid[i];
    }
    Bideque(int nRowInput, int nColInput, int initValueinput);
    ~Bideque();
    void display();
    void addLineTop();
    void addLineBottom();
    void addColLeft();
    void addColRight();
    void addValue(int x, int y, int value);
    std::vector<int> size();
    int getFromRelative(int x, int y);
    int& getFromAbsolute(int x, int y);
    void addValueFromRelative(int x, int y, int value);
    void displayMap();
    std::vector<int> getOrigin();
};