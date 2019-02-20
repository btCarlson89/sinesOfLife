#version 330

uniform vec2 res;
uniform float time;

uniform vec4 color1;
uniform vec4 color2;

uniform float gradientStart;
uniform float gradientEnd;

uniform vec2 pos;

uniform sampler2DRect screenTex;

in vec2 vTexCoord;

out vec4 fragColor;

const float TAU = 6.283185307179586476925286766559;
const float PI = 0.5 * TAU;

const float octaves = 8.0;
const vec2 globalVelocity = vec2(6.0, 8.0);

float hash11(float p)
{
    const float HASHSCALE1 = .1031;
	vec3 p3  = fract(vec3(p) * HASHSCALE1);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}

float getAmplitude(float octave)
{
    return 1.0 / pow(2.0, octave);
}

float getWavelength(float octave)
{
	const float maximumWavelength = 50.0;
    
    float wavelength = TAU * maximumWavelength / pow(2.0, octave);

    // Make it aperiodic with a random factor
    wavelength *= 0.75 + 0.5 * hash11(1.337 * octave);
    
    return wavelength;
}

float getSpeed(float octave)
{
    const float speedScaleFactor = 2.0;
    
    // Smallest waves travel twice as fast as given velocity,
    // largest waves travel half as fast
    const vec2 speedRange = vec2(2.0, 0.5);
    
    // Map octave to speed range
    float speed = speedScaleFactor * mix(speedRange.x, speedRange.y, octave / (max(1.0, octaves - 1.0)));
    
    // Add some randomness
    speed *= 0.5 + hash11(1.337 * octave);
    
    return speed;
}

float getHeight(vec2 position, vec2 velocity)
{
    float magnitude = length(velocity);
    vec2 direction = (magnitude > 1e-5) ? velocity / magnitude : vec2(0.0);

    float height = 0.0;
    
    for (float octave = 0.0; octave < octaves; octave += 1.0)
    {
        float amplitude = getAmplitude(octave);
        float wavelength = getWavelength(octave);
        float speed = magnitude * getSpeed(octave);
        float frequency = TAU / wavelength;
        float randomPhaseOffset = hash11(1.337 * octave) * TAU;
        float phase = speed * frequency + randomPhaseOffset;
        float theta = dot(-direction, position);
    
        height += amplitude * sin(theta * frequency + time * phase);
    }
    
    return height;
}

void main()
{
    vec2 uv = gl_FragCoord.xy / res.xy;
    
    //  Draw circle
    vec2 offset = uv - vec2(0.5, 0.5);
    float dist = sqrt(dot(offset, offset));
    float r = 0.5;
    float thickness = 0.01;
    float alpha = smoothstep(r + thickness, r - thickness, dist);

    //  Shading
	//float intensity =0.25 * getHeight(gl_FragCoord.xy, globalVelocity) + 0.5;
    //fragColor = mix(color1, color2, intensity);

    //  Color lookup
    fragColor = texture(screenTex, gl_FragCoord.xy + pos);

    fragColor.a = alpha;
}