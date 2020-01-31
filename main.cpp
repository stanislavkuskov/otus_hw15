#include <iostream>
#include <vector>

#include <cblas.h>
#include <dlib/clustering.h>
#include <dlib/rand.h>
#include <random>

using namespace std;
using namespace dlib;

void create_dataset(){
    std::string dataset_file_name = "../ds.csv";
    std::ofstream myfile;
    myfile.open(dataset_file_name);
    for (int i = 0; i < 150; ++i){
        int x = -(std::rand() % 100 + 1) + (std::rand() % 100 + 1);
        int y = -(std::rand() % 100 + 1) + (std::rand() % 100 + 1);
        myfile << x << ";" << y << "\n";
    }
    for (int i = 0; i < 25; ++i){
        int x = -(std::rand() % 10 + 1) - 50;
        int y = -(std::rand() % 10 + 1) - 50;
        myfile << x << ";" << y << "\n";
    }

    for (int i = 0; i < 25; ++i){
        int x = (std::rand() % 10 + 1) + 50;
        int y = (std::rand() % 10 + 1) + 50;
        myfile << x << ";" << y << "\n";
    }

    myfile.close();
}
int main() {

//    create_dataset();
    string x, y, line;
    ifstream myfile ("../ds.csv");

    std::vector<std::vector<int>> coords;

    if (myfile.is_open())
    {
        while (!myfile.eof()){
            getline(myfile, x, ';');
            getline(myfile, y, '\n');
            if (x.empty()){
                break;
            }
            coords.push_back({stoi(x), stoi(y)});
        }
    }

    else cout << "Unable to open file";
    cout << "UDataset";



    return 0;

}


