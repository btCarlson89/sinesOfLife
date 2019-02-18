#version 330

uniform int dir;
uniform float pad;
uniform vec2 res;
uniform vec2 pos;
uniform vec4 color;

uniform float gradientStart;
uniform float gradientEnd;

in vec2 vTexCoord;

out vec4 fragColor;


void main(){
	//	Normalize coordinates
	vec2 uv = gl_FragCoord.xy / res.xy;
    vec2 p = pos / res;
    float l;
    if(dir == 0 || dir == 2) l = pad / res.y;
    else l = pad / res.x;
    
    //  Color
    vec3 col;
    if(dir == 0) col = vec3(step(pos.y + l, uv.y)) * color.rgb;
    if(dir == 1) col = vec3(1.0 - step(1.0 - l, uv.x)) * color.rgb;
    
    //  Alpha
    float alpha;
    if(dir == 0) alpha = smoothstep(pos.y, pos.y + l,uv.y);
    if(dir == 1) alpha = 1.0 - smoothstep(1.0 - l, 1.0, uv.x);
    if(alpha < 1.0) alpha *= 0.67;

    //  Alpha gradient
    alpha *= smoothstep(gradientStart, gradientEnd, uv.x);
    alpha *= 1.0 - smoothstep(1.0 - gradientEnd, 1.0 - gradientStart, uv.x);
    
	//	Color out
	fragColor = vec4(col, alpha);
}