#pragma once
#include "cocos2d.h"
#ifdef _MSC_VER
typedef __int8  s8;
typedef __int16 s16;
typedef __int32 s32;
typedef __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
#else
typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#endif

typedef float f32;
typedef double f64;

/// shake action using perlin noise 1d
class PerlinTransformShakeAction : public cocos2d::ActionInterval
{
public:
	static PerlinTransformShakeAction* create(f32 duration, f32 fSpeed, f32 fMagnitude);

	virtual void update(f32 time) override;
	virtual void stop() override;

CC_CONSTRUCTOR_ACCESS:
	PerlinTransformShakeAction();
	virtual ~PerlinTransformShakeAction() {}

	bool initWithDuration(f32 duration, f32 fSpeed, f32 fMagnitude);

protected:
	f32 m_fSpeed;                       ///< frequency
	f32 m_fMagnitude;                   ///< pixel
	f32 m_fRandomStart;

private:
	CC_DISALLOW_COPY_AND_ASSIGN(PerlinTransformShakeAction);
};