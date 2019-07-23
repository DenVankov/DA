#ifndef DA2_BTREE_H
#define DA2_BTREE_H

#include <exception>
#include <new>
#include <cstdlib>
#include <cstdio>
#include "TString.h"
#include <iostream>

typedef unsigned long long TYPE;

class TBTree {
public:
    typedef TString TKey;
    typedef TYPE TValue;

    struct TData {
        TKey key;
        TValue value;
    };

    struct TNode {
        size_t n;
        bool leaf;
        TData *data;
        TNode **child;
    };

    explicit TBTree(size_t t);
    ~TBTree();

    void Insert(const TData &data);
    void Remove(const TKey &key);
    TData* Find(const TKey &key);

    bool Save(const char *filename);
    bool Load(const char *filename);
private:
    TNode *mroot;
    size_t mt;

    TNode* mCreateNode();
    TData* mFind(TNode *node, const TKey &key);
    void mDeleteNode(TNode *node);
    void mDeleteTree(TNode *node);
    void mShiftLeft(TNode *node, size_t index, size_t index2);
    void mShiftRight(TNode *node, size_t index, size_t index2);
    void mFlowLeft(TNode *parent, size_t index);
    void mFlowRight(TNode *parent, size_t index);
    void mSplitNode(TNode *parent, TNode *node, size_t index);
    void mMergeNode(TNode *parent, size_t index);
    void mInsertNonFull(TNode *node, const TData &data);
    void mRemove(TNode *node, const TKey &key);
    void mFixChild(TNode *node, size_t index);
    bool mSave(FILE *f, TNode *node);
    bool mLoad(FILE *f, TNode *node);
};
#endif //DA2_BTREE_H
