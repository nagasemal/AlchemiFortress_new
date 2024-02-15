#include "MagicCircle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
Texture2D tex3 : register(t2);
SamplerState samLinear : register(s0);


float4 blur(float2 uv)
{
	
    float power = 0.005f;
	
	// for���񂷉񐔕��p���[��������
    float center = 1.0f - power * 9.0f;
	
    float4 output = 0;
	
    for (int i = 0; i < 9;i++)
    {
        output += tex.Sample(samLinear, uv
		+ float2(((i % 3) - 1) * 0.01f, ((i / 3) - 1) * 0.01f)) * power;

    }
	
    output += center;
	
    return output;
}

float4 motionBlur(float2 uv)
{
    float power = 0.1f;
	
    float4 output = 0;
	
    for (int i = 0; i < 9;i++)
    {
        output += tex.Sample(samLinear, uv 
		+ float2(sin(diffuse.a - i * 0.1f) * 0.05f, 0.0f))
		* power * (10.0f - i) / 5.0f;

    }
	
    return output;
}


float4 main(PS_INPUT input) : SV_TARGET
{	
	// ���@�w�摜
    float4 output = tex.Sample(samLinear, input.Tex);

	// ���@�w���o��������J�ڗp���[���摜
	float4 output_2 = tex2.Sample(samLinear, input.Tex);
	
    float4 output_3 = tex3.Sample(samLinear, input.Tex * 0.8f + diffuse.a * 0.1f);

	// �o���ƐF�t��
	output.a *= step(output_2.x, diffuse.a);
	
	output.xyz *= step(output_2.xyz, diffuse.a);
	
    output *= input.Color;
	
    //output *= blur(input.Tex);
		
	// UV�X�N���[��	
    output.xyz += smoothstep(0.0f, 0.8f, output_3.xyz) * 0.5f;
	
	return output;
}