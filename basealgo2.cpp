#include "graph_algo.hpp"

algo::BaseAlgo2::BaseAlgo2(std::string s, std::string n) {
    name = n;
    check::exception_checker::check_judge_value(s);
    check::exception_checker::check_special_judge_value(s,n);
    directed_edge_num = 0;
    undirected_edge_num =0;
    node_num = 0;
    judge = s;
}

void algo::BaseAlgo2::set_judge(std::string j) {
    check::exception_checker::check_judge_value(j);
    judge = j;
}

void algo::BaseAlgo2::reset() {
    for (std::shared_ptr<data_struct::Node> node : node_list){
        node->set_prev(nullptr);
    }
}

void algo::BaseAlgo2::add_edge(std::shared_ptr <data_struct::Edge> edge) {
    if (name.compare(BELLMANFORD) == 0 && edge->get_value()<0 && judge == UNDIRECTED){
        throw std::runtime_error("Invalid value please use positive edge for undirected bellmanford");
    }
    std::shared_ptr<data_struct::Node> src = edge->get_src();
    std::shared_ptr<data_struct::Node> dst = edge->get_dst();
    directed_edge_list.push_back(edge);
    undirected_edge_list.push_back(edge);
    std::shared_ptr<data_struct::Edge> e(new data_struct::Edge(dst,src,edge->get_value()));
    undirected_edge_list.push_back(e);
    directed_edge_num += 1;
    undirected_edge_num +=2;
    if (std::find(node_list.begin(),node_list.end(),src) == node_list.end()){
        node_num += 1;
        node_list.push_back(src);
    }
    if (std::find(node_list.begin(),node_list.end(),dst) == node_list.end()){
        node_num += 1;
        node_list.push_back(dst);
    }
}