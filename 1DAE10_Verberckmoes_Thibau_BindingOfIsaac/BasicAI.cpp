#include "pch.h"
#include "BasicAI.h"
BasicAI::BasicAI(Point2f SpawnPos, Vector2f Velocity, int Health, int maxHealth, int fps, int nrOfFrames) :
	m_CenterPos(SpawnPos),
	m_Velocity(Velocity),
	m_Health(Health),
	m_MaxHealth(maxHealth),
	m_TimePassedForAnimation(0),
	m_FramesPerSec(fps),
	m_NrOfFramesForBody(nrOfFrames),
	m_AnimFrame(0),
	m_UpdatePosition(true)

{
}

BasicAI::~BasicAI()
{
}

void BasicAI::Draw() const
{
	
}

void BasicAI::Update(float elapsedSec, const Point2f& pos)
{
	
}

void BasicAI::CheckIfHit(const Point2f pos, std::vector<Tear*>& activetears,const SoundManager& soundManager)
{
}

Rectf BasicAI::GetHitbox() const
{
	return Rectf();
}

Point2f BasicAI::GetCenterPos() const
{
	return m_CenterPos;
}

void BasicAI::SetLocationOfPlayer(Point2f pos)
{
	m_LocationOfPlayer = pos;
}

int BasicAI::GetHealth() const
{
	return m_Health;
}

void BasicAI::SetUpdatePositionBool(bool move)
{
	m_UpdatePosition = move;
}

Point2f BasicAI::GetLocationOfPlayer() const
{
	return m_LocationOfPlayer;
}

void BasicAI::UpdateHitbox(Rectf hitBox)
{
	m_HitBox = hitBox;
}

void BasicAI::AIHit()
{
	m_Health -= 1;
}

void BasicAI::CalculateDeltaPos(float elapsedSec)
{
	Vector2f NormalizedVector;
	Vector2f PlayerPos;
	Vector2f AIpos;
	Vector2f SumVector;
	Vector2f DeltaVector;

	PlayerPos.x = m_LocationOfPlayer.x;
	PlayerPos.y = m_LocationOfPlayer.y;
	AIpos.x = m_CenterPos.x;
	AIpos.y = m_CenterPos.y;

	SumVector = PlayerPos - AIpos;
	NormalizedVector = SumVector.Normalized();
	
	DeltaPos = (m_Velocity.x * elapsedSec) * NormalizedVector;
//	std::cout << DeltaVector.x << " " << DeltaVector.y<<std::endl;
}





