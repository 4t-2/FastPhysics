#pragma once

#define AGLDIR <AGL/agl.hpp>

#include AGLDIR

namespace phy
{
	class Circle : public agl::Drawable
	{
		private:
			agl::Circle &shape;

		public:
			agl::Vec<float, 2> position;
			agl::Vec<float, 2> posOffset;
			agl::Vec<float, 2> velocity;
			agl::Vec<float, 2> force;
			float			   radius = 1;
			float			   mass	  = 1;

			Circle(agl::Circle &shape) : shape(shape)
			{
			}

			void update();

			void drawFunction(agl::RenderWindow &window) override
			{
				shape.setPosition(position);
				shape.setSize({radius, radius});

				window.drawShape(shape);
			}
	};

	// class Rectangle : public agl::Drawable
	// {
	// 	private:
	// 		agl::Rectangle &shape;
	//
	// 	public:
	// 		agl::Vec<float, 2> position;
	// 		agl::Vec<float, 2> velocity;
	// 		agl::Vec<float, 2> force;
	// 		agl::Vec<float, 2> size;
	// 		float			   mass;
	//
	// 		Rectangle(agl::Rectangle &shape) : shape(shape)
	// 		{
	// 		}
	//
	// 		void update()
	// 		{
	// 			velocity = velocity + (force * (1. / mass));
	// 			force	 = {0, 0};
	//
	// 			position = position + velocity;
	// 		}
	//
	// 		void drawFunction(agl::RenderWindow &window) override
	// 		{
	// 			shape.setPosition(position);
	// 			shape.setSize(size);
	//
	// 			window.drawShape(shape);
	// 		}
	// };

	class Environment : public agl::Drawable
	{
		private:
			std::vector<Circle> circleVec;
			// std::vector<Rectangle> rectangleVec;
			agl::Circle &circleShape;
			// agl::Rectangle &rectangleShape;

		public:
			float density = 0.1; // keep between 1 and 0

			Environment(agl::Circle &circleShape) : circleShape(circleShape)
			{
			}

			void addCircle(agl::Vec<float, 2> position, float radius, agl::Vec<float, 2> force, float mass);

			// void addRectangle(agl::Vec<float, 2> position, agl::Vec<float, 2> size,
			// agl::Vec<float, 2> force, float mass)
			// {
			// 	rectangleVec.emplace_back(Rectangle(rectangleShape));
			// 	rectangleVec[rectangleVec.size() - 1].position = position;
			// 	rectangleVec[rectangleVec.size() - 1].size	   = size;
			// 	rectangleVec[rectangleVec.size() - 1].force	   = force;
			// 	rectangleVec[rectangleVec.size() - 1].mass	   = mass;
			// }

			void update();

			void drawFunction(agl::RenderWindow &window) override
			{
				for (Circle &circle : circleVec)
				{
					window.draw(circle);
				}
				// for (Rectangle &rectangle : rectangleVec)
				// {
				// 	window.draw(rectangle);
				// }
			}

			std::vector<Circle> &getCircleVec();
	};
} // namespace phy
