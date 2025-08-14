#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"
#include <iostream>
#include <exception>
using namespace std;


FormulaParser::FormulaParser(std::string ln): tknzr {new Tokenizer{ln}} {}

TreeNode *FormulaParser::parseConjTerm() {
  // your code starts here
  //cout << "hereconjterm" << endl;
  Token rn = tknzr->getToken();
  string comp = rn.content;
  //cout << "2token rn:" << rn.content << endl;
  TreeNode *t1 = parseTerm();
  while(tknzr->hasToken()){
    tknzr->advanceToken();
    rn = tknzr->getToken();
    //cout << "3token rn:" << rn.content << endl;
    if (rn.content == "*"){
      tknzr->advanceToken();
      TreeNode *t2 = parseConjTerm();
      OperatorNode *andOP = new OperatorNode("*");
      andOP->updateChildren(t1,t2);
      return andOP;
    }
    else{
      break;
    }
  }
  return t1;
}

TreeNode *FormulaParser::parseTerm() {
  // your code starts here
  //cout << "hereterm" << endl;
  Token rn = tknzr->getToken();
  string comp = rn.content;
  if (rn.type == "Var"){
    VariableNode *child = new VariableNode(comp);
    return child;
  }
  else if (rn.type == "Const"){
    //cout << "YESS" << rn.content << endl;
    ConstantNode *child = new ConstantNode(comp);
    return child;
  }
  else if (comp == "-"){
    tknzr->advanceToken();
    TreeNode *t = parseTerm();
    OperatorNode *root = new OperatorNode("-");
    root->updateLeftChild(t);
    return root;
  }
  else if (comp == "("){
    tknzr->advanceToken();
    TreeNode *t = parseFormula();
    rn = tknzr->getToken();
    //cout << "CHECK inside brackets " << rn.content << endl;
    if (rn.content != ")"){
      //cout << "in parseterm )" << endl;
      throw invalid_argument("invalid input");
    }
    else{
      //cout << "--token rn:" << rn.content << endl;
      return t;
    }
  }
  else{
    //cout << "in parse term 2" << endl;
    throw invalid_argument("invalid input");
  }
}

TreeNode *FormulaParser::parseFormula() {
  // your code starts here
  //cout << "HEREfirst" << endl;
  Token rn = tknzr->getToken();
  string comp = rn.content;
  //cout << "1token rn:" << rn.content << endl;
  TreeNode *t1 = parseConjTerm();
  while(tknzr->hasToken()){
    //cout << "WHILE lOOP" << endl;
    //tknzr->advanceToken();
    //cout << tknzr->getToken() << endl;
    rn = tknzr->getToken();
    //cout << "4token rn:" << rn.content << endl;
    comp = rn.content;
    //cout << rn.content << endl;
    if (rn.content == "+"){
      //cout << "+" << endl;
      tknzr->advanceToken();
      rn = tknzr->getToken();
      //cout << "5token rn:" << rn.content << endl;
      TreeNode *t2 = parseFormula();
      OperatorNode *orOP = new OperatorNode("+");
      //cout << "orOP made"<< endl;
      orOP->updateChildren(t1,t2);
      return orOP;
    }
    else{
      break;
    }
  }
  return t1;
}

TreeNode * FormulaParser::getTreeRoot() {
  // your code starts here
  TreeNode *root = parseFormula();
  return root;
}

FormulaParser::~FormulaParser() {
  // your code starts here
}

AssignmentParser::AssignmentParser(std::string ln): tknzr {new Tokenizer{ln}} {}

std::map<std::string, bool> AssignmentParser::parseAssignment() {
  std::map<std::string, bool> results;
  // your code starts here
  string var;
  bool val;
  Token rn;
  while(tknzr->hasToken()){
    rn = tknzr->getToken();
    //cout << "token:" << rn.content << endl;
    if (rn.type == "Var"){
      var = rn.content;
      //cout << "var: " << var << endl;
      tknzr->advanceToken();
      rn = tknzr->getToken();
      if (rn.content == ":"){
        tknzr->advanceToken();
        rn = tknzr->getToken();
        if (rn.content == "0"){
          val = 0;
        }
        else if (rn.content == "1"){
          val = 1;
        }
        else{
          //cout << "1: parseassignment" << endl;
          throw invalid_argument("invalid input");// variable assigned to a variable
        }
        auto search = results.find(var); // find if var already exists
        if (search != results.end()){// found it
          if (search->second != val){// check for contradicting assignment
            //cout << "2: parseassignment" << endl;
            throw invalid_argument("contradicting assignment");
          }
          else{
            tknzr->advanceToken(); 
          }
        }
        else{
          results[var] = val;
          tknzr->advanceToken(); 
        }
      }
      else{
        //cout << "3: parseassignment" << endl;
        throw invalid_argument("invalid input");// ask var = var, and if the thing starts with ,
      }
    }
    else if (rn.content == ","){
      tknzr->advanceToken();
    }
    else{
      //cout << "4: parseassignment" << endl;
      throw invalid_argument("incomplete assignment");
    }
  }
  //for (auto const& x: results){
  //  cout << x.first    // string (key)
  //        << ':'
  //        << x.second   // string's value 
  //        << endl;
  //}
  return results;
}

AssignmentParser::~AssignmentParser() {
  // your code starts here
}
