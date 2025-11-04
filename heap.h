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

    //This function checks first if the size is maxed out, if so it returns nothing. If there is indeed room, then it
    //goes to the last index, (size) and makes that == to idx. The size is increased to show the growing of the heap and
    //then upheap is used at the end to correctly weigh all the nodes back to a minheap.
    void push(int idx, int weightArr[]) { //key, value
        // TODO: insert index at end of heap, restore order using upheap()
        if (size>=64) {
            return;
        }
        data[size] = idx;
        size++;
        upheap(size,weightArr);
    }

    /*int getSize() {
        return size;
    }*/
    //this checks if the heap is empty, if so I decided to just return -1. If it isn't empty then first the root is saved,
    //and the root is replaced with the last element
    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size <=0) {//in case its empty
            return -1;
        }
        int rootIdx = data[0];//saving the root

        data[0] = data[size - 1];//replacing the root with the last element
        downheap(0,weightArr);
        size--;
        return rootIdx; //returning smallest element/root
    }
    //The function goes until the current index is at the root, and then the parent index is initialized, and the
    //comparisons begin, weightArr is used for doing those comparisons. But since we're trying to also compare the data arry itself,
    //the data array went inside the weightArr for comparisons. The condition is if the pos is smaller than the parent. If
    //it is then the swap will be made. I did a manual swap of pos and parent. Pos moves upwards. ANd if the parent is smaller, then no
    //upheap needed, just break out the loop.
    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0){
            int parentIdx = (pos - 1) / 2;

            if (weightArr[data[pos]] < weightArr[data[parentIdx]]) {
                int temp = data[pos];//saves current index value
                data[pos] = data[parentIdx];//assigns parent index to pos
                data[parentIdx] = temp;//gives parent pos index
                pos = parentIdx;//move up
            }
            else {
                break;
            }
        }
    }

    //This function bubbles down the parent if it is larger than any of its children. First a check is made if a left
    //child even exists, if it does then the left and right child nodes are initialized, and the smallest is the left child.
    //Next a check is made if the right child exists and whether or not it's bigger than the left. If the right is smaller
    //then its assigned as the smallest node. Lastly there is a check on if the current parent is smaller than the smallest
    //node. If it is then the minheap is satisfied, if not then a swap is made to make it the smallest.
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