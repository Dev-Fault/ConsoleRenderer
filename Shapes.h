#pragma once
#include "Vector2.h"

namespace csr
{
	typedef std::vector<std::vector<char>> CharGrid;

	class Shape
	{
	protected:
		unsigned int width, height;
		Vector2 position, topLeft, topRight, bottomLeft, bottomRight;
		char drawChar;
		CharGrid drawing;

		void Initialize()
		{
			topLeft = Vector2(0, 0);
			topRight = Vector2(width, 0);
			bottomLeft = Vector2(0, height);
			bottomRight = Vector2(width, height);

			for (int r = 0; r != height; r++)
			{
				std::vector<char> row;
				for (int c = 0; c != width; c++)
				{
					row.push_back('\0');
				}
				drawing.push_back(row);
			}
		}

	public:
		static enum RotationDirection { LEFT, RIGHT };

		Vector2 GetPosition() const
		{
			return position;
		}

		Vector2 GetTopLeft() const
		{
			return topLeft;
		}

		Vector2 GetTopRight() const
		{
			return topRight;
		}

		Vector2 GetBottomLeft() const
		{
			return bottomLeft;
		}

		Vector2 GetBottomRight() const
		{
			return bottomRight;
		}

		Vector2 GetRelativeTopLeft() const
		{
			return position + topLeft;
		}

		Vector2 GetRelativeTopRight() const
		{
			return position + topRight;
		}

		Vector2 GetRelativeBottomLeft() const
		{
			return position + bottomLeft;
		}

		Vector2 GetRelativeBottomRight() const
		{
			return position + bottomRight;
		}

		void Translate(const Vector2& translation)
		{
			position.x += translation.x;
			position.y += translation.y;
		}

		void Rotate(RotationDirection rotationDirection, char count = 1)
		{
			for (int i = 0; i != count % 4; i++)
			{
				CharGrid rotatedDrawing;

				if (rotationDirection == RotationDirection::LEFT)
				{
					for (int c = width - 1; c >= 0; c--)
					{
						std::vector<char> row;
						for (int r = 0; r != height; r++)
						{
							row.push_back(drawing[r][c]);
						}
						rotatedDrawing.push_back(row);
					}
				}
				else
				{
					for (int c = 0; c != width; c++)
					{
						std::vector<char> row;
						for (int r = height - 1; r >= 0; r--)
						{
							row.push_back(drawing[r][c]);
						}
						rotatedDrawing.push_back(row);
					}
				}

				unsigned int temp = height;
				height = width;
				width = temp;

				drawing = rotatedDrawing;
			}			
		}

		CharGrid& GetDrawing() { return drawing; }
	};

	class Rectangle : public Shape
	{
	private:

	public:
		Rectangle(unsigned int width, unsigned int height, char drawChar = '#')
		{
			this->width = width;
			this->height = height;
			this->drawChar = drawChar;
			Initialize();

			for (int r = 0; r != height; r++)
			{
				for (int c = 0; c != width; c++)
				{
					drawing[r][c] = drawChar;
				}
			}
		}
	};

	class Triangle : public Shape
	{
	private:
		unsigned int base;

	public:
		static enum TriangleType { RIGHT_TRIANGLE, EQUILATERAL_TRIANGLE };

		Triangle(unsigned int base, unsigned int height, TriangleType triangleType = RIGHT_TRIANGLE, char drawChar = '#')
		{
			this->height = height;
			this->base = base;
			this->width = base;
			this->drawChar = drawChar;
			Initialize();

			int columns, rows;
			switch (triangleType)
			{
			case RIGHT_TRIANGLE:
				columns = base;
				for (int r = height - 1; r >= 0; r--)
				{
					for (int c = 0; c != columns; c++)
					{
						drawing[r][c] = drawChar;
					}
					columns--;
					if (columns < 0) columns = 0;
				}
				break;
			case EQUILATERAL_TRIANGLE:
				columns = base;
				rows = 0;
				for (int r = height - 1; r >= 0; r--)
				{
					for (int c = 0; c != columns; c++)
					{
						int columnIndex = c + rows;
						if (columnIndex < base)
						{
							drawing[r][columnIndex] = drawChar;
						}
					}
					columns -= 2;
					rows++;
					if (columns < 0) columns = 0;
				}
				break;
			}

		}
	};

	class Circle : public Shape
	{
	private:
		unsigned int diameter;

	public:
		Circle(unsigned int diameter, char drawChar = '#')
		{
			this->diameter = diameter;
			this->width = diameter;
			this->height = diameter;
			this->drawChar = drawChar;

			Initialize();

			for (int r = 0; r != height; r++)
			{
				for (int c = 0; c != width; c++)
				{
					drawing[r][c] = drawChar;
				}
			}

			if (diameter > 2)
			{
				drawing[0][0] = '\0';
				drawing[0][width - 1] = '\0';
				drawing[height - 1][0] = '\0';
				drawing[height - 1][width - 1] = '\0';
			}
		}
	};
}