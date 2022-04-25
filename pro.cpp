/**
 * @brief      PRL project 2
 * @author     Michal Sova (xsovam00@stud.fit.vutbr.cz)
 * @date       2022
 * @file pro.cpp
 */
#include "pro.h"

Edge::Edge(const char &v1, const char &v2, const bool &fe, const int &rank, const int &world_size){
    c_v1 = v1;
    c_v2 = v2;
    c_rank = rank;
    c_fe = fe;
    c_world_size = world_size;
    if (fe) {
        c_weight = 1;
    }
}

void Edge::create_etour(){

    // gather nodes of other edges
    vector<char> v1nodes(c_world_size);
    vector<char> v2nodes(c_world_size);
    MPI_Allgather(&c_v1, 1, MPI_CHAR, &v1nodes[0], 1, MPI_CHAR, MPI_COMM_WORLD);
    MPI_Allgather(&c_v2, 1, MPI_CHAR, &v2nodes[0], 1, MPI_CHAR, MPI_COMM_WORLD);
    
    // root (last edge in etour)
    if(c_rank == c_world_size / 2 + 1){
        c_etour = c_rank;
        return;
    }
    std::vector<char> next_edges;

    // collect possible next edges to vector
    for (int i = 0; i < v1nodes.size(); ++i) {
        if(v1nodes[i] == c_v2){
            next_edges.push_back(i);
        }
    }

    // only one next path (leaf node)
    if(next_edges.size() == 1){
        c_etour = next_edges.front();
    }
    // forward edge -> first left edge
    else if(c_rank < c_world_size / 2){
        c_etour = next_edges.front();
    }
    // not leaf node -> edge must be diferent (e. g. E1=(A,B); E2=(B,A); E7=(B,D) => etour(E1) = E7)
    else if (v2nodes[next_edges[1]] == c_v1){
        c_etour = next_edges.back();
    }
    else {
        c_etour = next_edges[1];
    }
}

void Edge::suffix_sum(){
    // gather other weights and etours
    vector<int> weights(c_world_size);
    vector<int> etours(c_world_size);
    MPI_Allgather(&c_weight, 1, MPI_INT, &weights[0], 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgather(&c_etour, 1, MPI_INT, &etours[0], 1, MPI_INT, MPI_COMM_WORLD);

    // last edge => 0
    c_weight = (c_etour == c_rank) ? 0 : c_weight;
    
    for (int k = 0;k <= ceil(log(c_world_size));++k){
        c_weight += weights[etours[c_rank]];
        c_etour = etours[etours[c_rank]];
        MPI_Allgather(&c_weight, 1, MPI_INT, &weights[0], 1, MPI_INT, MPI_COMM_WORLD);
        MPI_Allgather(&c_etour, 1, MPI_INT, &etours[0], 1, MPI_INT, MPI_COMM_WORLD);
    }
    c_weight += weights.back();
}

void Edge::preorder(const int nodes_count){
    // get edge order if it is forward edge
    int preorder_rank = - 1;
    if(c_fe){
        preorder_rank = nodes_count - c_weight + 1;
    }

    if (c_rank == 0){
        // gather other edge orders and their nodes 
        vector<int> pre_r(c_world_size);
        vector<char> pre_v(c_world_size);    
        MPI_Gather(&preorder_rank, 1, MPI_INT, &pre_r[0], 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Gather(&c_v2, 1, MPI_CHAR, &pre_v[0], 1, MPI_CHAR, 0, MPI_COMM_WORLD);
        
        // print first two nodes
        cout << c_v1 << c_v2;

        // search for the rest
        for (int order = 3; order <= nodes_count; ++order){
            // find index and print node at correct index
            int index = find(pre_r, order);
            if (index != -1){
                cout << pre_v[index];
            }
        }
        cout << endl;
    }
    else{
        MPI_Gather(&preorder_rank, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Gather(&c_v2, 1, MPI_CHAR, NULL, 0, MPI_CHAR, 0, MPI_COMM_WORLD);
    }
    
}

int Edge::find(const vector<int> &vec, const int &val){
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == val){
            return i;
        }
    }
    return -1;
}


Edge::~Edge() {}

void Edge::print_edge(){
    cout << "E" << c_rank << " = (" << c_v1 << ", " << c_v2 << ") next E" << c_etour << endl;
}

int main(int argc, char** argv) {
    string nodes = argv[1];

    MPI_Init(&argc, &argv);

    int world_size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    bool fe = false;

    
    char v1, v2;
    if (rank < nodes.size() - 1){
        v1 = nodes[rank / 2];
        v2 = nodes[rank + 1];
        fe = true;
    }
    else {
        int tmp_r = rank - nodes.size() + 1;
        v1 = nodes[tmp_r + 1];
        v2 = nodes[tmp_r / 2];
    }
    Edge e(v1, v2, fe, rank, world_size);
    e.create_etour();
    e.suffix_sum();
    e.preorder(nodes.size());


    MPI_Finalize();
}
