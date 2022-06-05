#include "MiniginPCH.h"
#include "ServiceLocator.h"


dae::NullSoundSystem dae::ServiceLocator::m_ss_DefaultInstance = dae::NullSoundSystem();
dae::SoundSystem* dae::ServiceLocator::m_ss_Instance = &m_ss_DefaultInstance;