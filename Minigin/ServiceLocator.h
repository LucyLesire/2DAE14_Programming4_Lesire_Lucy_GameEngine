#pragma once
#include <map>
#include <mutex>
#include <queue>
//#include <SDL_mixer.h>
#include <vector>
#include <memory>
#include <iostream>
#include "SDL_mixer.h"

using namespace std::literals::chrono_literals;


namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const unsigned short& id, const float& volume) = 0;
	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		void Play(const unsigned short& id, const float& volume) override
		{
			//auto sound = Mix_LoadWAV(pClips[id].c_str());
			m_pActiveClips.push(std::make_pair(volume,pClips[id]));

			m_ConditionVar.notify_all();
		}


		SDLSoundSystem(const std::map<unsigned short, std::string>& clips)
			:m_Thread(&SDLSoundSystem::PlaySound, this)
		{
			pClips = clips;
			//Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

		/*	if (SDL_Init(SDL_INIT_AUDIO) == -1) {
				printf("SDL_Init: %s\n", SDL_GetError());
				exit(1);
			}*/
			// open 44.1KHz, signed 16bit, system byte order,
			//      stereo audio, using 1024 byte chunks
			if (Mix_OpenAudio(44100, AUDIO_S32SYS, 2, 4096) == -1) {
				printf("Mix_OpenAudio: %s\n", Mix_GetError());
				exit(2);
			}
		}

		~SDLSoundSystem() override
		{
			Mix_CloseAudio();
			m_Cleanup = true;
			m_Thread.join();
		}

		void PlaySound()
		{
			std::unique_lock<std::mutex> lk(m_ConditionMutex);

			while(!m_Cleanup)
			{
				m_ConditionVar.wait(lk);
				auto sound = Mix_LoadWAV(m_pActiveClips.front().second.c_str());
				if (!sound)
					return;

				sound->volume = static_cast<Uint8>(m_pActiveClips.front().first * 100);
				Mix_PlayChannel(-1, sound, 0);
				m_pActiveClips.pop();
				std::this_thread::sleep_for(0.1s);
			}
		}

	private:
		std::map<unsigned short, std::string> pClips{};

		std::queue<std::pair<float, std::string>> m_pActiveClips{};
		std::mutex m_ConditionMutex{};
		std::condition_variable m_ConditionVar{};

		std::thread m_Thread;

		bool m_Cleanup{};
	};

	class NullSoundSystem final : public SoundSystem
	{
		void Play(const unsigned short&, const float&) override
		{

		}
	};

	class ServiceLocator final
	{
	private:
		static SoundSystem* m_ss_Instance;
		static NullSoundSystem m_ss_DefaultInstance;

	public:
		static SoundSystem& GetSoundSystem() { return *m_ss_Instance; }
		static void RegisterSoundSystem(SoundSystem* ss)
		{
			m_ss_Instance = ss == nullptr ? &m_ss_DefaultInstance : ss;
		}
	};
}


