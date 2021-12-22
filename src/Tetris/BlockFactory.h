#ifndef SRC_TETRIS_BLOCKFACTORY_H_
#define SRC_TETRIS_BLOCKFACTORY_H_

#include "Block.h"



class BlockFactory {
 public:
    static Block *createBlock(int choice);
};

#endif  // SRC_TETRIS_BLOCKFACTORY_H_
