// terrain data and drawing
#ifndef Mover_hpp
#define Mover_hpp

#include "Marker.hpp"
#include "Vec.hpp"

// terrain data and rendering methods
class Mover {
// private data
private:
	Marker *positionmarker;
	Marker *controlmarkers[4];
	Vec3f cps[4];
	float last_dt;
	bool with_controlmarkers;
	bool cp_visible;

// public data
public:

// public methods
public:
    // load mover,
    Mover(bool create_controlmarkers);

    // clean up allocated memory
    ~Mover();

	Vec3f getRandPoint();

	void hideControlMarkers();
	void showControlMarkers();

	void updatePosition(float t);

    // load/reload shaders
    void updateShaders();

    // draw mover object and control points
    void draw() const;
};

#endif