#pragma once

#include "cgp/cgp.hpp"
#include "ocean/ocean.hpp"

class Ship {
public:

	Ship();
	void initialize();
	void draw(cgp::scene_environment_basic const& environment);

	void computeRefPoints();

	void update(Ocean& ocean, float time);
	void computeRotation();
	void computeTranslation(float time);

	cgp::vec3 border(float u);


	// To generate
	cgp::mesh_drawable drawable;
	std::vector<cgp::vec3> refPoints;
	std::vector<cgp::vec3> movedRefPoints;

	// To move
	cgp::rotation_transform rotation;
	cgp::vec3 translation;
	cgp::vec3  speed = cgp::vec3(0.0f, 0.0f, 0.0f);
	cgp::vec3  accel = cgp::vec3(0.0f, 0.0f, 0.0f);
	float last_t = 0;
	float m = 10;
	float K = 5;

	// To show
	float scaling = 4.0f;
	int N_triangles;
	int N_triangles_desired = 5;
};