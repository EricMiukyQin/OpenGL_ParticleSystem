#version 330

uniform mat4 myTransformMatrix;
uniform mat4 myProjectionMatrix;
uniform mat4 myModelviewMatrix;

in vec4 myColor;
in vec3 myPosition;

out vec4 myColorOut;

void main() {
	mat4 transformMat = myProjectionMatrix * myModelviewMatrix * myTransformMatrix;
	gl_Position = transformMat * vec4(myPosition, 1.f);
	myColorOut = myColor;
}
