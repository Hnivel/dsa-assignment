/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template <class T>
class DLinkedListSE : public DLinkedList<T>
{
public:
    DLinkedListSE(void (*removeData)(DLinkedList<T> *) = 0, bool (*itemEQ)(T &, T &) = 0) : DLinkedList<T>(removeData, itemEQ) {};

    DLinkedListSE(const DLinkedList<T> &list)
    {
        this->copyFrom(list);
    }
    // (Unfinished)
    void sort(int (*comparator)(T &, T &) = 0)
    {
        if (this->count <= 1)
        {
            return;
        }

        DLinkedList<T> left_list, right_list;
        typename DLinkedList<T>::Node *current = this->head->next; // Skip dummy head node
        int mid = this->count / 2;

        for (int i = 0; i < mid; i++)
        {
            left_list.add(current->data);
            current = current->next;
        }

        for (int i = mid; i < this->count; i++)
        {
            right_list.add(current->data);
            current = current->next;
        }

        left_list.sort(comparator);
        right_list.sort(comparator);

        typename DLinkedList<T>::Node *left_node = left_list.head->next;   // Skip dummy head node
        typename DLinkedList<T>::Node *right_node = right_list.head->next; // Skip dummy head node
        this->clear();
        this->addDummyNodes(); // Add dummy head and tail nodes

        while (left_node != left_list.tail && right_node != right_list.tail) // Stop at dummy tail node
        {
            if (compare(left_node->data, right_node->data, comparator) <= 0)
            {
                this->add(left_node->data);
                left_node = left_node->next;
            }
            else
            {
                this->add(right_node->data);
                right_node = right_node->next;
            }
        }

        while (left_node != left_list.tail) // Stop at dummy tail node
        {
            this->add(left_node->data);
            left_node = left_node->next;
        }

        while (right_node != right_list.tail) // Stop at dummy tail node
        {
            this->add(right_node->data);
            right_node = right_node->next;
        }
    }

private:
    void addDummyNodes()
    {
        this->head = new typename DLinkedList<T>::Node();
        this->tail = new typename DLinkedList<T>::Node();
        this->head->next = this->tail;
        this->tail->prev = this->head;
    }

protected:
    static int compare(T &lhs, T &rhs, int (*comparator)(T &, T &) = 0)
    {
        if (comparator != 0)
            return comparator(lhs, rhs);
        else
        {
            if (lhs < rhs)
                return -1;
            else if (lhs > rhs)
                return +1;
            else
                return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */
