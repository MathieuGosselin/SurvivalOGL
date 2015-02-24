#pragma once
#include "sb6.h"
#include "vmath.h"

class SpotLight
{
public:
	struct
	{
		GLint ambientlight;
		GLint LightColor;
		GLint LightPosition;
		GLint Shininess;
		GLint Strength;

		GLint ConstantAttenuation;
		GLint LinearAttenuation;
		GLint QuadraticAttenuation;

		GLint ConeDirection;
		GLint SpotCosCutOff;
		GLint SpotExponent;
	}
	 uniforms;

	 vmath::vec4 vLightPosition;
	 vmath::vec4 vLightDirection;

	 SpotLight(GLuint program);

	 void update(vmath::mat4 model);

	~SpotLight(void);


};

