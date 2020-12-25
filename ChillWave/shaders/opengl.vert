
uniform mat4 u_WorldViewProjection;
uniform mat4 u_InverseWorld;
uniform mat4 u_TransposedWorld;
uniform vec3 u_CameraPos;
uniform vec4 u_LightColour;

void main(void)
{
	gl_Position = u_WorldViewProjection * gl_Vertex;
	
	vec4 normal = vec4(gl_Normal, 0.0);
	normal = u_InverseWorld * normal;
	normal = normalize(normal);
	
	vec4 worldpos = gl_Vertex * u_TransposedWorld;
	
	vec4 lightVector = worldpos - vec4(u_CameraPos,1.0);
	lightVector = normalize(lightVector);
	
	float tmp2 = dot(-lightVector, normal);
	
	vec4 tmp = (u_LightColour * tmp2) + u_LightColour;
	gl_FrontColor = vec4(tmp.x, tmp.y, tmp.z, 0.0);
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
