﻿#include "pch.h"
#include "framework.h"

#include "AudioMgr.h"

#include "AudioOpenAL.h"
#include "AudioSDL.h"

#include <iostream>

namespace Backend {
	namespace Audio {
		/* *************************************************************************************************
			GET / RESET SINGLETON INSTANCE OF AudioMgr
		************************************************************************************************* */
		AudioMgr* AudioMgr::instance = nullptr;

		AudioMgr* AudioMgr::getInstance() {
			if (instance == nullptr) {
				instance = new AudioSDL();
			}

			return instance;
		}

		void AudioMgr::resetInstance() {
			if (instance != nullptr) {
				delete instance;
				instance = nullptr;
			}
		}

		/* *************************************************************************************************
			CONSTRUCTOR
		************************************************************************************************* */
		AudioMgr::AudioMgr() {
			int sampling_rate_max = 0;
			for (const auto& [key, val] : SAMPLING_RATES) {
				if (val.first > sampling_rate_max) { sampling_rate_max = val.first; }
			}

			audioInfo.channels_max = SOUND_7_1;
			audioInfo.sampling_rate_max = SOUND_96000;
			audioInfo.channels = SOUND_STEREO;
			audioInfo.sampling_rate = SOUND_44100;
		}

		/* *************************************************************************************************
			SETTERS FOR BASIC AUDIO BACKEND
		************************************************************************************************* */
		void AudioMgr::SetSamplingRate(audio_settings& _audio_settings) {
			InitAudioBackend(_audio_settings, true);
		}

		/* *************************************************************************************************
			SETTERS FOR INFORMATION USED DURING EMULATION -> AUDIO THREAD AND CALLBACK
		************************************************************************************************* */
		void AudioMgr::SetVolume(const float& _volume, const float& _lfe) {
			audioInfo.master_volume.store(_volume);
			audioInfo.lfe.store(_lfe);
			audioInfo.settings_changed.store(true);
		}

		void AudioMgr::SetReverb(const float& _delay, const float& _decay) {
			audioInfo.decay.store(_decay);
			audioInfo.delay.store(_delay);
			audioInfo.settings_changed.store(true);
		}

		void AudioMgr::SetAudioChannels(const bool& _high, const bool& _low) {
			audioInfo.high_frequency.store(_high);
			audioInfo.low_frequency.store(_low);
			audioInfo.settings_changed.store(true);
		}
	}
}