#ifndef SRC_BLOCK_BLOCK_H_
#define SRC_BLOCK_BLOCK_H_

class Block {
 public:
   Block(int xPos, int yPos);
   ~Block();
   void initBlock();
   void updateBlock();
   void moveDown();
   void moveSideways(int direction);
   void reset(int direction);
   bool checkBlock();
   int** blockArray;
   int blockColor;

 protected:
   int xPos;
   int yPos;
};

#endif 
