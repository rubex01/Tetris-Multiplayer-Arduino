#ifndef SRC_LBLOCK_LBLOCK_H_
#define SRC_LBLOCK_LBLOCK_H_

#include "../Block.h"


class LBlock : public Block {
 public:
    LBlock(int xPos, int yPos);
    bool checkBlock();
};

#endif 
