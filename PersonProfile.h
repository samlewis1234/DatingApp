#ifndef PERSON_PROFILE
#define PERSON_PROFILE

#include <string>
#include <vector>
#include <unordered_set>
#include "provided.h"
#include "RadixTree.h"

// given a person, this class stores their name, email, and attributes

class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email);
    ~PersonProfile();
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    RadixTree<std::vector<std::string>> attributes;
    // easily stores AVPs as pointers
    struct AVPptr {
        std::string* keyptr;
        std::vector<std::string>* values;
        int index;
    };
    std::vector<AVPptr> attvalptr_vector;
    RadixTree<std::string> keyTree;
    std::string* find(std::vector<std::string> *vec, const std::string& val);
};

#endif // !PERSON_PROFILE
