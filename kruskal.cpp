#include "graph_algo.hpp"

algo::Kruskal::Kruskal(std::string s):BaseAlgo2(s,KRUSKAL){
    mst_wt = 0;
}

int algo::Kruskal::get_mst_value(){
    return mst_wt;
}

std::shared_ptr<data_struct::Node> algo::Kruskal::get_ancestor(std::shared_ptr <data_struct::Node> node){
    if(node->get_prev() == nullptr){
        return  node;
    }
    return get_ancestor(node->get_prev());
}

std::vector<std::shared_ptr<data_struct::Edge>> algo::Kruskal::generate_mst(){
    struct my_comparator{
        bool operator()(const std::shared_ptr<data_struct::Edge>& e1,const std::shared_ptr<data_struct::Edge>& e2 ){
            return e1->get_value() < e2->get_value();
        }
    };
    std::sort(undirected_edge_list.begin(), undirected_edge_list.end(), my_comparator());
    std::vector<std::shared_ptr<data_struct::Edge>> rv;
    for(int i=0;i<undirected_edge_num;i++){
        std::shared_ptr<data_struct::Edge> e = undirected_edge_list[i];
        std::shared_ptr<data_struct::Node> u = e->get_src();
        std::shared_ptr<data_struct::Node> v = e->get_dst();
        std::shared_ptr<data_struct::Node> u_a = get_ancestor(u);
        std::shared_ptr<data_struct::Node> v_a = get_ancestor(v);
        if (u_a != v_a){
            mst_wt += e->get_value();
            v_a->set_prev(u_a);
            rv.push_back(e);
        }
    }
    this->reset();
    return rv;
}