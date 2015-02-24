#include <sb6.h>
#include <math.h>
#include "MGStreamShader.h"
#include <iostream>
#include <sstream>


using namespace std;



#define DBOUT( s ){                        \
	std::wostringstream os_;                \
	os_ << s;                               \
	OutputDebugString((os_.str().c_str())); } \


//function
GLuint compile_shaders(void)
{
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint tessCtrl_shader;
	GLuint tessEval_shader;
	GLuint geo_shader;
	GLuint program;
	std::string text;

	//Read the Source code for the vertex shader.
	 text = MGStreamShader::rdtxtshade("_VertexShader.txt");
	const char *vertex_shader_source = text.c_str();

	//Create and compile vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader,1,&vertex_shader_source,NULL);
	glCompileShader(vertex_shader);

	//Read the Source code for the fragment shader.
	text = MGStreamShader::rdtxtshade("_FragmentShader.txt");
	const char *fragment_shader_source = text.c_str();

	//Create and compile the fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader,1,&fragment_shader_source,NULL);
	glCompileShader(fragment_shader);
	
	//Read the Source Code for the Tessellation control shader.
	text = MGStreamShader::rdtxtshade("_TessellationCtrlShader.txt");
	const char *tessCtrl_shader_source = text.c_str();

	//Create and compile the Tessellation control shader.
	tessCtrl_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(tessCtrl_shader,1,&tessCtrl_shader_source,NULL);
	glCompileShader(tessCtrl_shader);

	//Read the Source Code for the Tesselation Evaluation shader.
	text = MGStreamShader::rdtxtshade("_TessellationEvalShader.txt");
	const char *tessEval_shader_source = text.c_str();

	//Create and compile the Tessellation evaluation shader.
	tessEval_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(tessEval_shader,1,&tessEval_shader_source,NULL);
	glCompileShader(tessEval_shader);

	//Read the Source Code for the Geometry Shaders.
	text = MGStreamShader::rdtxtshade("_GeometryShader.txt");
	const char *geo_shader_source = text.c_str();

	//Create and compile the Geometry shader.
	geo_shader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geo_shader,1,&geo_shader_source,NULL);
	glCompileShader(geo_shader);

	//Create Program, attach shader to it and link it
	program = glCreateProgram();
	glAttachShader(program,vertex_shader);
	glAttachShader(program,tessCtrl_shader);
	glAttachShader(program,tessEval_shader);
	//glAttachShader(program,geo_shader);
	glAttachShader(program,fragment_shader);
	
	glLinkProgram(program);

	//Delete the shaders as the program has them now.	
	glDeleteShader(fragment_shader);
	glDeleteShader(geo_shader);
	glDeleteShader(tessEval_shader);
	glDeleteShader(tessCtrl_shader);
	glDeleteShader(vertex_shader);
	
	

	return program;
}

class my_application : public sb6::application
{
private:
	GLuint rendering_program;
	GLuint vertex_array_object;
public:
	float _red;
	float _blue;

	void startup()
	{
		rendering_program = compile_shaders();
		glGenVertexArrays(1,&vertex_array_object);
		glBindVertexArray(vertex_array_object);

		//Tessellation
		//glPatchParameteri(GL_PATCH_VERTICES,3);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

		//sb6::application::info.title = "MGOGL1.01";
	}

	void render(double currentTime)
	{
		_red = (float)sin(currentTime) * 0.5f + 0.5f;
		_blue = (float)cos(currentTime) * 0.5f + 0.5f;

		//DBOUT("Red: " << _red << ",Blue: " << _blue << ", CurrentTime: " << currentTime << "\r\n")

		 const GLfloat color[] = {0.0,0.0,0.0f,1.0f};
		 glClearBufferfv(GL_COLOR,0,color);


		//Use the program shader
		glUseProgram(rendering_program);

		GLfloat attrib[] = { (float)sin(currentTime) * 0.5f, (float)cos(currentTime) * 0.6f,0.0f,0.0f};
		const GLfloat colorTriangle[] = {_blue,_red,0.0f,0.0f};

		

		//Update the value of input attribute 0
		glVertexAttrib4fv(0,attrib);
		//glVertexAttrib4fv(1,colorTriangle);
		
		
		glDrawArrays(GL_PATCHES,0,3);
	}

	void shutdown()
	{
		glDeleteVertexArrays(1,&vertex_array_object);
		glDeleteProgram(rendering_program);
		glDeleteVertexArrays(1,&vertex_array_object);
	}
};

DECLARE_MAIN(my_application);



//int main(int argc, char** argv)
//{
//	
//	
//	system("pause");
//	return 0;
//}

