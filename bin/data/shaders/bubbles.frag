#version 330

uniform vec4 color;
uniform vec2 res;
uniform float time;

uniform float gradientStart;
uniform float gradientEnd;

in vec2 vTexCoord;

out vec4 fragColor;

float noise1(vec2 p)
{
    p = fract(p * vec2(233.42, 865.32));
    p += dot(p, p+32.33);
    return fract(p.x * p.y);
}

vec2 noise2(vec2 p)
{
    float n = noise1(p);
    return vec2(n, noise1(p+n));
}

vec2 getPos(vec2 id)
{
    vec2 noise = noise2(id);
        
    float x = sin(time * noise.x);
    float y = cos(time * noise.y);
    
    return vec2(x, y) * 0.4;
}

void main()
{
    //  Normalized pixel coordinates (from 0 to 1)
    vec2 uv = (gl_FragCoord.xy - .5 * res.xy) / res.y;

    //  Time varying pixel color
    vec3 col = vec3(.0);
    uv *= 7.0;
    float m = .0;
    
    //  Iter 1
    vec2 gridUv = fract(uv) -.5;
    vec2 cellId = floor(uv);
    
    vec2 p = getPos(cellId);
    float d = length(gridUv - p);
    float ri = clamp(noise1(cellId), 0.01, 0.06);
    float ro = ri + 0.05;
    m = smoothstep(ro, ri, d);
        
    col = vec3(m) * color.rgb;

    float alpha = col.r * 0.87;

    // Iter 2
    uv += 0.1;
    uv *= 1.41;
    m = 0.0;

    gridUv = fract(uv) -.5;
    cellId = floor(uv);

    p = getPos(cellId);
    d = length(gridUv - p);
    ri = clamp(noise1(cellId), 0.01, 0.06);
    ro = ri + 0.05;
    m = smoothstep(ro, ri, d);

    col = max(col, vec3(m) * color.rgb);
    alpha = max(alpha, col.r * 0.87);

    // Iter 3
    uv += 0.15;
    uv *= 1.41;
    m = 0.0;

    gridUv = fract(uv) -.5;
    cellId = floor(uv);

    p = getPos(cellId);
    d = length(gridUv - p);
    ri = clamp(noise1(cellId), 0.01, 0.06);
    ro = ri + 0.05;
    m = smoothstep(ro, ri, d);

    col = max(col, vec3(m) * color.rgb);
    alpha = max(alpha, col.r * 0.87);

    //  Alpha gradient
    alpha *= smoothstep(gradientStart, gradientEnd, gl_FragCoord.x / res.x);
    alpha *= 1.0 - smoothstep(1.0 - gradientEnd, 1.0 - gradientStart, gl_FragCoord.x / res.x);
    
    //  Output to screen
    fragColor = vec4(col,alpha);
}