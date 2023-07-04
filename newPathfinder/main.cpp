#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <windows.h>
#include <math.h> 




float squared(float x)
{
    return x * x;
}


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
    Bideque(int nRowInput, int nColInput, int initValueinput)
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
    ~Bideque() {}
    void display()
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
    void addLineTop()
    {
        grid.push_front(std::deque<int>{});
        for (int i = 0; i < nCol; i++)
        {
            grid[0].push_back(initValue);
        }
        xorigine++;
        nRow++;
    }
    void addLineBottom()
    {
        grid.push_back(std::deque<int>{});
        for (int i = 0; i < nCol; i++)
        {
            grid[nRow].push_back(initValue);
        }
        nRow++;
    }
    void addColLeft()
    {
        for (int i = 0; i < nRow; i++)
        {
            grid[i].push_front(initValue);
        }
        yorigine++;
        nCol++;
    }
    void addColRight()
    {
        for (int i = 0; i < nRow; i++)
        {
            grid[i].push_back(initValue);
        }
        nCol++;
    }
    void addValue(int x, int y, int value)
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
    std::vector<int> size()
    {
        return std::vector<int> {nRow, nCol};
    }
    int getFromRelative(int x, int y)
    {
        return grid[x + xorigine][y + yorigine];
    }
    int& getFromAbsolute(int x, int y)
    {
        return grid[x][y];
    }
    void addValueFromRelative(int x, int y, int value)
    {
        addValue(x + xorigine, y + yorigine, value);
    }
    void displayMap()
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
    std::vector<int> getOrigin()
    {
        return std::vector<int> {xorigine, yorigine};
    }
};


class VoyageurBase
{
protected:
    Bideque* labirynthe;
    Bideque* memoire;
    int xPos;
    int yPos;
    std::vector<std::vector<int>> history;
    float dist;
    int nStep;
    int maxMoves;
public:
    int reussite;
    VoyageurBase(Bideque* labiryntheInput, Bideque* memoireInput, int maxMovesInput)
    {
        labirynthe = labiryntheInput;//contient les lac, foret et murs
        memoire = memoireInput;//contient l'ebauche de carte a* necessaire a atteindre l'origine
        xPos = 0;//rand() % labirynthe->size()[0]; dans le cas ou on veux cree la carte le l'algo A*
        yPos = 0;//rand() % labirynthe->size()[0];
        history.push_back(std::vector<int> {xPos, yPos});//pour remplir la memoire en cas de reussite de la recherche de chemin
        nStep = 25000;
        reussite = 0;
        markPosition();
        maxMoves = maxMovesInput;
    }

    const std::vector<std::vector<int>> getHistory()
    {
        return history;
    }
    float computeDist()
    {
        return sqrtf(squared((float)xPos - labirynthe->getOrigin()[0]) + squared((float)yPos - labirynthe->getOrigin()[1]));
    }
    float computeDist(int x, int y)
    {
        return sqrtf(squared((float)x - labirynthe->getOrigin()[0]) + squared((float)y - labirynthe->getOrigin()[1]));
    }
    float computeCost(int x, int y)
    {
        if (labirynthe->getFromAbsolute(x, y) == 2)
        {
            return (1.1f * computeDist(x, y)) - memoire->getFromAbsolute(x, y) * ((rand() % 3) - 1);
        }
        else if (labirynthe->getFromAbsolute(x, y) == 3)
        {
            return (1.3f * computeDist(x, y)) - memoire->getFromAbsolute(x, y) * ((rand() % 3) - 1);
        }
        else if (labirynthe->getFromAbsolute(x, y) > 7)
        {
            return (labirynthe->getFromAbsolute(x, y) * computeDist(x, y)) - memoire->getFromAbsolute(x, y) * ((rand() % 3) - 1);
        }
        else
        {
            return computeDist(x, y);
        }
    }
    void markPosition()
    {
        history.push_back(std::vector<int>{ xPos, yPos });
        labirynthe->getFromAbsolute(xPos, yPos) += 8;
    }

    void resetLabirynthe()
    {
        xPos = 0;// rand() % labirynthe->size()[0];
        yPos = 0;// rand() % labirynthe->size()[0];
        for (int i = 0; i < labirynthe->size()[0]; i++)
        {
            for (int j = 0; j < labirynthe->size()[1]; j++)
            {
                labirynthe->addValue(i, j, labirynthe->getFromAbsolute(i, j) % 8);
            }
        }
        history.clear();
        history.push_back(std::vector<int> {xPos, yPos});
    }
    //en rebroussant chemin, on va ecrir des valeur de plus en plus petite alors qu'on seloigne de l'origine
    void writeMemoire()
    {
        for (int i = ((int)history.size() - 1); i > 0; i--)
        {
            memoire->getFromAbsolute(history[i][0], history[i][1]) = std::max(i, (*memoire)[history[i][0]][history[i][1]]);
        }
    }

