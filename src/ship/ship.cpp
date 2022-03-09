#include "Ship.hpp"

using namespace cgp;
#define PI 3.14159f

Ship::Ship() {}

void Ship::initialize() {
	drawable.initialize(mesh_load_file_obj("assets/ship_translated.obj"));
	drawable.texture = opengl_load_texture_image("assets/ship.jpg");
	drawable.shader = opengl_load_shader("shaders/ship/vert.glsl", "shaders/ship/frag.glsl");
}

void Ship::draw(cgp::scene_environment_basic const& environment) {
	drawable.transform.rotation = rotation;
	drawable.transform.translation = translation;
	drawable.transform.scaling = scaling;
	cgp::draw(drawable, environment);
}

void Ship::computeRefPoints() {
	refPoints.resize(3 * N_triangles);
	movedRefPoints.resize(3 * N_triangles);

	for (int i = 0; i < N_triangles; i++) {
		refPoints[3 * i] = vec3(0, 0, 0);
		refPoints[3 * i + 1] = border(2 * PI / N_triangles * i);
		refPoints[3 * i + 2] = border(2 * PI / N_triangles * (i + 1));
	}
}

void Ship::update(Ocean& ocean, float time) {
	if (N_triangles != N_triangles_desired) {
		N_triangles = N_triangles_desired;
		computeRefPoints();
	}

	for (int i = 0; i < 3 * N_triangles; i++) {
		movedRefPoints[i] = ocean.getVertexPos(refPoints[i], time);
	}
	computeRotation();
	computeTranslation(time);
}


void Ship::computeRotation() {
	cgp::quaternion q = cgp::quaternion(0,0,0,0);

	for (int i = 0; i < 1; i++) {
		vec3 e1 = normalize(refPoints[3 * i + 2] - refPoints[3 * i + 1]);
		vec3 e2 = normalize(- refPoints[3 * i + 0] + 0.5f * (refPoints[3 * i + 1] + refPoints[3 * i + 2]));
		e2 -= dot(e1, e2) * e1;
		e2 = normalize(e2);
		vec3 e1_target = normalize(movedRefPoints[3 * i + 2] - movedRefPoints[3 * i + 1]);
		vec3 e2_target = normalize(- movedRefPoints[3 * i + 0] + 0.5f * (movedRefPoints[3 * i + 1] + movedRefPoints[3 * i + 2]));
		e2_target -= dot(e1_target, e2_target) * e1_target;
		e2_target = normalize(e2_target);
		q += (rotation_transform::between_vector(e1, e2, e1_target, e2_target)).quat();
	}

	q /= N_triangles;
	rotation = rotation_transform::from_quaternion(q);
}

void Ship::computeTranslation(float time) {

	// Compute the translation based on the wave movement
	cgp::vec3 trans = vec3(0, 0, 0);
	for (int i = 0; i < N_triangles; i++) {
		vec3 prevMid = (refPoints[3 * i + 0] + refPoints[3 * i + 1] + refPoints[3 * i + 2]) / 3.0f;
		vec3 newMid = (movedRefPoints[3 * i + 0] + movedRefPoints[3 * i + 1] + movedRefPoints[3 * i + 2]) / 3.0f;
		trans += newMid - prevMid;
	}
	trans /= N_triangles;

	// Compute the speed metrics
	float dt = time - last_t;
	cgp::vec3 sp = (trans - translation) / dt;
	cgp::vec3 acc = (sp - speed) / dt;

	// Compute the associated force
	cgp::vec3 force = acc * m;

	// Compute the friction force
	cgp::vec3 forceFriction = -K * speed;

	// Compute the associated accel, speed, etc..
	accel = (force + forceFriction) / m;
	cgp::vec3 new_speed = speed + accel * dt;
	if (dot(speed, new_speed) < 0) // To prevent divergence
		new_speed = vec3(0, 0, 0);// -= dot(new_speed, speed) * speed / (pow(norm(speed), 2) * norm(new_speed));
	translation += new_speed * dt;

	// Update time
	last_t = time;
	speed = new_speed;

}

cgp::vec3 Ship::border(float u) {
	float Rx = 4 * scaling;
	float Ry = 1.3 * scaling;
	return cgp::vec3(Rx * std::cos(u), Ry * std::sin(u), -1.2f * scaling);
}