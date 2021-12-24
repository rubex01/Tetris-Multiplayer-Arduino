#include "BlockFactory.h"
#include "Tetrominoes/OBlock.h"
#include "Tetrominoes/SBlock.h"
#include "Tetrominoes/IBlock.h"
#include "Tetrominoes/ZBlock.h"
#include "Tetrominoes/TBlock.h"
#include "Tetrominoes/LBlock.h"
#include "Tetrominoes/JBlock.h"

/**
 * Creates a new Tetromino block depending on value given by param choice
 *
 * @param choice
 */
Block* BlockFactory::createBlock(int choice) {
    switch (choice) {
        case 1:
            return new OBlock(4, 0);
            break;
        case 2:
            return new SBlock(4, 0);
            break;
        case 3:
            return new IBlock(4, 0);
            break;
        case 4:
            return new ZBlock(4, 0);
            break;
        case 5:
            return new TBlock(4, 0);
            break;
        case 6:
            return new LBlock(4, 0);
            break;
        case 7:
            return new JBlock(4, 0);
            break;
    }
}
