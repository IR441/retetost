struct PSInput {
	float4 position : SV_POSITION;
	float4 color : COLOR;

};
// #DXR Extra: Perspective Camera
cbuffer CameraParams : register(b0)
{
	float4x4 view;
	float4x4 projection;
}
//// #DXR Extra: Perspective Camera
//cbuffer LightParams : register(b1)
//{
//	float4x4 l_view;
//	float4x4 l_projection;
//}
PSInput VSMain(float4 position : POSITION, float4 color : COLOR)
{
	PSInput result;

	// #DXR Extra: Perspective Camera
	float4 pos = position;
	pos = mul(view, pos);
	pos = mul(projection, pos);
	result.position = pos;
	result.color = color;

	return result;
}
float4 PSMain(PSInput input) : SV_TARGET{ return input.color; }
