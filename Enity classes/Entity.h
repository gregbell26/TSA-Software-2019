//
// Created by jimmy on 9/18/2019.
//

#ifndef GITHUB_ENTITY_H
#define GITHUB_ENTITY_H
struct sheetLocation{
    int xStart, xEnd;
    int yStart, yEnd;
};

class Entity {
    private:
        //going to be array if multiple sprites are needed
        sheetLocation* sheetPositions;
        int activeSprite;
        double xPosition;
        double yPosition;
    public:
        
};


#endif //GITHUB_ENTITY_H