    int getNSteps()
    {
        return nStep;
    }

    void moveN()
    {
        if ((yPos > 0) && ((*labirynthe)[xPos][yPos - 1] != 1))
        {
            yPos--;
            markPosition();
        }
        else
        {
            std::cout << "tu peux pas!" << std::endl;
        }
    }
    void moveS()
    {
        if ((yPos < (labirynthe->size()[1] - 1)) && ((*labirynthe)[xPos][yPos + 1] != 1))
        {
            yPos++;
            markPosition();
        }
        else
        {
            std::cout << "tu peux pas!" << std::endl;
        }
    }
    void moveE()
    {
        if ((xPos < (labirynthe->size()[0] - 1)) && ((*labirynthe)[xPos + 1][yPos] != 1))
        {
            xPos++;

            markPosition();
        }
        else
        {
            std::cout << "tu peux pas!" << std::endl;
        }
    }
    void moveO()
    {
        if ((xPos > 0) && ((*labirynthe)[xPos - 1][yPos] != 1))
        {
            xPos--;

            markPosition();
        }
        else
        {
            std::cout << "tu peux pas!" << std::endl;
        }
    }
    void moveNO()
    {
        if ((xPos > 0) && (yPos > 0) && ((*labirynthe)[xPos - 1][yPos - 1] != 1))
        {
            xPos--;
            yPos--;
            markPosition();
        }
        else
        {
            std::cout << "pas par la!" << std::endl;
        }
    }
    void moveNE()
    {
        if ((xPos < labirynthe->size()[0] - 1) && (yPos > 0) && ((*labirynthe)[xPos + 1][yPos - 1] != 1))
        {
            xPos++;
            yPos--;
            markPosition();
        }
        else
        {
            std::cout << "pas par la!" << std::endl;
        }
    }
    void moveSO()
    {
        if ((xPos > 0) && (yPos < labirynthe->size()[1] - 1) && ((*labirynthe)[xPos - 1][yPos + 1] != 1))
        {
            xPos--;
            yPos++;
            markPosition();
        }
        else
        {
            std::cout << "pas par la!" << std::endl;
        }
    }
    void moveSE()
    {
        if ((xPos < labirynthe->size()[0] - 1) && (yPos < labirynthe->size()[1] - 1) && ((*labirynthe)[xPos + 1][yPos + 1] != 1))
        {
            xPos++;
            yPos++;
            markPosition();
        }
        else
        {
            std::cout << "pas par la!" << std::endl;
        }
    }
};

class VoyageurDirect : public VoyageurBase
{
public:
    VoyageurDirect(Bideque* labiryntheInput, Bideque* memoireInput, int maxMovesInput) : VoyageurBase(labiryntheInput, memoireInput, maxMovesInput) {}
    ~VoyageurDirect() {}
    /*Ici on va regarder quel voisin est accessible (pas en dehors de la map)
    on vois plus tard le cas on l'on rencontre un mur*/
    std::vector<std::vector<int>> getNeighbors()
    {
        std::vector<std::vector<int>> out;
        if (xPos > 0 && yPos > 0)
        {
            out.push_back(std::vector<int> {xPos - 1, yPos - 1, 0});
        }
        if (yPos > 0)
        {
            out.push_back(std::vector<int> {xPos, yPos - 1, 1});
        }
        if (yPos > 0 && xPos < labirynthe->size()[0] - 1)
        {
            out.push_back(std::vector<int> {xPos + 1, yPos - 1, 2});
        }
        if (xPos < labirynthe->size()[0] - 1)
        {
            out.push_back(std::vector<int> {xPos + 1, yPos, 3});
        }
        if (xPos < labirynthe->size()[0] - 1 && yPos < labirynthe->size()[1] - 1)
        {
            out.push_back(std::vector<int>{ xPos + 1, yPos + 1, 4});
        }
        if (yPos < labirynthe->size()[1] - 1)
        {
            out.push_back(std::vector<int> {xPos, yPos + 1, 5});
        }
        if (yPos < labirynthe->size()[1] - 1 && xPos>0)
        {
            out.push_back(std::vector<int> {xPos - 1, yPos + 1, 6});
        }
        if (xPos > 0)
        {
            out.push_back(std::vector<int> {xPos - 1, yPos, 7});
        }
        return out;
    }

