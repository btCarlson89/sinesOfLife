#version 330

uniform int numDots;
uniform float time;
uniform vec2 res;
uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;
uniform vec4 color4;
uniform sampler2DRect posTex;

in vec2 vTexCoord;

out vec4 fragColor;

#define TWO_PI 6.283185307179586476925286766559

float rand(vec2 n) { 
    return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

vec3 hash33(vec3 p) { 
    float n = sin(dot(p, vec3(7, 157, 113)));    
    return fract(vec3(2097152, 262144, 32768)*n)*2. - 1.;
}

float noise(in vec3 p)
{
    vec3 i = floor(p + dot(p, vec3(0.333333)) );  p -= i - dot(i, vec3(0.166666)) ;
    vec3 i1 = step(p.yzx, p), i2 = max(i1, 1.0-i1.zxy); i1 = min(i1, 1.0-i1.zxy);    
    vec3 p1 = p - i1 + 0.166666, p2 = p - i2 + 0.333333, p3 = p - 0.5;
    vec4 v = max(0.5 - vec4(dot(p,p), dot(p1,p1), dot(p2,p2), dot(p3,p3)), 0.0);
    vec4 d = vec4(dot(p, hash33(i)), dot(p1, hash33(i + i1)), dot(p2, hash33(i + i2)), dot(p3, hash33(i + 1.)));
    return clamp(dot(d, v*v*v*8.)*1.732 + .5, 0., 1.);
}

void main(){
	//  Normalized pixel coordinates
    vec2 uv = (gl_FragCoord.xy) / res.y;
    //  Initialize
    float alpha = 0.0;
    float thickness = 0.002;
    vec3 color;
    float maxM1 = 0.0;
    float maxM2 = 0.0;
    float maxM3 = 0.0;
    //  Dot origin
    for(int i = 0; i < numDots; ++i){
        //  Get position
        vec2 pos = texture(posTex, vec2(i, 0.0)).xy;
        //  Get radius
        float radius = texture(posTex, vec2(i, 0.0)).z;
        float dr = 0.15 * radius;
        //  Add noise
        float angle = noise(vec3(pos.x * time * 0.5, pos.y * time * 0.1, 1.0)) * TWO_PI;
        vec2 dir = vec2(cos(angle), sin(angle));
        pos += 0.05* dir;
        //  Draw circle
        vec2 offset = uv - pos;
        float dist = sqrt(dot(offset, offset));
        float r = radius;
        alpha += smoothstep(r + thickness, r - thickness, dist);
        //  First mix
        r -= dr;
        float m = smoothstep(r + thickness, r - thickness, dist);
        if(m < maxM1) m = maxM1;
        else maxM1 = m;
        color = mix(color1, color2, m).rgb;
        //  Second mix
        r -= dr;
        m = smoothstep(r + thickness, r - thickness, dist);
        if(m < maxM2) m = maxM2;
        else maxM2 = m;
        color = mix(color, color3.rgb, m).rgb;
        //  Third mix
        r -= dr;
        m = smoothstep(r + thickness, r - thickness, dist);
        if(m < maxM3) m = maxM3;
        else maxM3 = m;
        color = mix(color, color4.rgb, m).rgb;

    }
    alpha = clamp(alpha, 0.0, 1.0);
    //
    
    //
    

	fragColor = vec4(color, alpha);
}