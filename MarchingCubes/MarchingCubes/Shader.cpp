#include "Shader.h"
Shader::Shader(const char* vertexPath, const char* geometryPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(geometryPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file’s buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		geometryCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vertexShaderCode = vertexCode.c_str();
	const char* geometryShaderCode = geometryCode.c_str();

	// 2. compile shaders
	unsigned int vertex, geometry;
	int success;
	char infoLog[512];
	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glShaderSource(geometry, 1, &geometryShaderCode, NULL);
	glCompileShader(vertex);
	glCompileShader(geometry);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	};
	glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geometry, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" <<
			infoLog << std::endl;
	};

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, geometry);
	//glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
			infoLog << std::endl;
	}
	// delete shaders; they’re linked into our program and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(geometry);
	//glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}