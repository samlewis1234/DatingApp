#ifndef MEMBER_DATABASE
#define MEMBER_DATABASE

#include <vector>
#include <string>
#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"

// this class takes our members.txt file, goes through it line by line, creating PersonProfiles and
// putting them in a couple RadixTrees

class MemberDatabase
{
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
    std::string attValPairtoString(AttValPair avp) {return(avp.attribute + avp.value);};
private:
    RadixTree <PersonProfile> emailTree; // email to PersonProfile
    RadixTree <std::vector<std::string>> attValTree; // AVP to vector of associated emails
};

#endif // !MEMBER_DATABASE
