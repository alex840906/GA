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

using namespace std;
vector<vector<string>> eil;

int main()
{
    vector<int> buffer;
    string line, tmp, a;
    int i = 0;

    eil.resize(data_size);
    srand(time(NULL));
    fstream file;
    file.open("GA/eil51.txt", ios::in);

    while (getline(file, line))
    {
        stringstream t_line(line);
        while (getline(t_line, tmp, ' '))
            eil[i].push_back(tmp);
        i++;
    }
      

    system("pause");
    return 0;
}