# Console Renderer

A simple console based renderer designed to draw simple shapes and translate or rotate them on a grid.

![Thumbnail](/images/thumbnail.png)

## How to use

To use the console renderer create an instance of the console renderer class specifying the desired width and height of the grid to be drawn. There is also a third optional parameter which sets the character to be used to represent points on the grid.
Once you have created a console renderer you can then create one of the three basic shapes rectangle, triangle, or circle. Each have slightly different constructors. Each shape instance should be created as a shape pointer to allow the renderer easy access. After creating your shape use the AddShape method in the console renderer class. Shapes can be translated or rotated using the corresponding functions of the shape class. After adding the shapes you can finally call the Render function on the console renderer to have it draw everything to stdout. The renderer also supports basic collision detection for moving objects within a loop.