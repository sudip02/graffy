/* 
 * File:   graph_operations.h
 * Author: bharath
 *
 * Created on April 18, 2012, 6:03 AM
 */

#ifndef GRAPH_OPERATIONS_H
#define	GRAPH_OPERATIONS_H

#include "graph.h"

namespace CDLib {
    
    
    
    id_type extract_subgraph(const graph& g, const node_set& nodes, graph& sg);
    void sample_graph(const graph&g, node_set& seeds, id_type hop_dist, graph& sample);
    // Naive implementation to Copy a graph. May be inefficient
    id_type copy_graph(const graph& src, graph& dst);
    double remove_edges_randomly(graph& g,double percentage);
    void multiply_vector_transform(const graph& g,double (*wt_transform_func)(const graph&g,id_type,id_type,double),bool right,const vector<double>& invec,vector<double>& outvec);
    void run_random_walks(const graph& g,const vector<double>& invec,id_type t,bool right,vector<double>& outvec);
    double transform_func_nop(const graph& g, id_type i, id_type j, double wt);
    double transform_func_row_stochastic(const graph& g, id_type i, id_type j, double wt);
    double transform_func_column_stochastic(const graph& g, id_type i, id_type j, double wt);
    double transform_func_max_rowcol_stochastic(const graph& g, id_type i, id_type j, double wt);
    double transform_func_min_rowcol(const graph& g, id_type i, id_type j, double wt);
    double transform_func_laplacian(const graph& g, id_type i, id_type j, double wt);
    double transform_func_normalized_laplacian_row(const graph& g, id_type i, id_type j, double wt);
    double transform_func_normalized_laplacian_col(const graph& g, id_type i, id_type j, double wt);

    template<typename AssociativeContainer>
    void get_neighbor_assoc_cont(const graph&g, id_type node_id, bool out, AssociativeContainer& cont) {
        if (out) {
            for (adjacent_edges_iterator aeit = g.out_edges_begin(node_id); aeit != g.out_edges_end(node_id); aeit++)
                cont.insert(aeit->first);
        } else {
            for (adjacent_edges_iterator aeit = g.in_edges_begin(node_id); aeit != g.in_edges_end(node_id); aeit++)
                cont.insert(aeit->first);
        }
    }

    template<typename SequentialContainer>
    void get_neighbor_seq_cont(const graph&g, id_type node_id, bool out,SequentialContainer& cont) {
        if (out) {
            for (adjacent_edges_iterator aeit = g.out_edges_begin(node_id); aeit != g.out_edges_end(node_id); aeit++)
                cont.push_back(aeit->first);
        } else {
            for (adjacent_edges_iterator aeit = g.in_edges_begin(node_id); aeit != g.in_edges_end(node_id); aeit++)
                cont.push_back(aeit->first);
        }
    }
    
    template<typename AssociativeContainer>
    void get_degrees_assoc_cont(const graph&g,bool out,bool weights, AssociativeContainer& cont) {
        for(id_type i=0;i<g.get_num_nodes();i++)
        {
            if(out)
            {
                if(weights)cont.insert(make_pair(i,g.get_node_out_weight(i)));
                else cont.insert(make_pair(i,g.get_node_out_degree(i)));
            }
            else
            {
                if(weights)cont.insert(make_pair(i,g.get_node_in_weight(i)));
                else cont.insert(make_pair(i,g.get_node_in_degree(i)));
            }
        }
    }
    
    
    template<typename SequentialContainer>
    void get_degrees_seq_cont(const graph&g,bool out,bool weights,SequentialContainer& cont) {
        for(id_type i=0;i<g.get_num_nodes();i++)
        {
            if(out)
            {
                if(weights)cont.push_back(make_pair(i,g.get_node_out_weight(i)));
                else cont.push_back(make_pair(i,g.get_node_out_degree(i)));
            }
            else
            {
                if(weights)cont.push_back(make_pair(i,g.get_node_in_weight(i)));
                else cont.push_back(make_pair(i,g.get_node_in_degree(i)));
            }
        }
    }
};


#endif	/* GRAPH_OPERATIONS_H */

