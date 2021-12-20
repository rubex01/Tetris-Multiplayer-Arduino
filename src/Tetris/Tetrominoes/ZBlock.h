#ifndef SRC_ZBLOCK_ZBLOCK_H_
#define SRC_ZBLOCK_ZBLOCK_H_

#include "../Block.h"


class ZBlock : public Block {
 public:
    ZBlock(int xPos, int yPos);
    bool checkBlock();
    
};

#endif 
