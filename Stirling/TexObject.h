/*! \file TexObject.h
    \brief Texture asset class
    Extends Drawable
*/

#ifndef TEXOBJECT_H
#define TEXOBJECT_H

#include "global_includes.h"
#include "Drawable.h"

class TexObject : Drawable {
public:
    TexObject(GLenum mode) : Drawable(mode) {};
    ~TexObject();

    void load2DTexture(const char* filename);

    /*! \fn init - initiates array/buffer objects
    \param int attribCount: number of attributes per vertex
    \return integer: 1 if ran correctly, -1 if error occured
    */
    int initLayout(int attribCount, int stride);

    /*! \fn loadLayoutBuffer - loads vertex buffer into Drawable and instantiates class as using a layout loading method
    \param GLfloat* vertices
    \param int size: number of vertices
    \return integer: 1 if ran correctly, -1 if error occured
    */
    int loadLayoutBuffer(vector<GLfloat> vertices, int size);

    int initTexture(int index, int dimensions, int stride);

	inline void embedColor() { Drawable::embedColor(); }

	inline int setIndexBuffer(vector<GLuint> buf) { return Drawable::setIndexBuffer(buf); }

	inline void setShader(Program* _shader) { Drawable::setShader(_shader); }

	inline void setModel(glm::mat4 _M) { Drawable::setModel(_M); }
	inline glm::mat4* getModel() { return Drawable::getModel(); }

    int draw();

protected:
    unsigned char * image;
    bool hasTexture;

    int texWidth, texHeight, texDepth;
};

#endif