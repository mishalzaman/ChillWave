out vec4 FragColor;

uniform sampler2D u_Texture1;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
in vec3 Normal;  
in vec2 TexCoord;

vec2 iResolution = vec2(1280,720);

const mat4 bayertl = mat4( 
 0.0/64.0, 32.0/64.0,  8.0/64.0, 40.0/64.0,
48.0/64.0, 16.0/64.0, 56.0/64.0, 24.0/64.0,
12.0/64.0, 44.0/64.0,  4.0/64.0, 36.0/64.0,
60.0/64.0, 28.0/64.0, 52.0/64.0, 20.0/64.0
);

const mat4 bayertr = mat4( 
 2.0/64.0, 34.0/64.0, 10.0/64.0, 42.0/64.0,
50.0/64.0, 18.0/64.0, 58.0/64.0, 26.0/64.0,
14.0/64.0, 46.0/64.0,  6.0/64.0, 38.0/64.0,
62.0/64.0, 30.0/64.0, 54.0/64.0, 22.0/64.0
);

const mat4 bayerbl = mat4( 
 3.0/64.0, 35.0/64.0, 11.0/64.0, 43.0/64.0,
51.0/64.0, 19.0/64.0, 59.0/64.0, 27.0/64.0,
15.0/64.0, 47.0/64.0,  7.0/64.0, 39.0/64.0,
63.0/64.0, 31.0/64.0, 55.0/64.0, 23.0/64.0
);
	
const mat4 bayerbr = mat4( 
 1.0/64.0, 33.0/64.0,  9.0/64.0, 41.0/64.0,
49.0/64.0, 17.0/64.0, 57.0/64.0, 25.0/64.0,
13.0/64.0, 45.0/64.0,  5.0/64.0, 37.0/64.0,
61.0/64.0, 29.0/64.0, 53.0/64.0, 21.0/64.0
);

float dither( mat4 m, ivec2 p )
{
	if( p.y == 0 ) 
	{
		if( p.x == 0 ) return m[0][0];
		else if( p.x == 1 ) return m[1][0];
		else if( p.x == 2 ) return m[2][0];
		else return m[3][0];	
	}	
	else if( p.y == 1 ) 
	{
		if( p.x == 0 ) return m[0][1];
		else if( p.x == 1 ) return m[1][1];
		else if( p.x == 2 ) return m[2][1];
		else return m[3][1];	
	}	
	else if( p.y == 2 ) 
	{
		if( p.x == 0 ) return m[0][1];
		else if( p.x == 1 ) return m[1][2];
		else if( p.x == 2 ) return m[2][2];
		else return m[3][2];	
	}	
	else 
	{
		if( p.x == 0 ) return m[0][3];
		else if( p.x == 1 ) return m[1][3];
		else if( p.x == 2 ) return m[2][3];
		else return m[3][3];	
	}	
}

void main()
{
	ivec2 p = ivec2(mod( gl_FragCoord.xy, 8.0 ));
	vec2 uv = gl_FragCoord.xy / iResolution.xy;
	vec3 c = texture( u_Texture1, TexCoord ).xyz;
	c = pow( c, vec3(2.2) );	
	c -= 1.0/255.0;
	
	vec3 d = vec3(0.0);
	if( p.x <= 3 && p.y <= 3 )
	{
		d.r = float( c.r > dither( bayertl, p ) );
		d.g = float( c.g > dither( bayertl, p ) );
		d.b = float( c.b > dither( bayertl, p ) );
	}
	else if ( p.x > 3 && p.y <= 3 )
	{
		d.r = float( c.r > dither( bayertr, p -ivec2(4,0) ) );
		d.g = float( c.g > dither( bayertr, p -ivec2(4,0) ) );
		d.b = float( c.b > dither( bayertr, p -ivec2(4,0) ) );
	}
	else if( p.x <= 3 && p.y > 3 )
	{
		d.r = float( c.r > dither( bayerbl, p-ivec2(0,4)  ) );
		d.g = float( c.g > dither( bayerbl, p-ivec2(0,4)  ) );
		d.b = float( c.b > dither( bayerbl, p-ivec2(0,4)  ) );
	}
	else if ( p.x > 3 && p.y > 3 )
	{
		d.r = float( c.r > dither( bayerbr, p -ivec2(4,4) ) );
		d.g = float( c.g > dither( bayerbr, p -ivec2(4,4) ) );
		d.b = float( c.b > dither( bayerbr, p -ivec2(4,4) ) );
	}

	// ambient
    float ambientStrength = 1.9;
    vec3 ambient = ambientStrength * lightColor * texture2D(u_Texture1, gl_FragCoord.xy).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - gl_FragCoord.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * texture2D(u_Texture1, TexCoord).rgb;
    
    // specular
    float specularStrength = 0.1;
    vec3 viewDir = normalize(viewPos - gl_FragCoord.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = ambient + diffuse;

	FragColor = vec4(d, 1.0) + vec4(result,1.0);
}