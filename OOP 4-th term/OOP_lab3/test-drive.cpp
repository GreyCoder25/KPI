#include "TrainStationDatabase.h"


int main()
{
    TrainStationDatabase db("/home/serhiy/OOP_lab3/input.csv");
    db.printTrainsList();
    db.deleteRouteInf(953);
    db.printTrainsList();
    db.printTrainInfo(953);
    db.printTrainsThatFollowTo("Lviv");
}
