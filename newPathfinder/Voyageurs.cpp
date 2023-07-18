#include "Voyageurs.hpp"

VoyageurDirect::VoyageurDirect(Bideque* labiryntheInput, Bideque* memoireInput, int maxMovesInput, bool randomInitInput) : VoyageurBase(labiryntheInput, memoireInput, maxMovesInput, randomInitInput) {}
VoyageurDirect::~VoyageurDirect() {}
/*Ici on va regarder quel voisin est accessible (pas en dehors de la map)
on vois plus tard le cas on l'on rencontre un mur*/
std::vector<std::vector<int>> VoyageurDirect::getNeighbors()
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
void VoyageurDirect::sortDirection(std::vector<std::vector<int>>* vectDir, bool stepByStep)
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
    //if (stepByStep)
    //{
    //    //en mode step by step on montre les differentes option avec leur cout
    //    std::cout << "vectdir:" << std::endl;
    //    for (int i = 0; i < vectDir->size(); i++)
    //    {
    //        std::cout << vectDir->at(i)[2] << "\t";
    //    }
    //    std::cout << std::endl;
    //    std::cout << "vectCost" << std::endl;
    //    for (int i = 0; i < vectDir->size(); i++)
    //    {
    //        std::cout << vectCost[i] << "\t";
    //    }
    //    std::cout << std::endl;
    //}
}

//avec computeBestDir on va obtenir la meilleur direction qui n'est pas un mur sous la forme d'un entier
// les direction sont classees de 0 a 7 en partant du Nord Ouest et ena llant dans le sens des aiguilles d'une montre. 
int VoyageurDirect::computeBestDir(bool stepByStep)
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
Bideque* VoyageurDirect::getMemoire()
{
    return memoire;
}
Bideque* VoyageurDirect::getLabirynthe()
{
    return labirynthe;
}

//move appel la fonction de deplacement correspondante
void VoyageurDirect::move(int dir)
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
void VoyageurDirect::search(bool stepByStep)
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
void VoyageurDirect::makeNSearch(int N)
{
    for (int i = 0; i < N; i++)
    {
        search(false);
    }
}

void VoyageurDirect::displayMemoryWindow(bool withTrace)
{
    int nrow = memoire->size()[0];
    int ncol = memoire->size()[1];
    sf::RenderWindow window(sf::VideoMode(nrow * 4, ncol * 4), "SFML works!");

    bool imgSaved = false;
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
        for (int i = 0; i < memoire->size()[0]; i++)
        {
            for (int j = 0; j < memoire->size()[1]; j++)
            {
                rectangle.setSize(sf::Vector2f(4, 4));
                rectangle.setFillColor(getColorFromInt(memoire->getFromAbsolute(i, j)));
                rectangle.setOutlineThickness(0);
                rectangle.setPosition((float)(i * 4), (float)(j * 4));
                window.draw(rectangle);
            }
        }
        if (withTrace)
        {
            for (int i = 0; i < history.size(); i++)
            {
                rectangle.setSize(sf::Vector2f(4, 4));
                rectangle.setFillColor(sf::Color(255, 255, 255, 255));
                rectangle.setOutlineThickness(0);
                rectangle.setPosition((float)(history[i][0] * 4), (float)(history[i][1] * 4));
                window.draw(rectangle);
            }
        }
        sf::Texture texture;
        texture.create(window.getSize().x, window.getSize().y);
        texture.update(window);
        if (!imgSaved && texture.copyToImage().saveToFile("..\\memory.png"))
        {
            imgSaved;
            std::cout << "screenshot saved to " << "..\\memory.png" << std::endl;
        }
        window.display();
    }
}

void VoyageurDirect::displayLabiryntheWindow()
{
    int nrow = labirynthe->size()[0];
    int ncol = labirynthe->size()[1];
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
        for (int i = 0; i < labirynthe->size()[0]; i++)
        {
            for (int j = 0; j < labirynthe->size()[1]; j++)
            {
                if (labirynthe->getFromAbsolute(i, j) > 0)
                {
                    rectangle.setSize(sf::Vector2f(4, 4));
                    if (labirynthe->getFromAbsolute(i, j) == 1)
                    {
                        rectangle.setFillColor(sf::Color(255, 255, 255, 255));
                    }
                    else if (labirynthe->getFromAbsolute(i, j) == 2)
                    {
                        rectangle.setFillColor(sf::Color(0, 0, 255, 255));
                    }
                    else if (labirynthe->getFromAbsolute(i, j) == 3)
                    {
                        rectangle.setFillColor(sf::Color(0, 255, 0, 255));
                    }
                    rectangle.setOutlineThickness(0);
                    rectangle.setPosition((float)(i * 4), (float)(j * 4));
                    window.draw(rectangle);
                }
            }
        }

        window.display();
    }
}


sf::Color getColorFromInt(int value)
{
    if (value == 0)
    {
        return sf::Color(0, 0, 0, 255);
    }
    value = (int)((value - 1) * 2 * 256 / 200);
    if (value / 255 == 0)
    {
        return sf::Color(0, value, 255 - value, 255);
    }
    else if (value / 255 == 1)
    {
        return sf::Color(value % 256, 255 - (value % 256), 0, 255);
    }
    return sf::Color(0, 0, 0, 0);
}