#include "MatchMaker.h"

#include <iostream>
using namespace std;


MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) : members(mdb), attTran(at) {}

MatchMaker::~MatchMaker() {}

// standard insertion sort
void insertionSort(vector<EmailCount*>& orderMe)
{
    for (int s = 2; s <= orderMe.size(); s++)
    {
        EmailCount* sortMe = orderMe[s - 1];

        int i = s - 2;
        while ((i >= 0) &&
               ((sortMe->count > orderMe[i]->count) ||
                (sortMe->count == orderMe[i]->count && sortMe->email < orderMe[i]->email))) {
                orderMe[i + 1] = orderMe[i];
                --i;
        }
        orderMe[i + 1] = sortMe;
    }
}

// gets matches for a person, given their email and a desired minimum number of compatible attributes
vector<EmailCount> MatchMaker::IdentifyRankedMatches(string email, int threshold) const
{
    RadixTree<std::string> compTree; // creates tree of matches
    std::vector<AttValPair> compList;
    const PersonProfile* currPerson = members.GetMemberByEmail(email);

    for (int i = 0; i < currPerson->GetNumAttValPairs(); i++) { // gets and translates AVPs
        AttValPair currAttValPair;
        currPerson->GetAttVal(i, currAttValPair);
        vector<AttValPair> currCompAttributes = attTran.FindCompatibleAttValPairs(currAttValPair);
        for (int i = 0; i < currCompAttributes.size(); i++) {
            std::string attvalstr = currCompAttributes[i].attribute + currCompAttributes[i].value;
            if (!compTree.search(attvalstr)) {  // no duplicates
                compTree.insert(attvalstr, "");
                compList.push_back(currCompAttributes[i]);
            }
        }
    }

    RadixTree<EmailCount> compEmailTree;
    std::vector<EmailCount*> compEmailList;

    for (int i = 0; i < compList.size(); i++) { // gets emails of those who have matching attributes
        vector<string> compPeople = members.FindMatchingMembers(compList[i]);
        for (int x = 0; x < compPeople.size(); x++) {
            if (email.compare(compPeople[x]) != 0) {
                EmailCount* emailcount = compEmailTree.search(compPeople[x]);
                if (emailcount == nullptr) {  // if email not present
                    EmailCount insertEmail(compPeople[x], 1);
                    compEmailTree.insert(compPeople[x], insertEmail);
                    emailcount = compEmailTree.search(compPeople[x]);
                    compEmailList.push_back(emailcount);
                }
                else {  // if email already shares attribute(s)
                    emailcount->count++;
                }
            }
        }
    }

    insertionSort(compEmailList);

    std::vector<EmailCount> result; // only add emails with matches >= our threshold
    for (int i = 0; i < compEmailList.size(); i++) {
        if (compEmailList[i]->count >= threshold) {
            result.push_back(*compEmailList[i]);
        }
    }
    return result;
}
