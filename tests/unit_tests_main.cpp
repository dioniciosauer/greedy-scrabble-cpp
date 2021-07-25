
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <TrieNode.hpp>

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(DictionaryTests, BasicTest)
{
    std::ifstream inputDict{ "dictionary.txt" };
    std::vector<std::string> words{ };

    EXPECT_TRUE(inputDict.is_open());

    if(inputDict.is_open())
    {
        std::string word{ };
        while(std::getline(inputDict, word))
        {
            words.push_back(word);
        }

        inputDict.close();
    }

    const auto dictionary{ std::make_shared<Scrabble::TrieNode>(words) };

    for(const auto& word : words)
    {
        EXPECT_TRUE(dictionary->ContainsWord(word));
    }
}
