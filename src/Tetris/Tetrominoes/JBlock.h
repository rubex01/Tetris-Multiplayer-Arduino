#ifndef SRC_JBLOCK_JBLOCK_H_
#define SRC_JBLOCK_JBLOCK_H_

#include "../Block.h"


class JBlock : public Block {
 public:
    JBlock(int xPos, int yPos);
    bool checkBlock();
};

#endif 
