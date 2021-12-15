#ifndef SRC_SQUARE_SQUARE_H_
#define SRC_SQUARE_SQUARE_H_

#include "Block.h"


class Square : public Block {
 public:
    Square(int xPos, int yPos);
    bool checkBlock();
};

#endif 
