#include "BTree.h"

TBTree::TBTree(size_t t) {
    mt = t < 2 ? 2 : t;
    mroot = mCreateNode();
}

TBTree::~TBTree() {
    mDeleteTree(mroot);
}

void TBTree::Insert(const TData &data) {
    TNode* root = mroot;

    if (root->n == mt * 2 - 1) {
        TNode* rootNew = mCreateNode();

        mroot = rootNew;
        rootNew->leaf = false;
        rootNew->n = 0;
        rootNew->child[0] = root;

        mSplitNode(rootNew, root, 0);
        mInsertNonFull(rootNew, data);
    } else {
        mInsertNonFull(root, data);
    }
}

TBTree::TData* TBTree::Find(const TKey &key) {
    return mFind(mroot, key);
}

void TBTree::Remove(const TBTree::TKey &key) {
    mRemove(mroot, key);

    if (!mroot->leaf && mroot->n == 0) {
        TNode* rootNew = mroot->child[0];
        mDeleteNode(mroot);
        mroot = rootNew;
    }
}

TBTree::TNode* TBTree::mCreateNode() {
    TNode* node = nullptr;
    node = new TNode;
    node->data = new TData[mt * 2 - 1];
    node->child = new TNode*[mt * 2];

    if (!node->data || !node->child) {
        printf("ERROR: No memory\n");
        exit(0);
    }

    node->n = 0;
    node->leaf = true;

    size_t cnt = mt * 2;

    for (size_t i = 0; i < cnt; ++i) {
        node->child[i] = nullptr;
    }

    return node;
}

TBTree::TData* TBTree::mFind(TNode *node, const TKey &key) {
    size_t i = 0;

    while (i < node->n && node->data[i].key < key) {
        i += 1;
    }

    if (i < node->n && node->data[i].key == key) {
        return &node->data[i];
    }

    if (!node->leaf) {
        return mFind(node->child[i], key);
    }

    return nullptr;
}

void TBTree::mDeleteNode(TNode *node) {
    delete[] node->data;
    delete[] node->child;
    delete node;
}

void TBTree::mDeleteTree(TNode *node) {
    if (node == nullptr) {
        return;
    }

    for (size_t i = 0; i < node->n + 1; ++i) {
        mDeleteTree(node->child[i]);
    }

    mDeleteNode(node);
}

void TBTree::mShiftLeft(TNode *node, size_t index, size_t index2) {
    for (size_t i = index; i < node->n; ++i) {
        node->data[i - 1].value = node->data[i].value;
        node->data[i - 1].key.Swap(node->data[i].key);
    }

    if (!node->leaf) {
        for (size_t i = index2; i < node->n + 1; ++i) {
            node->child[i - 1] = node->child[i];
        }
    }

    node->child[node->n] = nullptr;
    node->n -= 1;
}

void TBTree::mShiftRight(TNode *node, size_t index, size_t index2) {
    /*for (int i = node->n - 1; i >= index; --i) {
        node->data[i + 1].value = node->data[i].value;
        node->data[i + 1].key.Swap(node->data[i].key);
    }
*/
    for (int i = static_cast<int>(node->n) - 1; i >= static_cast<int>(index); --i)
    {
        node->data[i + 1].value = node->data[i].value;
        node->data[i + 1].key.Swap(node->data[i].key);
    }

    if (!node->leaf) {
        for (size_t i = node->n; i >= index2; --i) {
            node->child[i + 1] = node->child[i];
        }
    }

    node->n += 1;
}

void TBTree::mFlowLeft(TNode *parent, size_t index) {
    TNode* left = parent->child[index];
    TNode* right = parent->child[index + 1];

    left->data[left->n].value = parent->data[index].value;
    left->data[left->n].key.Swap(parent->data[index].key);

    parent->data[index].value = right->data[0].value;
    parent->data[index].key.Swap(right->data[0].key);

    if (!right->leaf) {
        left->child[left->n + 1] = right->child[0];
    }

    mShiftLeft(right, 1, 1);

    left->n += 1;
}

void TBTree::mFlowRight(TNode *parent, size_t index) {
    TNode* left = parent->child[index];
    TNode* right = parent->child[index + 1];

    mShiftRight(right, 0, 0);

    right->data[0].value = parent->data[index].value;
    right->data[0].key.Swap(parent->data[index].key);

    parent->data[index].value = left->data[left->n - 1].value;
    parent->data[index].key.Swap(left->data[left->n - 1].key);

    if (!left->leaf) {
        right->child[0] = left->child[left->n];
    }

    left->child[left->n] = nullptr;
    left->n -= 1;
}

void TBTree::mSplitNode(TNode *parent, TNode *node, size_t index) {
    TNode* node2 = mCreateNode();

    node2->leaf = node->leaf;
    node2->n = mt - 1;
    node->n = node2->n;

    for (size_t i = 0; i < node2->n; ++i) {
        node2->data[i].value = node->data[i + mt].value;
        node2->data[i].key.Swap(node->data[i + mt].key);
    }

    if (!node->leaf) {
        for (size_t i = 0; i < mt; ++i) {
            node2->child[i] = node->child[i + mt];
        }
    }

    mShiftRight(parent, index, index + 1);

    parent->child[index + 1] = node2;

    parent->data[index].value = node->data[mt - 1].value;
    parent->data[index].key.Swap(node->data[mt - 1].key);
}

void TBTree::mMergeNode(TNode *parent, size_t index) {
    TNode* left = parent->child[index];
    TNode* right = parent->child[index + 1];

    left->data[left->n].value = parent->data[index].value;
    left->data[left->n].key.Swap(parent->data[index].key);

    for (size_t i = 0; i < right->n; ++i) {
        left->data[left->n + i + 1].value = right->data[i].value;
        left->data[left->n + i + 1].key.Swap(right->data[i].key);
    }

    if (!right->leaf) {
        for (size_t i = 0; i < right->n + 1; ++i) {
            left->child[left->n + i + 1] = right->child[i];
        }
    }

    left->n += right->n + 1;

    mShiftLeft(parent, index + 1, index + 2);
    mDeleteNode(right);
}

