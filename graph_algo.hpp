#ifndef ALGO
#define ALGO
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <algorithm>
#include <deque>
#include <memory>
#define int_max 0x7fffffff
extern std::string DIRECTED;
extern std::string UNDIRECTED;
extern std::string DIJKSTRA;
extern std::string BELLMANFORD;
extern std::string KSP;
extern std::string FINDCYCLE;
extern std::string PRIM;
extern std::string KRUSKAL;
namespace check{
    class exception_checker{
    public:
        static void check_judge_value(std::string judge);
        static void check_special_judge_value(std::string judge,std::string name);
    };
}
namespace data_struct{
    class Node{
    private:
        std::string label;
        std::shared_ptr<data_struct::Node> prev;

    public:
        Node(std::string l);
        void set_label(std::string l);
        std::string get_label();
        std::shared_ptr<data_struct::Node> get_prev();
        void set_prev(std::shared_ptr<data_struct::Node> p);
        friend std::ostream& operator<<(std::ostream &strm, const std::shared_ptr<data_struct::Node> n);

    };
    std::ostream& operator<<(std::ostream &strm, const std::shared_ptr<data_struct::Node> n);
    class Edge{
    private:
        int weight;
        std::shared_ptr<data_struct::Node> s;
        std::shared_ptr<data_struct::Node> d;
    public:
        Edge(std::shared_ptr<data_struct::Node> src, std::shared_ptr<data_struct::Node> dst, int w);
        void set_value(int w);
        int get_value()const;
        std::shared_ptr<data_struct::Node> get_src();
        std::shared_ptr<data_struct::Node> get_dst();
        friend std::ostream& operator<<(std::ostream &strm, const std::shared_ptr<data_struct::Edge> n);

    };
    std::ostream& operator<<(std::ostream &strm, const std::shared_ptr<data_struct::Edge> n);

    class Path{
    private:
        std::vector<std::shared_ptr<data_struct::Node>> path_list;
        int total;
    public:
        void add_to_path(std::shared_ptr<data_struct::Node> n);
        Path();
        Path(std::shared_ptr<data_struct::Node> node, int t);
        void set_total(int t);
        std::shared_ptr<data_struct::Node> get_last_one();
        int get_total()const;
        std::vector<std::shared_ptr<data_struct::Node>> get_path_list();
        friend std::ostream& operator<<(std::ostream &strm, const std::shared_ptr<data_struct::Path> p);
    };
    std::ostream& operator<<(std::ostream &strm, const std::shared_ptr<data_struct::Path> p);
}

namespace algo{
    class BaseAlgo{
    public:
        void add_edge(std::shared_ptr<data_struct::Edge> edge);
        void set_judge(std::string j);
        void reset();
        std::unordered_map<std::shared_ptr<data_struct::Node>,std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>> directed_adj_list;
        std::unordered_map<std::shared_ptr<data_struct::Node>,std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>> undirected_adj_list;
        std::vector<std::shared_ptr<data_struct::Node>> node_list;
        std::string judge;
        std::string name;
        BaseAlgo(std::string s, std::string n);
    };

    class BaseAlgo2{
    public:
        void add_edge(std::shared_ptr<data_struct::Edge> edge);
        void reset();
        std::vector<std::shared_ptr<data_struct::Node>> node_list;
        std::vector<std::shared_ptr<data_struct::Edge>> directed_edge_list;
        std::vector<std::shared_ptr<data_struct::Edge>> undirected_edge_list;
        int directed_edge_num;
        int undirected_edge_num;
        int node_num;
        std::string judge;
        std::string name;
        void set_judge(std::string j);
        BaseAlgo2(std::string s, std::string n);
    };

    class BellManFord: public BaseAlgo2{
    public:
        bool cycle_exist();
        BellManFord(std::string s);
        std::shared_ptr<data_struct::Path> shortest_path(std::shared_ptr<data_struct::Node> src, std::shared_ptr<data_struct::Node> dst);
    private:
        bool cycle;
    };


    class Dijkstra: public BaseAlgo{
    public:
        Dijkstra(std::string s);
        std::shared_ptr<data_struct::Path> shortest_path(std::shared_ptr<data_struct::Node> src, std::shared_ptr<data_struct::Node> dst);
    };

    class KSP{
    public:
        KSP(std::string s);
        void add_edge(std::shared_ptr<data_struct::Edge> edge);
        std::vector<std::shared_ptr<data_struct::Path>>k_shortest_path(std::shared_ptr<data_struct::Node> src, std::shared_ptr<data_struct::Node> dst, int k);
        void set_judge(std::string j);
    private:
        std::unordered_map<std::shared_ptr<data_struct::Node>,std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>> directed_adj_list;
        std::unordered_map<std::shared_ptr<data_struct::Node>,std::vector<std::pair<std::shared_ptr<data_struct::Node>,int>>> undirected_adj_list;
        std::string judge;
    };

    class FindCycle:public BaseAlgo{
    public:
        FindCycle(std::string s);
        //dfs check function
        bool check_cycle_directed(std::shared_ptr<data_struct::Node> node,std::unordered_map<std::shared_ptr<data_struct::Node>,bool>& visited, std::unordered_map<std::shared_ptr<data_struct::Node>,bool>& rec_stack);
        bool check_cycle_directed();
        // dfs check
        bool check_cycle_undirected(std::shared_ptr<data_struct::Node> node,std::unordered_map<std::shared_ptr<data_struct::Node>,bool>& visited,std::shared_ptr<data_struct::Node> parent );
        bool check_cycle_undirected();
        bool exist_cycle();

    };

    class Prim:public BaseAlgo{
    public:
        Prim(std::string s);
        int get_mst_value();
        std::vector<std::shared_ptr<data_struct::Edge>> generate_mst();
    private:
        int mst_wt;
    };

    class Kruskal: public BaseAlgo2{
    public:
        Kruskal(std::string s);
        int get_mst_value();
        std::shared_ptr<data_struct::Node> get_ancestor(std::shared_ptr<data_struct::Node> node);
        std::vector<std::shared_ptr<data_struct::Edge>> generate_mst();

    private:
        int mst_wt;
    };

}

using node_ptr = std::shared_ptr<data_struct::Node>;
using edge_ptr = std::shared_ptr<data_struct::Edge>;
using path_ptr = std::shared_ptr<data_struct::Path>;
#endif