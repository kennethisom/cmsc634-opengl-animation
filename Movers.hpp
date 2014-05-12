// terrain data and drawing
#ifndef Movers_hpp
#define Movers_hpp

#include "Mover.hpp"

// terrain data and rendering methods
class Movers {
// private data
private:
	unsigned int num_movers;
	Mover *movers[25];


// public data
public:
    bool show_controls;                // true if control points should be visible
	bool cloud;				           // true for grad assignment with multiple movers
	bool orbit;						   // true for extra credit state for single mover in an orbit - probably needs to be two functions

// public methods
public:
    // load mover(s),
    Movers();

    // clean up allocated memory
    ~Movers();

	void showControls();
	void hideControls();

	void updatePositions();

    // load/reload shaders
    void updateShaders();

    // draw all mover objects
    void draw() const;
};

#endif