void TBTree::mInsertNonFull(TNode *node, const TData &data) {
    int i = static_cast<int>(node->n) - 1;

    if (node->leaf) {
        while (i >= 0 && data.key < node->data[i].key) {
            node->data[i + 1].value = node->data[i].value;
            node->data[i + 1].key.Swap(node->data[i].key);
            i -= 1;
        }

        node->data[i + 1] = data;
        node->n += 1;
    } else {
        while (i >= 0 && data.key < node->data[i].key) {
            i -= 1;
        }

        i += 1;

        if (node->child[i]->n == mt * 2 - 1) {
            mSplitNode(node, node->child[i], i);

            if (node->data[i].key < data.key) {
                i += 1;
            }
        }

        mInsertNonFull(node->child[i], data);
    }
}

void TBTree::mRemove(TBTree::TNode *node, const TBTree::TKey &key) {
    size_t i = 0;

    while (i < node->n && node->data[i].key < key) {
        i += 1;
    }

    if (i < node->n && node->data[i].key == key) {
        if (node->leaf) {
            mShiftLeft(node, i + 1, i + 2);
        } else {
            TNode* otherNode = node->child[i + 1];

            while (otherNode->child[0] != nullptr) {
                otherNode = otherNode->child[0];
            }

            node->data[i].value = otherNode->data[0].value;
            node->data[i].key.Swap(otherNode->data[0].key);

            mRemove(node->child[i + 1], otherNode->data[0].key);
            mFixChild(node, i + 1);
        }
    } else if (!node->leaf) {
        mRemove(node->child[i], key);
        mFixChild(node, i);
    }
}

void TBTree::mFixChild(TNode *node, size_t index) {
    if (node->child[index]->n >= mt) {
        return;
    }

    TNode* left = index > 0 ? node->child[index - 1] : nullptr;
    TNode* right = index < node->n ? node->child[index + 1] : nullptr;

    if (left != nullptr && right != nullptr) {
        if (left->n >= mt) {
            mFlowRight(node, index - 1);
        } else if (right->n >= mt) {
            mFlowLeft(node, index);
        } else {
            mMergeNode(node, index - 1);
        }
    } else if (left != nullptr) {
        if (left->n >= mt) {
            mFlowRight(node, index - 1);
        } else {
            mMergeNode(node, index - 1);
        }
    } else {
        if (right->n >= mt) {
            mFlowLeft(node, index);
        }
        else {
            mMergeNode(node, index);
        }
    }
}

bool TBTree::Save(const char *filename) {
    FILE* f = fopen(filename, "wb");

    if (!f) {
        printf("ERROR: Can`t open the file %s", filename);
        return false;
    }

    if (fwrite(&mt, sizeof(mt), 1, f) != 1) {
        return false;
    }

    bool ans = mSave(f, mroot);

    fclose(f);

    return ans;
}

bool TBTree::Load(const char *filename) {
    FILE* f = fopen(filename, "rb");

    if (!f) {
        printf("ERROR: Can`t open the file \n");
        return false;
    }

    if (fread(&mt, sizeof(mt), 1, f) != 1) {
        return false;
    }

    TNode* rootNew = mCreateNode();
    bool ans = mLoad(f, rootNew);
    fclose(f);

    if (ans) {
        mDeleteTree(mroot);
        mroot = rootNew;
        return true;
    } else {
        mDeleteTree(rootNew);
        return false;
    }
}

bool TBTree::mSave(FILE *f, TNode *node) {
    if (fwrite(&node->n, sizeof(node->n), 1, f) != 1) {
        return false;
    }

    if (fwrite(&node->leaf, sizeof(node->leaf), 1, f) != 1) {
        return false;
    }

    for (size_t i = 0; i < node->n; ++i) {
        const TData* data = &node->data[i];
        const size_t strLen = data->key.Length();
        const char* str = data->key.GetStr();

        if (fwrite(&strLen, sizeof(strLen), 1, f) != 1) {
            return false; }

        if (fwrite(str, sizeof(char), strLen, f) != strLen) {
            return false;
        }

        if (fwrite(&data->value, sizeof(data->value), 1, f) != 1) {
            return false;
        }
    }

    if (!node->leaf) {
        for (size_t i = 0; i < node->n + 1; ++i) {
            if (!mSave(f, node->child[i])) {
                return false;
            }
        }
    }

    return true;
}

bool TBTree::mLoad(FILE *f, TBTree::TNode *node) {
    char buffer[257];

    if (fread(&node->n, sizeof(node->n), 1, f) != 1) {
        return false;
    }

    if (fread(&node->leaf, sizeof(node->leaf), 1, f) != 1) {
        return false;
    }

    for (size_t i = 0; i < node->n; ++i) {
        TData* data = &node->data[i];
        size_t strLen = 0;

        if (fread(&strLen, sizeof(strLen), 1, f) != 1) {
            return false;
        }

        if (fread(buffer, sizeof(char), strLen, f) != strLen) {
            return false;
        }

        if (fread(&data->value, sizeof(data->value), 1, f) != 1) {
            return false;
        }

        buffer[strLen] = '\0';
        data->key = buffer;
    }

    if (!node->leaf) {
        for (size_t i = 0; i < node->n + 1; ++i) {
            node->child[i] = mCreateNode();
            if (!mLoad(f, node->child[i])) {
                return false;
            }
        }
    }

    return true;
}