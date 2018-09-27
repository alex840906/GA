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
#define num_autosome 10
#define crossover_rate 0.7
#define mutation_rate 0.1

using namespace std;
vector<vector<float>> eil;

void readfile()
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
void init(vector<vector<int>> &path)
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
    // for(i=0;i<data_size;i++)
    //     cout<<path[9][i]<<endl;
    //     cout<<endl<<endl;
}

void selectionD()
{
}
void crossover(vector<vector<int>> &path)
{
    int i, j, k, r_1, r_2, tmp;
    int segmentation_point_1, segmentation_point_2;
    double possibility_to_cross;
    vector<vector<int>> changed_path;
    vector<int> remain_path_index(10), it;
    changed_path.resize(10);

    for (i = 0; i < num_autosome; i++)
    {
        remain_path_index[i] = i;
        //cout<<remain_path_index[i]<<endl;
    }

    for (i = 0; i < (num_autosome / 2); i++)
    {
        r_1 = rand() % (remain_path_index.size());
        r_2 = rand() % (remain_path_index.size());
        while (r_2 == r_1)
            r_2 = rand() % (remain_path_index.size());

        segmentation_point_1 = rand() % (data_size - 1);
        segmentation_point_2 = rand() % (data_size - segmentation_point_1 - 1) + segmentation_point_1 + 1;

        possibility_to_cross = (float)rand() / RAND_MAX;

        cout << "r_1 = " << r_1 << " r_2 =  " << r_2 << "  cross rate: " << possibility_to_cross << endl;

        cout << segmentation_point_1 << " " << segmentation_point_2 << endl;
        // for (k = 0; k < remain_path_index.size(); k++)
        //     cout << remain_path_index[k] << endl;
        // cout << endl;

        int flag = 1, changed_record[data_size] = {0};
        //////////////////doing crossover///////////////////////////////
        if (possibility_to_cross < crossover_rate)
        {
            for (j = segmentation_point_1 + 1; j <= segmentation_point_2; j++)
            {
                tmp = path[remain_path_index[r_1]][j];
                path[remain_path_index[r_1]][j] = path[remain_path_index[r_2]][j];
                path[remain_path_index[r_2]][j] = tmp;
                changed_record[j] = 1;
            }

            for (j = 0; j <= data_size; j++)
            {
                if (changed_record[j] == 0)
                {
                    flag = 1;
                    tmp = path[remain_path_index[r_1]][j];
                    while (flag)
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
            }

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
        //////////////////doing crossover//////////////////////////////
    }
}

void mutation()
{
}

void fitness()
{
}

int main()
{
    int i, j;
    srand(time(NULL));

    readfile();

    vector<vector<int>> num_path;
    num_path.resize(num_autosome);
    init(num_path);

    // for (i = 0; i < num_autosome; i++)
    // {
    //     cout << "path " << i << endl;
    //     for (j = 0; j < data_size; j++)
    //         cout << num_path[i][j] << "->";
    //     cout << endl
    //          << endl;
    // }

    // cout << "////////////////" << endl;

    int itteration = 0;
    while (itteration <= 0)
    {
        crossover(num_path);

        // for (i = 0; i < num_autosome; i++)
        // {
        //     cout << "path " << i << endl;
        //     for (j = 0; j < data_size; j++)
        //         cout << num_path[i][j] << "->";
        //     cout << endl
        //          << endl;
        // }
        itteration++;
    }

    system("pause");
    return 0;
}