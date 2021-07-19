#include "graph_algo.hpp"

algo::Dijkstra::Dijkstra(std::string s):BaseAlgo(s,DIJKSTRA) {}

std::shared_ptr<data_struct::Path> algo::Dijkstra::shortest_path(std::shared_ptr <data_struct::Node> src,
                                                                 std::shared_ptr <data_struct::Node> dst) {
    // cost and next hop will be stored in the min heap
    typedef std::pair<int, std::shared_ptr<data_struct::Node>> my_pair;
    struct my_comparator{
        bool operator() (const std::pair<int, std::shared_ptr<const data_struct::Node>>& p1, const std::pair<int, std::shared_ptr<const data_struct::Node>>& p2){
            return  p1.first > p2.first;
        }
    };
    std::priority_queue< my_pair, std::vector<my_pair>, my_comparator >pq;
    std::unordered_map<std::shared_ptr<data_struct::Node>,int> dist;
    pq.push(std::make_pair(0, src));
    for (std::shared_ptr<data_struct::Node> node : this->node_list){
        dist[node] = int_max;
    }
    dist[src] = 0;
    while(!pq.empty()){
        std::shared_ptr<data_struct::Node> s = pq.top().second;
        pq.pop();
        if (s == dst){
            break;
        }
        std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>::iterator i;
        std::unordered_map<std::shared_ptr<data_struct::Node>,std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>> adj_list;
        if(judge.compare(DIRECTED) == 0){
            adj_list = directed_adj_list;
        }else{
            adj_list = undirected_adj_list;
        }
        for (i = adj_list[s].begin(); i != adj_list[s].end(); ++i)
        {
            std::shared_ptr<data_struct::Node> d = i->first;
            int weight = i->second;
            if (dist[s] + weight < dist[d]){
                dist[d] = dist[s] + weight;
                d->set_prev(s);
                pq.push(std::make_pair(dist[d],d));
            }
        }
    }
    std::shared_ptr<data_struct::Path> rv(new data_struct::Path(dst,dist[dst]));
    this->reset();
    return rv;
}