//
//  main.cpp
//  CECS 328 Project2
//
//  Created by So Young Sarah Lee on 11/22/19.
//  Copyright © 2019 wonsuk seo. All rights reserved.
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <math.h>

using namespace std;

class Operator{
    protected :
    int value;
    string symbol;
    string op;
    int p ;
public:
    Operator(){
    }
    Operator(int prioity){
        p = prioity;
    }
    int getP(){
        return p;
    }
    string getOp(){
        return symbol;
    }
    string getType(){

        return op;
    }
    int getValue(){
        return value;
    }
};

class Plus : public Operator{
public:
    Plus(){
        p = 1;
        symbol = "+";
        op = "op";

    }

};
class Minus : public Operator{
public:
    Minus(){
        p = 1;
        symbol = "-";
        op = "op";
        
    }
       };
class Divide : public Operator{
public:
    Divide(){
        p = 2;
        symbol = "/";
        op = "op";
    }
   
};

class Multiplcation : public Operator{
public:
    Multiplcation(){
        p = 2;
        symbol = "*";
        op = "op";
        
    }
 
};

class Power : public Operator{
public:
    Power(){
        p = 3;
        symbol = "^";
        op = "op";
    }
    
};

class integer : public Operator{
public:
    integer(int a){
        value = a;
        op = "num";
    }
    int getValue(){
        return value;
    }
};

class ParseTree{
     
      
      Operator *root;
      
      ParseTree *left;
      
      ParseTree *right;
    
public:
 int eval(ParseTree* root)
 {
    
     if (!root)
         return 0;
   
     
     if (!root->left && !root->right)
         return (root->root->getValue());
   
    
     int left_val = eval(root->left);
   
     int right_val = eval(root->right);
   
     
     if (root->root ->getOp()=="+")
         return left_val+right_val;
   
     if (root->root->getOp()=="-")
         return left_val-right_val;
   
     if (root->root->getOp()=="*")
         return left_val*right_val;
     if(root->root->getOp()=="/")
     return left_val/right_val;
     
     return pow(left_val,right_val);
 } ;
        
    
    ParseTree(){};
    void setRoot(Operator* o1){
        root = o1;
    }
    void setLeft(ParseTree* pl){
        left = pl;
    }
    void setRight(ParseTree* pr){
        right = pr;
    }
    
};

int main() {
    
    int c;
    string e;
    string num = "";
    vector <Operator*> array;
    
    while(true){
        
        cout << "1.Run the program" << endl;
        cout << "2.Quit" << endl;
        
        cin >> c;
        switch(c){
            case 1:
            cout << "Put expression" << endl;
            cin >> e;
        for( int i = 0; i <= e.length(); i++){
               if(e[i] == '+'){
                 array.push_back(new integer(stoi(num)));
                   num = "";
                array.push_back(new Plus());
                
               }
                    
                else if(e[i] == '-'){
                    array.push_back(new integer(stoi(num)));
                    num = "";
                    array.push_back(new Minus());
                    
                }
                    
                else if(e[i] == '*'){
                array.push_back(new integer(stoi(num)));
                num = "";
                array.push_back(new Multiplcation());
                                 
                }
                    
                else if(e[i] == '/'){
                array.push_back(new integer(stoi(num)));
                num = "";
                                 
                array.push_back(new Divide());
                                 
                }
                else if(e[i] == '^'){
                array.push_back(new integer(stoi(num)));
                num = "";
                array.push_back(new Power());
                
                }
                else{
                  
                    num += e[i];
                }
           
                  
                }
                
                array.push_back(new integer(stoi(num)));
                
            /*
                for (int i=0; i < array.size(); i++){
                    cout << array[i] -> getValue() << endl;
                    cout << array[i] -> getType() << endl;
                    
                }
               */
                
vector <Operator*> postFix;
stack <Operator*> first;
                
 for(int j=0; j <array.size(); j++){
     
    if(array[j]->getType() == "num"){
        postFix.push_back(array[j]);
    
    }
     
    else{
        if(first.empty()){
                first.push(array[j]);
    }
    else{
        
        if(first.top()->getP() < array[j]->getP()){
        first.push(array[j]);
        }
    else{
                        
       while(!first.empty() && first.top()->getP() >= array[j] ->getP()){
            postFix.push_back(first.top());
            first.pop();
}
          
        first.push(array[j]);
        
         }
         }
        }
    
                         
}
    while(!first.empty()){
    postFix.push_back(first.top());
        first.pop();
     
    }
          
               
                //while
    cout << "Postfix expression: " ;
    for(int a = 0; a< postFix.size(); a++){
        if(postFix[a]->getType() == "num"){
            cout<<postFix[a]->getValue();
                          }
        else if(postFix[a] ->getType() == "op"){
            cout<<postFix[a]->getOp();
                              
                          }
                
            }//for
        cout << endl;

             
                
stack<ParseTree*> pt;
vector <Operator*>:: iterator iter = postFix.begin();
                
  while(iter != postFix.end())
  
  {
      if(*iter.getType() == "num"){
          ParseTree *p1 = new ParseTree();
          p1 ->setRoot(*iter);
          p1 ->setLeft(nullptr);
          p1 ->setRight(nullptr);
          pt.push(new ParseTree());
      }
      else{
          ParseTree *p2 = new ParseTree();
          p2 ->setRoot(*iter);
          p2 ->setLeft(pt.top());
          pt.pop();
          p2 -> setRight(pt.top());
          pt.pop();
          pt.push(p2);
          }
          
          
  }


                
                
        } //switch
    
        
    }//while
                     
    return 0;
    
}
