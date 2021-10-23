#pragma once
#include <iostream>
#include <vector>
#include "Shapes.h"

namespace csr
{
	class ConsoleRenderer
	{
	private:
		char emptyCellChar;
		unsigned int width;
		unsigned int height;
		CharGrid background;
		std::vector<Shape*> shapes;

		void InitializeGrid();
		void FillGrid();
		void Draw(Shape*);

	public:
		ConsoleRenderer(unsigned int, unsigned int, char = '.');
		~ConsoleRenderer();
		void AddShape(Shape* shape);
		void Render(bool clearScreen = true);

		int GetWidth() const { return width; }
		int GetHeight() const { return height; }

		bool PointInBounds(const Vector2& point) const;
		bool ShapeInBounds(const Shape* shape);
		bool ShapeInBounds(const Shape* shape, const Vector2& translation);
		bool ShapeCollidesWithShape(const Shape* shape1, const Shape* shape2);
	};
}