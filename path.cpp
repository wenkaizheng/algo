#include "graph_algo.hpp"

data_struct::Path::Path() {
    total = 0;
}

data_struct::Path::Path(std::shared_ptr <data_struct::Node> node, int t){
    set_total(t);
    while(node!= nullptr){
        add_to_path(node);
        node = node->get_prev();
    }
    std::reverse(path_list.begin(),path_list.end());
}

void data_struct::Path::set_total(int t){
    total = t;
}

int data_struct::Path::get_total()const{
    return total;
}

void data_struct::Path::add_to_path(std::shared_ptr <data_struct::Node> n){
    path_list.push_back(n);
}

std::vector<std::shared_ptr<data_struct::Node>> data_struct::Path::get_path_list(){
    return path_list;
}

std::shared_ptr<data_struct::Node> data_struct::Path::get_last_one(){
    return path_list[path_list.size()-1];
}

std::ostream& data_struct::operator<<(std::ostream &strm, const std::shared_ptr<data_struct::Path> p){
    std::string rv  = "";
    for(std::shared_ptr<data_struct::Node> i : p->get_path_list()){
        rv += i->get_label() + "->";
    }
    rv = rv.substr(0,rv.size()-2);
    rv += " with cost " + std::to_string(p->get_total());
    return strm << rv;
}