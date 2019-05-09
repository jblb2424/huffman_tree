#include "huffNode.h"
#include <iostream>
using namespace std;


HuffNode::HuffNode(char c) {
  freq = 1;
  character = c;
  left = NULL;
  right = NULL;
}
