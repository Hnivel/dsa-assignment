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
        // Initialize in_degrees with zeros
        xMap<T, int> in_degrees(this->hash_code);
        for (T vertex : sorted_list)
        {
            in_degrees.put(vertex, 0);
        }
        // Calculate in_degrees
        for (T vertex : sorted_list)
        {
            DLinkedList<T> neighbors = this->graph->getOutwardEdges(vertex);
            for (T neighbor : neighbors)
            {
                in_degrees.put(neighbor, in_degrees.get(neighbor) + 1);
            }
        }
        // Initialize queue with vertices that their in_degrees are zeros
        Queue<T> queue;
        for (T vertex : sorted_list)
        {
            if (in_degrees.get(vertex) == 0)
            {
                queue.push(vertex);
            }
        }
        // Perform BFS
        DLinkedList<T> return_list;
        while (queue.empty() == false)
        {
            T current = queue.pop();
            return_list.add(current);
            DLinkedList<T> neighbors = this->graph->getOutwardEdges(current);
            for (T neighbor : neighbors)
            {
                in_degrees.put(neighbor, in_degrees.get(neighbor) - 1);
                if (in_degrees.get(neighbor) == 0)
                {
                    queue.push(neighbor);
                }
            }
        }
        // Check if there was a cycle
        if (return_list.size() != sorted_list.size())
        {
            throw std::runtime_error("This graph is not a Directed Acyclic Graph");
        }
        return return_list;
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
        // Initialize visited with false
        xMap<T, bool> visited(this->hash_code);
        for (T vertex : sorted_list)
        {
            visited.put(vertex, false);
        }
        // Perform DFS
        for (typename DLinkedList<T>::BWDIterator it = sorted_list.bbegin(); it != sorted_list.bend(); it--)
        {
            T vertex = *it;
            if (visited.get(vertex) == false)
            {
                dfs(vertex, visited, stack, sorted);
            }
        }
        DLinkedList<T> return_list;
        // Construct the return list
        while (stack.empty() == false)
        {
            return_list.add(stack.pop());
        }
        return return_list;
    }
    // DLinkedList<T> dfsSort(bool sorted = true)
    // {
    //     DLinkedListSE<T> sorted_list = this->graph->vertices();
    //     if (sorted == true)
    //     {
    //         sorted_list.sort();
    //     }
    //     // Initialize visited with false
    //     xMap<T, bool> visited(this->hash_code);
    //     xMap<T, bool> in_stack(this->hash_code);
    //     for (T vertex : sorted_list)
    //     {
    //         visited.put(vertex, false);
    //         in_stack.put(vertex, false);
    //     }

    //     Stack<T> dfs_stack;
    //     Stack<T> post_order_stack;

    //     // Perform DFS iteratively
    //     for (T vertex : sorted_list)
    //     {
    //         if (visited.get(vertex) == false)
    //         {
    //             dfs_stack.push(vertex); // Start DFS for unvisited vertex
    //         }

    //         while (dfs_stack.empty() == false)
    //         {
    //             T current = dfs_stack.peek();

    //             if (in_stack.get(current) == true) // Cycle detected
    //             {
    //                 dfs_stack.pop();
    //                 if (visited.get(current) == false)
    //                 {
    //                     visited.put(current, true);
    //                     post_order_stack.push(current);
    //                 }
    //                 continue;
    //             }
    //             in_stack.put(current, true);
    //             // Push unvisited neighbors
    //             DLinkedListSE<T> neighbors = this->graph->getOutwardEdges(current);
    //             if (sorted == true)
    //             {
    //                 neighbors.sort();
    //             }
    //             for (T neighbor : neighbors)
    //             {
    //                 if (visited.get(neighbor) == false && in_stack.get(neighbor) == false)
    //                 {
    //                     dfs_stack.push(neighbor);
    //                 }
    //             }
    //         }
    //     }

    //     // Construct the return list
    //     DLinkedList<T> return_list;
    //     while (post_order_stack.empty() == false)
    //     {
    //         return_list.add(post_order_stack.pop());
    //     }
    //     return return_list;
    // }

protected:
    // Helper functions
    // (Finished)
    void dfs(T vertex, xMap<T, bool> &visited, Stack<T> &stack, bool sorted = true)
    {
        visited.put(vertex, true);
        DLinkedListSE<T> neighbors = this->graph->getOutwardEdges(vertex);
        if (sorted == true)
        {
            neighbors.sort();
        }
        for (typename DLinkedList<T>::BWDIterator it = neighbors.bbegin(); it != neighbors.bend(); it--)
        {
            T neighbor = *it;
            if (visited.get(neighbor) == false)
            {
                dfs(neighbor, visited, stack, sorted);
            }
        }
        stack.push(vertex);
    }
    // (Finished)
    xMap<T, int> vertex2inDegree(int (*hash)(T &, int))
    {
        xMap<T, int> in_degrees(hash);
        DLinkedList<T> vertices = this->graph->vertices();
        // Initialize in_degrees with zeros
        for (T vertex : vertices)
        {
            in_degrees.put(vertex, 0);
        }
        // Calculate in_degrees
        for (T vertex : vertices)
        {
            DLinkedList<T> neighbors = this->graph->getOutwardEdges(vertex);
            for (T neighbor : neighbors)
            {
                in_degrees.put(neighbor, in_degrees.get(neighbor) + 1);
            }
        }
        return in_degrees;
    }
    // (Finished)
    xMap<T, int> vertex2outDegree(int (*hash)(T &, int))
    {
        xMap<T, int> out_degrees(hash);
        DLinkedList<T> vertices = this->graph->vertices();
        // Initialize out_degrees with zeros
        for (T vertex : vertices)
        {
            out_degrees.put(vertex, 0);
        }
        // Calculate out_degrees
        for (T vertex : vertices)
        {
            DLinkedList<T> neighbors = this->graph->getOutwardEdges(vertex);
            for (T neighbor : neighbors)
            {
                out_degrees.put(vertex, out_degrees.get(vertex) + 1);
            }
        }
        return out_degrees;
    }
    // (Finished)
    DLinkedList<T> listOfZeroInDegrees()
    {
        DLinkedList<T> zero_in_degrees;
        DLinkedList<T> vertices = this->graph->vertices();
        for (T vertex : vertices)
        {
            if (this->graph->inDegree(vertex) == 0)
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
