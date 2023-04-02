#include "../../../FastPhys/fastphys.hpp"
#include <cstdlib>
#include <limits>
#include <vector>

#define WIDTH  1920
#define HEIGHT 1080


int main()
{
	agl::RenderWindow window;
	window.setup({1920, 1080}, "PhysicsTest");
	window.setFPS(60);
	window.setClearColor(agl::Color::Black);

	agl::ShaderBuilder vert;
	vert.setDefaultVert();
	std::string vertSrc = vert.getSrc();

	agl::ShaderBuilder frag;
	frag.setDefaultFrag();
	std::string fragSrc = frag.getSrc();

	agl::Shader shader;
	shader.compileSrc(vertSrc, fragSrc);
	window.getShaderUniforms(shader);
	shader.use();

	agl::Camera camera;
	camera.setOrthographicProjection(0, 1920, 1080, 0, 0.1, 100);
	camera.setView({0, 0, 10}, {0, 0, 0}, {0, 1, 0});

	window.updateMvp(camera);

	agl::Event event;
	event.setWindow(window);

	agl::Texture blank;
	blank.setBlank();

	agl::Circle shape(32);
	shape.setTexture(&blank);
	shape.setColor(agl::Color::White);

	agl::Rectangle recshape;
	recshape.setTexture(&blank);
	recshape.setColor(agl::Color::White);

	phy::Environment phySim(shape);

	for (float i = 0; i < (2 * PI); i += .1)
	{
		agl::Vec<float, 2> position = agl::pointOnCircle(i);

		float size = (((float)rand() / (float)RAND_MAX) * 10) + 10;

		size = 10;

		phySim.addCircle(agl::Vec<float, 2>{WIDTH / 2., HEIGHT / 2.} +
							 (position * (400 * ((float)rand() / (float)RAND_MAX))),
						 size, {0, 0}, size * size);
	}

	float clickDown = false;

	while (!event.windowClose())
	{
		event.poll([](XEvent xev) {});

		window.clear();

		window.draw(phySim);

		window.display();

		phySim.update();

		if (event.isPointerButtonPressed(Button1Mask))
		{
			if (!clickDown)
			{
				float size = (((float)rand() / (float)RAND_MAX) * 19) + 1;
				phySim.addCircle(event.getPointerWindowPosition(), 10, {0, 0}, 10);
			}
			clickDown = true;
		}
		else
		{
			clickDown = false;
		}
	}

	window.close();

	shader.deleteProgram();
	blank.deleteTexture();
}
