#include "treeNode.h"
#include <map>
#include <exception>
#include <iostream>
using namespace std;
TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
  // your code starts here
  return content;
}

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  return leftChild;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  return rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  // your code starts here
  leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild) {
  // your code starts here
  leftChild = lChild;
  rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {}

bool OperatorNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  bool left;
  bool right;
  //cout << "CHECK" << left << right << endl;
  if (getContent() == "+"){
    left = getLeftChild()->evaluate(assignment);
    right = getRightChild()->evaluate(assignment);
    return left || right;
  }
  else if (getContent() == "*"){
    left = getLeftChild()->evaluate(assignment);
    right = getRightChild()->evaluate(assignment);
    return left && right;
  }
  else if (getContent() == "-"){
    left = getLeftChild()->evaluate(assignment);
    return !left;
  }
  else{
    return false;
  }
}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

bool ConstantNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  if (getContent() == "0"){
    return false;
  }
  else{
    return true;
  }
}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

bool VariableNode::evaluate(const std::map<std::string, bool> &assignment) const {
  // your code starts here
  auto search = assignment.find(getContent());//double check after for error cases
  if (search != assignment.end()) {  // found it
    //cout << "found it : " << search->first << endl;
    return search->second;
  }
  else{
    //cout << "treenode.cc" << endl;
    throw invalid_argument("incomplete assignment");
  }  
}

TreeNode::~TreeNode() {
  // your code starts here
}
