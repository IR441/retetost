#include "Common.hlsl"

struct STriVertex
{
	float3 vertex;
	float4 color;
	float3 normal;
	float2 uv;
};


StructuredBuffer<STriVertex> BTriVertex : register(t0);
StructuredBuffer<int> indices: register(t1);




struct MyStructColor
{
	float4 a;
	float4 b;
	float4 c;
};

cbuffer Colors : register(b0)
{
	MyStructColor Tint[3];
}


//影
struct ShadowHitInfo
{
	bool isHit;
};
// Raytracing acceleration structure, accessed as a SRV
RaytracingAccelerationStructure SceneBVH : register(t2);
 
// #DXR Extra: Perspective Light
cbuffer LightParams : register(b1)
{
	float4x4 l_view;
	float4x4 l_projection;
}
//ペイロードを受け取る
//交差属性を受け取る、原点からの距離
[shader("closesthit")] 
void ClosestHit(inout HitInfo payload, Attributes attrib) 
{
	float3 barycentrics =
		float3(1.f - attrib.bary.x - attrib.bary.y, attrib.bary.x, attrib.bary.y);

	uint vertId = 3 * PrimitiveIndex();

	/// #DXR Extra: Per-Instance Data
	float3 hitColor = float3(0.6, 0.7, 0.6);

	
		 hitColor = BTriVertex[indices[vertId + 0]].color * barycentrics.x +
		BTriVertex[indices[vertId + 1]].color * barycentrics.y +
		BTriVertex[indices[vertId + 2]].color * barycentrics.z;

	 //float3 light = normalize(float3(1,-1,1));
	 //float brightness = dot(-light, BTriVertex[indices[vertId + 0]].normal);


	 //float3 hsv;
	 //float4 ret = (float4)0;
	 //     // RGB to HSV
	 //float a=max(hitColor.g, hitColor.b);
	 // float m_max = max(hitColor.r, a);
	 // float b = min(hitColor.g, hitColor.b);
	 // float m_min = min(hitColor.r,b);
	 // float delta = m_max - m_min;
	 //
	 // hsv.z = m_max; // v
	 //     if (m_max != 0.0) {
	 //         hsv.y = delta / m_max;//s
	 //
		//  }
		//  else {
		//	  hsv.y = 0.0;//s
		//  }
		//  if (hitColor.r == m_max) {
  //         hsv.x = (hitColor.g - hitColor.b) / delta;// h

		//  }
		//  else if (hitColor.g == m_max) {
  //         hsv.x = 2 + (hitColor.b - hitColor.r) / delta;// h

		//  }
		//  else {
  //         hsv.x = 4 + (hitColor.r - hitColor.g) / delta;// h

		//  }
  //    hsv.x /= 6.0;
  //    if (hsv.x < 0) hsv.x += 1.0;

	 // //
	 // hsv.b= brightness;

	 //     // HSV to RGB
	 // if (hsv.y == 0) { /* Grayscale */
		//          ret.r = ret.g = ret.b = hsv.z;// v
		// 
	 // }
	 // else {
		//  if (1.0 <= hsv.x) hsv.x -= 1.0;
		//  hsv.x *= 6.0;
		//  float i = floor(hsv.x);
		//  float f = hsv.x - i;
		//  float aa = hsv.z * (1 - hsv.y);
		//  float bb = hsv.z * (1 - (hsv.y * f));
		//  float cc = hsv.z * (1 - (hsv.y * (1 - f)));
		//  if (i < 1) {
		//	              ret.r = hsv.z; ret.g = cc;    ret.b = aa;
		//	 
		//  }
		//  else if (i < 2) {
		//	              ret.r = bb;    ret.g = hsv.z; ret.b = aa;
		//	 
		//  }
		//  else if (i < 3) {
		//	              ret.r = aa;    ret.g = hsv.z; ret.b = cc;
		//	 
		//  }
		//  else if (i < 4) {
		//	              ret.r = aa;    ret.g = bb;    ret.b = hsv.z;
		//	 
		//  }
		//  else if (i < 5) {
		//	              ret.r = cc;    ret.g = aa;    ret.b = hsv.z;
		//	 
		//  }
		//  else {
		//	              ret.r = hsv.z; ret.g = aa;    ret.b = bb;
		//	 
		//  }
		// 
	 // }


	 //hitColor= float3(ret.r, ret.g, ret.b);

		 float3 lightPos = float3(2, 10, -2);
		 //normal
	 float3 normalColor= BTriVertex[indices[vertId + 0]].normal * barycentrics.x +
		 BTriVertex[indices[vertId + 1]].normal * barycentrics.y +
		 BTriVertex[indices[vertId + 2]].normal * barycentrics.z;
	 //toon
	 if (normalColor.x !=0.0f && normalColor.y != 1.0f&&normalColor.z != 0.0f) {
		 float light = 0.5 - dot(normalColor, lightPos) * 0.5f;

		 if(light<0.5f){
			 light = 1.0f;
		 }
		 else {
			 light = 0.5f;
		 }
		 hitColor *= light;

		 float3 cameraPosition = WorldRayOrigin();
		 cameraPosition /= length(cameraPosition);

		 float d = dot(cameraPosition, normalColor);

	
	  }
	 

	
	payload.colorAndDistance = float4(hitColor, RayTCurrent());


}

[shader("closesthit")]
void PlaneClosestHit(inout HitInfo payload, Attributes attrib)
{
	float3 lightPos = float3(2, 5, -2);
	float3 cameraPosition = WorldRayOrigin();
	float3 cameraDirection = WorldRayDirection();
	float3 worldOrigin = WorldRayOrigin() + RayTCurrent() * WorldRayDirection();
	float3 lightDir = normalize(lightPos - worldOrigin);

	HitInfo colorpayload;
	colorpayload.colorAndDistance = float4(1, 0, 0, 1);

	cameraDirection.y = -cameraDirection.y;
	RayDesc colorray;
	colorray.Origin = worldOrigin;
	colorray.Direction = cameraDirection;
	colorray.TMin = 0.01;
	colorray.TMax = 100000;
	
	//反射
	TraceRay(
		SceneBVH,
		RAY_FLAG_NONE,
		0xFF,
		0,
		0,
		0,
		colorray,
		colorpayload);

	RayDesc ray;
	ray.Origin = worldOrigin;
	ray.Direction = lightDir;
	ray.TMin = 0.01;
	ray.TMax = 100000;
	bool hit = true;

	ShadowHitInfo shadowPayload;
	shadowPayload.isHit = false;

	//影ぼかし
	float tag = shadowPayload.isHit ? 0.0f : 1.0f;
	for (int i = 0; i < 10; i++) {
		float3 b_lightPos = lightPos;
		b_lightPos.z += i*0.1f;

		lightDir = normalize(b_lightPos - worldOrigin);
		ray.Direction = lightDir;
		TraceRay(
			SceneBVH,
			RAY_FLAG_NONE,
			0xFF,
			1,
			0,
			1,
			ray,
			shadowPayload);
		tag += shadowPayload.isHit ? 0.0f : 1.0f;
	}

	

	float3 barycentrics =
		float3(1.f - attrib.bary.x - attrib.bary.y, attrib.bary.x, attrib.bary.y);

	float4 hitColor = float4((colorpayload.colorAndDistance.rgb), RayTCurrent());
	hitColor = (hitColor+ float4(0.1, 0.1, 0.1, 1)* tag) / 2;
	payload.colorAndDistance = float4(hitColor);
	
}