Texture2D Texture : register(t0);
sampler Sampler : register(s0);

// �V���h�E�}�b�v�e�N�X�`��
Texture2D ShadowMapTexture : register(t3);
// �V���h�E�}�b�v�p�e�N�X�`���T���v���[
SamplerComparisonState ShadowMapSampler : register(s1);

// �萔�o�b�t�@
cbuffer Parameters : register(b0)
{
    float4 DiffuseColor             : packoffset(c0);	// �f�B�t���[�Y�F
    float3 EmissiveColor            : packoffset(c1);	// �G�~�b�V�u�F
    float3 SpecularColor            : packoffset(c2);	// �X�y�L�����F
    float  SpecularPower            : packoffset(c2.w);	// �X�y�L�����̋��x

    float3 LightDirection[3]        : packoffset(c3);	// ���C�g�̕���
    float3 LightDiffuseColor[3]     : packoffset(c6);	// ���C�g�̐F
    float3 LightSpecularColor[3]    : packoffset(c9);	// ���C�g�̃X�y�L�����F

    float3 EyePosition              : packoffset(c12);	// �J�����̈ʒu

    float3 FogColor                 : packoffset(c13);	// �t�H�O�̐F
    float4 FogVector                : packoffset(c14);	// �t�H�O�̂�����

    float4x4 World                  : packoffset(c15);	// ���[���h�s��
    
    float3x3 WorldInverseTranspose  : packoffset(c19);	// ���[���h�t�]�u�s��
    float4x4 WorldViewProj          : packoffset(c22);	// ���[���h�s�� �~ �r���[�s�� �~ �v���W�F�N�V�����s��

};

// �ǉ�����萔�o�b�t�@
cbuffer Parameters : register(b1)
{
    float4x4 LightViewProj : packoffset(c0);
    float4 LightDir : packoffset(c5);
    float4 LightAmbient : packoffset(c6);
};

// �v���O�������ŕω����鎞�ԕϐ�������
cbuffer UserParam : register(b2)
{
    float4 Time;
    float4 PaintColor;
    float4 LimLightColor;
    float4 Eyes;    // �����_
    float4 LightPosition;
    float4 MousePosition;
    float4 CrystalPosition[10];
    
    float4x4 View; // �r���[�s��
    float4x4 Proj; // �v���W�F�N�V�����s��
}

struct PSInput
{
    float4 PositionPS : SV_Position;
    float4 Diffuse : COLOR0;
    float3 Specular : COLOR1;
    float2 TexCoord : TEXCOORD0;
    float4 LightViewPos : TEXCOORD1;
    float4 Position : Position;
    float3 Normal : NORMAL;
};

float4 AddScreen(float4 color, float4 screenCol)
{
    return 1 - (1 - color) * (1 - screenCol);
}