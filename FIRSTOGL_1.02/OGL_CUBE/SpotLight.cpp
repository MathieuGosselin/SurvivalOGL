#include "SpotLight.h"


SpotLight::SpotLight(GLuint program)
{
	uniforms.ambientlight = glGetUniformLocation(program,"ambientlight");
		uniforms.LightColor = glGetUniformLocation(program,"LightColor");
		uniforms.LightPosition = glGetUniformLocation(program,"LightPosition");
		uniforms.Shininess = glGetUniformLocation(program,"Shininess");
		uniforms.Strength = glGetUniformLocation(program,"Strength");
		uniforms.ConstantAttenuation = glGetUniformLocation(program,"ConstantAttenuation");
		uniforms.LinearAttenuation = glGetUniformLocation(program,"LinearAttenuation");
		uniforms.QuadraticAttenuation = glGetUniformLocation(program,"QuadraticAttenuation");
		uniforms.ConeDirection = glGetUniformLocation(program,"ConeDirection");
		uniforms.SpotCosCutOff = glGetUniformLocation(program,"SpotCosCutOff");
		uniforms.SpotExponent = glGetUniformLocation(program,"SpotExponent");

		vLightPosition = vmath::vec4(0,-0.5,-.02,0);
		vLightDirection = vmath::vec4(vmath::vec3(0,0,-10),1);

		glUniform3fv(uniforms.LightPosition,1,vLightPosition);
		glUniform3fv(uniforms.ConeDirection,1,vLightDirection);

		glUniform3fv(uniforms.ambientlight,1,vmath::vec3(0.17f,0.11f,0.11f));
		glUniform3fv(uniforms.LightColor,1,vmath::vec3(.92f,.40f,.44f));
		
		glUniform1f(uniforms.Shininess,0.5f);
		glUniform1f(uniforms.Strength,0.5f);

		glUniform1f(uniforms.ConstantAttenuation,.8f);
		glUniform1f(uniforms.LinearAttenuation,.8f);

		glUniform1f(uniforms.QuadraticAttenuation,.5f);
		glUniform1f(uniforms.SpotCosCutOff,8.6f);
		glUniform1f(uniforms.SpotExponent,1.0f);
}

void SpotLight::update(vmath::mat4 model)
{
	glUniform3fv(uniforms.LightPosition,1,vLightPosition * model);
	glUniform3fv(uniforms.ConeDirection,1,vLightDirection * model);
}

SpotLight::~SpotLight(void)
{
}