    /*ici on utilise l'agorythme de tri a bulles pour classer les direction par interet
    cet interet changera en fonction du mode de search dans le quel on se trouve.
    */
    void sortDirection(std::vector<std::vector<int>>* vectDir, bool stepByStep)
    {
        std::vector<float> vectCost;
        // on recupere d'abord les cout de deplacement
        for (int i = 0; i < vectDir->size(); i++)
        {
            /*si on est en step by step, on prendra le meilleur chemin trouver grace a la memoire du voyageur*/
            if (stepByStep)
            {
                vectCost.push_back(-(float)memoire->getFromAbsolute(vectDir->at(i)[0], vectDir->at(i)[1]));

            }
            else
            {
                //si non, on a le choix de prendre en compte ou pas l'experience
                //du voyageur via computeCost puis on ajout un leger malus pour les deplassement en diagonale
                vectCost.push_back(computeCost(vectDir->at(i)[0], vectDir->at(i)[1]) + (vectDir->at(i)[2] % 2) * 0.4f);
            }
        }
        //Ici on tri du cout le plus faible au plus eleve
        for (int i = 1; i < vectDir->size(); i++)
        {
            int k = i;
            while (k > 0 && vectCost[k - 1] > vectCost[i])
            {
                k--;
            }
            vectCost.insert(vectCost.begin() + k, vectCost[i]);
            vectCost.erase(vectCost.begin() + i + 1);
            vectDir->insert(vectDir->begin() + k, vectDir->at(i));
            vectDir->erase(vectDir->begin() + i + 1);
        }
        if (stepByStep)
        {
            //en mode step by step on montre les differentes option avec leur cout
            std::cout << "vectdir:" << std::endl;
            for (int i = 0; i < vectDir->size(); i++)
            {
                std::cout << vectDir->at(i)[2] << "\t";
            }
            std::cout << std::endl;
            std::cout << "vectCost" << std::endl;
            for (int i = 0; i < vectDir->size(); i++)
            {
                std::cout << vectCost[i] << "\t";
            }
            std::cout << std::endl;
        }
    }


    //avec computeBestDir on va obtenir la meilleur direction qui n'est pas un mur sous la forme d'un entier
    // les direction sont classees de 0 a 7 en partant du Nord Ouest et ena llant dans le sens des aiguilles d'une montre. 
    int computeBestDir(bool stepByStep)
    {
        std::vector<std::vector<int>> vectDir = getNeighbors();
        sortDirection(&vectDir, stepByStep);
        int i = 0;
        for (; i < vectDir.size(); i++)
        {
            if (labirynthe->getFromAbsolute(vectDir[i][0], vectDir[i][1]) != 1)
            {
                return vectDir[i][2];
            }
        }
        return vectDir[i][2];

    }

    Bideque* getMemoire()
    {
        return memoire;
    }

    Bideque* getLabirynthe()
    {
        return labirynthe;
    }

    //move appel la fonction de deplacement correspondante
    void move(int dir)
    {
        if (dir == 0)
        {
            moveNO();
        }
        else if (dir == 1)
        {
            moveN();
        }
        else if (dir == 2)
        {
            moveNE();
        }
        else if (dir == 3)
        {
            moveE();
        }
        else if (dir == 4)
        {
            moveSE();
        }
        else if (dir == 5)
        {
            moveS();
        }
        else if (dir == 6)
        {
            moveSO();
        }
        else if (dir == 7)
        {
            moveO();
        }
        else
        {
            std::cout << "pas bouger!" << std::endl;
        }
    }

    void search(bool stepByStep)
    {
        int nMoves = 0;
        if (stepByStep)
        {
            while (computeDist() > 0 && nMoves < maxMoves)
            {
                    int dir = computeBestDir(true);
                    move(dir);
                    nMoves++;
                    //labirynthe->displayMap();
            }
            if (computeDist() == 0)
            {
                std::cout << "on a trouver le crane de cristal en " << nMoves << " mouvement!" << std::endl << std::endl;
                //labirynthe->displayMap();
                //resetLabirynthe();
                //reussite++;
            }
            else
            {
                std::cout << "on a pas trouve..." << std::endl << std::endl;
                //labirynthe->displayMap();
            }
        }
        else
        {
            while (computeDist() > 0 && nMoves < maxMoves)
            {
                int dir = computeBestDir(false);
                move(dir);
                nMoves++;
            }
            if (computeDist() == 0)
            {
                //std::cout << "on a trouver le crane de cristal en " << nMoves << " mouvement!" << std::endl << std::endl;
                writeMemoire();
                resetLabirynthe();
                nStep = std::min(nMoves, nStep);
            }
            else
            {
                //std::cout << "on a pas trouve..." << std::endl << std::endl;
                resetLabirynthe();
            }
        }
    }
    void makeNSearch(int N)
    {
        for (int i = 0; i < N; i++)
        {
            search(false);
        }
    }
};


