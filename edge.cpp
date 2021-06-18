# include "graph_algo.hpp"

data_struct::Edge::Edge(std::shared_ptr <data_struct::Node> src, std::shared_ptr <data_struct::Node> dst, int w) {
    s = src;
    d = dst;
    weight = w;
}

int data_struct::Edge::get_value(){
    return weight;
}

void data_struct::Edge::set_value(int w){
    weight = w;
}

std::shared_ptr<data_struct::Node> data_struct::Edge::get_src(){
    return s;
}

std::shared_ptr<data_struct::Node> data_struct::Edge::get_dst(){
    return d;
}

std::ostream& data_struct::operator<<(std::ostream &strm, const std::shared_ptr<data_struct::Edge> e){
    std::string rv = e->get_src()->get_label() + "-" + e->get_dst()->get_label() + " " + std::to_string(e->get_value());
    return strm << rv;
}
