#include "MyModelShader.hlsli"

float4 main(PSInput pin) : SV_TARGET0
{    
    // �����_�̕���
    float3 Direction = pin.Position.xyz - Eyes.xyz;
    
    // �����_�ƃJ�����ʒu�̋���(�����قǎ��_�͈͂�傫�����邽��)
    float d = distance(Eyes.xyz, EyePosition);
    
    // �����_�܂ł̋���
    float Distance = length(Direction) / (d * 0.25);
    // �����_����̋����̉e��
    float fixationAtten = saturate(1.0f / (Distance * Distance));
    float power = 1.05;
    
    fixationAtten *= power;
           
    // �[�x�l
    float depth = (length((EyePosition.xyz - Eyes.xyz) - pin.Position.xyz) / 100);
    
    // �����_�͈�,�A�E�g���C���`��,�[�x�l,���ݒ�
    return float4(fixationAtten, Time.x, depth, 1.0f);
    
}