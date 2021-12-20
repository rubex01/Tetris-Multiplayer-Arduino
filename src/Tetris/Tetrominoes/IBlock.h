#ifndef SRC_IBLOCK_IBLOCK_H_
#define SRC_IBLOCK_IBLOCK_H_

#include "../Block.h"


class IBlock : public Block {
 public:
    IBlock(int xPos, int yPos);
    bool checkBlock();
};

#endif 
