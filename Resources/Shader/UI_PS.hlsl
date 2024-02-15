#include "UI.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

#define PI 3.14159265359

float4 main(PS_INPUT input) : SV_TARGET
{
	//�@�摜�\��
	float4 output = tex.Sample(samLinear, input.tex);

	//�@�|���S���ɔC�ӂ̐F��t����
	float4 outputw = output * colors;

	outputw.rgb *= input.color.rgb;

	//�@if���̕`�����Ɠ��� �����ō��
    float sharpen = 0.0f;
	//�@���E�ǂ��炩���邩��bool�̑��
    float directionFlag = step(1.0f, windowSize.z);
	
    sharpen += lerp(1.0f, 0.0f, step(input.color.a, (colors.z * directionFlag) + (input.tex.x + (input.tex.x * -2.0f * directionFlag)))); // ����
    
    outputw.a *= sharpen;

	return outputw;
}