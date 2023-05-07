#ifndef ATTRIBUTE_TRANSLATOR
#define ATTRIBUTE_TRANSLATOR

#include <vector>
#include <string>
#include "provided.h"
#include "RadixTree.h"


// matches similar, but not identical attributes (for example, "favorite_food,taco" and  "favorite_food,mexican")
// this is done with the given file, translator.txt

class AttributeTranslator
{
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
    std::string attValPairtoString(AttValPair avp) {return(avp.attribute + avp.value);};
private:
    RadixTree<std::vector<AttValPair*>> compAttributes;
    bool contains(std::vector<AttValPair*>* vec, const AttValPair& attval);
    RadixTree<AttValPair> valueAttrs;
};

#endif // !ATTRIBUTE_TRANSLATOR
