#include "BlockFactory.h"
#include "Tetrominoes/OBlock.h"
#include "Tetrominoes/SBlock.h"
#include "Tetrominoes/IBlock.h"
#include "Tetrominoes/ZBlock.h"
#include "Tetrominoes/TBlock.h"
#include "Tetrominoes/LBlock.h"
#include "Tetrominoes/JBlock.h"


Block* BlockFactory::createBlock(int choice) {
    if (choice == 0) {
        return new OBlock(4, 0);
    }
    if (choice == 1) {
        return new SBlock(4, 0);
    }
    if (choice == 2) {
        return new IBlock(4, 0);
    }
    if (choice == 3) {
        return new ZBlock(4, 0);
    }
    if (choice == 4) {
        return new TBlock(4, 0);
    }
    if (choice == 5) {
        return new LBlock(4, 0);
    }
    if (choice == 6) {
        return new JBlock(4, 0);
    }
}
