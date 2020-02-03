#include <iostream>
#include <utility>
#include <vector>

#include <cblas.h>
#include <dlib/clustering.h>
#include <dlib/rand.h>
#include <random>

using namespace std;
using namespace dlib;

void create_dataset(const std::string& dataset_file_name){
    std::ofstream myfile;
    myfile.open(dataset_file_name);
    for (int i = 0; i < 100; ++i){
        int x = -(std::rand() % 100 + 1) + (std::rand() % 100 + 1);
        int y = -(std::rand() % 100 + 1) + (std::rand() % 100 + 1);
        myfile << x << ";" << y << "\n";
    }
    for (int i = 0; i < 50; ++i){
        int x = -(std::rand() % 20 + 1) - 50;
        int y = -(std::rand() % 20 + 1) - 50;
        myfile << x << ";" << y << "\n";
    }

    for (int i = 0; i < 50; ++i){
        int x = (std::rand() % 20 + 1) + 50;
        int y = (std::rand() % 20 + 1) + 50;
        myfile << x << ";" << y << "\n";
    }

//    for (int i = 0; i < 25; ++i){
//        int x = (std::rand() % 20 + 1) + 10;
//        int y = (std::rand() % 20 + 1) + 10;
//        myfile << x << ";" << y << "\n";
//    }

    myfile.close();
}

void create_dlib_dataset(const std::string& dataset_file_name){
    dlib::rand rnd;
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
}

void predict(std::string dataset_file_name, std::string result_file_name){

//  тип записи - вектор из 2 элементов [[x, y],]
    typedef matrix<double,2,1> sample_type;
//    массив записей (датафрейм)
    std::vector<sample_type> samples;
    sample_type m;

//    параметры kmeans алгоритма
    typedef radial_basis_kernel<sample_type> kernel_type;
//    увеличил точность (tolerance) и добавил словарей. Теперь кластерицация точнее но медленнее
    kcentroid<kernel_type> kc(kernel_type(0.1),0.001, 16);
    kkmeans<kernel_type> test(kc);

//  читаем датасет из файла и заполняем датафрейм
    string x, y, line;
    ifstream dataset_file(dataset_file_name);
    if (dataset_file.is_open())
    {
        while (!dataset_file.eof()){
            getline(dataset_file, x, ';');
            getline(dataset_file, y, '\n');
            if (x.empty()){
                break;
            }
            m(0) = stod(x);
            m(1) = stod(y);
            samples.push_back(m);
        }
    }

//    определяем центры кластеров
    std::vector<sample_type> initial_centers;
    test.set_number_of_centers(3);
    pick_initial_centers(3, initial_centers, samples, test.get_kernel());

//    тренируем центры на датафрейме
    test.train(samples, initial_centers);

//    пишем файл с предсказаниями
    std::ofstream result_file;
    result_file.open(result_file_name);

    for (auto & sample : samples)
    {
        double x = sample(0);
        double y = sample(1);
        int res = test(sample);
        result_file << x << ";" << y << ";" << res << "\n";
    }
    result_file.close();
}


int main() {

//    std::string dataset_file_name = "dlib_dataset.txt";
//    std::string result_file_name = "dlib_result.txt";
//
//    create_dlib_dataset(dataset_file_name);
//
//    predict(dataset_file_name, result_file_name);

    std::string dataset_file_name = "my_dataset.txt";
    std::string result_file_name = "my_result.txt";

    create_dataset(dataset_file_name);

    predict(dataset_file_name, result_file_name);

    return 0;

}


