#include "VoyageurBase.hpp"

class VoyageurDirect : public VoyageurBase
{
public:
    VoyageurDirect(Bideque* labiryntheInput, Bideque* memoireInput, int maxMovesInput, bool randomInitInput);
    ~VoyageurDirect();
    /*Ici on va regarder quel voisin est accessible (pas en dehors de la map)
    on vois plus tard le cas on l'on rencontre un mur*/
    std::vector<std::vector<int>> getNeighbors();

    /*ici on utilise l'agorythme de tri a bulles pour classer les direction par interet
    cet interet changera en fonction du mode de search dans le quel on se trouve.
    */
    void sortDirection(std::vector<std::vector<int>>* vectDir, bool stepByStep);


    //avec computeBestDir on va obtenir la meilleur direction qui n'est pas un mur sous la forme d'un entier
    // les direction sont classees de 0 a 7 en partant du Nord Ouest et ena llant dans le sens des aiguilles d'une montre. 
    int computeBestDir(bool stepByStep);

    Bideque* getMemoire();

    Bideque* getLabirynthe();

    //move appel la fonction de deplacement correspondante
    void move(int dir);

    void search(bool stepByStep);
    void makeNSearch(int N);
};
sf::Color getColorFromInt(int value);
void displayMemoryWindow(VoyageurDirect* voyageur, bool withTrace);
void displayLabiryntheWindow(VoyageurDirect* voyageur);