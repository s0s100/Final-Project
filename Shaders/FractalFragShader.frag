#version 430 core

in vec3 pos;
out vec4 fragColor;
uniform float time;

float mandelbrot(vec2 proj){
	vec2 c = proj * 2 + vec2(-0.56267837374, 0.65679461735);
	// vec2 pos = proj + vec2(-1.96680095, 0.00000478);
	vec2 z = vec2(0.0);
	float iterNum = 256.0;
	float n = 2.0;
	for (int i = 0; i < iterNum; i++){
		z = vec2(pow(z.x, 2) - pow(z.y, 2), 2.0 * z.x * z.y) + c;
		if (sqrt(dot(z,z)) >= n) {
			return i/iterNum;// From 0 to 1
		}
	}

	return 0.0;
}

float julia(vec2 proj, float a){
	vec2 z = proj * 2;
	// vec2 c = vec2(8 - a,-8 + a);
	vec2 c = vec2(1 - a, 1 - a);
	float iterNum = 256.0;
	float n = 2.0;
	float increment = 10.0;
	for (int i = 0; i < iterNum; i++){
		z = vec2(pow(z.x, 2) - pow(z.y, 2), 2.0 * z.x * z.y) + c;
		if (sqrt(dot(z,z)) >= n) {
			return i/iterNum * increment;// From 0 to 1
		}
	}

	return 0.0;
}

// C=r*cos(a)+i*r*sin(a)
float julia2(vec2 proj, float a){
	vec2 z = proj * 2;	
	float r = 0.77;
	vec2 c = vec2(r * cos(a), r * sin(a));
	float iterNum = 256.0;
	float n = 3;
	float increment = 10.0;
	for (int i = 0; i < iterNum; i++){
		z = vec2(pow(z.x, 2) - pow(z.y, 2), 2.0 * z.x * z.y) + c;
		if (sqrt(dot(z,z)) >= n) {
			return i/iterNum * increment;// From 0 to 1
		}
	}

	return 0.0;
}

// Get the color using value [0,1] and time [0, +inf)
vec3 getColor(float val, float time){
	// Simplies black/white solution
	//result += val;

	// Color clange using cos and time instead of the random value
	if (val != 0) {
		float r = 0;
		float g = 0;
		float b = 0;
		float cosVal = cos(time) / 2;
		float cosVal2 = cos(time + radians(180)) / 2;
		if (val < 0.8 && val > 0.2) {
			r = cosVal;
			g = val;
			b = cosVal2;
		}
		
		return vec3(r, g, b);
	}
	
	return vec3(0.0);
}

void main(){
	vec2 proj = pos.xy;
	// Zoom in using current program runtime
	// proj /= pow(time, 2);
	// proj /= pow(time, 2);
	// float res = mandelbrot(proj);
	// float res = julia(proj, time / 2);
	float res = julia2(proj, time / 2);

	vec3 col = vec3(0);
	col += getColor(res, time);

	fragColor = vec4(col, 1.0);
}