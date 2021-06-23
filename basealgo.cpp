#include "graph_algo.hpp"

algo::BaseAlgo::BaseAlgo(std::string s, std::string n){
    name = n;
    check::exception_checker::check_judge_value(s);
    check::exception_checker::check_special_judge_value(s,n);
    judge = s;
}

void algo::BaseAlgo::reset(){
    for (std::shared_ptr<data_struct::Node> node : node_list){
        node->set_prev(nullptr);
    }
}
void algo::BaseAlgo::set_judge(std::string j) {
    check::exception_checker::check_judge_value(j);
    judge = j;
}
void algo::BaseAlgo::add_edge(std::shared_ptr <data_struct::Edge> edge){
    std::shared_ptr<data_struct::Node> src = edge->get_src();
    std::shared_ptr<data_struct::Node> dst = edge->get_dst();
    // next hop and cost will be stored in adj list
    directed_adj_list[src].push_back(std::make_pair(dst, edge->get_value()));
    undirected_adj_list[src].push_back(std::make_pair(dst, edge->get_value()));
    undirected_adj_list[dst].push_back(std::make_pair(src, edge->get_value()));

    if (std::find(node_list.begin(), node_list.end(), src) == node_list.end()){
        node_list.push_back(src);
    }
    if (std::find(node_list.begin(), node_list.end(), dst) == node_list.end()){
        node_list.push_back(dst);
    }
}