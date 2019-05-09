// Code written by Aaron Bloomfield, 2014
// Released under a CC BY-SA license
// This code is part of the https://github.com/aaronbloomfield/pdr repository

#include <iostream>
#include <string>
#include "heap.h"
#include "huffNode.h"
using namespace std;

// default constructor
binary_heap::binary_heap() : heap_size(0) {
    HuffNode *dummyNode; //Would This Work?
    heap.push_back(dummyNode);
}

// builds a heap from an unsorted vector
binary_heap::binary_heap(vector<HuffNode*> vec) : heap_size(vec.size()) {
    heap = vec;
    heap.push_back(heap[0]);
    HuffNode * dummyNode; //Would This Work?
    heap[0] = dummyNode;
    for ( int i = heap_size/2; i > 0; i-- )
        percolateDown(i);
}

// the destructor doesn't need to do much
binary_heap::~binary_heap() {
}

void binary_heap::insert(HuffNode *  x) {
    // a vector push_back will resize as necessary
    heap.push_back(x);
    // move it up into the right position
    percolateUp(++heap_size);
}

void binary_heap::percolateUp(int hole) {
    // get the value just inserted
    HuffNode* x = heap[hole];
    // while we haven't run off the top and while the
    // value is less than the parent...
    for ( ; (hole > 1) && (x -> freq < heap[hole/2] -> freq); hole /= 2 )
        heap[hole] = heap[hole/2]; // move the parent down
    // correct position found!  insert at that spot
    heap[hole] = x;
}

HuffNode* binary_heap::deleteMin() {
  
    // make sure the heap is not empty
    if ( heap_size == 0 )
        throw "deleteMin() called on empty heap";
    // save the value to be returned
    HuffNode * ret = heap[1];
    // move the last inserted position into the root
    heap[1] = heap[heap_size--];
    // make sure the vector knows that there is one less element
    heap.pop_back();
    // percolate the root down to the proper position
    percolateDown(1);
    // return the old root node
    return ret;
  
  HuffNode *  placeHolder;
  return placeHolder;
}

void binary_heap::percolateDown(int hole) {
  
    // get the value to percolate down
    HuffNode* x = heap[hole];
    // while there is a left child...
    while ( hole*2 <= heap_size ) {
        int child = hole*2; // the left child
        // is there a right child?  if so, is it lesser?
        if ( (child+1 <= heap_size) && (heap[child+1] -> freq < heap[child] -> freq) )
            child++;
        // if the child is greater than the node...
        if ( x -> freq > heap[child] -> freq ) {
            heap[hole] = heap[child]; // move child up
            hole = child;             // move hole down
        } else
            break;
    }
    // correct position found!  insert at that spot
    heap[hole] = x;
  
}

HuffNode *  binary_heap::findMin() {
    if ( heap_size == 0 )
        throw "findMin() called on empty heap";
    return heap[1];
}

unsigned int binary_heap::size() {
    return heap_size;
}

void binary_heap::makeEmpty() {
    heap_size = 0;
}

bool binary_heap::isEmpty() {
    return heap_size == 0;
}

void binary_heap::print() {
    cout << "(" << heap[0] -> freq << ") ";
    for ( int i = 1; i <= heap_size; i++ ) {
        cout << heap[i] -> character << " ";
        // next line from from http://tinyurl.com/mf9tbgm
        bool isPow2 = (((i+1) & ~(i))==(i+1))? i+1 : 0;
        if ( isPow2 )
            cout << endl << "\t";
    }
    cout << endl;
}

void binary_heap::printHuff(string s, HuffNode* root) {
 
  if (root -> left ==  NULL && root -> right == NULL) {
    if(root -> character == ' ') {
      cout << "space";
    }
    else {
      cout << root -> character;

    }
    
    cout << " ";
    cout << s << endl;
    encodes[root -> character] = s;
  }
  
  else if(root -> left != NULL && root-> right == NULL) {

    printHuff(s+"0", root -> left);
  }

  else if(root -> left == NULL & root -> right != NULL) {
     printHuff(s+"1", root -> right);
  }

  else if(root -> left != NULL & root -> right != NULL) {
     printHuff(s+"0", root -> left);
     printHuff(s+"1", root -> right);
  }

  
}

void binary_heap::decode(HuffNode * insert, string encode, HuffNode * root ) {
  
  if(encode.size() == 1) {
    if(encode == "0"  && root -> left == NULL) {
      root -> left = insert;
    }

     if(encode == "1" && root -> right == NULL) {
      root -> right = insert;
    }
    
  }


  else {
  
    if(encode.at(0) == '0' && root -> left == NULL) {
      HuffNode * parentNode = new HuffNode('_');
      root -> left = parentNode;
      encode.erase(0,1);
      decode(insert, encode, root -> left);
    }

    else  if(encode.at(0) == '1' && root -> right == NULL) {
      HuffNode * parentNode = new HuffNode('_');
      root -> right = parentNode;
      encode = encode.erase(0,1);
      decode(insert, encode, root -> right);
    }

    else if(encode.at(0) == '0' && root -> left != NULL) {
      encode.erase(0,1);
      decode(insert, encode, root -> left);
    }

    else if(encode.at(0) == '1' && root -> right != NULL) {
      encode.erase(0,1);
      decode(insert, encode, root -> right);
    }
  
    
  }
  
}
