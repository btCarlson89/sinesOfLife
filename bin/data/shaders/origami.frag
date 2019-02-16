#version 330

uniform vec2 res;
uniform int N;

uniform sampler2DRect colors;
uniform sampler2DRect p0s;
uniform sampler2DRect p1s;
uniform sampler2DRect p2s;

in vec2 vTexCoord;

out vec4 fragColor;

// signed distance to a 2D triangle
float sdTriangle( in vec2 p0, in vec2 p1, in vec2 p2, in vec2 p )
{
	vec2 e0 = p1 - p0;
	vec2 e1 = p2 - p1;
	vec2 e2 = p0 - p2;

	vec2 v0 = p - p0;
	vec2 v1 = p - p1;
	vec2 v2 = p - p2;

	vec2 pq0 = v0 - e0*clamp( dot(v0,e0)/dot(e0,e0), 0.0, 1.0 );
	vec2 pq1 = v1 - e1*clamp( dot(v1,e1)/dot(e1,e1), 0.0, 1.0 );
	vec2 pq2 = v2 - e2*clamp( dot(v2,e2)/dot(e2,e2), 0.0, 1.0 );
    
    float s = sign( e0.x*e2.y - e0.y*e2.x );
    vec2 d = min( min( vec2( dot( pq0, pq0 ), s*(v0.x*e0.y-v0.y*e0.x) ),
                       vec2( dot( pq1, pq1 ), s*(v1.x*e1.y-v1.y*e1.x) )),
                       vec2( dot( pq2, pq2 ), s*(v2.x*e2.y-v2.y*e2.x) ));

	return -sqrt(d.x)*sign(d.y);
}

void main()
{
    //	Normalize coordinates
	vec2 uv = (gl_FragCoord.xy) / res.xy;

    //  Initialize
    //  Color
    vec3 c = texture(colors, vec2(0.0, 0.0)).rgb;
    float alpha = 0.0;
    float maxAlpha = 0.0;
    float colorMix = 0.0;

    //  Draw triangles
    for(int i = 0; i < 3; ++i){
        //  Read vertex positions
        vec2 p0 = texture(p0s, vec2(i, 0.0)).xy;
        //p0 = vec2(0.0, 0.0);
        vec2 p1 = texture(p1s, vec2(i, 0.0)).xy;
        vec2 p2 = texture(p2s, vec2(i, 0.0)).xy;

        //  Distance function
        float d = sdTriangle( p0, p1, p2, uv );
        float pct = 1.0 - sign(d);
        
        //  Color & Alpha
        vec3 color = texture(colors, vec2(i, 0.0)).rgb;
        colorMix = mix(pct, 1.0, 1.0-smoothstep(0.0, 0.005, d));
        alpha = max(alpha, colorMix);
        alpha = mix(alpha, 1.0, 1.0-smoothstep(0.0, 0.005, d));
        if(alpha > maxAlpha)
        {
            maxAlpha = alpha;
            c = color;
        }
        else
            c = mix(c, color, colorMix);
    }

    //  Final out
	fragColor = vec4(c, alpha);
}