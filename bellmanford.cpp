#include "graph_algo.hpp"

algo::BellManFord::BellManFord(std::string s):BaseAlgo2(s,"bellmanford"){
    cycle = false;
}

bool algo::BellManFord::cycle_exist() {
    return cycle;
}

std::shared_ptr<data_struct::Path> algo::BellManFord::shortest_path(std::shared_ptr <data_struct::Node> src,
                                                                    std::shared_ptr <data_struct::Node> dst) {
    std::map<std::shared_ptr<data_struct::Node>,int> dist;
    for (std::shared_ptr<data_struct::Node> node : this->node_list){
        dist[node] = int_max;
    }
    dist[src] = 0;
    int num_edge;
    std::vector<std::shared_ptr<data_struct::Edge>> edge_object_lists;
    if(judge.compare("directed") == 0){
        num_edge = directed_edge_num;
        edge_object_lists = directed_edge_list;
    }else{
        num_edge = undirected_edge_num;
        edge_object_lists = undirected_edge_list;
    }

    for(int i=0; i< node_num-1; ++i) {
        for (int j = 0; j < num_edge; ++j) {
            std::shared_ptr<data_struct::Node> s =edge_object_lists[j]->get_src();
            std::shared_ptr<data_struct::Node> d =edge_object_lists[j]->get_dst();
            if (dist[s] != int_max &&
                dist[d] > dist[s] +edge_object_lists[j]->get_value()){
                dist[d] = dist[s] +edge_object_lists[j]->get_value();
                d->set_prev(s);
            }
        }
    }
    // check if the negative circle exist
    for(int i=0; i<num_edge; ++i) {
        std::shared_ptr<data_struct::Node> s =edge_object_lists[i]->get_src();
        std::shared_ptr<data_struct::Node> d =edge_object_lists[i]->get_dst();
        if (dist[s] != int_max && dist[d] > dist[s] +edge_object_lists[i]->get_value()) {
            cycle = true;
            std::shared_ptr<data_struct::Path> rv(new data_struct::Path());
            this->reset();
            return rv;
        }
    }
    std::shared_ptr<data_struct::Path> rv(new data_struct::Path(dst,dist[dst]));
    this->reset();
    return rv;
}