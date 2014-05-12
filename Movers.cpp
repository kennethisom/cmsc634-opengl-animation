#include "Movers.hpp"
#include "Mover.hpp"

#include <GLFW/glfw3.h>
#include <math.h>

Movers::Movers(): show_controls(true), cloud(false), orbit(false) {
	num_movers = 25;
	for (unsigned int i=0; i < num_movers; i++) {
		movers[i] = new Mover(i==0);
	}
}

// clean up allocated memory
Movers::~Movers() {
	delete[] movers;
}

void Movers::showControls() {
	if (!show_controls) {
		show_controls = true;
		movers[0]->showControlMarkers();
	}
}

void Movers::hideControls() {
	if (show_controls) {
		show_controls = false;
		movers[0]->hideControlMarkers();
	}
}

// update mover positions
void Movers::updatePositions() {
	float t, tint, tdec;
	t = (float) glfwGetTime();
	tdec = modf(t, &tint);
	if (cloud) {
		for (unsigned int i=0; i < num_movers; i++) {
			movers[i]->updatePosition(tdec);
		}
	} else {
		movers[0]->updatePosition(tdec);
	}
}

// load/reload shaders
void Movers::updateShaders() {
	for (unsigned int i=0; i < num_movers; i++) {
		movers[i]->updateShaders();
	}
}

// draw all mover objects
void Movers::draw() const {
	if (cloud) {
		for (unsigned int i=0; i < num_movers; i++) {
			movers[i]->draw();
		}
	} else {
		movers[0]->draw();
	}
}