
#include "Program.h"

Program::Program() :
	pid(0),
	vShaderName(""),
	fShaderName(""),
	verbose(true)
{
	
}

Program::~Program()
{
	
}

void Program::setShaderNames(const string &v, const string &f)
{
	vShaderName = v;
	fShaderName = f;
}

bool Program::init()
{
    PPK_ASSERT_DEBUG(glGetError() == GL_NO_ERROR, "Shader(s) failed to compile correctly\n");
    // Vertex shader
    ifstream vertIn(vShaderName);
    string vertContents((istreambuf_iterator<char>(vertIn)), istreambuf_iterator<char>());
    const GLchar* vertSource = vertContents.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSource, NULL);
    glCompileShader(vertexShader);
    // Check for compile time errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment shader
    ifstream fragIn(fShaderName);
    string fragContents((istreambuf_iterator<char>(fragIn)), istreambuf_iterator<char>());
    const GLchar* fragSource = fragContents.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSource, NULL);
    glCompileShader(fragmentShader);
    // Check for compile time errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Link shaders
    pid = glCreateProgram();
    glAttachShader(pid, vertexShader);
    glAttachShader(pid, fragmentShader);
    glLinkProgram(pid);
    // Check for linking errors
    glGetProgramiv(pid, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(pid, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    PPK_ASSERT_DEBUG(glGetError() == GL_NO_ERROR, "Shader(s) failed to compile correctly\n");
    
    return true;
	/*GLint rc;
	
	// Create shader handles
	GLuint VS = glCreateShader(GL_VERTEX_SHADER);
	GLuint FS = glCreateShader(GL_FRAGMENT_SHADER);
	
	// Read shader sources
	const char *vshader = GLSL::textFileRead(vShaderName.c_str());
	const char *fshader = GLSL::textFileRead(fShaderName.c_str());
	glShaderSource(VS, 1, &vshader, NULL);
	glShaderSource(FS, 1, &fshader, NULL);
	
	// Compile vertex shader
	glCompileShader(VS);
	glGetShaderiv(VS, GL_COMPILE_STATUS, &rc);
	if(!rc) {
		if(isVerbose()) {
			GLSL::printShaderInfoLog(VS);
			printf("Error compiling vertex shader %s\n", vShaderName.c_str());
		}
		return false;
	}
	
	// Compile fragment shader
	glCompileShader(FS);
	glGetShaderiv(FS, GL_COMPILE_STATUS, &rc);
	if(!rc) {
		if(isVerbose()) {
			GLSL::printShaderInfoLog(FS);
			printf("Error compiling fragment shader %s\n", fShaderName.c_str());
		}
		return false;
	}
	
	// Create the program and link
	pid = glCreateProgram();
	glAttachShader(pid, VS);
	glAttachShader(pid, FS);
	glLinkProgram(pid);
	glGetProgramiv(pid, GL_LINK_STATUS, &rc);
	if(!rc) {
		if(isVerbose()) {
			GLSL::printProgramInfoLog(pid);
			printf("Error linking shaders %s and %s\n", vShaderName.c_str(), fShaderName.c_str());
		}
		return false;
	}
	
	GLSL::printError();
	PPK_ASSERT_FATAL(glGetError() == GL_NO_ERROR, "Shader(s) failed to compile correctly\n");
	return true;*/
}

void Program::bind()
{
	glUseProgram(pid);
}

void Program::unbind()
{
	glUseProgram(0);
}

void Program::addAttribute(const string &name)
{
	attributes[name] = GLSL::getAttribLocation(pid, name.c_str());
}

void Program::addUniform(const string &name)
{
	uniforms[name] = GLSL::getUniformLocation(pid, name.c_str());
}

GLint Program::getAttribute(const string &name) const
{
	map<string,GLint>::const_iterator attribute = attributes.find(name.c_str());
	if(attribute == attributes.end()) {
		if(isVerbose()) {
			printf("%s is not an attribute variable\n", name);
		}
		return 0;
	}
	return attribute->second;
}

GLint Program::getUniform(const string &name) const
{
	map<string,GLint>::const_iterator uniform = uniforms.find(name.c_str());
	if(uniform == uniforms.end()) {
        if (isVerbose()) {
            printf("%s is not a uniform variable\n", name);
		}
		return 0;
	}
	return uniform->second;
}
