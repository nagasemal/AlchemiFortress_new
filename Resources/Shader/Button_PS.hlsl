#include "Button.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
Texture2D tex3 : register(t2);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	// ���n�̃e�N�X�`��
	Texture2D none;
	// �^�C�g�����S
	float4 output = none.Sample(samLinear,input.Tex);

	// �ݒ肵���F���󂯂Ƃ�
	output = Colors;

	return output;
}