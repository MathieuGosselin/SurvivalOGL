#include "camera.h"

#include "MGstream.h"
#include <iostream>
#include <sstream>
//
//camera::camera(int windowWidth, int windowHeight,vmath::vec4 position,vmath::vec4 lookat, vmath::vec4 camUp)
//{ 
//	projection = vmath::perspective(60.0f,(float)windowWidth/(float)windowHeight, 0.1f,100.0f);
//	
//	view = vmath::mat4(position,lookat,camUp,vmath::vec4(0.0f,0.0f,0.0f,1.0f));
//}

using namespace vmath;

#define MAX_VERTICAL_ANGLE 85.0f
#define ANGLE 360.0f

camera::camera() :
	_position(14.0f,1.5f,12.0f),
	_horizontalAngle(180.0f),
	_verticalAngle(0.0f),
	_fieldOfView(60.0f),
	_nearPlane(0.01f),
	_farPlane(100.0f),
	_viewportAspectRatio(800.0f/600.0f)
{
}

const vmath::vec3& camera::position() const {
	return _position;
}

void camera::setPosition(const vec3& position)
{
	_position = position;
}

void camera::offsetPosition(const vec3& offset)
{
	_position += offset;
	//DBOUT("POSITION: " << _position[0] << "," << _position[1] << "," << _position[2]);
}

float camera::fieldOfView() const {
	return _fieldOfView;
}

void camera::setFieldOfView(float fieldOfView) {
	if(fieldOfView > 0.0f && fieldOfView < 180.0f)
	_fieldOfView = fieldOfView;
}

float camera::nearPlane() const {
	return _nearPlane;
}

float camera::farPlane() const {
	return _nearPlane;
}

float camera::HorizontalAngle() const {
	return _horizontalAngle;
}

float camera::VerticalAngle() const {
	return _verticalAngle;
}

void camera::setNearAndFarPlane(float nearPlane, float farPlane) {
    if(nearPlane > 0.0f)
		if(farPlane > nearPlane){
			_nearPlane = nearPlane;
			_farPlane = farPlane;
		}
}

mat4 camera::orientation() const {
	mat4 orientation;
	

	orientation = rotate(_verticalAngle, vec3(1,0,0)) * rotate(_horizontalAngle, vec3(0,1,0));
	/*DBOUT(*orientation[0] << "," << *orientation[1] << "," << *orientation[2] << "," << *orientation[3] << ",\r\n" 
		<< *orientation[4] << "," << *orientation[5] << "," << *orientation[6] << "," << *orientation[7] << ",\r\n"
		<< *orientation[8] << "," << *orientation[9] << "," << *orientation[10] << "," << *orientation[11] << ",\r\n" 
		<< *orientation[12] << "," << *orientation[13] << "," << *orientation[14] << "," << *orientation[15] << "||" <<_verticalAngle << ",\r\n");*/
	return orientation;
}

void camera::offsetOrientation(float upAngle, float rightAngle)
{
	
	_horizontalAngle += rightAngle;
	_verticalAngle += upAngle;

	if(_verticalAngle > MAX_VERTICAL_ANGLE)
		_verticalAngle -= upAngle;

	if(_verticalAngle < -MAX_VERTICAL_ANGLE)
		_verticalAngle -= upAngle;

	if(_horizontalAngle > ANGLE)
		_horizontalAngle -= ANGLE;

	if(_horizontalAngle < -ANGLE)
		_horizontalAngle += ANGLE;
	//normalizeAngles();
}

void camera::lookAt(vec3 position)
{
	if(position != _position)
	{
		vec3 direction = normalize(position - _position);
		_verticalAngle = radians(asinf(-direction[2]));
		_horizontalAngle = -radians(atan2f(-direction[1],-direction[3]));
		normalizeAngles();
	}
}

float camera::viewportAspectRatio() const {
	return _viewportAspectRatio;
}

void camera::setViewportAspectRatio(float viewportAspectRatio) {
	if(viewportAspectRatio > 0.0)
		_viewportAspectRatio = viewportAspectRatio;
}

//vec3 camera::forward() const {
//	vec4 forward = vec4(1.0f,1.0f,1.0f,1.0f);
//		return vec3(forward);
//}

mat4 camera::matrix() const {
	return projection() * view();
}

mat4 camera::projection() const {
	return perspective(_fieldOfView, _viewportAspectRatio, _nearPlane, _farPlane);
}

mat4 camera::view() const {
	return orientation() ;
}

void camera::normalizeAngles() {
	_horizontalAngle = fmodf(_horizontalAngle, 360.0f);
	if(_horizontalAngle < 0.0f)
		_horizontalAngle += 360.0f;

	//if(_verticalAngle > MAX_VERTICAL_ANGLE)
	//{
	//	_verticalAngle = MAX_VERTICAL_ANGLE;
	//}
	//else
	//	if(_verticalAngle < -MAX_VERTICAL_ANGLE)
	//	{
	//		_verticalAngle = -MAX_VERTICAL_ANGLE;
	//	}
}



camera::~camera(void)
{
}
