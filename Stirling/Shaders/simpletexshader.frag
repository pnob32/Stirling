#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
   color = mix(texture(texture0, TexCoord), texture(texture1,
TexCoord), 0.2);
}
/*
void main()
{
    color = vec4(ourColor, 1.0) * texture(ourTexture, TexCoord);
}*/
