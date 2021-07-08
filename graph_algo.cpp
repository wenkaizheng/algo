#include "graph_algo.hpp"

std::string DIRECTED = "directed";
std::string UNDIRECTED = "undirected";
std::string DIJKSTRA = "dijkstra";
std::string BELLMANFORD = "bellmanford";
std::string KSP = "ksp";
std::string FINDCYCLE = "find_cycle";
std::string PRIM = "prim";
std::string KRUSKAL = "kruskal";
std::string EDMONDSKARP = "enmondskarp";
void check::exception_checker::check_special_judge_value(std::string judge, std::string name) {
    if (judge.compare(DIRECTED) == 0){
        if (name.compare(PRIM) == 0 or name.compare(KRUSKAL) == 0 ){
            throw std::runtime_error("Invalid value please use undirected for prim and kruskal");
        }
    }
}

void check::exception_checker::check_judge_value(std::string judge) {

    if (judge.compare(UNDIRECTED) == 0){
        return;
    }else if (judge.compare(DIRECTED) == 0){
        return;
    }else{
        throw std::runtime_error("Invalid value please use undirected or directed");
    }
}
