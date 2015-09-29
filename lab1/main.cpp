#include <iostream>
#include <stdio.h>
#include "porter.h"
#include <map>
#include <regex>
#include <string.h>
#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;

regex puncmark(",|\\.|!|\\?|\\\"|…|:|-|\\(|\\)|—|\\[|\\]");//edit for punctuation

void statistic(string wordFIle, map<string,int>* store) { //counting frequences
    if (regex_search(wordFIle,puncmark)) {
        wordFIle=regex_replace(wordFIle,puncmark,"");
    }
    if (wordFIle=="") return;
    porter(&wordFIle);
    if (store->count(wordFIle)==1) {                       //addition of old element
        (*store)[wordFIle]++;
    }
    else {                                            //addition of new element
        store->insert ( pair<string,int>(wordFIle,1) );
    }
}

bool compare(map<string,int>::value_type &i1, map<string,int>::value_type &i2)
{
    return i1.second<i2.second;
}

void outputMAP(map<string,int> store) {
    while(store.size()!=0)
    {
        auto it =max_element(store.begin(), store.end(),compare);
        cout << it->first<<" : "<<it->second<<endl;
        store.erase(it);
    }
    
}

int main()
{
    map <string,int> STORE;
    char buffer[20];                                  //TODO:vector->map
    string wordFIle;                                       //*->&, no delete and new
    FILE *file;                                            //punctuation,sorted map
    file = fopen("/1", "r");
    if (file==NULL) {
        cout<<"trouble"<<endl;
        return 1;
    }
    while (fscanf (file, "%s", buffer)!=EOF ) {
        wordFIle=buffer;
        statistic(wordFIle, &STORE);
    }
    fclose(file);
    cout<<endl;
    outputMAP(STORE);
    return 0;
}