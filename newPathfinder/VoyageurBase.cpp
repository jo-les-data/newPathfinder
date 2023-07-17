#include "VoyageurBase.hpp"



float squared(float x)
{
    return x * x;
}


VoyageurBase::VoyageurBase(Bideque* labiryntheInput, Bideque* memoireInput, int maxMovesInput, bool randomInitInput)
{
    labirynthe = labiryntheInput;//contient les lac, foret et murs
    memoire = memoireInput;//contient l'ebauche de carte a* necessaire a atteindre l'origine
    randomInit = randomInitInput;
    if (randomInit)
    {
        xPos = rand() % labirynthe->size()[0];
        yPos = rand() % labirynthe->size()[0];
    }
    else
    {
        xPos = 0;//rand() % labirynthe->size()[0]; dans le cas ou on veux cree la carte le l'algo A*
        yPos = 0;//rand() % labirynthe->size()[0];
    }
    history.push_back(std::vector<int> {xPos, yPos});//pour remplir la memoire en cas de reussite de la recherche de chemin
    nStep = 25000;
    reussite = 0;
    markPosition();
    maxMoves = maxMovesInput;
}

const std::vector<std::vector<int>> VoyageurBase::getHistory()
{
    return history;
}
float VoyageurBase::computeDist()
{
    return sqrtf(squared((float)xPos - labirynthe->getOrigin()[0]) + squared((float)yPos - labirynthe->getOrigin()[1]));
}
float VoyageurBase::computeDist(int x, int y)
{
    return sqrtf(squared((float)x - labirynthe->getOrigin()[0]) + squared((float)y - labirynthe->getOrigin()[1]));
}
float VoyageurBase::computeCost(int x, int y)
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
void VoyageurBase::markPosition()
{
    history.push_back(std::vector<int>{ xPos, yPos });
    labirynthe->getFromAbsolute(xPos, yPos) += 8;
}

void VoyageurBase::resetLabirynthe()
{
    if (randomInit)
    {
        xPos = rand() % labirynthe->size()[0];
        yPos = rand() % labirynthe->size()[0];
    }
    else
    {
        xPos = 0;
        yPos = 0;
    }
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
void VoyageurBase::writeMemoire()
{
    for (int i = ((int)history.size() - 1); i > 0; i--)
    {
        memoire->getFromAbsolute(history[i][0], history[i][1]) = std::max(i, (*memoire)[history[i][0]][history[i][1]]);
    }
}

int VoyageurBase::getNSteps()
{
    return nStep;
}

void VoyageurBase::moveN()
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
void VoyageurBase::moveS()
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
void VoyageurBase::moveE()
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
void VoyageurBase::moveO()
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
void VoyageurBase::moveNO()
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
void VoyageurBase::moveNE()
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
void VoyageurBase::moveSO()
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
void VoyageurBase::moveSE()
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

