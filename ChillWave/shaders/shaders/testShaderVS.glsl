vec4 gl_Color = vec4(1,1,1,1);

void main()
{
	gl_FrontColor = vec4(1,1,1,1);
	gl_Position = ftransform();
}