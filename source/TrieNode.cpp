
#include <algorithm>

#include <TrieNode.hpp>

using namespace Scrabble;

TrieNode::TrieNode(const std::vector<std::string>& words) 
: leaf_(false), terminal_(false), level(0), prefix(""), words(words), children()
{
    /* Sort at the root and it shouldn't be necessary to sort again due to
     * how the child creation process works
     */
    std::sort(this->words.begin(), this->words.end());
    if(words.size() != 0)
    {
        CreateChildren();
    }
}

TrieNode::TrieNode(const std::vector<std::string>& words, const int level, const std::string& prefix) 
: level(level), prefix(prefix), words(words), children(), terminal_(std::find(words.begin(), words.end(), prefix) != words.end())
{
    // A node is a terminal node if its prefix exists as a word in its collection of words
    // A node is a leaf if it is terminal, and its prefix is the only word in its collection of words
    leaf_ = words.size() == 1 && terminal_;
    if(!leaf_)
    {
        // Naturally, children only need to be made for non-leaf nodes.
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
        // If there's only one word, then only one child needs to be made for this node.
        const auto firstLetter{ words.front().front() };
        children.try_emplace(firstLetter, std::shared_ptr<TrieNode>(new TrieNode(words, childLevel, prefix + firstLetter)));
    }
    else
    {
        std::vector<std::string> childWords{ };
        /* The potential prefixes for the child nodes are the parents prefix with each letter
         * of the alphabet appended. Create each potential child prefix from the alphabet,
         * and iterate through the parents words to see if there's a word with that prefix.
         * 
         * If so, collect it. After iterating through every word, if the list of child words
         * is not empty, initialize a new child with those words, storing it in the children
         * of the parent with the letter of the alphabet it corresponds to.
         */
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
                    children.try_emplace(letter, std::shared_ptr<TrieNode>(new TrieNode(childWords, childLevel, childPrefix)));
                    childWords.clear();
                }
            }
        }
    }
}

bool TrieNode::ContainsPrefix(const std::string& word) const
{
    return FindNodeWithPrefix(prefix).has_value();
}

bool TrieNode::ContainsWord(const std::string& word) const
{
    if(const auto wordAsPrefix{ FindNodeWithPrefix(prefix) }; wordAsPrefix)
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
    if(prefix.length() == level)
    {
        return this->prefix == prefix ? std::optional<std::shared_ptr<const TrieNode>>{ shared_from_this() } :  std::optional<std::shared_ptr<const TrieNode>>{ };
    }
    else if(prefix.length() < level)
    {
        if(auto child{ children.find(prefix.at(level)) }; child != children.end())
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
        if(child->leaf_)
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

bool TrieNode::leaf() const
{
    return leaf_;
}

bool TrieNode::terminal() const
{
    return terminal_;
}
