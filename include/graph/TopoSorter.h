/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "stacknqueue/Stack.h"
#include "stacknqueue/Queue.h"
#include "hash/IMap.h"
#include "hash/xMap.h" // delete later

template <class T>
class TopoSorter
{
public:
    static int DFS;
    static int BFS;

protected:
    DGraphModel<T> *graph;
    int (*hash_code)(T &, int);

public:
    // (Finished)
    TopoSorter(DGraphModel<T> *graph, int (*hash_code)(T &, int) = 0)
    {
        this->graph = graph;
        this->hash_code = hash_code;
    }
    // (Finished)
    DLinkedList<T> sort(int mode = 0, bool sorted = true)
    {
        DLinkedList<T> sorted_list;
        if (mode == DFS)
        {
            sorted_list = dfsSort(sorted);
        }
        else if (mode == BFS)
        {
            sorted_list = bfsSort(sorted);
        }
        return sorted_list;
    }
    DLinkedList<T> bfsSort(bool sorted = true)
    {
        DLinkedListSE<T> sorted_list = this->graph->vertices();
        if (sorted == true)
        {
            sorted_list.sort();
        }
        Queue<T> queue;
        xMap<T, bool> visited(this->hash_code);
        for (T vertex : sorted_list)
        {
            visited.put(vertex, false);
        }
        for (T vertex : sorted_list)
        {
            if (visited[vertex] == false)
            {
                queue.push(vertex);
                visited.put(vertex, true);
                while (queue.empty() == false)
                {
                    T current = queue.pop();
                    DLinkedList<T> neighbors = this->graph->getOutwardEdges(current);
                    for (T neighbor : neighbors)
                    {
                        if (visited[neighbor] == false)
                        {
                            queue.push(neighbor);
                            visited.put(neighbor, true);
                        }
                    }
                    sorted_list.add(current);
                }
            }
        }
        return sorted_list;
    }
    // (Finished)
    DLinkedList<T> dfsSort(bool sorted = true)
    {
        DLinkedListSE<T> sorted_list = this->graph->vertices();
        if (sorted == true)
        {
            sorted_list.sort();
        }
        Stack<T> stack;
        xMap<T, bool> visited(this->hash_code);
        for (T vertex : sorted_list)
        {
            visited.put(vertex, false);
        }
        for (T vertex : sorted_list)
        {
            if (visited[vertex] == false)
            {
                dfs(vertex, visited, stack);
            }
        }
        while (stack.empty() == false)
        {
            sorted_list.add(stack.pop());
        }
        return sorted_list;
    }

protected:
    // Helper functions
    // (Finished)
    void dfs(T vertex, xMap<T, bool> &visited, Stack<T> &stack)
    {
        visited.put(vertex, true);
        DLinkedList<T> neighbors = this->graph->getOutwardEdges(vertex);
        for (T neighbor : neighbors)
        {
            if (visited[neighbor] == false)
            {
                dfs(neighbor, visited, stack);
            }
        }
        stack.push(vertex);
    }
    // (Unfinished)
    xMap<T, int> vertex2inDegree(int (*hash)(T &, int))
    {
        xMap<T, int> in_degrees(hash);
        DLinkedList<T> vertices = this->graph->vertices();
        for (T vertex : vertices)
        {
            in_degrees.put(vertex, 0);
        }
        for (T vertex : vertices)
        {
            DLinkedList<T> neighbors = this->graph->getInwardEdges(vertex);
            for (T neighbor : neighbors)
            {
                in_degrees.put(neighbor, in_degrees[neighbor] + 1);
            }
        }
        return in_degrees;
    }
    // (Unfinished)
    xMap<T, int> vertex2outDegree(int (*hash)(T &, int))
    {
        xMap<T, int> out_degrees(hash);
        DLinkedList<T> vertices = this->graph->vertices();
        for (T vertex : vertices)
        {
            out_degrees.put(vertex, 0);
        }
        for (T vertex : vertices)
        {
            DLinkedList<T> neighbors = this->graph->getOutwardEdges(vertex);
            for (T neighbor : neighbors)
            {
                out_degrees.put(neighbor, out_degrees[neighbor] + 1);
            }
        }
        return out_degrees;
    }
    // (Unfinished)
    DLinkedList<T> listOfZeroInDegrees()
    {
        DLinkedList<T> zero_in_degrees;
        DLinkedList<T> vertices = this->graph->vertices();
        xMap<T, int> in_degrees = vertex2inDegree(this->hash_code);
        for (T vertex : vertices)
        {
            if (in_degrees[vertex] == 0)
            {
                zero_in_degrees.add(vertex);
            }
        }
        return zero_in_degrees;
    }
};
// TopoSorter
template <class T>
int TopoSorter<T>::DFS = 0;
template <class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////

#endif /* TOPOSORTER_H */
