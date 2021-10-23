#include <chrono>
#include <thread>
#include "ConsoleRenderer.h"

using namespace csr;

void Sleep(int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

ConsoleRenderer::ConsoleRenderer(unsigned int width, unsigned int height, char emptyCellChar)
{
	this->width = width * 2;
	this->height = height;
	this->emptyCellChar = emptyCellChar;
	InitializeGrid();
	FillGrid();
}

ConsoleRenderer::~ConsoleRenderer()
{
	for (int i = 0; i != shapes.size(); i++)
	{
		delete shapes[i];
	}
}

void ConsoleRenderer::InitializeGrid()
{
	for (int r = 0; r != height; r++)
	{
		std::vector<char> row;
		for (int c = 0; c != width; c++)
		{
			row.push_back('\0');
		}
		background.push_back(row);
	}
}

void ConsoleRenderer::AddShape(Shape* shape)
{
	shapes.push_back(shape);
}

void ConsoleRenderer::Render(bool clearScreen)
{
	if (clearScreen) system("cls");

	for (int i = 0; i != shapes.size(); i++)
	{
		Draw(shapes[i]);
	}
	for (int r = 0; r != height; r++)
	{
		for (int c = 0; c != width; c++)
		{
			std::cout << background[r][c];
		}
		std::cout << '\n';
	}
	Sleep(10);
	FillGrid();
}

void ConsoleRenderer::FillGrid()
{
	for (int r = 0; r != background.size(); r++)
	{
		for (int c = 0; c != background[r].size(); c++)
		{
			if (c % 2 == 0)
			{
				background[r][c] = emptyCellChar;
			}
			else
			{
				background[r][c] = ' ';
			}
		}
	}
}

void ConsoleRenderer::Draw(Shape* shape)
{
	CharGrid drawing = shape->GetDrawing();

	for (int r = 0; r != drawing.size(); r++)
	{
		for (int c = 0; c != drawing[r].size(); c++)
		{
			int columnOffset = (shape->GetPosition().x + c) * 2;
			int rowOffset = shape->GetPosition().y + r;
			bool columnInRange = columnOffset < width && columnOffset >= 0;
			bool rowInRange = rowOffset < height && rowOffset >= 0;
			if (columnInRange && rowInRange)
			{
				if (drawing[r][c] != '\0')
				{
					background[rowOffset][columnOffset] = drawing[r][c];
				}
			}
		}
	}
}

bool ConsoleRenderer::PointInBounds(const Vector2& point) const
{
	bool xInBounds = point.x <= GetWidth() && point.x >= 0;
	bool yInBounds = point.y <= GetHeight() && point.y >= 0;

	return xInBounds && yInBounds;
}

bool ConsoleRenderer::ShapeInBounds(const Shape* shape)
{
	bool topLeftInBounds = PointInBounds(shape->GetRelativeTopLeft());
	bool topRightInBounds = PointInBounds(shape->GetRelativeTopRight());
	bool bottomLeftInBounds = PointInBounds(shape->GetRelativeBottomLeft());
	bool bottomRightInBounds = PointInBounds(shape->GetRelativeBottomRight());

	return topLeftInBounds && topRightInBounds && bottomLeftInBounds && bottomRightInBounds;
}

bool ConsoleRenderer::ShapeInBounds(const Shape* shape, const Vector2& translation)
{
	bool topLeftInBounds = PointInBounds(shape->GetRelativeTopLeft() + translation);
	bool topRightInBounds = PointInBounds(shape->GetRelativeTopRight() + translation);
	bool bottomLeftInBounds = PointInBounds(shape->GetRelativeBottomLeft() + translation);
	bool bottomRightInBounds = PointInBounds(shape->GetRelativeBottomRight() + translation);

	return topLeftInBounds && topRightInBounds && bottomLeftInBounds && bottomRightInBounds;
}

bool ConsoleRenderer::ShapeCollidesWithShape(const Shape* shape1, const Shape* shape2)
{
	bool xCollides = shape1->GetRelativeTopLeft().x <= shape2->GetRelativeBottomRight().x && shape1->GetRelativeBottomRight().x >= shape2->GetRelativeTopLeft().x;
	bool yCollides = shape1->GetRelativeTopLeft().y <= shape2->GetRelativeBottomRight().y && shape1->GetRelativeBottomRight().y >= shape2->GetRelativeTopLeft().y;
	return xCollides && yCollides;
}