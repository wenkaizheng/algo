#include "graph_algo.hpp"

algo::FindCycle::FindCycle(std::string s):BaseAlgo(s,FINDCYCLE) {}

bool algo::FindCycle::check_cycle_directed() {
    std::map<std::shared_ptr<data_struct::Node>,bool> visited;
    std::map<std::shared_ptr<data_struct::Node>,bool> rec_stack;
    for (std::shared_ptr<data_struct::Node> node : this->node_list){
        visited[node] = false;
        rec_stack[node] = false;
    }
    for(std::shared_ptr<data_struct::Node> node : this->node_list){
        if (!visited[node]){
            if (check_cycle_directed(node,visited,rec_stack)){
                return true;
            }
        }
    }
    return false;
}

bool algo::FindCycle::check_cycle_directed(std::shared_ptr <data_struct::Node> node,
                                           std::map<std::shared_ptr<data_struct::Node>, bool> &visited,
                                           std::map<std::shared_ptr<data_struct::Node>, bool> &rec_stack) {
    visited[node] = true;
    rec_stack[node] = true;
    typename std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>::iterator i;
    for (i = directed_adj_list[node].begin(); i != directed_adj_list[node].end(); ++i)
    {
        std::shared_ptr<data_struct::Node> d = i->first;
        if(!visited[d]){
            if (check_cycle_directed(d,visited,rec_stack)){
                return true;
            }
        }else if (rec_stack[d]){
            return true;
        }
    }
    rec_stack[node] = false;
    return false;
}

bool algo::FindCycle::check_cycle_undirected(){
    std::map<std::shared_ptr<data_struct::Node>,bool> visited;
    for (std::shared_ptr<data_struct::Node> node : this->node_list){
        visited[node] = false;
    }
    for(std::shared_ptr<data_struct::Node> node : this->node_list){
        if (!visited[node]){
            if (check_cycle_undirected(node,visited, nullptr)){
                return true;
            }
        }
    }
    return false;
}

bool algo::FindCycle::check_cycle_undirected(std::shared_ptr <data_struct::Node> node,
                                             std::map<std::shared_ptr<data_struct::Node>, bool> &visited,
                                             std::shared_ptr <data_struct::Node> parent){
    visited[node] = true;
    typename std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>::iterator i;
    for (i = undirected_adj_list[node].begin(); i != undirected_adj_list[node].end(); ++i)
    {
        std::shared_ptr<data_struct::Node> d = i->first;
        if(!visited[d]){
            if (check_cycle_undirected(d,visited,node)){
                return true;
            }
        }else if (parent!=d){
            return true;
        }
    }
    return false;
}

bool algo::FindCycle::exist_cycle(){
    if(this->judge.compare("undirected") == 0){
        return check_cycle_undirected();
    }else if (this->judge.compare("directed") == 0){
        return check_cycle_directed();
    }else{
        return false;
    }
}
