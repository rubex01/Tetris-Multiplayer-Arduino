#ifndef SRC_SBLOCK_SBLOCK_H_
#define SRC_SBLOCK_SBLOCK_H_

#include "../Block.h"


class SBlock : public Block {
 public:
    SBlock(int xPos, int yPos);
    bool checkBlock();
};

#endif 
