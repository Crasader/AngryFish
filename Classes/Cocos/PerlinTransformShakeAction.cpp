///*
//* PerlinShakeAction.cpp
//*
//*  Created on: Mar 18, 2016
//*      Author: Joseph39 & OscarLeif
//*/
//
#include "PerlinTransformShakeAction.h"


USING_NS_CC;

///////////////////////////////////////////////////////////////////////////////
// perlin noise
///////////////////////////////////////////////////////////////////////////////
//https://mrl.nyu.edu/~perlin/doc/oscar.html
/* coherent noise function over 1, 2 or 3 dimensions */
/* (copyright Ken Perlin) */

#define PERLIN_B 0x100
#define PERLIN_BM 0xff

#define PERLIN_N 0x1000
#define PERLIN_NP 12   /* 2^N */
#define PERLIN_NM 0xfff

static s32 p[PERLIN_B + PERLIN_B + 2];
//static f32 g3[B + B + 2][3];
//static f32 g2[B + B + 2][2];
static f32 g1[PERLIN_B + PERLIN_B + 2];
static s32 start = 1;

static void init(void);

#define s_curvePerlin(t) ( t * t * (3. - 2. * t) )

#define lerpPerlin(t, a, b) ( a + t * (b - a) )

#define setupPerlin(i,b0,b1,r0,r1)\
	t = vec[i] + PERLIN_N;\
	b0 = ((s32)t) & PERLIN_BM;\
	b1 = (b0+1) & PERLIN_BM;\
	r0 = t - (s32)t;\
	r1 = r0 - 1.;

static void init(void)
{
	s32 i, j, k;

	for (i = 0; i < PERLIN_B; i++) {
		p[i] = i;

		g1[i] = (f32)((cocos2d::random() % (PERLIN_B + PERLIN_B)) - PERLIN_B) / PERLIN_B;

		//for (j = 0 ; j < 2 ; j++)
		//	g2[i][j] = (f32)((cocos2d::random() % (B + B)) - B) / B;
		//normalize2(g2[i]);

		//for (j = 0 ; j < 3 ; j++)
		//	g3[i][j] = (f32)((random() % (B + B)) - B) / B;
		//normalize3(g3[i]);
	}

	while (--i) {
		k = p[i];
		p[i] = p[j = cocos2d::random() % PERLIN_B];
		p[j] = k;
	}

	for (i = 0; i < PERLIN_B + 2; i++) {
		p[PERLIN_B + i] = p[i];
		g1[PERLIN_B + i] = g1[i];
		//for (j = 0 ; j < 2 ; j++)
		//	g2[B + i][j] = g2[i][j];
		//for (j = 0 ; j < 3 ; j++)
		//	g3[B + i][j] = g3[i][j];
	}
}

double noise1(double arg)
{
	s32 bx0, bx1;
	f32 rx0, rx1, sx, t, u, v, vec[1];

	vec[0] = arg;
	if (start) {
		start = 0;
		init();
	}

	setupPerlin(0, bx0, bx1, rx0, rx1);

	sx = s_curvePerlin(rx0);

	u = rx0 * g1[p[bx0]];
	v = rx1 * g1[p[bx1]];

	return lerpPerlin(sx, u, v);
}

///////////////////////////////////////////////////////////////////////////////
// CShakeAction
///////////////////////////////////////////////////////////////////////////////
PerlinTransformShakeAction::PerlinTransformShakeAction()
{
	m_fSpeed = 0.0f;
	m_fMagnitude = 0.0f;
	m_fRandomStart = 0.0f;
}

PerlinTransformShakeAction* PerlinTransformShakeAction::create(f32 duration, f32 fSpeed, f32 fMagnitude)
{
	PerlinTransformShakeAction*ret = new (std::nothrow) PerlinTransformShakeAction();

	if (ret)
	{
		if (ret->initWithDuration(duration, fSpeed, fMagnitude))
		{
			ret->autorelease();
		}
		else
		{
			delete ret;
			ret = nullptr;
		}
	}

	return ret;
}

bool PerlinTransformShakeAction::initWithDuration(f32 duration, f32 fSpeed, f32 fMagnitude)
{
	bool ret = false;

	if (ActionInterval::initWithDuration(duration))
	{
		m_fSpeed = fSpeed;
		m_fMagnitude = fMagnitude;
		m_fRandomStart = cocos2d::random(-1000.0f, 1000.0f);
		ret = true;
	}

	return ret;
}

void PerlinTransformShakeAction::update(f32 fPercent)
{
	if (_target == nullptr)
		return;

	f32 fDamper = 1.0f - clampf(2.0f * fPercent - 1.0f, 0.0f, 1.0f);

	f32 fAlphaX = m_fRandomStart + m_fSpeed * fPercent;
	f32 fAlphaY = (m_fRandomStart + 1000.0f) + m_fSpeed * fPercent;

	// noise1 output range: -0.5 ~ 0.5
	f32 x = noise1(fAlphaX) * 2.0f;    // mapping -1.0 ~ 1.0
	f32 y = noise1(fAlphaY) * 2.0f;

	x *= (m_fMagnitude * fDamper);
	y *= (m_fMagnitude * fDamper);

	Mat4 mat;
	mat.m[12] = x;
	mat.m[13] = y;
	mat.m[14] = 0.0f;
	mat.m[15] = 1.0f;

	_target->setAdditionalTransform(&mat);
}

void PerlinTransformShakeAction::stop()
{
	if (_target)
		_target->setAdditionalTransform(nullptr);
	ActionInterval::stop();
}