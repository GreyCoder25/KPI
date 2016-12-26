#ifndef TRAINSTATIONDATABASE_H
#define TRAINSTATIONDATABASE_H

#include "BinTree.h"

class TrainStationDatabase {

public:
    TrainStationDatabase(const char* inputFileName);
    void printTrainsList();
    void printTrainInfo(int trainNumber);
    void printTrainsThatFollowTo(const string& stationName);
    void deleteRouteInf(int trainNumber);

private:
    BinTree database;

};

#endif // TRAINSTATIONDATABASE_H
