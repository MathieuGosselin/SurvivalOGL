#include <sb6.h>
#include <sb6ktx.h>
#include <vmath.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "MGstream.h"
#include "camera.h"
#include "Map.h"

#include "Entity.h"

using namespace MGstream;
using namespace vmath;

#define PI 3.14159265

#define MOUSE_SENSIBILITY .2
#define SPEED 0.06


#define KEY_A 65
#define KEY_S 83
#define KEY_W 87
#define KEY_D 68
#define KEY_E 69
#define KEY_Q 81

#define KEY_T 84
#define KEY_G 71
#define KEY_Y 89
#define KEY_H 72
#define KEY_U 85
#define KEY_J 74

#define KEY_UP 283
#define KEY_DOWN 284

class main : public sb6::application{
private:
	GLuint rendering_program;
	GLuint vao;
	GLuint buffer;

	GLfloat fspotcoscutoff;

	GLfloat CdirX;
	GLfloat CdirY;
	GLfloat CdirZ;

	vec4 vLightPosition;

	Map map;
	camera cam;
	Entity *ent;

	float last_Xpos;
	float last_Ypos;
	char LogBuffer[4098];

	

	 struct
    {
        GLint mvp;
		GLint mv;
		GLint model;
        GLint offset;

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
		


    } uniforms;

	 struct{
		 std::vector<int> action;
		 std::vector<int> key;
	 }keyboard;

    GLuint          tex_wall;
    GLuint          tex_ceiling;
    GLuint          tex_floor;

public:
	GLuint compile_shader()
	{
		GLuint program;
		GLuint vs;
		GLuint fs;
		std::string text;

		text = readtxt("..//OGL_CUBE//_vertexShader.txt");
		const char *vs_source = text.c_str();

		
		vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs,1,&vs_source,NULL);
		glCompileShader(vs);

		glGetShaderInfoLog(vs,1024,NULL,LogBuffer);
		if(LogBuffer[1] != -51)
		{
			writetxt("VertexShaderLOG.txt",LogBuffer);
			//glfwCloseWindow();
		}

		text = readtxt("..//OGL_CUBE//_fragmentshader.txt");
		const char *fs_source = text.c_str();

		fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs,1,&fs_source,NULL);
		glCompileShader(fs);

		glGetShaderInfoLog(fs,1024,NULL,LogBuffer);
		if(LogBuffer[1] != -51)
		{
			writetxt("FragmentShaderLOG.txt",LogBuffer);
			//glfwCloseWindow();
		}
		program = glCreateProgram();
		glAttachShader(program,vs);
		glAttachShader(program,fs);
		glLinkProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	void startup()
	{
		//Remove cursor from game.
		glfwDisable(GLFW_MOUSE_CURSOR);
		glEnable(GL_DEPTH_TEST);
		
		
		rendering_program = compile_shader();
		
		map.loadmap("..//OGL_CUBE//media//map//MapTest2.png");
		ent = new Entity("..//OGL_CUBE//media//model//SpiderMan//SpiderMan.obj",vmath::vec3(10.0f,5.0f,10.0f));
		

		glGetProgramInfoLog(rendering_program,1024,NULL,LogBuffer);
		if(LogBuffer[1] != -51)
		{
			writetxt("ProgramLOG.txt",LogBuffer);
			//glfwCloseWindow();
		}

		

		uniforms.mvp = glGetUniformLocation(rendering_program,"mvp");
		uniforms.mv = glGetUniformLocation(rendering_program,"mv");
		uniforms.model = glGetUniformLocation(rendering_program,"m");
		//uniforms.offset = glGetUniformLocation(rendering_program,"offset");
		uniforms.ambientlight = glGetUniformLocation(rendering_program,"ambientlight");
		uniforms.LightColor = glGetUniformLocation(rendering_program,"LightColor");
		uniforms.LightPosition = glGetUniformLocation(rendering_program,"LightPosition");
		uniforms.Shininess = glGetUniformLocation(rendering_program,"Shininess");
		uniforms.Strength = glGetUniformLocation(rendering_program,"Strength");
		uniforms.ConstantAttenuation = glGetUniformLocation(rendering_program,"ConstantAttenuation");
		uniforms.LinearAttenuation = glGetUniformLocation(rendering_program,"LinearAttenuation");
		uniforms.QuadraticAttenuation = glGetUniformLocation(rendering_program,"QuadraticAttenuation");
		uniforms.ConeDirection = glGetUniformLocation(rendering_program,"ConeDirection");
		uniforms.SpotCosCutOff = glGetUniformLocation(rendering_program,"SpotCosCutOff");
		uniforms.SpotExponent = glGetUniformLocation(rendering_program,"SpotExponent");

		
		glUseProgram(rendering_program);

		

		tex_wall = sb6::ktx::file::load("..//OGL_CUBE//media//textures//brick.ktx");
		tex_floor = sb6::ktx::file::load("..//OGL_CUBE//media//textures//floor.ktx");
		tex_ceiling = sb6::ktx::file::load("..//OGL_CUBE//media/textures//ceiling.ktx");

		GLuint textures[] = {tex_wall,tex_floor,tex_ceiling};

		last_Xpos = 0.0f;
		last_Ypos = 0.0f;

		fspotcoscutoff = 8.6f;

		CdirX = 0.0f;
		CdirY = 0.0f;
		CdirZ = -10.0f;

		vLightPosition = vec4(0,-0.5,-.02,0);

		for(int i = 0; i < 3;i++)
		{
			glBindTexture(GL_TEXTURE_2D,textures[i]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}

		//Initalization de la camera;
		//cam = camera(info.windowWidth,info.windowHeight,vmath::vec4(0.0f,0.0f,-10.0f,0.0f),vmath::vec4(0.0f,0.0f,0.0f,0.0f),vmath::vec4(0.0f,0.0f,1.0f,0.0f));
		cam = camera();

		 
	}

	void onResize(int w, int h)
	{
		sb6::application::onResize(w,h);
		//aspect = (float)info.windowWidth / (float)info.windowHeight;
		//proj_matrix
	}

	void render(double currentTime)
	{
		static const GLfloat black[] = {0.0f,0.0f,0.0f,0.0f};
		float t = (float)currentTime;

		glViewport(0,0,info.windowWidth,info.windowHeight);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glClearBufferfv(GL_COLOR,0,black);
		
		
		
		

		vmath::mat4 proj_matrix = vmath::perspective(60.0f,(float)info.windowWidth / (float)info.windowHeight, 0.1f, 100.0f);

		//glUniform1f(uniforms.offset,t * 0.009f);
		
		glUniform3fv(uniforms.ambientlight,1,vmath::vec3(0.07f,0.01f,0.01f));
		glUniform3fv(uniforms.LightColor,1,vec3(.92f,.40f,.44f));
		
		glUniform1f(uniforms.Shininess,0.5f);
		glUniform1f(uniforms.Strength,0.5f);

		glUniform1f(uniforms.ConstantAttenuation,.8f);
		glUniform1f(uniforms.LinearAttenuation,.8f);

		glUniform1f(uniforms.QuadraticAttenuation,.5f);
		glUniform1f(uniforms.SpotCosCutOff,fspotcoscutoff);
		glUniform1f(uniforms.SpotExponent,1.0f);


		
		int i;
		 GLuint textures[] = { tex_wall, tex_floor, tex_wall, tex_ceiling };
      
		 vmath::mat4 m_matrix =    vmath::translate(-cam.position()) /** vmath::translate(vec3(12.0,-1.5,12.0)) * vmath::rotate(90.0f * (float)t * 0.9f, vmath::vec3(0.0f, 0.0f, 1.0f)) *
									vmath::translate(vec3(-12.0,-1.5,-12.0))*/;
			
			vmath::mat4 mvp =  cam.matrix() * m_matrix ;
			

			
            glUniformMatrix4fv(uniforms.mvp, 1, GL_FALSE, mvp);
			glUniformMatrix4fv(uniforms.mv,1,GL_FALSE, cam.view() * m_matrix);
			glUniformMatrix4fv(uniforms.model,1,GL_FALSE, m_matrix);
			glUniform3fv(uniforms.LightPosition,1,vLightPosition * m_matrix);
			glUniform3fv(uniforms.ConeDirection,1,vec4(vec3(CdirX,CdirY, CdirZ),1) * m_matrix);
			
		//	DBOUT(CdirY << endl);
		for(i = 0 ; i < 3; i++)
		{
		glBindVertexArray(map.VAO[i]);
		glBindTexture(GL_TEXTURE_2D, textures[i+1]);
		
		glDrawArrays(GL_TRIANGLES,0,200000);
		}

		m_matrix = vmath::translate(-cam.position()) * vmath::translate(ent->Position) * vmath::rotate(90.0f * float(t) * 0.9f,vec3(0.0,1.0,0.0)) ;

		mvp =  cam.matrix() * m_matrix ;
			

			
        glUniformMatrix4fv(uniforms.mvp, 1, GL_FALSE, mvp);
		glUniformMatrix4fv(uniforms.mv,1,GL_FALSE, cam.view() * m_matrix);
		//glUniformMatrix4fv(uniforms.model,1,GL_FALSE, m_matrix);
		//glUniform3fv(uniforms.LightPosition,1,vLightPosition * m_matrix);
		//glUniform3fv(uniforms.ConeDirection,1,vec4(vec3(CdirX,CdirY, CdirZ),1) * m_matrix);

		ent->Draw();
		UpdateKey();
	}

	void onMouseMove(int x, int y)
	{
		glfwSetMousePos(info.windowWidth/2,info.windowHeight/2);
		//if(x != info.windowWidth/2 && y != info.windowHeight/2){
			if(last_Xpos == 0 && last_Ypos == 0)
			{
				last_Xpos = (float)x;
				last_Ypos = (float)y;
			}
			cam.offsetOrientation((float)((y - info.windowHeight/2 ) * MOUSE_SENSIBILITY),(float)((x - info.windowWidth/2 ) * MOUSE_SENSIBILITY));
			
			//DBOUT("Angle HORIZONTAL" << cam.HorizontalAngle() << "\r\n");
			//DBOUT("X: " << x << " Y: " << y << "\r\n");
			/*last_Xpos = (float)x;
			last_Ypos = (float)y;*/
		//}
	}

	void onKey(int key, int action)
	{
		//DBOUT("KEY: " << key << "\r\n");

		if(action == 0)
		{
			keyboard.action.pop_back();
			keyboard.key.erase(std::remove(keyboard.key.begin(),keyboard.key.end(),key), keyboard.key.end());			
		}
		else
		{
			if(keyboard.action.size() > 4)
			{
				keyboard.action.pop_back();
				keyboard.key.pop_back();
			}
			keyboard.action.push_back(action);
			keyboard.key.push_back(key);
		}
		
	}

	void UpdateKey()
	{
		
			for(int i = 0; i < keyboard.key.size(); i++)
			{
				if(keyboard.action[i] == 1)
				{
					vec3 move;
			
					switch(keyboard.key[i])
					{
						case KEY_W:
							move = vec3(sin(cam.HorizontalAngle()* PI/180 ),0.0f,-cos(cam.HorizontalAngle() * PI/180));
							cam.offsetPosition(move * SPEED);
							break;
						case KEY_S:
							move = vec3(sin(cam.HorizontalAngle()* PI/180 ),0.0f,-cos(cam.HorizontalAngle() * PI/180));
							cam.offsetPosition(move * SPEED * -1);
							break;
						case KEY_A:
							move = vec3(sin((cam.HorizontalAngle() + 90)* PI/180 ),0.0f,-cos((cam.HorizontalAngle()+90) * PI/180));
							cam.offsetPosition(move * (SPEED*.75) *-1);
							break;
						case KEY_D:
							move = vec3(sin((cam.HorizontalAngle()+90)* PI/180 ),0.0f,-cos((cam.HorizontalAngle()+90) * PI/180));
							cam.offsetPosition(move * (SPEED*.75));
							break;
						case KEY_E:
							cam.offsetPosition(vec3(0.0f,-SPEED,0.0f));
							break;
						case KEY_Q:
							cam.offsetPosition(vec3(0.0f,SPEED,0.0f));
							break;
						case KEY_T: CdirX += 0.05f; 
							DBOUT("X :" << CdirX << " Y: " << CdirY << "Z: " << CdirZ << endl);
							break;
						case KEY_G: CdirX -= 0.05f;DBOUT("X :" << CdirX << " Y: " << CdirY << "Z: " << CdirZ << endl);
							break;
						case KEY_Y: CdirY += 0.05f; DBOUT("X :" << CdirX << " Y: " << CdirY << "Z: " << CdirZ << endl);
							break;
						case KEY_H: CdirY -= 0.05f;DBOUT("X :" << CdirX << " Y: " << CdirY << "Z: " << CdirZ << endl);
							break;
						case KEY_U: CdirZ += 0.05f;DBOUT("X :" << CdirX << " Y: " << CdirY << "Z: " << CdirZ << endl);
							break;
						case KEY_J: CdirZ -= 0.05f;DBOUT("X :" << CdirX << " Y: " << CdirY << "Z: " << CdirZ << endl);
							break;
						case KEY_UP: fspotcoscutoff += 0.005f;
							DBOUT("SPOT: "<< fspotcoscutoff << "\r\n");
							break;
						case KEY_DOWN: fspotcoscutoff -= 0.005f;
							DBOUT("SPOT: " << fspotcoscutoff  << "\r\n");
							break;
						}
				}
			}
			
	}
};
DECLARE_MAIN(main);