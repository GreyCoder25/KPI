#include "TrainStationDatabase.h"
#include <fstream>
#include <cstdlib>

using std::ifstream;
using std::cerr;
using std::exit;
using std::getline;

TrainStationDatabase::TrainStationDatabase(const char* inputFileName) {

    ifstream inpFile(inputFileName);
    if (!inpFile) {
        cerr<<"File could not be opened"<<endl;
        exit(1);
    }
    int num;
    while(inpFile >> num) {
        char r;
        inpFile >> r;

        string dest;
        getline(inpFile, dest, ';');
        int h, m;
        inpFile >> h >> m;
        Time time(h, m);

        TreeNode tn(num, dest, time);
        database.add(tn);

        //cout << "fhjghjf" << endl;
    }


    inpFile.close();
}

void TrainStationDatabase::printTrainsList() {

    cout << "List of available trains: " << endl << endl;
    database.print();

}

void TrainStationDatabase::printTrainInfo(int trainNumber) {

    cout << "Information about train number " << trainNumber << ":"<<endl << endl;

    TreeNode* p = database.find(trainNumber);
    if (p != 0)
        p->printData();
    else
        cout << "Train with this number doesn't exist" << endl << endl;

}

void TrainStationDatabase::printTrainsThatFollowTo(const string& stationName) {

    cout << "Trains that follow to " << stationName << ":" << endl << endl;
    database.findAllAndPrint(stationName);

}

void TrainStationDatabase::deleteRouteInf(int trainNumber) {

    if (database.remove(trainNumber))
        cout << "Train with number " << trainNumber << " was deleted" << endl << endl;
    else
        cout << "Can't be deleted because train with this number doesn't exist" << endl << endl;

}
