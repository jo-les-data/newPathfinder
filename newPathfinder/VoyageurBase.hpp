#include "bideque.hpp"

float squared(float x);

class VoyageurBase
{
protected:
    Bideque* labirynthe;
    Bideque* memoire;
    bool randomInit;
    int xPos;
    int yPos;
    std::vector<std::vector<int>> history;
    float dist;
    int nStep;
    int maxMoves;
public:
    int reussite;
    VoyageurBase(Bideque* labiryntheInput, Bideque* memoireInput, int maxMovesInput, bool randomInitInput);
    const std::vector<std::vector<int>> getHistory();
    float computeDist();
    float computeDist(int x, int y);
    float computeCost(int x, int y);
    void markPosition();
    void resetLabirynthe();
    //en rebroussant chemin, on va ecrir des valeur de plus en plus petite alors qu'on seloigne de l'origine
    void writeMemoire();
    int getNSteps();
    void moveN();
    void moveS();
    void moveE();
    void moveO();
    void moveNO();
    void moveNE();
    void moveSO();
    void moveSE();
};

