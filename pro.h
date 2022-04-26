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
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  v1          start node
     * @param[in]  v2          end node
     * @param[in]  fe          forward edge
     * @param[in]  rank        The rank of process
     * @param[in]  world_size  number of processes
     */
    Edge(const char &v1, const char &v2, const bool &fe, const int &rank, const int &world_size);
    
    /**
     * @brief      Adds next edge in etour.
     */
    void create_etour();
    
    /**
     * @brief      calculates weight for edge
     */
    void suffix_sum();
    
    /**
     * @brief      correction of weights and print of nodes in preorder
     */
    void print_preorder();
    
    /**
     * @brief      Searches for the first match of value @val in vector @vec.
     *
     * @param[in]  vec   The vector
     * @param[in]  val   The searched value
     *
     * @returns    index of @val in @vec
     * @returns    -1 if not found 
     */
    int find(const vector<int> &vec, const int &val);
    ~Edge();

    // debug function
    void print_edge();

private:
    char c_v1; // start node
    char c_v2; // end node
    int c_rank; // rank of process (index of edge)
    int c_world_size; // number of edges (processes)
    bool c_fe; // forward edge
    int c_weight = 0; // weight of the edge
    int c_etour; // neghbor (next edge in etour)
};
