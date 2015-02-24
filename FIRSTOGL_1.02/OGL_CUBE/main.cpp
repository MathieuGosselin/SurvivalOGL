#include <sb6.h>
#include <sb6ktx.h>
#include <vmath.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "MGstream.h"
#include "camera.h"
#include "World.h"

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
	//Entity *ent;

	float last_Xpos;
	float last_Ypos;
	char LogBuffer[4098];

	World* myWorld;

	 struct
    {
        GLint mvp;
		GLint mv;
		GLint model;
        GLint offset;

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

		glGetProgramInfoLog(rendering_program,1024,NULL,LogBuffer);
		if(LogBuffer[1] != -51)
		{
			writetxt("ProgramLOG.txt",LogBuffer);
			//glfwCloseWindow();
		}

		glUseProgram(rendering_program);

		myWorld = new World("..//OGL_CUBE//media//map//MapTest2.png",rendering_program);
		//ent = new Entity("..//OGL_CUBE//media//model//SpiderMan//SpiderMan.obj",vmath::vec3(10.0f,5.0f,10.0f));

		
		
		

		

		tex_wall = sb6::ktx::file::load("..//OGL_CUBE//media//textures//brick.ktx");
		tex_floor = sb6::ktx::file::load("..//OGL_CUBE//media//textures//floor.ktx");
		tex_ceiling = sb6::ktx::file::load("..//OGL_CUBE//media/textures//ceiling.ktx");

		GLuint textures[] = {tex_floor,tex_wall,tex_ceiling};

		last_Xpos = 0.0f;
		last_Ypos = 0.0f;
;

		for(int i = 0; i < 3;i++)
		{
			glBindTexture(GL_TEXTURE_2D,textures[i]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
 
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

		myWorld->Update();
		myWorld->Draw();

		//int i;
		// GLuint textures[] = { tex_wall, tex_floor, tex_wall, tex_ceiling };
  //    
		// vmath::mat4 m_matrix =    vmath::translate(-cam.position()) /** vmath::translate(vec3(12.0,-1.5,12.0)) * vmath::rotate(90.0f * (float)t * 0.9f, vmath::vec3(0.0f, 0.0f, 1.0f)) *
		//							vmath::translate(vec3(-12.0,-1.5,-12.0))*/;
		//	
		//	vmath::mat4 mvp =  cam.matrix() * m_matrix ;
		//	

		//	
  //          glUniformMatrix4fv(uniforms.mvp, 1, GL_FALSE, mvp);
		//	glUniformMatrix4fv(uniforms.mv,1,GL_FALSE, cam.view() * m_matrix);
		//	glUniformMatrix4fv(uniforms.model,1,GL_FALSE, m_matrix);
		//	
		////	DBOUT(CdirY << endl);
		//for(i = 0 ; i < 3; i++)
		//{
		//glBindVertexArray(map.VAO[i]);
		//glBindTexture(GL_TEXTURE_2D, textures[i+1]);
		//
		//glDrawArrays(GL_TRIANGLES,0,200000);
		//}

		//m_matrix = vmath::translate(-cam.position()) * vmath::translate(ent2->Position) * vmath::rotate(90.0f * float(t) * 0.9f,vec3(0.0,1.0,0.0)) ;

		//mvp =  cam.matrix() * m_matrix ;
		//	

		//	
  //      glUniformMatrix4fv(uniforms.mvp, 1, GL_FALSE, mvp);
		//glUniformMatrix4fv(uniforms.mv,1,GL_FALSE, cam.view() * m_matrix);
		//glUniformMatrix4fv(uniforms.model,1,GL_FALSE, m_matrix);
		//glUniform3fv(uniforms.LightPosition,1,vLightPosition * m_matrix);
		//glUniform3fv(uniforms.ConeDirection,1,vec4(vec3(CdirX,CdirY, CdirZ),1) * m_matrix);



		//ent->Draw();


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

			
			myWorld->cam->offsetOrientation((float)((y - info.windowHeight/2 ) * MOUSE_SENSIBILITY),(float)((x - info.windowWidth/2 ) * MOUSE_SENSIBILITY));
			
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
							move = vec3(sin(myWorld->cam->HorizontalAngle()* PI/180 ),0.0f,-cos(myWorld->cam->HorizontalAngle() * PI/180));
							myWorld->cam->offsetPosition(move * SPEED);
							break;
						case KEY_S:
							move = vec3(sin(myWorld->cam->HorizontalAngle()* PI/180 ),0.0f,-cos(myWorld->cam->HorizontalAngle() * PI/180));
							myWorld->cam->offsetPosition(move * SPEED * -1);
							break;
						case KEY_A:
							move = vec3(sin((myWorld->cam->HorizontalAngle() + 90)* PI/180 ),0.0f,-cos((myWorld->cam->HorizontalAngle()+90) * PI/180));
							myWorld->cam->offsetPosition(move * (SPEED*.75) *-1);
							break;
						case KEY_D:
							move = vec3(sin((myWorld->cam->HorizontalAngle()+90)* PI/180 ),0.0f,-cos((myWorld->cam->HorizontalAngle()+90) * PI/180));
							myWorld->cam->offsetPosition(move * (SPEED*.75));
							break;
						case KEY_E:
							myWorld->cam->offsetPosition(vec3(0.0f,-SPEED,0.0f));
							break;
						case KEY_Q:
							myWorld->cam->offsetPosition(vec3(0.0f,SPEED,0.0f));
							break;
						case KEY_T: 
							break;
						case KEY_G: 
							break;
						case KEY_Y: 
							break;
						case KEY_H: 
							break;
						case KEY_U: 
							break;
						case KEY_J:
							break;
						case KEY_UP:
							break;
						case KEY_DOWN: 
							break;
						}
				}
			}
			
	}
};
DECLARE_MAIN(main);