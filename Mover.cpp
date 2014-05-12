#include "Mover.hpp"
#include "Marker.hpp"
#include "Vec.inl"

#include <stdio.h>
#include <stdlib.h>

Mover::Mover(bool create_controlmarkers) {
	with_controlmarkers = create_controlmarkers;
	cp_visible = create_controlmarkers;
	positionmarker = new Marker(15.f);
	for (unsigned int i=0; i < 4; i++) {
		Vec3f position = getRandPoint();
		cps[i] = position;
		if (with_controlmarkers) {
			controlmarkers[i] = new Marker(5.f);
			controlmarkers[i]->updatePosition(position);
		}
		if (i == 1) {
			positionmarker->updatePosition(position);
		}
		last_dt = 0.f;
	}
}

Mover::~Mover() {
	delete positionmarker;
	if (with_controlmarkers) {
		for (unsigned int i=0; i < 4; i++) {
			delete controlmarkers[i];
		}
	}
}

Vec3f Mover::getRandPoint() {
	float x = (rand() % 700) + ((rand() % 1000) / 1000.f) - 350.5f;
	float y = (rand() % 400) + ((rand() % 1000) / 1000.f) - .5f;
	float z = (rand() % 400) + ((rand() % 1000) / 1000.f) - 200.5f;
	return vec3<float>(x, y, z);
}

void Mover::hideControlMarkers() {
	cp_visible = false;
}

void Mover::showControlMarkers() {
	cp_visible = true;
	for (unsigned int i=0; i < 4; i++) {
		controlmarkers[i]->updatePosition(cps[i]);
	}
}

void Mover::updatePosition(float dt)
{
	if (dt < last_dt) {
		// update control points
		for (int i=0; i < 3; i++) {
			cps[i] = cps[i+1];
			if (with_controlmarkers && cp_visible) {
				controlmarkers[i]->updatePosition(cps[i]);
			}
		}
		Vec3f position = getRandPoint();
		cps[3] = position;
		if (with_controlmarkers && cp_visible) {
			controlmarkers[3]->updatePosition(position);
		}
	}

	float dt2 = dt * dt;
	float dt3 = dt2 * dt;
    Vec3f new_position = cps[1] + 
						(-.5f*cps[0] + .5f*cps[2]) * dt +
						(cps[0] - 2.5f*cps[1] + 2.f*cps[2] - .5f*cps[3]) * dt2 +
						(-.5f*cps[0] + 1.5f*cps[1] - 1.5f*cps[2] + .5f*cps[3]) * dt3;
	positionmarker->updatePosition(new_position);
	last_dt = dt;
}

void Mover::updateShaders() {
	positionmarker->updateShaders();
	if (with_controlmarkers && cp_visible) {
		controlmarkers[0]->updateShaders();
		controlmarkers[1]->updateShaders();
		controlmarkers[2]->updateShaders();
		controlmarkers[3]->updateShaders();
	}
}

void Mover::draw() const {
	positionmarker->draw();
	if (with_controlmarkers && cp_visible) {
		controlmarkers[0]->draw();
		controlmarkers[1]->draw();
		controlmarkers[2]->draw();
		controlmarkers[3]->draw();
	}
}