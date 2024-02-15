#include "Veil.hlsli"

Texture2D tex : register(t0);
Texture2D ruleTex : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	// �ݒ肵���F���󂯂Ƃ�
	float4 output = Colors;
	// ���[���摜���󂯎��
	float4 rule = ruleTex.Sample(samLinear, input.Tex);

	// diffuse.g,b�ɂ͏c���̒l�������Ă���
	float2 imageRage = float2(input.Tex.x * diffuse.g, input.Tex.y * diffuse.b);
	// ���ɕ\������摜���󂯎��
	float4 imageTex = tex.Sample(samLinear, imageRage);

	// ���[���摜��p�����t�F�[�h���� (diffuse.a ���ԕϐ�.1)
	output.a *= step(rule.x, diffuse.a);
	// ���o�̈�,�F���ɓ����t�F�[�h�������s���@(diffuse.r ���ԕϐ�.2)
	output.rgb *= step(rule.x, diffuse.r);
	//// ���������𒆂ɕ`�悷�镶���摜�ɂ��s��
	imageTex.a *= step(rule.x, diffuse.r);

	// ���ɂ̂݉摜��`�悷��
	output += imageTex;

	return output;
}