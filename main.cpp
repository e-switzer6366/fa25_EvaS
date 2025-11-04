//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}
//This function as per the instructions first makes a minHeap object and then using a for loop pushes all the leaf indices
//to the heap. Next a while loop is used which conditions are heap.size > 1, this is important because if the size is zero or
//less than nothing can be done. The two smallest nodes are popped into a variable, then the parent goes to the nect free node.
//After that the left and right arrays are used as pointers, and they are set to those nodes we just popped. This is to help with
//merging them together for a new node. After they are set then the parent is now set to the sum of those two weights.
//Finally, that new node is pushed into the array and nextFree is incremented. It returns the index of the smallest node
//which is the root.
int buildEncodingTree(int nextFree) {
    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)
    MinHeap heap = MinHeap();
    for (int i = 0; i < nextFree; i++) {
        heap.push(nextFree, weightArr);
    }
    //heap.push(nextFree,weightArr);
    while (heap.size > 1 ){
        int first = heap.pop(weightArr);//saving the first smallest node
        int second = heap.pop(weightArr);//second smallest node (root)

        int parent = nextFree;//parent goes to the next free node (leaf)

        leftArr[parent] = first;
        rightArr[parent] = second;
        weightArr[parent] = weightArr[first]+ weightArr[second];//combining the weight into parent

        heap.push(parent, weightArr);//put the new node into heap

        nextFree++;
    }
    return heap.pop(weightArr);
}

//This function assings code to the characters in the messege using a stack. The idea behind this is the huffman encoding algorithm.
//Per the instructions a stack pair is used which is the first thing also intitialized. After that the root is pushed onto the stack
//as a starting point for the traversal. While the stack is not empty then the top of the stack is saved in a variable, then popped.
//It's popped so that a traversal is possible to go through all the nodes. After that syntax is used to specifically access the int parameter
//of the stack pair and assign that to a variable. Same thing is done for the string part, the int is named the index, and the string is the code.
//Next leaf nodes are checked, and if they are encountered then that is the signal to finalize the code for that character. It is the end of the path
//if a leaf node is encountered. Otherwise internal nodes are encountered and those are used as the path to get to the leaf nodes.
//if right or left exists then they're pushed onto the stack with the string part of the pair as code + 1 or 0.
//This all works so that the root is the first thing to start with but then it is popped, if right or left nodes are encountered they are pushed
//onto the stack , making it possible to then again pop the nodes and check for leaf nodes and so forth.
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    stack<pair<int, string >> stack;
    stack.push({root,""});
    while (!stack.empty()) {
        pair<int, string> top = stack.top(); //saves the top val to add it to the code arr
        stack.pop();//pops to traverse

        int idx = top.first;//assiging a variable to the int in the stack pair
        string code = top.second;//assigning a variable to the string part

        int l = leftArr[idx];
        int r = rightArr[idx];

        if (l == -1 && r == -1) {
            codes[idx] = code;//this marks the completion of the code on that path/character
        }
        else {
             if (r!=-1) {
                 stack.push({r, code + "1"});//continue the path
             }
            if (l != -1) {
                stack.push({l, code + "0" });
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}