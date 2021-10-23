#include <iostream>
#include "ConsoleRenderer.h"

using namespace csr;

int main()
{
	ConsoleRenderer consoleRenderer(24, 100, '.');
	Shape* leftBorder = new Rectangle(2, 16, 'X');
	Shape* rightBorder = new Rectangle(2, 16, 'X');
	Shape* topBorder = new Rectangle(16, 2, 'X');
	Shape* bottomBorder = new Rectangle(16, 2, 'X');
	Shape* leftEye = new Circle(4, 'O');
	Shape* rightEye = new Circle(4, 'O');
	Shape* nose = new Triangle(5, 4, Triangle::EQUILATERAL_TRIANGLE, '#');
	Shape* mouth = new Rectangle(10, 2, 'X');
	leftBorder->Translate(Vector2(2, 4)); 
	rightBorder->Translate(Vector2(20, 4));
	topBorder->Translate(Vector2(4, 2));
	bottomBorder->Translate(Vector2(4, 20));
	nose->Translate(Vector2(9, 11));
	nose->Rotate(Shape::RotationDirection::LEFT, 2);
	leftEye->Translate(Vector2(5, 6));
	rightEye->Translate(Vector2(14, 6));
	mouth->Translate(Vector2(6, 16));
	consoleRenderer.AddShape(leftBorder);
	consoleRenderer.AddShape(rightBorder);
	consoleRenderer.AddShape(topBorder);
	consoleRenderer.AddShape(bottomBorder);
	consoleRenderer.AddShape(nose);
	consoleRenderer.AddShape(leftEye);
	consoleRenderer.AddShape(rightEye);
	consoleRenderer.AddShape(mouth);
	consoleRenderer.Render();
}