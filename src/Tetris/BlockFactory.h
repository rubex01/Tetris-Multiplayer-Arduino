#ifndef SRC_BLOCKFACTORY_BLOCKFACTORY_H_
#define SRC_BLOCKFACTORY_BLOCKFACTORY_H_

#include "Block.h"



class BlockFactory {
 public:
    static Block *createBlock(int choice);

};

#endif 
