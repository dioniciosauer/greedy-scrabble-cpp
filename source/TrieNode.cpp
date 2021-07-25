
#include <TrieNode.hpp>

using namespace Scrabble;

TrieNode::TrieNode(const std::vector<std::string>& words) 
: terminal_(false), level(0), prefix_(""), children()
{
    for(const auto& word : words)
    {
        AddWord(word);
    }
}

TrieNode::TrieNode(const int level, const std::string& prefix, const bool terminal)
: terminal_(terminal), level(level), prefix_(prefix), children()
{
}

bool TrieNode::AddWord(const std::string& word)
{
    // Check if the word is already in the Trie
    if(IsRoot() && ContainsWord(word))
    {
        return true;
    } // Check if the prefix of this node prefixes the word, also checks that the word is >= the prefix
    else if (word.rfind(prefix_, 0) == std::string::npos)
    {
        return false;
    }
    else
    {
        const auto childLetter{ word.at(level) };
        const auto childLevel{ level + 1 };
        const auto isTerminal{ childLevel == word.length() };
        auto child{ std::shared_ptr<TrieNode>(nullptr) };
        if(const auto childEntry{ children.find(childLetter) }; childEntry != children.end())
        {
            child = childEntry->second;
            if(isTerminal)
            {
                child->terminal(true);
                return true;
            }
            else
            {
                return child->AddWord(word);
            }
        }
        else
        {
            const auto childPrefix{ isTerminal ? word : prefix_ + word.at(level) };
            child = std::shared_ptr<TrieNode>( new TrieNode(childLevel, childPrefix, isTerminal));

            children.try_emplace(childLetter, child);
            if(isTerminal)
            {
                return true;
            }
            else
            {
                return child->AddWord(word);
            }
        }
    }
}

bool TrieNode::ContainsPrefix(const std::string& prefix) const
{
    return FindNodeWithPrefix(prefix).has_value();
}

bool TrieNode::ContainsWord(const std::string& word) const
{
    if(const auto wordAsPrefix{ FindNodeWithPrefix(word) }; wordAsPrefix)
    {
        return wordAsPrefix.value()->terminal_;
    }
    else
    {
        return false;
    }
}

std::optional<std::shared_ptr<const TrieNode>> TrieNode::FindNodeWithPrefix(const std::string& prefix) const
{
    if(prefix.length() == level + 1)
    {
        if(const auto child{ children.find(prefix.at(level)) }; child != children.end())
        {
            return { child->second };
        }
        else
        {
            return { };
        }
    }
    else if(prefix.length() > level)
    {
        if(const auto& child{ children.find(prefix.at(level)) }; child != children.end())
        {
            return child->second->FindNodeWithPrefix(prefix);
        }
        else
        {
            return { };
        }
    }
    else
    {
        return { };
    }
}

bool TrieNode::IsLeaf() const
{
    return children.size() == 0;
}

bool TrieNode:: IsRoot() const
{
    return prefix_ == "";
}

const std::vector<char> TrieNode::ValidFirstLetters(const std::string& word) const
{
    std::vector<char> validLetters{ };

    for(const auto& [letter, child] : children)
    {
        if(ContainsWord(letter + word))
        {
            validLetters.push_back(letter);
        }
    }
    return validLetters;
}

const std::vector<char> TrieNode::ValidLastLetters(const std::string& word) const
{
    std::vector<char> validLetters{ };

    if(auto childExists{ FindNodeWithPrefix(word) }; childExists)
    {
        const auto child{ childExists.value() };
        if(child->IsLeaf())
        {
            return validLetters;
        }
        else
        {
            for(const auto [letter, grandChild] : child->children)
            {
                if(grandChild->terminal_)
                {
                    validLetters.push_back(letter);
                }
            }
        }
    }
    return validLetters;
}

bool TrieNode::terminal() const
{
    return terminal_;
}

void TrieNode::terminal(const bool terminal)
{
    terminal_ = terminal;
}
