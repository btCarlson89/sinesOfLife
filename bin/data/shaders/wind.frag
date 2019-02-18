#version 330

uniform vec2 res;
uniform float time;
uniform int N;

uniform float gradientStart;
uniform float gradientEnd;

uniform sampler2DRect colors;
uniform sampler2DRect offsets;
uniform sampler2DRect timeFactors;
uniform sampler2DRect noiseFactors;

in vec2 vTexCoord;

out vec4 fragColor;

float plot(vec2 st, float y){
  return  smoothstep( y - 0.03, y, st.y) -
          smoothstep( y, y + 0.03, st.y);
}

void main(){
	//	Normalize coordinates
	vec2 uv = gl_FragCoord.xy / res.xy;

    //  Initialize
    float alpha = 0.0;
    float maxAlpha = 0.0;
    
    //  Color
    vec3 c;
    c = texture(colors, vec2(0.0, 0.0)).rgb;

    //  Resize & center coordinate system
    vec2 p = uv * 2.0 - 1.0;
    float scale = 2.0;
    p *= scale;

    //  Noise
    float y0 = p.y;
    for(int i = 0; i < N; ++i){
        //  Time
        float t = time * texture(timeFactors, vec2(i, 0)).x;
        //  Apply offset
        float offset = (texture(offsets, vec2(i, 0)).x * 2.0 - 1.0);
        p.y = y0 + offset;
        //  Noise parameters
        float n0 = texture(noiseFactors, vec2(i, 0)).x;
        float n1 = texture(noiseFactors, vec2(i, 0)).y;
        float n2 = texture(noiseFactors, vec2(i, 0)).z;
        float n3 = texture(noiseFactors, vec2(i, 0)).w;
        //  Noise function
        float y = sin(p.x + offset + t + n1) + n2 * sin(p.x * 2. + t + n3) + 0.1 * sin(p.x * 3. + t + n3);
        y *= n0;
        float pct = plot(p,y);
        //  Color
        vec3 color = texture(colors, vec2(i, 0.0)).rgb;
        alpha *= texture(colors, vec2(i, 0.0)).a;
        alpha = max(alpha, pct);
        if(alpha > maxAlpha)
        {
            c = color;
            maxAlpha = alpha;
        }
        else
            c = mix(c, color, pct);
    }

    //  Alpha gradient
    alpha *= smoothstep(gradientStart, gradientEnd, uv.x);
    alpha *= 1.0 - smoothstep(1.0 - gradientEnd, 1.0 - gradientStart, uv.x);
    
	fragColor = vec4(c,alpha);
}