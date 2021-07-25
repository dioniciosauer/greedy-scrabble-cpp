#ifndef TRIENODE_HPP
#define TRIENODE_HPP

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace Scrabble
{
    class TrieNode
    {
        public:
            TrieNode(const std::vector<std::string>& words);

            bool ContainsPrefix(const std::string& prefix) const;

            bool ContainsWord(const std::string& word) const;

            std::optional<std::shared_ptr<const TrieNode>> FindNodeWithPrefix(const std::string& prefix) const;

            bool IsLeaf() const;

            const std::vector<char> ValidFirstLetters(const std::string& word) const;

            const std::vector<char> ValidLastLetters(const std::string& word) const;

            bool terminal() const;

        private:
            TrieNode(const int level, const std::string& prefix, const bool terminal);

            bool AddWord(const std::string& word);

            bool IsRoot() const;

            void terminal(const bool terminal);

            bool                terminal_;
            const int           level;
            const std::string   prefix_;
            std::map<char, std::shared_ptr<TrieNode>> children;
        
    };
}

#endif TRIENODE_HPP
