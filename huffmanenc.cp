//Justin Barry
//jbb2fe

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "huffNode.h"
#include "heap.h"
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;


vector<HuffNode *>  deleteRepeats(vector<HuffNode*> characters) {
  vector <HuffNode*> returnChars = characters;
  for(int i = 0; i < returnChars.size(); i++) { 
    for(int j = 0 ; j < returnChars.size(); j++) {
      if(returnChars[j] -> character == returnChars[i]->character && i != j ) {
	returnChars[i]->freq += returnChars[j]->freq;
	returnChars.erase(returnChars.begin() + j);
      }
    }

  }

  return returnChars;
}

binary_heap generateHuffTree(binary_heap heap) {

  binary_heap retHeap = heap;
  while(retHeap.size() >= 2) {
    HuffNode* parentNode = new HuffNode('_');
    HuffNode* min1 = retHeap.deleteMin();
    HuffNode* min2 = retHeap.deleteMin();
    /*
    cout << min1 -> character;
    cout << ":";
    cout << min1 -> freq;
    cout << " -> ";
    cout << min2 -> character;
    cout << ":";
    cout << min2 -> freq<< endl;
    */
    parentNode ->left = min1;
    parentNode->right = min2;
    
    int newFreq = (min1 ->freq) + ( min2->freq);
      parentNode -> freq = newFreq;

   
    retHeap.insert(parentNode);
  }
  return retHeap;

}





int main(int argc, char **argv){
    vector<char> allChars;
    vector<char> loadedChars;
    vector<HuffNode *> loadedNodes;
  
    // verify the correct number of parameters
    if ( argc != 2 ) {
        cout << "Must supply the input file name as the one and only parameter" << endl;
        exit(1);
    }
    // attempt to open the supplied file.  FILE is a type desgined to
    // hold file pointers.  The first parameter to fopen() is the
    // filename.  The second parameter is the mode -- "r" means it
    // will read from the file.
    FILE *fp = fopen(argv[1], "r");
    // if the file wasn't found, output and error message and exit
    if ( fp == NULL ) {
        cout << "File '" << argv[1] << "' does not exist!" << endl;
        exit(2);
    }
    // read in each character, one by one.  Note that the fgetc() will
    // read in a single character from a file, and returns EOF when it
    // reaches the end of a file.
    char g;
    while ( (g = fgetc(fp)) != EOF )
        cout << g;
    // a nice pretty separator
    cout << "----------------------------------------" << endl;
    // rewinds the file pointer, so that it starts reading the file
    // again from the begnning
    rewind(fp);
    // read the file again, and print to the screen
    while ( (g = fgetc(fp)) != EOF ) {
      cout << g;
      allChars.push_back(g);
      vector<char>::iterator it = find(loadedChars.begin(), loadedChars.end(), g);
      if(it == loadedChars.end()) {
      loadedChars.push_back(g);
      HuffNode *n = new HuffNode(g);
      loadedNodes.push_back(n);

      } else {
	for(int i = 0; i < loadedNodes.size(); i++) {
	  if(loadedNodes[i] -> character == g)
	    loadedNodes[i] -> freq += 1;
	}
      }

    }

    
    // close the file
    fclose(fp);

    vector<HuffNode * > fixedList =  loadedNodes;
    fixedList.erase(fixedList.begin() + (fixedList.size() - 1)); //FIX THIS

    //FOR DEBUGGING PURPOSES
    /*
    cout << fixedList.size() << endl;
    for(int i = 0; i < fixedList.size(); i++) {
      cout << fixedList[i] -> character;
      cout << "- ";
      cout << fixedList[i] ->freq << endl;
    }
    */

    binary_heap minHeap;
    for(int i = 0; i < fixedList.size(); i++) {
      minHeap.insert(fixedList[i]); //fill up our heap
    }
    
   

    binary_heap huffTree = generateHuffTree(minHeap);
    HuffNode* root = huffTree.heap[1];
    /*
    cout << root->left ->character <<  endl;
    cout << root->left->left ->character <<  endl;
    cout << root->left->left -> character <<  endl;
    cout << root->left->left->left-> character <<  endl;
    cout << root->left->left->left->left-> character <<  endl;
    */
    
    int size = allChars.size() - 1;
    double regCost = 8 * size;
    double huffCost = 0.0;
 
    
    huffTree.printHuff("", root);
    cout << "----------------------------------------" << endl;
    for(int i = 0; i< allChars.size(); i++) {
      string enc = huffTree.encodes[allChars[i]];
      huffCost += enc.size();
      cout << enc;
      cout << " ";
    }
    cout << endl;
    cout << "----------------------------------------" << endl;

    double compressionRatio = regCost / huffCost;
    double treeCost = huffCost / size;
    cout << "There are a total of ";
    cout << size;
    cout << " symbols encoded" << endl;
    cout << "There are ";
    cout << fixedList.size();
    cout << " distict symbols used." << endl;
    cout << "Compression ratio: ";
    cout << compressionRatio << endl;;
    cout << "The Huffman tree costs: ";
    cout << treeCost;
    cout << " bits per character" << endl;
    

  return 0;
}
