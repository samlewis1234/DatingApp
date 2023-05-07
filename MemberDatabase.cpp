#include "MemberDatabase.h"
#include <iostream>
#include <fstream>
using namespace std;

MemberDatabase::MemberDatabase() {}

MemberDatabase::~MemberDatabase() {}

bool MemberDatabase::LoadDatabase(string filename) {
    ifstream infile(filename);
    if (!infile) {return false;} //if file does not exist
    string line;
    bool nameAdded = false;
    bool emailAdded = false;
    string name;
    string email;
    PersonProfile* add = nullptr;
    int numRecords = 0;
    int maxatt = 0;
    int attcount = 0;
    // realized that some of the above variables could be consolidated into something like a "lineCount" for each person, but this works
    while (getline(infile, line)) {
        if (line.empty()) { // blank lines between people
            continue;
        }
        else if (!nameAdded) { // first line of profile is name
            name = line;
            nameAdded = true;
        }
        else if (!emailAdded) { // second line is email
            email = line;
            if (emailTree.search(email) != nullptr) {return false;} // returns false if database has repeats
            emailAdded = true;
        }
        else if (isdigit(line[0])) { // next line is number of attributes
            maxatt = std::stoi(line);
        }
        else if (!isdigit(line[0])) { // next maxatt lines are attributes
            if (add == nullptr) {
                add = new PersonProfile(name, email);
            }
            size_t pos = line.find(","); // splits atts and values
            string attribute = line.substr(0, pos);
            string value = line.substr(pos + 1);
            //std::cout << attcount+1 << ": " << attribute << ", " << value << std::endl; useful for debugging
            AttValPair insert(attribute, value);
            add->AddAttValPair(insert); // adds AVP
            string attVal = attValPairtoString(insert);
            std::vector<std::string> *attEmails = attValTree.search(attVal);
            if (attEmails == nullptr) { // if new email (first AVP)
                vector<string> vecEm;
                vecEm.push_back(email);
                attValTree.insert(attVal, vecEm);
            }
            else {
                attEmails->push_back(email);
            }
            attcount++;

            if (attcount == maxatt) { // ends loop once count reached, resets helper variables
                if (add != nullptr) {
                    emailTree.insert(email, (*add));
                }
                nameAdded = false;
                emailAdded = false;
                add = nullptr;
                attcount = 0;
                maxatt = 0;
                numRecords++;
                continue;
            }
        }
    }
    infile.close();
    return true;
}

// simple match finding, used in MatchMaker
vector<string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    vector<string> emails;
    vector<string>* val = attValTree.search(input.attribute+input.value);
    if (val != nullptr) {
        emails = *val;
    }
    return emails;
}

// given email, find (pointer to) PersonProfile
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    return emailTree.search(email);
}
