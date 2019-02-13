#version 330

uniform vec2 res;
uniform float time;
uniform int N;

uniform sampler2DRect colors;
uniform sampler2DRect offsets;
uniform sampler2DRect timeFactors;
uniform sampler2DRect noiseFactors;

in vec2 vTexCoord;

out vec4 fragColor;

float plot(vec2 st, float x){
  return  smoothstep( x - 0.075, x, st.x) -
          smoothstep( x, x + 0.05, st.x);
}

void main(){
	//	Normalize coordinates
	vec2 uv = gl_FragCoord.xy / res.xy;

    //  Initialize
    float alpha = 0.0;

    //  Resize & center coordinate system
    vec2 p = uv * 2.0 - 1.0;
    float scale = 4.0;
    p *= scale;

    //  Noise
    float x0 = p.x;
    for(int i = 0; i < N; ++i){
        //  Time
        float t = time * texture(timeFactors, vec2(i, 0)).x;
        //  Apply offset
        float offset = (texture(offsets, vec2(i, 0)).x * 2.0 - 1.0);
        p.x = x0 + scale * offset;
        //  Noise parameters
        float n0 = texture(noiseFactors, vec2(i, 0)).x;
        float n1 = texture(noiseFactors, vec2(i, 0)).y;
        float n2 = texture(noiseFactors, vec2(i, 0)).z;
        float n3 = texture(noiseFactors, vec2(i, 0)).w;
        //  Noise function
        float x = sin(p.y + t + n1) + n2 * sin(p.y * 2. + t + n3) + 0.1 * sin(p.y * 3. + t + n3);
        x *= n0;
        float pct = plot(p,x);
        alpha *= texture(colors, vec2(i, 0.0)).a;
        alpha = max(alpha, pct);
    }

    //  Color
    vec3 c;
	c = texture(colors, vec2(0.0, 0.0)).rgb;
    
	fragColor = vec4(c,alpha);
}