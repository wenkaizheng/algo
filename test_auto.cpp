#include "graph_algo.hpp"

int main(){

    node_ptr a0(new data_struct::Node("0"));
    node_ptr a1(new data_struct::Node("1"));
    node_ptr a2(new data_struct::Node("2"));
    node_ptr a3(new data_struct::Node("3"));
    node_ptr a4(new data_struct::Node("4"));
    node_ptr a5(new data_struct::Node("5"));

    // test edge for most cases
    edge_ptr e0(new data_struct::Edge(a0,a1,5));
    edge_ptr e1(new data_struct::Edge(a0,a3,2));
    edge_ptr e2(new data_struct::Edge(a3,a1,2));
    edge_ptr e3(new data_struct::Edge(a1,a4,1));
    edge_ptr e4(new data_struct::Edge(a1,a2,5));
    edge_ptr e5(new data_struct::Edge(a4,a2,1));
    edge_ptr e6(new data_struct::Edge(a0,a2,0));
    edge_ptr e7(new data_struct::Edge(a2,a0,0));
    edge_ptr e8(new data_struct::Edge(a2,a3,0));
    edge_ptr e9(new data_struct::Edge(a3,a3,0));
    edge_ptr e10(new data_struct::Edge(a3,a4,0));


    // egde for max flow testing
    edge_ptr edge0(new data_struct::Edge(a0,a1,16));
    edge_ptr edge1(new data_struct::Edge(a0,a2,13));
    edge_ptr edge2(new data_struct::Edge(a2,a1,4));
    edge_ptr edge3(new data_struct::Edge(a1,a2,10));
    edge_ptr edge4(new data_struct::Edge(a1,a3,12));
    edge_ptr edge5(new data_struct::Edge(a3,a2,9));
    edge_ptr edge6(new data_struct::Edge(a2,a4,14));
    edge_ptr edge7(new data_struct::Edge(a4,a3,7));
    edge_ptr edge8(new data_struct::Edge(a3,a5,20));
    edge_ptr edge9(new data_struct::Edge(a4,a5,4));


    //negative cycle one for BellManFord
//    node_ptr a5(new data_struct::Node("5"));
    node_ptr a6(new data_struct::Node("6"));
    node_ptr a7(new data_struct::Node("7"));
    edge_ptr e11(new data_struct::Edge(a5,a6,3));
    edge_ptr e12(new data_struct::Edge(a6,a7,-6));
    edge_ptr e13(new data_struct::Edge(a7,a5,2));
    try{
        std::shared_ptr<algo::Dijkstra> de(new algo::Dijkstra(""));
    }catch (std::exception& e){
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    std::shared_ptr<algo::Dijkstra> d(new algo::Dijkstra(UNDIRECTED));
    d->add_edge(e0);
    d->add_edge(e1);
    d->add_edge(e2);
    d->add_edge(e3);
    d->add_edge(e4);
    d->add_edge(e5);
    path_ptr path = d->shortest_path(a0,a2);

    std::cout << path << std::endl;
    std::cout << "Undirected Dijkstra done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;

    d->set_judge(DIRECTED);

    path = d->shortest_path(a0,a2);

    std::cout << path << std::endl;
    std::cout << "Directed Dijkstra done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;



    std::shared_ptr<algo::BellManFord> b (new algo::BellManFord(UNDIRECTED));
    b->add_edge(e0);
    b->add_edge(e1);
    b->add_edge(e2);
    b->add_edge(e3);
    b->add_edge(e4);
    b->add_edge(e5);
    path_ptr path1 = b->shortest_path(a0,a2);

    std::cout << path1  << std::endl;
    std::cout << b->cycle_exist() << "\n";
    std::cout << "Undirected BellmanFord done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;

    b->set_judge(DIRECTED);

    path1 = b->shortest_path(a0,a2);

    std::cout << path1  << std::endl;
    std::cout << b->cycle_exist() << "\n";
    std::cout << "Directed BellmanFord done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;



    std::shared_ptr<algo::BellManFord> b1 (new algo::BellManFord(DIRECTED));
    b1->add_edge(e11);
    b1->add_edge(e12);
    b1->add_edge(e13);
    path_ptr path2 = b1->shortest_path(a5,a7);

    std::cout << "Empty path " << path2  << std::endl;
    std::cout << b1->cycle_exist() << "\n";
    std::cout << "BellmanFord2 done\n";
    std::cout << a5->get_prev() << std::endl;
    std::cout << a6->get_prev() << std::endl;
    std::cout << a7->get_prev() << std::endl;
    try {
        std::shared_ptr <algo::BellManFord> b1e(new algo::BellManFord(UNDIRECTED));
        b1e->add_edge(e11);
        b1e->add_edge(e12);
        b1e->add_edge(e13);
    }catch (std::exception& e){
        std::cout << "Standard exception: " << e.what() << std::endl;
    }


    std::shared_ptr<algo::KSP> k(new algo::KSP(UNDIRECTED));
    k->add_edge(e0);
    k->add_edge(e1);
    k->add_edge(e2);
    k->add_edge(e3);
    k->add_edge(e4);
    k->add_edge(e5);
    std::vector<path_ptr> path_list = k->k_shortest_path(a0,a2,5);
    for(path_ptr p: path_list){
        std::cout << p << std::endl;
    }
    std::cout << "Undirected KSP done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;

    k->set_judge(DIRECTED);
    path_list = k->k_shortest_path(a0,a2,5);
    for(path_ptr p: path_list){
        std::cout << p << std::endl;
    }
    std::cout << "Directed KSP done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;


    std::shared_ptr<algo::FindCycle> f (new algo::FindCycle(DIRECTED));
    f->add_edge(e0);
    f->add_edge(e6);
    f->add_edge(e5);
    f->add_edge(e4);
    f->add_edge(e7);
    f->add_edge(e8);
    f->add_edge(e9);
    std::cout << f->exist_cycle() <<std::endl;
    std::cout << "directed graph cycle detection done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;

    std::shared_ptr<algo::FindCycle> fd (new algo::FindCycle(DIRECTED));
    fd->add_edge(e0);
    fd->add_edge(e1);
    fd->add_edge(e2);
    fd->add_edge(e3);
    fd->add_edge(e4);
    fd->add_edge(e5);
    std::cout << fd->exist_cycle() <<std::endl;
    std::cout << "directed graph cycle detection2 done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;

    fd->set_judge(UNDIRECTED);
    std::cout << fd->exist_cycle() <<std::endl;
    std::cout << "directed graph construction for undirected graph cycle detection2 done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;


    fd->set_judge(DIRECTED);
    std::cout << fd->exist_cycle() <<std::endl;
    std::cout << "undirected graph construction for directed graph cycle detection2 done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;



    std::shared_ptr<algo::FindCycle> f1 (new algo::FindCycle(UNDIRECTED));
    f1->add_edge(e0);
    f1->add_edge(e6);
    f1->add_edge(e4);
    f1->add_edge(e1);
    f1->add_edge(e10);
    std::cout << f->exist_cycle() <<std::endl;
    std::cout << "undirected graph cycle detection done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;

    std::shared_ptr<algo::FindCycle> fd1 (new algo::FindCycle(UNDIRECTED));
    fd1->add_edge(e0);
    fd1->add_edge(e1);
    fd1->add_edge(e4);
    std::cout << fd1->exist_cycle() <<std::endl;
    std::cout << "undirected graph cycle detection2 done\n";
    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;

    node_ptr A (new data_struct::Node("A"));
    node_ptr B (new data_struct::Node("B"));
    node_ptr C (new data_struct::Node("C"));
    node_ptr D (new data_struct::Node("D"));
    node_ptr E (new data_struct::Node("E"));
    node_ptr F (new data_struct::Node("F"));
    node_ptr G (new data_struct::Node("G"));

    edge_ptr Edge0(new data_struct::Edge(A,B,7));
    edge_ptr Edge1(new data_struct::Edge(A,D,5));
    edge_ptr Edge2(new data_struct::Edge(D,B,9));
    edge_ptr Edge3(new data_struct::Edge(D,E,15));
    edge_ptr Edge4(new data_struct::Edge(D,F,6));
    edge_ptr Edge5(new data_struct::Edge(F,E,8));
    edge_ptr Edge6(new data_struct::Edge(B,E,7));
    edge_ptr Edge7(new data_struct::Edge(B,C,8));
    edge_ptr Edge8(new data_struct::Edge(C,E,5));
    edge_ptr Edge9(new data_struct::Edge(E,G,9));
    edge_ptr Edge10(new data_struct::Edge(F,G,11));

    std::shared_ptr<algo::Prim> p(new algo::Prim(UNDIRECTED));
    try{
        std::shared_ptr<algo::Prim> pe(new algo::Prim(DIRECTED));
    }catch (std::exception& e){
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    p->add_edge(Edge0);
    p->add_edge(Edge1);
    p->add_edge(Edge2);
    p->add_edge(Edge3);
    p->add_edge(Edge4);
    p->add_edge(Edge5);
    p->add_edge(Edge6);
    p->add_edge(Edge7);
    p->add_edge(Edge8);
    p->add_edge(Edge9);
    p->add_edge(Edge10);

    std::vector<edge_ptr> rv = p->generate_mst();
    std::cout << p->get_mst_value() << std::endl;
    for(edge_ptr e: rv){
        std::cout<< e;
        std::cout << "\n";
    }
    std::cout << A->get_prev() << std::endl;
    std::cout << B->get_prev() << std::endl;
    std::cout << C->get_prev() << std::endl;
    std::cout << D->get_prev() << std::endl;
    std::cout << E->get_prev() << std::endl;
    std::cout << F->get_prev() << std::endl;
    std::cout << G->get_prev() << std::endl;

    std::shared_ptr<algo::Kruskal> k1(new algo::Kruskal(UNDIRECTED));
    try{
        std::shared_ptr<algo::Kruskal> k1e(new algo::Kruskal(DIRECTED));
    }catch (std::exception& e){
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    k1->add_edge(Edge0);
    k1->add_edge(Edge1);
    k1->add_edge(Edge2);
    k1->add_edge(Edge3);
    k1->add_edge(Edge4);
    k1->add_edge(Edge5);
    k1->add_edge(Edge6);
    k1->add_edge(Edge7);
    k1->add_edge(Edge8);
    k1->add_edge(Edge9);
    k1->add_edge(Edge10);

    std::vector<edge_ptr> rv1 = k1->generate_mst();
    std::cout << k1->get_mst_value() << std::endl;
    for(edge_ptr e: rv1){
        std::cout<< e;
        std::cout << "\n";
    }
    std::cout << A->get_prev() << std::endl;
    std::cout << B->get_prev() << std::endl;
    std::cout << C->get_prev() << std::endl;
    std::cout << D->get_prev() << std::endl;
    std::cout << E->get_prev() << std::endl;
    std::cout << F->get_prev() << std::endl;
    std::cout << G->get_prev() << std::endl;

    std::shared_ptr<algo::EdmondsKarp> max_flow(new algo::EdmondsKarp(DIRECTED));
    max_flow->add_edge(edge0);
    max_flow->add_edge(edge1);
    max_flow->add_edge(edge2);
    max_flow->add_edge(edge3);
    max_flow->add_edge(edge4);
    max_flow->add_edge(edge5);
    max_flow->add_edge(edge6);
    max_flow->add_edge(edge7);
    max_flow->add_edge(edge8);
    max_flow->add_edge(edge9);
    std::vector<edge_ptr> rv2 = max_flow->generate_max_flow(a0,a5);

    for(edge_ptr e: rv2){
        std::cout<< e;
        std::cout << "\n";
    }
    std::cout << max_flow->get_max_flow() << std::endl;


    max_flow->set_judge(UNDIRECTED);
    std::vector<edge_ptr> rv3 = max_flow->generate_max_flow(a0,a5);

    for(edge_ptr e: rv3){
        std::cout<< e;
        std::cout << "\n";
    }
    std::cout << max_flow->get_max_flow() << std::endl;

    std::cout << a0->get_prev() << std::endl;
    std::cout << a1->get_prev() << std::endl;
    std::cout << a2->get_prev() << std::endl;
    std::cout << a3->get_prev() << std::endl;
    std::cout << a4->get_prev() << std::endl;
    std::cout << a5->get_prev() << std::endl;

    return 0;
}