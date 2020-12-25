
uniform sampler2D u_Texture1;
uniform mat4 u_WorldViewProjection;
uniform mat4 u_InverseWorld;
uniform mat4 u_TransposedWorld;
uniform vec3 u_CameraPos;
uniform vec4 u_LightColour;

void main (void)
{
    vec4 col = texture2D(u_Texture1, vec2(gl_TexCoord[0]));
    col *= gl_Color;
    gl_FragColor = col * 2.0;
}
