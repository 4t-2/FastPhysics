#include "../inc/Environment.hpp"
#include <cmath>

void phy::Circle::update()
{
	velocity = velocity + (force * (1. / mass));
	force	 = {0, 0};

	position = position + posOffset;
	position = position + velocity;

	posOffset = {0, 0};
}

void phy::Environment::addCircle(agl::Vec<float, 2> position, float radius, agl::Vec<float, 2> force, float mass)
{
	circleVec.emplace_back(Circle(circleShape));
	circleVec[circleVec.size() - 1].position = position;
	circleVec[circleVec.size() - 1].radius	 = radius;
	circleVec[circleVec.size() - 1].force	 = force;
	circleVec[circleVec.size() - 1].mass	 = mass;
}

void phy::Environment::update()
{
	// update position
	for (Circle &circle : circleVec)
	{
		circle.update();
	}

	// for (Rectangle &rectangle : rectangleVec)
	// {
	// 	rectangle.update();
	// 	rectangle.force += agl::Vec<float, 2>{0, gravity} * rectangle.mass;
	// }

	// collision detection
	for (int i = 0; i < circleVec.size(); i++)
	{
		Circle &circle = circleVec[i];

		for (int x = i + 1; x < circleVec.size(); x++)
		{
			// drag

			circle.force -= circle.velocity * density;

			// collision

			Circle &otherCircle = circleVec[x];

			if (&otherCircle == &circle)
			{
				continue;
			}

			agl::Vec<float, 2> circleOffset = otherCircle.position - circle.position;

			float circleDistance = circleOffset.length();

			float circleOverlap = (otherCircle.radius + circle.radius) - circleDistance;

			if (circleOverlap > 0)
			{
				agl::Vec<float, 2> offsetNormal = circleOffset.normalized();
				agl::Vec<float, 2> pushback		= offsetNormal * circleOverlap;

				float actingMass = circle.mass > otherCircle.mass ? otherCircle.mass : circle.mass;

				// agl::Vec<float, 2> velocityDelta = circle.velocity -
				// otherCircle.velocity;
				//
				// agl::Vec<float, 2> forceBack = velocityDelta * actingMass;
				//
				// circle.force -= forceBack;
				// otherCircle.force += forceBack;

				// circle.position -= pushback * (otherCircle.mass / (circle.mass +
				// otherCircle.mass)); otherCircle.position += pushback * (circle.mass
				// / (circle.mass + otherCircle.mass));

				circle.posOffset -= pushback * (otherCircle.mass / (circle.mass + otherCircle.mass));
				otherCircle.posOffset += pushback * (circle.mass / (circle.mass + otherCircle.mass));

				circle.force -= pushback * actingMass;
				otherCircle.force += pushback * actingMass;
			}
		}

		// // boundry
		// agl::Vec<float, 2> boundryPosition = {500, 500};
		// float			   boundryRadius   = 500;
		//
		// agl::Vec<float, 2> offset = circle.position;
		// offset					  = offset - boundryPosition;
		//
		// float distance = offset.length();
		//
		// float overlap = distance + circle.radius - boundryRadius;
		//
		// if (overlap > 0)
		// {
		// 	agl::Vec<float, 2> offsetNormal = offset.normalized();
		// 	agl::Vec<float, 2> pushback		= offsetNormal *
		// overlap;
		//
		// 	circle.position -= pushback;
		//
		// 	circle.force -= pushback * circle.mass;
		//
		// 	// circle.force -= pushback * circle.mass;
		// }
	}

	// for (Rectangle &rectangle : rectangleVec)
	// {
	// 	for (Rectangle &otherRectangle : rectangleVec)
	// 	{
	// 		if (&rectangle == &otherRectangle)
	// 		{
	// 			continue;
	// 		}
	//
	// 		bool collide = false;
	// 		collide		 = collide || (otherRectangle.position.x) >=
	// (rectangle.position.x) &&
	// (otherRectangle.position.y)
	// >= (rectangle.position.y) &&
	// (otherRectangle.position.x) <= (rectangle.position.x + rectangle.size.x)
	// &&
	// (otherRectangle.position.y)
	// <= (rectangle.position.y + rectangle.size.y);
	//
	// 		collide =
	// 			collide || (otherRectangle.position.x +
	// otherRectangle.size.x)
	// >= (rectangle.position.x) &&
	// (otherRectangle.position.y + otherRectangle.size.y) >=
	// (rectangle.position.y) &&
	// (otherRectangle.position.x
	// + otherRectangle.size.x)
	// <= (rectangle.position.x
	// + rectangle.size.x)
	// && (otherRectangle.position.y
	// + otherRectangle.size.y)
	// <= (rectangle.position.y
	// + rectangle.size.y);
	//
	// 		collide =
	// 			collide || (otherRectangle.position.x) >=
	// (rectangle.position.x)
	// && (otherRectangle.position.y
	// + otherRectangle.size.y)
	// >= (rectangle.position.y) &&
	// (otherRectangle.position.x) <= (rectangle.position.x + rectangle.size.x)
	// && (otherRectangle.position.y
	// + otherRectangle.size.y) <=
	// (rectangle.position.y + rectangle.size.y);
	//
	// 		collide =
	// 			collide || (otherRectangle.position.x) >=
	// (rectangle.position.x)
	// && (otherRectangle.position.y
	// + otherRectangle.size.y)
	// >= (rectangle.position.y) &&
	// (otherRectangle.position.x) <= (rectangle.position.x + rectangle.size.x)
	// && (otherRectangle.position.y
	// + otherRectangle.size.y) <=
	// (rectangle.position.y + rectangle.size.y);
	//
	// 		std::cout << collide << std::endl;
	// 	}
	// }
}

std::vector<phy::Circle> &phy::Environment::getCircleVec()
{
	return circleVec;
}
