uniform mat4 mvp;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{	
	FragPos = gl_Vertex.xyz; 
	Normal = gl_Normal;
	TexCoord = gl_MultiTexCoord0.st;
	gl_Position = mvp * gl_Vertex;
}