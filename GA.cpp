#include "vector"
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <sstream>
#define data_size 51
#define num_autosome 50
#define crossover_rate 0.7
#define mutation_rate 0.1
#define dim 2

using namespace std;
vector<vector<float>> eil;
vector<int> best_path;
float best_distance;

void readfile() /////////讀檔//////////////
{
    string line, tmp;
    int tmp_2;
    int i = 0;

    eil.resize(data_size);
    fstream file;
    file.open("GA/eil51.txt", ios::in);

    while (getline(file, line))
    {
        stringstream t_line(line), ss;
        while (getline(t_line, tmp, ' '))
        {
            ss.clear();
            ss << tmp;
            ss >> tmp_2;
            eil[i].push_back(tmp_2);
        }
        i++;
    }
}
void init(vector<vector<int>> &path) //////////////初始化//////////////////
{
    int r, i, j = 0;
    vector<int> init_path;

    for (i = 0; i < data_size; i++)
        init_path.push_back(i);

    for (i = 0; i < num_autosome; i++)
        for (j = 0; j < data_size; j++)
            path[i].push_back(init_path[j]);

    int tmp;
    for (i = 0; i < num_autosome; i++)
    {
        for (j = 0; j < data_size; j++)
        {
            r = rand() % data_size;
            tmp = path[i][j];
            path[i][j] = path[i][r];
            path[i][r] = tmp;
        }
    }
}

void selectionD(vector<vector<int>> &new_path, vector<vector<int>> path, vector<float> selection_rate)
{
    vector<float> pie_chart;
    vector<int> remain_path;
    remain_path.resize(num_autosome);
    pie_chart.resize(num_autosome + 1);
    pie_chart[0] = 0;
    int i, j, r;
    //cout<<selection_rate<<endl;
    for (i = 1; i <= num_autosome; i++)
    {
        pie_chart[i] += (pie_chart[i - 1] + selection_rate[i - 1]);
        //cout<<pie_chart[i]<<endl;
    }
    for (i = 0; i < num_autosome; i++)
    {
        r = rand() % ((int)pie_chart[num_autosome]);
        for (j = 0; j < num_autosome; j++)
        {
            if (r >= pie_chart[j] && r <= pie_chart[j + 1])
                remain_path[i] = j;
        }
    }
    for (i = 0; i < num_autosome; i++)
        for (j = 0; j < data_size; j++)
        {
            new_path[i][j] = path[remain_path[i]][j];
        }
}
void crossover(vector<vector<int>> &path)
{
    int i, j, k, r_1, r_2, tmp;
    int segmentation_point_1, segmentation_point_2;
    double possibility_to_cross;
    vector<vector<int>> changed_path;
    vector<int> remain_path_index(num_autosome), it;
    changed_path.resize(10);

    for (i = 0; i < num_autosome; i++)
        remain_path_index[i] = i;

    for (i = 0; i < (num_autosome / 2); i++)
    {
        r_1 = rand() % (remain_path_index.size());
        r_2 = rand() % (remain_path_index.size());
        while (r_2 == r_1)
            r_2 = rand() % (remain_path_index.size());

        segmentation_point_1 = rand() % (data_size - 1);
        segmentation_point_2 = rand() % (data_size - segmentation_point_1 - 1) + segmentation_point_1 + 1;

        possibility_to_cross = (float)rand() / RAND_MAX;

        int flag = 1, changed_record[data_size] = {0};
        //////////////////doing crossover///////////////////////////////
        if (possibility_to_cross < crossover_rate)
        {
            ////////////////////切割交換////////////////////
            for (j = segmentation_point_1 + 1; j <= segmentation_point_2; j++)
            {
                tmp = path[remain_path_index[r_1]][j];
                path[remain_path_index[r_1]][j] = path[remain_path_index[r_2]][j];
                path[remain_path_index[r_2]][j] = tmp;
                changed_record[j] = 1;
            }
            ////////////////////切割交換////////////////////
            vector<vector<int>> origin_path;
            
            for (j = 0; j <= data_size; j++)
                if (changed_record[j] == 0)
                {
                    flag = 1;
                    tmp = path[remain_path_index[r_1]][j];
                    while (flag) /////////////routine finding the oppisite data/////////////////
                    {
                        for (k = segmentation_point_1 + 1; k <= segmentation_point_2; k++)
                        {
                            if (tmp == path[remain_path_index[r_1]][k])
                            {
                                tmp = path[remain_path_index[r_2]][k];
                                break;
                            }
                            else if (k == segmentation_point_2)
                                flag = 0;
                        }
                    }
                    for (k = 0; k <= segmentation_point_1; k++)
                        if (tmp == path[remain_path_index[r_2]][k])
                        {
                            path[remain_path_index[r_2]][k] = path[remain_path_index[r_1]][j];
                            path[remain_path_index[r_1]][j] = tmp;
                            break;
                        }

                    for (k = segmentation_point_2; k <= data_size; k++)
                        if (tmp == path[remain_path_index[r_2]][k])
                        {
                            path[remain_path_index[r_2]][k] = path[remain_path_index[r_1]][j];
                            path[remain_path_index[r_1]][j] = tmp;
                            break;
                        }
                }
            ///////////////erase兩兩交換的index///////////////////////
            r_1 = remain_path_index[r_1];
            r_2 = remain_path_index[r_2];
            vector<int>::iterator it = remain_path_index.begin();

            for (; it != remain_path_index.end();)
            {
                if (*it == r_1 || *it == r_2)
                    it = remain_path_index.erase(it);
                else
                    ++it;
            }
        }
        else
        {
            r_1 = remain_path_index[r_1];
            r_2 = remain_path_index[r_2];
            vector<int>::iterator it = remain_path_index.begin();

            for (; it != remain_path_index.end();)
            {
                if (*it == r_1 || *it == r_2)
                    it = remain_path_index.erase(it);

                else
                    ++it;
            }
        }
        ///////////////erase兩兩交換的index///////////////////////
        //////////////////crossover done//////////////////////////////
    }
}

