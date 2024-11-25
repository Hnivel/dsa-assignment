/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
// #include "stacknqueue/PriorityQueue.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(bool (*vertexEQ)(T &, T &), string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str) {}
    // (Finished)
    void connect(T from, T to, float weight = 0)
    {
        VertexNode *from_node = this->getVertexNode(from);
        if (from_node == nullptr)
        {
            throw VertexNotFoundException(this->vertex2str(from));
        }
        VertexNode *to_node = this->getVertexNode(to);
        if (to_node == nullptr)
        {
            throw VertexNotFoundException(this->vertex2str(to));
        }
        if (from == to)
        {
            from_node->connect(to_node, weight);
        }
        else
        {
            from_node->connect(to_node, weight);
            to_node->connect(from_node, weight);
        }
    }
    // (Finished)
    void disconnect(T from, T to)
    {
        VertexNode *from_node = this->getVertexNode(from);
        if (from_node == nullptr)
        {
            throw VertexNotFoundException(this->vertex2str(from));
        }
        VertexNode *to_node = this->getVertexNode(to);
        if (to_node == nullptr)
        {
            throw VertexNotFoundException(this->vertex2str(to));
        }
        if (from == to)
        {
            from_node->disconnect(to_node);
        }
        else
        {
            from_node->disconnect(to_node);
            to_node->disconnect(from_node);
        }
    }
    // (Finished)
    void remove(T vertex)
    {
        VertexNode *node = this->getVertexNode(vertex);
        if (node == nullptr)
        {
            throw VertexNotFoundException(this->vertex2str(vertex));
        }
        auto it = this->nodeList.begin();
        while (it != this->nodeList.end())
        {
            VertexNode *current_node = *it;
            current_node->removeTo(node);
            it++;
        }
        this->nodeList.removeItem(node);
    }
    // (Finished)
    static UGraphModel<T> *create(T *vertices, int nvertices, Edge<T> *edges, int nedges, bool (*vertexEQ)(T &, T &), string (*vertex2str)(T &))
    {
        UGraphModel<T> *graph = new UGraphModel<T>(vertexEQ, vertex2str);
        for (int i = 0; i < nvertices; i++)
        {
            graph->add(vertices[i]);
        }
        for (int i = 0; i < nedges; i++)
        {
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
        }
        for (int i = 0; i < nedges; i++)
        {
            graph->connect(edges[i].to, edges[i].from, edges[i].weight);
        }
        return graph;
    }
};

#endif /* UGRAPHMODEL_H */
