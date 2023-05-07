#include "AttributeTranslator.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

AttributeTranslator::AttributeTranslator() {}
AttributeTranslator::~AttributeTranslator() {}

// load translator.txt file
bool AttributeTranslator::Load(std::string filename) {
    string myText;
    ifstream MyReadFile(filename);
    while (getline(MyReadFile, myText)) {
        istringstream f(myText);
        std::vector<string> strvec;
        string strvalue;
        while (getline(f, strvalue, ',')) {
            strvec.push_back(strvalue);
        }

        AttValPair src(strvec[0], strvec[1]); // attribute-value 1
        AttValPair comp(strvec[2], strvec[3]); // attribute-value 2

        string compatt = attValPairtoString(comp);
        AttValPair* compattptr = valueAttrs.search(compatt);
        if (compattptr == nullptr) { // if new AVP
            valueAttrs.insert(compatt, comp);
            compattptr = valueAttrs.search(compatt);
        }

        string key = attValPairtoString(src);
        vector<AttValPair*>* vec = compAttributes.search(key);
        if (vec == nullptr) { // if attribute-value 1 new
            vector<AttValPair*> compFeatures;
            compFeatures.push_back(compattptr);
            compAttributes.insert(key, compFeatures);
        }
        else {
            if (!contains(vec,comp)) {
                vec->push_back(compattptr);
            }
        }
    }
    MyReadFile.close();
    return true;
}

// once RadixTrees of compatible attributes have been created, search them
vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
    vector<AttValPair> result;
    vector<AttValPair*>* vec = compAttributes.search(source.attribute+source.value);
    if (vec == nullptr) { // if no matches (not sure if this ever occurs)
        return result;
    }
    for (int i = 0; i < vec->size(); i++) { // vector of all matches
        result.push_back((*(*vec)[i]));
    }
    return result;
}

// if vec contains attval return true
bool AttributeTranslator::contains(std::vector<AttValPair*>* vec, const AttValPair& attval) {
    if (vec != nullptr) {
        for (int i = 0; i < vec->size(); i++) {
            if ((*(*vec)[i]) == attval) {
                return true;
            }
        }
    }
    return false;
}
