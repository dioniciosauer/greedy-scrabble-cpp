
#include <algorithm>

#include <TrieNode.hpp>

using namespace Scrabble;

TrieNode::TrieNode(const std::vector<std::string>& words) 
: leaf(false), terminal(false), level(0), prefix(""), words(words), children()
{
    std::sort(this->words.begin(), this->words.end());
    CreateChildren();
}

TrieNode::TrieNode(const std::vector<std::string>& words, int level, const std::string& prefix) 
: level(level), prefix(prefix), words(words), children()
{
    leaf = words.size() == 1 && level == words.front().length();
    terminal = std::find(words.begin(), words.end(), prefix) != words.end();
    if(!leaf)
    {
        CreateChildren();
    }
}

void TrieNode::CreateChildren()
{
    constexpr std::string_view alphabet{ "abcdefghijklmnopqrstuvwxys" };
    constexpr auto numLetters{ alphabet.length() };
    const auto childLevel{ level + 1 };

    if(words.size() == 1)
    {
        const auto firstLetter{ words.front().front() };
        children.try_emplace(firstLetter, std::make_shared<TrieNode>(words, childLevel, prefix + firstLetter));
    }
    else
    {
        std::vector<std::string> childWords{ };
        for(const auto letter : alphabet)
        {
            for(auto word{ words.begin() }; word != words.end(); word = std::next(word))
            {
                const auto childPrefix{ prefix + letter };
                if(word->rfind(childPrefix, 0) != std::string::npos)
                {
                    childWords.push_back(*word);
                }
                else if(std::next(word) == words.end() && !childWords.empty())
                {
                    children.try_emplace(letter, std::make_shared<TrieNode>(childWords, childLevel, childPrefix));
                    childWords.clear();
                }
            }
        }
    }
}

std::optional<std::shared_ptr<const TrieNode>> TrieNode::GetNodeWithPrefix(const std::string& prefix) const
{
    if(prefix.length() == level)
    {
        return this->prefix == prefix ? { shared_from_this() } : { };
    }
    else if(prefix.length() < level)
    {
        if(auto child{ children.find(prefix.at(level)) }; child != children.end())
        {
            return child->second->GetNodeWithPrefix(prefix);
        }
    }
    else
    {
        return { };
    }
}

bool TrieNode::ContainsWord(const std::string& word) const
{
    
}

const std::map<char, std::shared_ptr<TrieNode>>& TrieNode::children() const
{
    return children;
}

bool TrieNode::leaf() const
{
    return leaf;
}

bool TrieNode::terminal() const
{
    return terminal;
}