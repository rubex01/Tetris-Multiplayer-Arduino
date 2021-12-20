#ifndef SRC_TBLOCK_TBLOCK_H_
#define SRC_TBLOCK_TBLOCK_H_

#include "../Block.h"


class TBlock : public Block {
 public:
    TBlock(int xPos, int yPos);
    bool checkBlock();
};

#endif 
