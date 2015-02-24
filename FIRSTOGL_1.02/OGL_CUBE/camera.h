#pragma once
#include "sb6.h"
#include "vmath.h"


class camera
{
public:
	camera();

	//position of the camera.
	const vmath::vec3& position() const;
	void setPosition(const vmath::vec3& position);
	void offsetPosition(const vmath::vec3& offset);

	//Setting up the perpesctive camera.
	float fieldOfView() const;
	void setFieldOfView(float fieldOfView);

	float nearPlane() const;
	float farPlane() const;
	float HorizontalAngle() const;
	float VerticalAngle() const;
	void setNearAndFarPlane(float nearPlane, float farPlane);

	vmath::mat4 orientation() const;

	void offsetOrientation(float upAngle, float rightAngle);
	void lookAt(vmath::vec3 position);

	float viewportAspectRatio() const;
	void setViewportAspectRatio(float viewportAspectRatio);

	vmath::vec3 forward() const;

	vmath::vec3 right() const;

	vmath::vec3 up() const;

	vmath::mat4 matrix() const;

	vmath::mat4 projection() const;

	vmath::mat4 view() const;

	//destructor
	~camera(void);

private: 
	vmath::vec3 _position;
	float _horizontalAngle;
	float _verticalAngle;
	float _fieldOfView;
	float _nearPlane;
	float _farPlane;
	float _viewportAspectRatio;

	void normalizeAngles();
};

