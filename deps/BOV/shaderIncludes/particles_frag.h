static GLchar particles_frag[]={"#version 150 core\n"
"\n"
"layout (std140) uniform objectBlock\n"
"{\n"
"	vec4 fillColor;    // set by bov_points_set_color()\n"
"	vec4 outlineColor; // set by bov_points_set_outline_color()\n"
"	vec2 localPos;     // set by bov_points_set_pos()\n"
"	vec2 localScale;   // set by bov_points_scale()\n"
"	float width;       // set by bov_points_set_width()\n"
"	float marker;      // set by bov_poitns_set_markers()\n"
"	float outlineWidth;// set by bov_points_set_outline_width()\n"
"	int space_type;    // set by bov_points_set_space_type()\n"
"                       // 0: normal sizes, 1: unzoomable, 2: unmodifable pixel size\n"
"};\n"
"\n"
"layout (std140) uniform worldBlock\n"
"{\n"
"	vec2 resolution;\n"
"	vec2 translate;\n"
"	float zoom;\n"
"};\n"
"\n"
"in vec2 posGeom;\n"
"flat in vec2 speedGeom;\n"
"flat in vec4 dataGeom;\n"
"flat in float pixelSize; // = 2.0 / (min(resolution.x, resolution.y) * zoom)\n"
"\n"
"uniform sampler2D textu;\n"
"\n"
"out vec4 outColor;\n"
"\n"
"void main() {\n"
"	float sdf = length(posGeom) - width;\n"
"	vec2 alpha = smoothstep(-pixelSize, pixelSize, -sdf - vec2(0.0f, outlineWidth));\n"
"	float distToCenter = 1-(length(abs(localPos-posGeom))/width);\n"
"	vec4 m = mix(outlineColor, dataGeom, alpha.y);\n"
"	vec3 col = vec3(m.r, m.g, m.b);\n"
"	col = col/length(col);\n"
"	col = col/length(col);\n"
"	outColor.r = col.x;\n"
"	outColor.g = col.y;\n"
"	outColor.b = col.z;\n"
"	if(marker == 3){//Light particules\n"
"		if(posGeom.x < 0 && posGeom.y < 0){\n"
"			if(distToCenter > 0.99){\n"
"				outColor.a = 1;\n"
"			} else\n"
"				outColor.a = (distToCenter)*0.8 + 0.2;//*0.2 + 0.8;\n"
"		} else {\n"
"			outColor.a = 0;\n"
"		}\n"
"		outColor.g = 0;\n"
"	} else if(speedGeom.x == -1000) {//Fluid\n"
"		outColor.a = 1;\n"
"		//outColor.a = (distToCenter+0.5)*0.2 + 0.6;\n"
"		if(distToCenter < 0.3)\n"
"			outColor.a = 0;\n"
"		outColor.g = 0;\n"
"		outColor.a *= alpha.x;\n"
"	} else if(speedGeom.x == -2000){//Shadow particles\n"
"		outColor = m;\n"
"		outColor.g = 0;\n"
"		outColor.a = 1;\n"
"		outColor.a *= alpha.x;		\n"
"	} else if(speedGeom.x >= 4000){//Continious field\n"
"		outColor.r = distToCenter*(speedGeom.x - 4000);\n"
"		outColor.g = 1;\n"
"		outColor.b = distToCenter;\n"
"		outColor.a = 0.2;\n"
"		outColor.a *= alpha.x;\n"
"	} else {\n"
"		outColor.g = 0;\n"
"		outColor.a = 1;\n"
"		outColor.a *= alpha.x;\n"
"	}\n"
"}\n"
};