void mutation(vector<vector<int>> &path) ///////////////突變////////////////
{
    int i, j, r_1, r_2, tmp;
    double possibility_to_mutation;

    for (i = 0; i < num_autosome; i++)
    {
        possibility_to_mutation = (double)rand() / RAND_MAX;
        if (possibility_to_mutation < mutation_rate)
        {
            r_1 = rand() % data_size;
            r_2 = rand() % data_size;
            while (r_1 == r_2)
                r_2 = rand() % data_size;

            tmp = path[i][r_1];
            path[i][r_1] = path[i][r_2];
            path[i][r_2] = tmp;
        }
    }
}

void fitness(vector<vector<int>> &path, float Denominator, vector<float> &selection_rate)
{
    int i, j, k, best_path_index = 0;
    float current_distance = 0;
    vector<float> path_distance;
    path_distance.assign(10, 0);
    path_distance.resize(num_autosome);

    for (i = 0; i < num_autosome; i++)
    {
        current_distance = 0.0;
        for (j = 0; j < data_size - 1; j++)
        {
            current_distance = 0;
            for (k = 0; k < dim; k++)
                current_distance += (pow(eil[path[i][j]][k] - eil[path[i][j + 1]][k], 2));

            current_distance = sqrt(current_distance);
            path_distance[i] += current_distance;
        }
        if (path_distance[i] < best_distance)
        {
            best_distance = path_distance[i];
            best_path_index = i;
        }
        Denominator += path_distance[i];
    }
    for (i = 0; i < num_autosome; i++)
        selection_rate[i] = 1 / (path_distance[i] / Denominator);

    for (i = 0; i < data_size; i++)
        best_path[i] = path[best_path_index][i];
}

int main()
{
    int i, j;
    srand(time(NULL));

    readfile();

    vector<vector<int>> num_path;
    num_path.resize(num_autosome);

    init(num_path);

    int itteration = 0;
    vector<float> selection_rate(num_autosome);
    float Denominator;
    best_distance = 10000;
    while (itteration <= 5000)
    {
        best_path.resize(data_size);
        Denominator = 0;
        fitness(num_path, Denominator, selection_rate);
        selectionD(num_path, num_path, selection_rate);
        crossover(num_path);
        mutation(num_path);
        itteration++;
    }
    cout << best_distance << endl;
    system("pause");
    return 0;
}