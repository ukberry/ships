/*
 * shaders.cpp
 *
 *  Created on: 28 Jun 2014
 *      Author: sam
 */

#include "shaders.h"

const char *vert_shader_main = "#version 300 es\n"
		"layout(location = 0) in vec4 vCoord;"
		"layout(location = 1) in vec2 texCoord;"
		"layout(location = 2) in vec3 vNormal;"
		"layout(location = 3) in vec4 colour;"
		"uniform mat4 M;"
		"uniform mat4 V;"
		"uniform mat4 P;"
		"uniform mat3 Minv;"
		"uniform mat4 Vinv;"
		"uniform mat4 VSprite;"
		"uniform bool isSprite;"
		"out vec4 vColour;"
		"void main() {"
		"mat4 MVP;"
		"if (isSprite) {"
		"gl_Position = VSprite * M * vCoord ;"
		"}"
		"else {"
		"MVP = P * V * M;"
		"gl_Position = MVP *vCoord;"
		"}"
		"vec3 normalDirection = normalize(Minv*vNormal);"
		//"vec3 light_dir = normalize(vec3(Vinv * vec4(0.0, 0.0, 0.0, 1.0) - M * vCoord));"
		"vec3 lightDirection = normalize(vec3(1.0,0.3,1.0));"
		"vec3 lightDirection2 = normalize(vec3(-1.0,-1,-0.7));"

		//"vColour = colour * vec4( 0.3 + vec3(1)*max(0.0,dot(lightDirection,normalDirection)), 1.0);"
		"vColour = vec4( vec3(colour)*(max(0.0,dot(normalDirection,lightDirection))+vec3(0.3,0.1,0.3)*max(0.0,dot(normalDirection,lightDirection2))), 1.0);"
		//"vColour = colour;"
		"}";

const char *frag_shader_main = "#version 300 es\n"
		"precision mediump float;"
		"in vec4 vColour;"
		"out vec4 fColour;"
		"void main() {"
		"fColour = vColour;"
		//" fColour = vec4(0., 0., 1., 1.);"
		"}";

void print_log(GLint object) {
	GLint log_length = 0;
	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else {
		std::cerr << "printlog: Not a shader or a program\n";
		return;
	}

	char* log = new char[log_length];

	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, NULL, log);
	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, NULL, log);

	std::cerr << log;
	delete log;
}

GLuint create_program() {

	std::cout << "Creating GL program...\n";
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vs, 1, &vert_shader_main, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
	if (0 == compile_ok) {
		std::cerr << "Error in vertex shader\n";
		print_log(vs);
		return 0;
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fs, 1, &frag_shader_main, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
	if (!compile_ok) {
		std::cerr << "Error in fragment shader\n";
		print_log(fs);
		return 0;
	}

	std::cout << "Shaders compiled... linking...\n";

	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		std::cerr << "glLinkProgram:";
		return 0;
	}

	glDeleteShader(fs);
	glDeleteShader(vs);
	std::cout << "Shaders compiled on graphics card successfully!\n";
	return program;
}
