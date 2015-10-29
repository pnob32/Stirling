/*! \file Program.h
    \brief Header file for includes and definitions on GLSL shader wrapper
*/

#ifndef PROGRAM_H
#define PROGRAM_H

#include "global_includes.h"
#include "GLSL.h"

class Program
{
public:
	Program();
	virtual ~Program();
	
	inline void setVerbose(bool v) { verbose = v; }
	inline bool isVerbose() const { return verbose; }

	inline GLuint getPID() { return pid; }
	
	void setShaderNames(const std::string &v, const std::string &f);
	virtual bool init();
	virtual void bind();
	virtual void unbind();

	void addAttribute(const std::string &name);
	void addUniform(const std::string &name);
	GLint getAttribute(const std::string &name) const;
	GLint getUniform(const std::string &name) const;
	
protected:
	std::string vShaderName;
	std::string fShaderName;
	
private:
	GLuint pid;
	std::map<std::string,GLint> attributes;
	std::map<std::string,GLint> uniforms;
	bool verbose;
};

#endif