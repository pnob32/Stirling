#include "TexObject.h"

void TexObject::load2DTexture(const char* filename) {
    // Load and create a texture
	textures.push_back(0);
    glGenTextures(1, &textures[textures.size()-1]);
    glBindTexture(GL_TEXTURE_2D, textures[textures.size()-1]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
    image = SOIL_load_image(filename, &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

/*! \fn initLayout - initiates array/buffer objects
\param int attribCount: number of attributes per vertex
\return integer: 1 if ran correctly, -1 if error occured
*/
int TexObject::initLayout(int attribCount, int stride) {
    return Drawable::initLayout(attribCount, stride);
}

/*! \fn loadLayoutBuffer - loads vertex buffer into Drawable and instantiates class as using a layout loading method
\param GLfloat* vertices
\param int size: number of vertices
\return integer: 1 if ran correctly, -1 if error occured
*/
int TexObject::loadLayoutBuffer(vector<GLfloat> vertices, int size) {
    return Drawable::loadLayoutBuffer(vertices, size);
}

int TexObject::initTexture(int index, int dimensions, int stride) {
    glBindVertexArray(VAO);
    
    glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(index);

    glBindVertexArray(0); // Unbind VAO

    PPK_ASSERT_WARNING(glGetError() == GL_NO_ERROR, "Problem loading layout buffer\n");
    if (glGetError != GL_NO_ERROR) {
        return -1;
    }

    return 1;
}

int TexObject::draw() {
    // Bind Texture

    //glBindTexture(GL_TEXTURE_2D, texture);
    return Drawable::draw();
}