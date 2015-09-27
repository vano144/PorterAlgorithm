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
regex puncmark(",|\\.|!|\\?|\\\"|…|:|-|\\(|\\)|—|\\[|\\]"); //edit for punctuation

void statistic(string wordFIle,bool* added, vector<frequency>* store) { //counting frequences
    if (regex_search(wordFIle,puncmark)) {
        wordFIle=regex_replace(wordFIle,puncmark,"");
    }
    if (wordFIle!="") {
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
void output(vector<frequency> store) {
    for (int j = 0;j<store.size();j++) {
        cout<<store[j].word<<":";
        cout<<store[j].repeat<<endl;
    }
    
}
bool compare(frequency a, frequency b) {
    return b.repeat > a.repeat;
}
int main()
{
    vector<frequency> store;
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
        statistic(wordFIle, &added, &store);
        i++;
        added=false;
    }
    fclose(file);
    cout<<endl;
    std::sort(store.rbegin(), store.rend(),compare);
    output(store);
}