//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) { //key, value
        // TODO: insert index at end of heap, restore order using upheap()
        if (size==0) {//in case there is no parent, idx will become parent
            data[0] = idx;
        }
        else {
            data[size] = idx;
            size++;//keeping track of heap elements inside
        }
        //upHeap(); implemtn later
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size ==0) {//in case its empty
            return 0;
        }
        int rootIdx = data[0];//saving the root

        data[0] = data[size - 1];//replacing the root with the last element
        size--;
        //downheap()
        return rootIdx; //returning smallest element/root
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0){//goes until current index is at root
            int parentIdx = (pos - 1) / 2;//setting up a parent variable

            if (weightArr[data[parentIdx]] < weightArr[data[parentIdx]]) {//comparing if the parent is smaller than the curr index
                int temp = data[pos];//saves current index value
                data[pos] = data[parentIdx];//assigns parent index to pos
                data[parentIdx] = temp;//gives parent pos index
                pos = parentIdx;//move up
            }
            else {
                break;//if its not bigger then break
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (2 * pos + 1 < size) {//this is while a left child exists
            int leftC = 2 * pos + 1;
            int rightC = 2 * pos + 2;
            int smallest = leftC;

            if (rightC < size && weightArr[data[rightC]] < weightArr[data[leftC]]) {//checks if right child exists and then compare right child weight to the left
                smallest = rightC;//if right is indeed smaller than left, then right is smallest node
            }

            if (weightArr[data[pos]] <= weightArr[data[smallest]]) {//checks if the curr parent is already the smallest (satisying min heap)
                break;
            }
            else {//swaps the smallest and parent
                int temp = data[pos];
                data[pos] = data[smallest];
                data[smallest] = temp;

                pos = smallest;//move down
            }
        }
    }
};

#endif