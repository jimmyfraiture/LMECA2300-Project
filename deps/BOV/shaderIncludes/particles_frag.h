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
"out vec4 outColor;\n"
"\n"
"void main()\n"
"{\n"
"	float sdf = length(posGeom) - width;\n"
"	vec2 alpha = smoothstep(-pixelSize, pixelSize, -sdf - vec2(0.0f, outlineWidth));\n"
"	float distToCenter = 1-(length(abs(localPos-posGeom))/width);\n"
"	//outColor = vec4(distToCenter, 0, 0, 1);\n"
"	//outColor = dataGeom*distToCenter*2;\n"
"	//outColor = distToCenter*alpha.y;\n"
"	vec4 m = mix(outlineColor, dataGeom, alpha.y);\n"
"	//outColor = m;\n"
"	vec3 col = vec3(m.r, m.g, m.b);\n"
"	col = col/length(col);\n"
"	col = col/length(col);\n"
"	outColor.r = col.x;\n"
"	outColor.g = col.y;\n"
"	outColor.b = col.z;\n"
"	if(marker == 3){//Light particules\n"
"		if(posGeom.x > 0 && posGeom.y > 0){\n"
"			outColor.a = (distToCenter)*0.6 + 0.4;//*0.2 + 0.8;\n"
"		} else {\n"
"			outColor.a = 0;\n"
"		}\n"
"	//Faudra encore ajouter un cas pour quand on plot la pression etc\n"
"	} else if(speedGeom.x == -1000) {//Il ne l'a pas encore je ne sais pas pq\n"
"		outColor.a = 1;\n"
"		outColor.a = (distToCenter+0.5)*0.2 + 0.6;/////////Utiliser pour le fluide\n"
"		if(distToCenter > 0.5){\n"
"			outColor.a = 0.8;\n"
"		}else if(distToCenter < 0.3){\n"
"			outColor.a = 0;\n"
"		}\n"
"		//outColor.a = 0.6;\n"
"		outColor.a *= alpha.x;\n"
"	} else {\n"
"		/*\n"
"		float distToLight = 1 - length(posGeom + width/2)/width;//- length(abs(localPos + width/2)/2) + 0.5;\n"
"		if(gl_Color.a == 0){\n"
"			outColor.a = 0.5;\n"
"		} else {\n"
"			outColor.a = 1;\n"
"		}*/\n"
"		outColor.a = 1;\n"
"		outColor.a *= alpha.x;\n"
"	}\n"
"}\n"
};
