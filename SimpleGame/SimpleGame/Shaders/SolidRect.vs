#version 330

in vec3 a_Position;		// ����
uniform vec4 u_Trans;	// ��������
//uniform float u_Time;

void main()
{
	vec4 newPosition;
	//newPosition = a_Position // * sin(u_time)
	
	
	newPosition.xy = a_Position.xy*u_Trans.w + u_Trans.xy;
	newPosition.z = 0;
	newPosition.w= 1;
	gl_Position = newPosition;

	//float term = sin(u_Time);
	//FragColor = vec4(u_Color.r*term, u_Color.g*term, u_Color.b*term)
}
