#include "graph_algo.hpp"

void algo::KSP::set_judge(std::string j) {
    check::exception_checker::check_judge_value(j);
    judge = j;
}
algo::KSP::KSP(std::string s) {
    judge = s;
}
void algo::KSP::add_edge(std::shared_ptr <data_struct::Edge> edge) {
    std::shared_ptr<data_struct::Node> src = edge->get_src();
    std::shared_ptr<data_struct::Node> dst = edge->get_dst();
    // next hop and cost will be stored in adj list
    undirected_adj_list[src].push_back(std::make_pair(dst, edge->get_value()));
    undirected_adj_list[dst].push_back(std::make_pair(src, edge->get_value()));
    directed_adj_list[src].push_back(std::make_pair(dst, edge->get_value()));
}

std::vector<std::shared_ptr<data_struct::Path>> algo::KSP::k_shortest_path(std::shared_ptr <data_struct::Node> src,
                                                                           std::shared_ptr <data_struct::Node> dst,
                                                                           int k) {
    std::vector<std::shared_ptr<data_struct::Path>> rv;
    struct my_comparator{
        bool operator() (const std::shared_ptr<const data_struct::Path> & p1, const std::shared_ptr<const data_struct::Path>& p2){
            return  p1->get_total() > p2->get_total();
        }
    };
    std::priority_queue< std::shared_ptr<data_struct::Path>, std::vector<std::shared_ptr<data_struct::Path>>, my_comparator >pq;
    std::shared_ptr<data_struct::Path> p (new data_struct::Path());
    p->add_to_path(src);
    pq.push(p);
    while(!pq.empty()){
        std::shared_ptr<data_struct::Path> cur = pq.top();
        pq.pop();
        std::shared_ptr<data_struct::Node> s = nullptr;

        s = cur->get_last_one();
        if (s == dst){
            rv.push_back(cur);
            k -= 1;
            if (k == 0){
                break;
            }else{
                continue;
            }
        }

        std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>::iterator i;
        std::unordered_map<std::shared_ptr<data_struct::Node>,std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>> adj_list;
        if (judge.compare(DIRECTED) == 0){
            adj_list = directed_adj_list;
        }else{
            adj_list = undirected_adj_list;
        }
        for (i = adj_list[s].begin(); i != adj_list[s].end(); ++i)
        {
            std::shared_ptr<data_struct::Path> new_path (new data_struct::Path());
            for (std::shared_ptr<data_struct::Node> node: cur->get_path_list()){
                new_path->add_to_path(node);
            }
            std::shared_ptr<data_struct::Node> d = i->first;
            new_path->add_to_path(d);
            new_path->set_total(cur->get_total() + i->second);
            pq.push(new_path);
        }
    }
    return rv;
}