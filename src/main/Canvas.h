/**
 * @file Canvas.h
 * @brief Describes the Canvas responsible for holding all the layers and
 * curves.
 * @author Samuel Gauthier
 * @version 1.0
 * @date 2018-09-14
 */
#ifndef CANVAS_H
#define CANVAS_H

//#include "Layer.h"

class Canvas {

public:
    Canvas(unsigned int width, unsigned int height);
    ~Canvas();

    unsigned int getWidth();
    unsigned int getHeight();
    

private:
   unsigned int width; 
   unsigned int height; 
   //unique_ptr<Layer> root;
};

#endif /* ifndef CANVAS_H */
