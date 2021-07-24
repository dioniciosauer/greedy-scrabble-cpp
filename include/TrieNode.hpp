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

            bool leaf() const;

            bool terminal() const;

            const std::map<char, std::shared_ptr<TrieNode>>& children() const;

            const std::vector<char>& ValidLastLetters(const std::string& word);

            const std::vector<char>& ValidFirstLetter(const std::string& prefix);

            std::optional<std::shared_ptr<const TrieNode>> GetNodeWithPrefix(const std::string& prefix) const;

            bool ContainsPrefix(const std::string& word);

            bool ContainsWord(const std::string& word) const;

        private:
            TrieNode(const std::vector<std::string>& words, const int level, const std::string& prefix);

            void CreateChildren();

            bool leaf;
            bool terminal;
            int  level;
            std::vector<std::string> words;
            std::string prefix;
            std::vector<std::vector<std::shared_ptr<TrieNode>>> levels;
            std::map<char, std::shared_ptr<TrieNode>> children;
        
    }
}

#endif TRIENODE_HPP