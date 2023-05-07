#ifndef MATCH_MAKER
#define MATCH_MAKER

#include <string>
#include <vector>
#include "provided.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"

// this is the "master" class. while not too complex itself, it is responsable for constructing the other classes, and making the program run

class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    const MemberDatabase& members;
    const AttributeTranslator& attTran;
};


#endif // !MATCH_MAKER
