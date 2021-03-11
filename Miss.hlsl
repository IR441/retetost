#include "Common.hlsl"

//ジオメトリがヒットしなかったとき実行
[shader("miss")]
void Miss(inout HitInfo payload : SV_RayPayload)
{
    //uint2 launchIndex = DispatchRaysIndex().xy;
    //float2 dims = float2(DispatchRaysDimensions().xy);

    //float ramp = launchIndex.y / dims.y;

    //sun vector
    float3 Sun_vector = (1,1,0.2);
    Sun_vector /= length(Sun_vector);
    float3 cameraDirection = WorldRayDirection();
    cameraDirection /= length(cameraDirection);
    float Sun_cos = cameraDirection.x * Sun_vector.x + cameraDirection.y * Sun_vector.y + cameraDirection.z * Sun_vector.z;
    float Sun_mcos= cameraDirection.x * Sun_vector.x - cameraDirection.y * Sun_vector.y + cameraDirection.z * Sun_vector.z;

    //sky
    float soko = sqrt(cameraDirection.x * cameraDirection.x + cameraDirection.z * cameraDirection.z);
    float shamen = sqrt(cameraDirection.x * cameraDirection.x + cameraDirection.y * cameraDirection.y + cameraDirection.z * cameraDirection.z);
    float hightcos = soko / shamen;
    float hightsin = cameraDirection.y / shamen;
    float4 color = float4(0.0f, 0.0f, 0.7f, 1.0f) * (1 - hightsin* hightsin)+float4(0.0f, 5.0f, 5.0f, 1.0f) * (hightsin * hightsin);
    
    //sun color
    if (Sun_cos > 0.999)color = float4(1.0f, 0.0f, 0.0f, 1.0f);
    if (Sun_mcos >0.999)color = float4(1.0f, 0.0f, 0.0f, 1.0f);

    payload.colorAndDistance = color;
    
}