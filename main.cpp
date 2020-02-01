#include <iostream>
#include <vector>

#include <cblas.h>
#include <dlib/clustering.h>
#include <dlib/rand.h>
#include <random>

using namespace std;
using namespace dlib;

std::string create_dataset(){

    std::string dataset_file_name = "ds.csv";
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
    return dataset_file_name;
}

std::string create_dlib_dataset(){
    dlib::rand rnd;

    std::string dataset_file_name = "ds_dlib.csv";
    std::ofstream myfile;
    myfile.open(dataset_file_name);

    const long num = 50;
    // make some samples near the origin
    double radius = 0.5;

    for (long i = 0; i < num; ++i)
    {
        double sign = 1;
        if (rnd.get_random_double() < 0.5)
            sign = -1;
        double x = 2*radius*rnd.get_random_double()-radius;
        double y = sign*sqrt(radius*radius - x*x);
        myfile << x << ";" << y << "\n";
    }

    radius = 10.0;
    for (long i = 0; i < num; ++i)
    {
        double sign = 1;
        if (rnd.get_random_double() < 0.5)
            sign = -1;
        double x = 2*radius*rnd.get_random_double()-radius;
        double y = sign*sqrt(radius*radius - x*x);
        myfile << x << ";" << y << "\n";
    }

    radius = 4.0;
    for (long i = 0; i < num; ++i)
    {
        double sign = 1;
        if (rnd.get_random_double() < 0.5)
            sign = -1;
        double x = 2*radius*rnd.get_random_double()-radius;
        double y = sign*sqrt(radius*radius - x*x);

        // translate this point away from the origin
        x += 25;
        y += 25;

        myfile << x << ";" << y << "\n";

    }
    myfile.close();
    return dataset_file_name;
}

int main() {

    std::string dataset_file_name = create_dlib_dataset();

    typedef matrix<double,2,1> sample_type;
    std::vector<sample_type> samples;
    sample_type m;

    typedef radial_basis_kernel<sample_type> kernel_type;
    kcentroid<kernel_type> kc(kernel_type(0.1),0.01, 8);
    kkmeans<kernel_type> test(kc);

    string x, y, line;
    ifstream myfile(dataset_file_name);

    std::vector<std::vector<int>> coords;

    if (myfile.is_open())
    {
        while (!myfile.eof()){
            getline(myfile, x, ';');
            getline(myfile, y, '\n');
            if (x.empty()){
                break;
            }
            m(0) = stod(x);
            m(1) = stod(y);
            samples.push_back(m);
        }
    }

    else cout << "Unable to open file";

    std::vector<sample_type> initial_centers;
    test.set_number_of_centers(3);
    pick_initial_centers(3, initial_centers, samples, test.get_kernel());

    test.train(samples, initial_centers);

    std::ofstream resfile;
    resfile.open("result.csv");


    for (unsigned long i = 0; i < samples.size(); ++i)
    {
        double x = samples[i](0);
        double y = samples[i](1);
        int res = test(samples[i]);
        resfile << x << ";" << y << ";" << res << "\n";

    }

    resfile.close();
    return 0;

}


