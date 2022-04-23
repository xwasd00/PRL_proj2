/**
 * @brief      PRL project 2
 * @author     Michal Sova (xsovam00@stud.fit.vutbr.cz)
 * @date       2022
 * @file pro.cpp
 */
#include "pro.h"
#include <unistd.h>


class Edge {
public:
    Edge(const char &v1, const char &v2, const int &rank);
    ~Edge();

    // debug
    void print_edge();

private:
    char c_v1;
    char c_v2;
    int c_rank;
};

Edge::Edge(const char &v1, const char &v2, const int &rank){
    c_v1=v1;
    c_v2=v2;
    c_rank=rank;
}
Edge::~Edge() {}

void Edge::print_edge(){
    cout << "E" << c_rank << " = (" << c_v1 << ", " << c_v2 << ")" << endl;
}

int main(int argc, char** argv) {
    string nodes = argv[1];

    MPI_Init(&argc, &argv);

    int world_size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    
    char v1, v2;
    if (rank < nodes.size() - 1){
        v1 = nodes[rank / 2];
        v2 = nodes[rank + 1];
    }
    else {
        int tmp_r = rank - nodes.size() + 1;
        v1 = nodes[tmp_r + 1];
        v2 = nodes[tmp_r / 2];
    }
    Edge e(v1, v2, rank);
    for(int i = 0; i < world_size; ++i){
        if (rank == i){
            e.print_edge();
        }
        else {
            sleep(1);
        }
    }


    MPI_Finalize();
}