sf::Color getColorFromInt(int value)
{
    if (value == 0)
    {
        return sf::Color(0, 0, 0, 255);
    }
    value = (int)((value-1) * 2 * 256 / 200);
    if (value / 255 == 0)
    {
        return sf::Color(0, value, 255 - value, 255);
    }
    else if (value / 255 == 1)
    {
        return sf::Color(value % 256, 255 - (value % 256), 0, 255);
    }
}


void displayMemoryWindow(VoyageurDirect* voyageur, bool withTrace)
{
    sf::Font* font = new sf::Font;
    if (!font->loadFromFile("arial.ttf"));

    delete font;
    int nrow = voyageur->getLabirynthe()->size()[0];
    int ncol = voyageur->getLabirynthe()->size()[1];
    sf::RenderWindow window(sf::VideoMode(nrow*4, ncol*4), "SFML works!");


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        sf::RectangleShape rectangle;
        for (int i = 0; i < voyageur->getLabirynthe()->size()[0]; i++)
        {
            for (int j = 0; j < voyageur->getLabirynthe()->size()[1]; j++)
            {
                rectangle.setSize(sf::Vector2f(4, 4));
                rectangle.setFillColor(getColorFromInt(voyageur->getMemoire()->getFromAbsolute(i,j)));
                rectangle.setOutlineThickness(0);
                rectangle.setPosition(i*4, j*4);
                window.draw(rectangle);
            }
        }
        if (withTrace)
        {
            for (int i = 0; i < voyageur->getHistory().size(); i++)
            {
                rectangle.setSize(sf::Vector2f(4, 4));
                rectangle.setFillColor(sf::Color(255,255,255,255));
                rectangle.setOutlineThickness(0);
                rectangle.setPosition(voyageur->getHistory()[i][0]*4, voyageur->getHistory()[i][1]*4);
                window.draw(rectangle);
            }
        }
        window.display();
    }
}
void displayLabiryntheWindow(VoyageurDirect* voyageur)
{
    sf::Font* font = new sf::Font;
    if (!font->loadFromFile("arial.ttf"));

    delete font;
    int nrow = voyageur->getLabirynthe()->size()[0];
    int ncol = voyageur->getLabirynthe()->size()[1];
    sf::RenderWindow window(sf::VideoMode(nrow * 4, ncol * 4), "SFML works!");


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        sf::RectangleShape rectangle;
        for (int i = 0; i < voyageur->getLabirynthe()->size()[0]; i++)
        {
            for (int j = 0; j < voyageur->getLabirynthe()->size()[1]; j++)
            {
                if (voyageur->getLabirynthe()->getFromAbsolute(i, j)>0)
                {
                    rectangle.setSize(sf::Vector2f(4, 4));
                    if (voyageur->getLabirynthe()->getFromAbsolute(i, j) == 1)
                    {
                        rectangle.setFillColor(sf::Color(255,255,255,255));
                    }
                    else if (voyageur->getLabirynthe()->getFromAbsolute(i, j) == 2)
                    {
                        rectangle.setFillColor(sf::Color(0, 0, 255, 255));
                    }
                    else if (voyageur->getLabirynthe()->getFromAbsolute(i, j) == 3)
                    {
                        rectangle.setFillColor(sf::Color(0, 255, 0, 255));
                    }
                    rectangle.setOutlineThickness(0);
                    rectangle.setPosition(i * 4, j * 4);
                    window.draw(rectangle);
                }
            }
        }

        window.display();
    }
}



int main()
{
    srand(time(NULL));
    std::cout << "Hello World!\n";
    int N = 150;
    Bideque grille(N, N, 0);
    Bideque memoire(N, N, 0);
    std::cout << "createion de la grille ok" << std::endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i != 0 || j != 0)
            {
                int s = (rand() % 7);
                if (s > 5 && (i != grille.getOrigin()[0] || j != grille.getOrigin()[1]))
                {
                    grille.addValue(i, j, 1);
                }
                if (s < 6 && s > 4 && (i != grille.getOrigin()[0] || j != grille.getOrigin()[1]))
                {
                    grille.addValue(i, j, 2);
                }
                if (s < 5 && s > 2 && (i != grille.getOrigin()[0] || j != grille.getOrigin()[1]))
                {
                    grille.addValue(i, j, 3);
                }
            }
        }
    }
    std::cout << "ajout des obstacle ok" << std::endl;


    //grille.displayMap();
    VoyageurDirect indiana(&grille, &memoire, 200);

    std::cout << "creation du voyageur ok" << std::endl;
    std::cout << (int)2.5 << std::endl;
    displayLabiryntheWindow(&indiana);
    indiana.makeNSearch(1000);
    std::cout << "recherche terminee" << std::endl;
    displayMemoryWindow(&indiana, false);
    indiana.search(true);
    displayMemoryWindow(&indiana, true);
}
