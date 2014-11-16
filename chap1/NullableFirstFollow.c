#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

typedef struct product{
  string non_term;
  vector<string> term;
}product;

bool isNon_term(string lhs){
  if(lhs[0]>='A' && lhs[0] <='Z'){
    return true;
  }
  return false;
}
product make_product(string lhs,vector<string>& rhs){
  if(!isNon_term(lhs)){
    fprintf(stderr,"%s\n","lhs must be non_term");
  }
  product product_;
  product_.non_term = lhs;
  product_.term = rhs;
  return product_;
}
vector<product> products;
set<string> terms;
set<string> non_terms;
map<string,bool> nullable;
map<string,set<string> > first;
map<string,set<string> > follow;
void init(){
  string epsion("epsion");
  set<string>::iterator iter = non_terms.begin();
  while(iter != non_terms.end()){
    set<string> empty1,empty2;
    nullable[*iter] = false;
    first[*iter] = empty1;
    follow[*iter] = empty2;
    iter++;
  }
  iter = terms.begin();
  while(iter != terms.end()){
    nullable[*iter] = false;
    set<string> empty3,empty4;
    if(*iter != epsion){
      empty3.insert(*iter);
    }
    first[*iter] = empty3;
    follow[*iter] = empty4;
    iter++;
  }

  nullable[epsion] = true;
  vector<product>::iterator it = products.begin();
  while(it != products.end()){
    product prod = *it;
    vector<string> term = prod.term;
    if(term.size() == 1 && find(term.begin(),term.end(),epsion) != term.end()){
      nullable[prod.non_term] = true;
    }
    it++;
  }
}
void input_products(){
  int num_of_term;
  cout << "input the number of term: ";
  cin >> num_of_term;
  for(int i = 0;i < num_of_term;i++){
    string input;
    cin >> input;
    terms.insert(input);
  }
  cout << "input products:" << endl;
    string non_term,input;
    string term_item;
    getchar();
    while(getline(cin,input)){
      vector<string> terms;
      istringstream istring(input);
      istring >> non_term;
      non_terms.insert(non_term);
      while(istring >> term_item){
        terms.push_back(term_item);
      }
      products.push_back(make_product(non_term,terms));
    }
}
/*void printproducts(){
  vector<product>::iterator iter = products.begin();
  while(iter!=products.end()){
    product pro = *iter;
    cout << pro.non_term << "=";
    vector<string>term = pro.term;
    vector<string>::iterator iter2 = term.begin();
    while(iter2 != term.end()){
      cout << " " << *iter2;
      iter2++;
    }
    cout << endl;
    iter++;
  }
  }*/
void calcNullableFirstFollow(){
  while(true){
    bool changed = false;
    vector<product>::iterator iter = products.begin();
    while(iter != products.end()){
      product prod = *iter;
      string non_term = prod.non_term;
      vector<string> term = prod.term;
      bool allNullable = true;
      for(vector<string>::iterator i = term.begin();i!=term.end();i++){
        if(nullable[*i] == false){
          allNullable = false;
          break;
        }
      }
      if(allNullable){
        if(nullable[non_term] == false){
          changed = true;
        }
        nullable[non_term] = true;
      }

      for(int i = 0;i<term.size();i++){
        for(int j = i;j<term.size();j++){
          int sum = first[non_term].size() + follow[term[i]].size() + follow[term[i]].size();
          bool flag = true;
          for(int k = 0;k<i;k++){
            if(!nullable[term[k]]){
              flag = false;
              break;
            }
          }
          if(flag){

            first[non_term].insert(first[term[i]].begin(),first[term[i]].end());
          }
          if(i!=j){
            flag = true;
            for(int k = i+1;k<j;k++){
              if(!nullable[term[k]]){
                flag = false;
                break;
              }
            }
            if(flag){

              follow[term[i]].insert(first[term[j]].begin(),first[term[j]].end());
            }
          }
          flag = true;
          for(int k = i+1;k<term.size();k++){
            if(!nullable[term[k]]){
              flag = false;
              break;
            }
          }
          if(flag){

            follow[term[i]].insert(follow[non_term].begin(),follow[non_term].end());
          }
          if(sum != first[non_term].size() + follow[term[i]].size() + follow[term[i]].size()){
            changed = true;
          }



        }
      }
      iter++;
    }
    if(!changed){
      break;
    }
  }
}
void outputNullableFirstFollow(){
  set<string>::iterator it = non_terms.begin();
  while(it!=non_terms.end()){
    cout << *it << " " ;
    cout << (nullable[*it] ? "t\t" : "f\t") ;
    set<string>::iterator iter = first[*it].begin();



    while(iter!=first[*it].end()){
      cout << *iter << " ";
      iter++;
    }
    cout << "\t";
    iter = follow[*it].begin();
    while(iter!=follow[*it].end()){
      cout << *iter << " ";
      iter++;
    }
    cout << endl;
    it++;
  }
}
int main(){
  input_products();
  init();
  //printproducts();
  calcNullableFirstFollow();
  outputNullableFirstFollow();
  return 0;
}
