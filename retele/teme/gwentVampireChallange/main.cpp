#include <fstream>
#include <vector>
#include <string>

#define MELEE_VAMPIRE 1
#define RANGED_VAMPIRE

using namespace std;

ofstream fout("sol.txt");

void init();
void bkt(int step, int attack);

int palisadeHP;

vector<string> solutionSteps;

struct vampireSide{

    int ranged;
    int melee;
};
vampireSide vSide;

struct peasant {

    int location;
    int hp;
}

struct peasantSide {

    int rangedHand;
    int rangedPlay;
    int siegeHand;
    int siegePlay;
};
peasantSide pSide;

int main()
{
    init();
    bkt(0);
    return 0;
}

void init() {

    palisadeHP = 4;
    vSide.melee =0;
    vSide.ranged = 0;
    pSide.rangedPlay = 0;
    pSide.SiegePlay = 0;
}

void bkt(int step)
{
if (palisadeHP == 10)
    exit(0);

}
