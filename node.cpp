# include "graph_algo.hpp"

data_struct::Node::Node(std::string l){
    prev = nullptr;
    label = l;
}

void data_struct::Node::set_label(std::string l){
    label = l;
}

std::string data_struct::Node::get_label(){
    return  label;
}

std::shared_ptr<data_struct::Node> data_struct::Node::get_prev(){
    return prev;
}

void data_struct::Node::set_prev(std::shared_ptr<data_struct::Node> p){
    prev = p;
}


std::ostream& data_struct::operator<<(std::ostream &strm, const std::shared_ptr<data_struct::Node> n){
    if (n == nullptr){
        return strm << "nullptr";
    }
    return strm << n->get_label();
}