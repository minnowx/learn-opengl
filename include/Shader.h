#pragma once
#include "PCH.h"

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, const GLfloat* value) const;
	void setVec3(const std::string& name, const GLfloat* value) const;
private:
	void checkCompile(unsigned int shader, const char* type);
};
