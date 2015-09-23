#include <iostream>
#include <stdio.h>
#include "porter.h"
#include <vector>
#include <regex>
using namespace std;

struct frequency {
    int repeat;
    string word;
};
regex puncmark(",|\\.|!|\\?$"); //edit for punctuation

void statistic(string wordFIle,bool* added, vector<frequency>* store) { //counting frequences
    if (regex_search(wordFIle,puncmark)) {
        wordFIle=regex_replace(wordFIle,puncmark,"");
    }
    if (wordFIle!="") {                                                 //first addition
        if (store->size()==0) {
            frequency a;
            a.repeat=1;
            porter(&wordFIle);
            a.word=wordFIle;
            store->insert(store->end(),a);
            *added = true;
        }
        else {
            porter(&wordFIle);
            for (int j = 0;j<store->size();j++) {
                if ((*store)[j].word==wordFIle) {                       //addition of old element
                    (*store)[j].repeat++;
                    *added=true;
                    break;
                }
            }
            if (!(*added)) {                                            //addition of new element
                frequency v;
                v.repeat=1;
                v.word = wordFIle;
                store->insert(store->end(),v);
            }
        }
    }
};
void output(vector<frequency> store) {
    for (int j = 0;j<store.size();j++) {
        cout<<store[j].word<<endl;
        cout<<store[j].repeat<<endl;
    }
    
}
int main()
{
    vector<frequency>* store=new vector<frequency>(); //&
    char buffer[20];
    string wordFIle;
    FILE *file;
    int i = 0;
    bool added;
    
    added=false;
    file = fopen("/1", "r");
    if (file==NULL) {
        cout<<"trouble"<<endl;
        return 0;
    }
    while (fscanf (file, "%s", buffer)!=EOF ) {
        wordFIle=buffer;
        statistic(wordFIle, &added, store);
        i++;
        added=false;
    }
    fclose(file);
    cout<<endl;
    output(*store);
    delete store;
}