#include "graph_algo.hpp"

algo::Prim::Prim(std::string s):BaseAlgo(s,PRIM){
    mst_wt = 0;
}

int algo::Prim::get_mst_value() {
    return mst_wt;
}

std::vector<std::shared_ptr<data_struct::Edge>> algo::Prim::generate_mst(){
    std::shared_ptr <data_struct::Node> src = node_list[0];
    std::unordered_map<std::shared_ptr<data_struct::Node>,bool> visited;
    std::unordered_map<std::shared_ptr<data_struct::Node>,int> dist;
    typedef std::pair<int, std::shared_ptr<data_struct::Node>> my_pair;
    struct my_comparator{
        bool operator() (const std::pair<int, std::shared_ptr<const data_struct::Node>>& p1, const std::pair<int, std::shared_ptr<const data_struct::Node>>& p2){
            return  p1.first > p2.first;
        }
    };
    std::priority_queue< my_pair, std::vector<my_pair>, my_comparator >pq;
    for (std::shared_ptr<data_struct::Node> node : node_list){
        visited[node] = false;
        dist[node] = int_max;
    }
    pq.push(std::make_pair(0, src));
    dist[src] = 0;
    while(!pq.empty()){
        std::shared_ptr<data_struct::Node> s = pq.top().second;
        pq.pop();
        if (visited[s]){
            continue;
        }
        visited[s] = true;
        typename std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>::iterator i;
        for (i = undirected_adj_list[s].begin(); i != undirected_adj_list[s].end(); ++i)
        {
            std::shared_ptr<data_struct::Node> d = i->first;
            int weight = i->second;
            if (!visited[d] && dist[d] > weight){
                dist[d] = weight;
                pq.push(std::make_pair(dist[d],d));
                d->set_prev(s);
            }
        }
    }
    std::vector<std::shared_ptr<data_struct::Edge>> rv;
    for (std::shared_ptr<data_struct::Node> node : node_list){
        if (node->get_prev()){
            std::shared_ptr<data_struct::Edge> e(new data_struct::Edge(node->get_prev(),node,dist[node]));
            rv.push_back(e);
            mst_wt += dist[node];
        }
    }
    this->reset();
    return rv;
}