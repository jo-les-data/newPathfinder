#include "bideque.hpp"


Bideque::Bideque(int nRowInput, int nColInput, int initValueinput)
{
    if (nRowInput > 0 && nColInput > 0)
    {
        nRow = 0;
        nCol = 0;
        initValue = initValueinput;
        best = 1000;
        for (int i = 0; i < nRowInput; i++)
        {
            addLineTop();
        }
        for (int j = 0; j < nColInput; j++)
        {
            addColRight();
        }
        xorigine = nRow / 2;
        yorigine = nCol / 2;
    }
}

Bideque::~Bideque() {}

void Bideque::display()
{
    std::cout << "grille de taille (" << nRow << "," << nCol << ")" << std::endl << std::endl;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Bideque::addLineTop()
{
    grid.push_front(std::deque<int>{});
    for (int i = 0; i < nCol; i++)
    {
        grid[0].push_back(initValue);
    }
    xorigine++;
    nRow++;
}

void Bideque::addLineBottom()
{
    grid.push_back(std::deque<int>{});
    for (int i = 0; i < nCol; i++)
    {
        grid[nRow].push_back(initValue);
    }
    nRow++;
}

void Bideque::addColLeft()
{
    for (int i = 0; i < nRow; i++)
    {
        grid[i].push_front(initValue);
    }
    yorigine++;
    nCol++;
}

void Bideque::addColRight()
{
    for (int i = 0; i < nRow; i++)
    {
        grid[i].push_back(initValue);
    }
    nCol++;
}

void Bideque::addValue(int x, int y, int value)
{
    if (x < 0)
    {
        for (int i = 0; i < -x; i++)
        {
            addLineTop();
        }
        addValue(0, y, value);
    }
    else if (x > (nRow - 1))
    {
        int diffRow = (x - (nRow - 1));
        for (int i = 0; i < diffRow; i++)
        {
            addLineBottom();
        }
        addValue(nRow - 1, y, value);
    }
    else if (y < 0)
    {
        for (int j = 0; j < -y; j++)
        {
            addColLeft();
        }
        addValue(x, 0, value);
    }
    else if (y > (nCol - 1))
    {
        int diffCol = (y - (nCol - 1));
        for (int j = 0; j < diffCol; j++)
        {
            addColRight();
        }
        addValue(x, nCol - 1, value);
    }
    else
    {
        grid[x][y] = value;
    }
}

std::vector<int> Bideque::size()
{
    return std::vector<int> {nRow, nCol};
}

int Bideque::getFromRelative(int x, int y)
{
    return grid[x + xorigine][y + yorigine];
}

int& Bideque::getFromAbsolute(int x, int y)
{
    return grid[x][y];
}

void Bideque::addValueFromRelative(int x, int y, int value)
{
    addValue(x + xorigine, y + yorigine, value);
}

void Bideque::displayMap()
{
    std::cout << "grille de taille (" << nRow << "," << nCol << ")" << std::endl << std::endl;
    std::cout << "l'origine est a (" << xorigine << "," << yorigine << std::endl;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == 1)
            {
                SetConsoleTextAttribute(hConsole, 127);
                std::cout << "N" << " ";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (grid[i][j] == 2)
            {

                SetConsoleTextAttribute(hConsole, 144);
                std::cout << "w" << " ";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (grid[i][j] == 3)
            {

                SetConsoleTextAttribute(hConsole, 32);
                std::cout << "F" << " ";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (grid[i][j] % 8 == 0 && grid[i][j] > 0)
            {
                SetConsoleTextAttribute(hConsole, 64);
                std::cout << "X" << " ";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (grid[i][j] % 8 == 2 && grid[i][j] > 2)
            {
                SetConsoleTextAttribute(hConsole, 64);
                std::cout << "W" << " ";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else if (grid[i][j] % 8 == 3 && grid[i][j] > 3)
            {
                SetConsoleTextAttribute(hConsole, 64);
                std::cout << "F" << " ";
                SetConsoleTextAttribute(hConsole, 7);
            }
            else
            {
                if (i == xorigine && j == yorigine)
                {
                    SetConsoleTextAttribute(hConsole, 96);
                    std::cout << "0" << " ";
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else
                {
                    std::cout << "." << " ";
                }
            }
        }
        std::cout << std::endl;
    }
}

std::vector<int> Bideque::getOrigin()
{
    return std::vector<int> {xorigine, yorigine};
}

