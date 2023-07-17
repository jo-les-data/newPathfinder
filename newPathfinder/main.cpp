#include <ctime>
#include <math.h> 
#include <cstdlib>
#include <conio.h>
#include <cstdlib>
#include "Voyageurs.hpp"












int main()
{
    srand((unsigned int)time(NULL));
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
    VoyageurDirect indiana(&grille, &memoire, 200, false);

    std::cout << "creation du voyageur ok" << std::endl;
    displayLabiryntheWindow(&indiana);
    indiana.makeNSearch(1000);
    std::cout << "recherche terminee" << std::endl;
    displayMemoryWindow(&indiana, false);
    indiana.search(true);
    displayMemoryWindow(&indiana, true);
}
