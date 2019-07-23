#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <time.h>

const int ALPHABET_SIZE = 28;
int REMINDER, END;
std::string text;
size_t SIZE;

class SuffixTreeNode {
public:
    SuffixTreeNode(int start, int *end);
    void ExtendSuffixTree(int pos);
    int EdgeLength();
    void GetLinearCircleString();
    void SetSuffixLink();
private:
    std::shared_ptr<SuffixTreeNode> children[ALPHABET_SIZE];
    std::shared_ptr<SuffixTreeNode> suffix_link;
    int start;
    int *end;
    int suffix_index;
};

struct ActivePoint {
    std::shared_ptr<SuffixTreeNode> node;
    int symbol;
    int length;
};

ActivePoint actPoint;
std::shared_ptr<SuffixTreeNode> root;

SuffixTreeNode::SuffixTreeNode(int start, int *end)
{
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        this->children[i] = nullptr;
    }
    this->suffix_link = root;
    this->start = start;
    this->end = end;
    this->suffix_index = END;
}

int SuffixTreeNode::EdgeLength()
{
    return *end - start + 1;
}

void SuffixTreeNode::SetSuffixLink()
{
    suffix_link = root;
}

void SuffixTreeNode::ExtendSuffixTree(int pos)
{
    std::shared_ptr<SuffixTreeNode> cur = root;
    std::shared_ptr<SuffixTreeNode> link = root;
    std::shared_ptr<SuffixTreeNode> next_node, cur_node;

    ++REMINDER;

    while (REMINDER > 0) {

        if (actPoint.length == 0) {
            actPoint.symbol = pos;
        }

        int symbol = text[actPoint.symbol] - 'a';
        if (!actPoint.node->children[symbol]) {
            actPoint.node->children[symbol] = std::make_shared<SuffixTreeNode>(pos, &END);

            if (link != root) {
                link->suffix_link = actPoint.node;
                link = root;
            } else link = actPoint.node;
        } else {

            if (actPoint.length >= actPoint.node->children[symbol]->EdgeLength()) {
                int length = actPoint.node->children[symbol]->EdgeLength();
                actPoint.length -= length;
                actPoint.node = actPoint.node->children[symbol];
                actPoint.symbol += length;
                continue;
            }

            if (text[actPoint.node->children[symbol]->start + actPoint.length] == text[pos]) {
                actPoint.length++;

                if (link != root)
                    link->suffix_link = actPoint.node;
                break;
            }

            cur = actPoint.node->children[symbol];

            int *position = new int;
            *position = cur->start + actPoint.length - 1;
            int next_pos = cur->start + actPoint.length;
            int next_symbol = text[next_pos] - 'a';
            int cur_symbol = text[pos] - 'a';

            cur_node = std::make_shared<SuffixTreeNode>(pos, &END);
            next_node = std::make_shared<SuffixTreeNode>(cur->start, position);

            actPoint.node->children[symbol] = next_node;
            cur->start = next_pos;
            next_node->children[next_symbol] = cur;
            next_node->suffix_index = -1;
            next_node->children[cur_symbol] = cur_node;

            if (link != root)
                link->suffix_link = next_node;
            link = next_node;
        }

        REMINDER--;

        if (actPoint.node == root && actPoint.length > 0) {
            actPoint.length--;
            actPoint.symbol = pos - REMINDER + 1;
        }
        else {
            actPoint.node = actPoint.node->suffix_link;
        }

    }
}

void SuffixTreeNode::GetLinearCircleString()
{
    SuffixTreeNode *cur = root.get();
    int size = 0, k, i;
    while (true) {
        for (i = 0; i < ALPHABET_SIZE; ++i) {
            if (cur->children[i]) {
                for (k = cur->children[i]->start; k <= *(cur->children[i]->end); ++k) {
                    if (size < SIZE)
                        std::cout << text[k];
                    else {
                        std::cout << "\n";
                        return;
                    }
                    ++size;
                }

                cur = cur->children[i].get();
                break;
            }
        }
    }
}

int main()
{
    int tmp = -1;
    int i;

    while (std::cin >> text) {
        END = -1;
        REMINDER = 0;

        root = std::make_shared<SuffixTreeNode>(-1, &tmp);
        root->SetSuffixLink();

        actPoint.node = root;
        actPoint.length = 0;

        SIZE = text.size();
        text += text;
        for (i = 0; i < 2 * SIZE; ++i) {
            ++END;
            root->ExtendSuffixTree(END);
        }
        root->GetLinearCircleString();
    }
    return 0;
}