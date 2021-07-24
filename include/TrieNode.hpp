#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace Scrabble
{
    class TrieNode : public std::enable_shared_from_this<TrieNode>
    {
        public:
            TrieNode(const std::vector<std::string>& words);

            bool ContainsPrefix(const std::string& word) const;

            bool ContainsWord(const std::string& word) const;

            std::optional<std::shared_ptr<const TrieNode>> FindNodeWithPrefix(const std::string& prefix) const;

            const std::vector<char> ValidFirstLetters(const std::string& word) const;

            const std::vector<char> ValidLastLetters(const std::string& word) const;

            bool leaf() const;

            bool terminal() const;

        private:
            TrieNode(const std::vector<std::string>& words, const int level, const std::string& prefix);

            void CreateChildren();

            bool leaf_;
            bool terminal_;
            int  level;
            std::vector<std::string> words;
            std::string prefix;
            std::vector<std::vector<std::shared_ptr<TrieNode>>> levels;
            std::map<char, std::shared_ptr<TrieNode>> children;
        
    };
}

#endif TRIENODE_HPP