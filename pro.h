/**
 * @brief      PRL project 2 header file
 * @author     Michal Sova (xsovam00@stud.fit.vutbr.cz)
 * @date       2022
 * @file pro.h
 */
#include <iostream>
#include <vector>
#include <mpi.h>
#include <math.h>

using namespace std;
MPI_Status status;

class Edge {
public:
    Edge(const char &v1, const char &v2, const bool &fe, const int &rank, const int &world_size);
    void create_etour();
    void suffix_sum();
    void print_preorder();
    int find(const vector<int> &vec, const int &val);
    ~Edge();

    // debug
    void print_edge();

private:
    char c_v1;
    char c_v2;
    int c_rank;
    int c_world_size;
    bool c_fe;
    int c_weight = 0;
    int c_etour;
};
