/**
 * @brief      PRL project 2
 * @author     Michal Sova (xsovam00@stud.fit.vutbr.cz)
 * @date       2022
 * @file pro.cpp
 */
#include "pro.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
        string s;
        cin >> s;
        cout << "rank: " << rank << ", world_size: " << world_size << ", string: " << s << endl;
    }


    MPI_Finalize();
}
