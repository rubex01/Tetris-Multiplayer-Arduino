#ifndef SRC_OBLOCK_OBLOCK_H_
#define SRC_OBLOCK_OBLOCK_H_

#include "../Block.h"


class OBlock : public Block {
 public:
    OBlock(int xPos, int yPos);
    bool checkBlock();
};

#endif 
