#include "PersonProfile.h"
#include <iostream>
#include <fstream>
using namespace std;

PersonProfile::PersonProfile(string name, string email) : m_name(name), m_email(email) {}
PersonProfile::~PersonProfile() {}

string PersonProfile::GetName() const {return m_name;}

string PersonProfile::GetEmail() const {return m_name;}

// adds attribute-value pair to person's profile
void PersonProfile::AddAttValPair(const AttValPair& attval) {
    string* v_ptr = nullptr;
    vector<string>* values = attributes.search(attval.attribute);
    
    if (values == nullptr) { // if no value associated with attval.attribute, add attval.value to our attributes Tree
        vector<string> v;
        v.push_back(attval.value);
        attributes.insert(attval.attribute, v);
        values = attributes.search(attval.attribute);
    } else { // if there is an associated value
        v_ptr = find(values, attval.value);
        if (v_ptr != nullptr) { // failsafe
            return;
        }
        values->push_back(attval.value);
    }

    string* k_ptr = keyTree.search(attval.attribute);
    if (k_ptr == nullptr) { // if attribute not found, insert it
        keyTree.insert(attval.attribute, attval.attribute);
        k_ptr = keyTree.search(attval.attribute);
    }
    // add to AVP pointer Tree
    AVPptr avp({k_ptr, values, static_cast<int>(values->size())-1});
    attvalptr_vector.push_back(avp);
}

int PersonProfile::GetNumAttValPairs() const
{
    return static_cast<int>(attvalptr_vector.size());
}

// gets AVP specified by attribute_num and puts it in attval. if successful, returns true
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if (attribute_num < 0 || attribute_num > GetNumAttValPairs() - 1) { // failsafe, should not occur
        return false;
    }
    attval.attribute = *attvalptr_vector[attribute_num].keyptr;
    vector<string> values = *attvalptr_vector[attribute_num].values;
    int index = attvalptr_vector[attribute_num].index;
    attval.value = values[index];
    return true;
}

// finds string str in a given vector, returns a pointer to it (nullptr if not found)
string* PersonProfile::find(vector<string>* vec, const string& str) {
    if (vec != nullptr) {
        for (int i = 0; i < vec->size(); i++) {
            if ((*vec)[i].compare(str) == 0) {
                return &(*vec)[i];
            }
        }
    }
    return nullptr;
}
