#include "graph_algo.hpp"

algo::MaxFlowEdgeObject::MaxFlowEdgeObject(int w, int uw, bool u):weight(w),unchanged_weight(uw),undo(u) {}
algo::EdmondsKarp::EdmondsKarp(std::string s) {
    judge = s;
}
void algo::EdmondsKarp::set_judge(std::string j) {
    check::exception_checker::check_judge_value(j);
    judge = j;
    max_flow = 0;
}

int algo::EdmondsKarp::get_max_flow() {
    return max_flow;
}
void algo::EdmondsKarp::reset(){
    for(std::shared_ptr<data_struct::Node> node:node_list){
        node->set_prev(nullptr);
    }
}
void algo::EdmondsKarp::add_edge(std::shared_ptr <data_struct::Edge> edge) {
    std::shared_ptr<data_struct::Node> src = edge->get_src();
    std::shared_ptr<data_struct::Node> dst = edge->get_dst();
    int edge_value = edge->get_value();

    // undo is normal since not directed
    undirected_adj_list[src][dst] = algo::MaxFlowEdgeObject (edge_value,edge_value, false);
    undirected_adj_list[dst][src] = algo::MaxFlowEdgeObject (edge_value,edge_value, false);

    // we need undo as 0 if directed
    directed_adj_list[src][dst] =  algo::MaxFlowEdgeObject (edge_value,edge_value, false);;
    directed_adj_list[dst][src] =  algo::MaxFlowEdgeObject (0,0,true);

    node_list.push_back(src);
    node_list.push_back(dst);
}

bool algo::EdmondsKarp::bfs(std::shared_ptr <data_struct::Node> src,
                            std::shared_ptr <data_struct::Node> dst) {
    std::unordered_map<std::shared_ptr<data_struct::Node>,bool> visited;
    std::queue<std::shared_ptr<data_struct::Node>> queue;
    for (std::shared_ptr<data_struct::Node> node : this->node_list){
        visited[node] = false;
    }
    queue.push(src);
    std::unordered_map<std::shared_ptr<data_struct::Node>,MaxFlowEdgeObject>::iterator i;
    std::unordered_map<std::shared_ptr<data_struct::Node>, std::unordered_map<std::shared_ptr<data_struct::Node>,MaxFlowEdgeObject>> adj_list;
    if(judge.compare(DIRECTED) == 0){
        adj_list = directed_adj_list;
    }else{
        adj_list = undirected_adj_list;
    }
    while(!queue.empty()){
        std::shared_ptr<data_struct::Node> cur = queue.front();
        queue.pop();
        visited[cur] = true;
        for(i = adj_list[cur].begin(); i != adj_list[cur].end(); ++i){
            std::shared_ptr<data_struct::Node> d = i->first;
            int weight = i->second.weight;
            if(!visited[d] && weight>0){
                d->set_prev(cur);
                if(d == dst){
                    return true;
                }
                queue.push(d);
            }
        }
    }
    return false;
}
std::vector<std::shared_ptr<data_struct::Edge>> algo::EdmondsKarp::generate_max_flow(
        std::shared_ptr <data_struct::Node> src, std::shared_ptr <data_struct::Node> dst) {
    std::unordered_map<std::shared_ptr<data_struct::Node>, std::unordered_map<std::shared_ptr<data_struct::Node>,MaxFlowEdgeObject>>* adj_list;
   // std::unordered_map<std::shared_ptr<data_struct::Node>, std::unordered_map<std::shared_ptr<data_struct::Node>,MaxFlowEdgeObject>> copy_adj_list;
    if(judge.compare(DIRECTED) == 0){
        adj_list = &directed_adj_list;
        //copy_adj_list = directed_adj_list_copy;
    }else{
        adj_list = &undirected_adj_list;
       // copy_adj_list = undirected_adj_list_copy;
    }
    while(bfs(src,dst)){
        std::shared_ptr<data_struct::Node> cur = dst;
        int min_edge = int_max;
        while(cur->get_prev()){
            std::shared_ptr<data_struct::Node> parent = cur->get_prev();
            //std::cout << parent << " " << cur << " " << adj_list[parent][cur] << std::endl;
            min_edge = min_edge < (*adj_list)[parent][cur].weight? min_edge: (*adj_list)[parent][cur].weight;
            cur = parent;
        }
        max_flow += min_edge;
        cur = dst;
        while(cur->get_prev()){
            std::shared_ptr<data_struct::Node> parent = cur->get_prev();
            (*adj_list)[parent][cur].weight -= min_edge;
            (*adj_list)[cur][parent].weight += min_edge;
            cur = parent;
        }
        this->reset();
    }
    std::unordered_map<std::shared_ptr<data_struct::Node>, std::unordered_map<std::shared_ptr<data_struct::Node>,MaxFlowEdgeObject>>::iterator i;
    std::unordered_map<std::shared_ptr<data_struct::Node>,MaxFlowEdgeObject>::iterator j;
    std::vector<std::shared_ptr<data_struct::Edge>> rv;
    for(i = (*adj_list).begin();i!=(*adj_list).end();++i){
        std::shared_ptr<data_struct::Node> cur = i->first;
        for(j = i->second.begin();j!= i->second.end();j++){
            std::shared_ptr<data_struct::Node> next = j->first;
            int value = j->second.weight;
            int original = j->second.unchanged_weight;
            bool undo = j->second.undo;
            if (!undo && original>value){
                std::shared_ptr<data_struct::Edge> e(new data_struct::Edge(cur,next,original-value));
                rv.push_back(e);
            }
        }
    }
    this->reset();
    return rv;
}