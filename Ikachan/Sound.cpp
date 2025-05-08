#include "Sound.h"
#include "System.h"
//#include <dsound.h>
#include <stdio.h>

//DirectSound objects
// LPDIRECTSOUND       lpDS;
// LPDIRECTSOUNDBUFFER lpPRIMARYBUFFER;

//DirectSound buffers
#define SE_MAX 512
// LPDIRECTSOUNDBUFFER lpSECONDARYBUFFER[SE_MAX];

//DirectSound interface
#if 0
bool InitDirectSound(HWND hwnd)
{
	//Create DirectSound object
	if (DirectSoundCreate(NULL, &lpDS, NULL) != DS_OK)
		return false;
	lpDS->SetCooperativeLevel(hwnd, DSSCL_EXCLUSIVE);

	//Create primary sound buffer
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(dsbd));
	dsbd.dwSize = sizeof(dsbd);
	dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
	lpDS->CreateSoundBuffer(&dsbd, &lpPRIMARYBUFFER, NULL);

	//Clear secondary sound buffers
	for (int i = 0; i < SE_MAX; i++)
		lpSECONDARYBUFFER[i] = NULL;
	return true;
}
#endif

void EndDirectSound()
{
#if 0
	//Release secondary sound buffers
	for (int i = 0; i < 8; i++) //Should be SE_MAX
	{
		if (lpSECONDARYBUFFER[i] != NULL)
		{
			lpSECONDARYBUFFER[i]->Release();
			lpSECONDARYBUFFER[i] = NULL;
		}
	}

	//Release primary sound buffer
	if (lpPRIMARYBUFFER != NULL)
	{
		lpPRIMARYBUFFER->Release();
		lpPRIMARYBUFFER = NULL;
	}

	//Release DirectSound object
	if (lpDS != NULL)
	{
		lpDS->Release();
		lpDS = NULL;
	}
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

//Sound object creation and release
void ReleaseSoundObject(int no)
{
#if 0
	if (lpSECONDARYBUFFER[no] != NULL)
	{
		lpSECONDARYBUFFER[no]->Release();
		lpSECONDARYBUFFER[no] = NULL;
	}
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

bool InitSoundObject(const char* resname, int no)
{
#if 0
	//Find and lock resource
	HRSRC hrscr;
	if ((hrscr = FindResource(NULL, resname, "WAVE")) == NULL)
		return false;
	unsigned long *lpunsigned long = (unsigned long*)LockResource(LoadResource(NULL, hrscr));

	//Create sound buffer
	DSBUFFERDESC dsbd;
	memset(&dsbd, 0, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	dsbd.dwBufferBytes = *(unsigned long*)((BYTE*)lpunsigned long + 0x36);
	dsbd.lpwfxFormat = (LPWAVEFORMATEX)(lpunsigned long + 5);
	if (lpDS->CreateSoundBuffer(&dsbd, &lpSECONDARYBUFFER[no], NULL) != DS_OK)
		return false;

	//Lock sound buffer
	LPVOID lpbuf1, lpbuf2;
	unsigned long dwbuf1, dwbuf2;
	lpSECONDARYBUFFER[no]->Lock(0, *(unsigned long*)((BYTE*)lpunsigned long + 0x36),
		&lpbuf1, &dwbuf1, &lpbuf2, &dwbuf2, 0);

	//Copy data
	memcpy(lpbuf1, (BYTE*)lpunsigned long + 0x3A, dwbuf1);
	if (dwbuf2 != 0)
		memcpy(lpbuf2, (BYTE*)lpunsigned long + 0x3A + dwbuf1, dwbuf2);
	
	//Unlock sound buffer
	lpSECONDARYBUFFER[no]->Unlock(lpbuf1, dwbuf1, lpbuf2, dwbuf2);
	return true;
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
	return false;
#endif
}

void PlaySoundObject(int no, int mode)
{
#if 0
	if (lpSECONDARYBUFFER[no] != NULL)
	{
		switch (mode)
		{
			case SOUND_MODE_STOP: //Stop
				lpSECONDARYBUFFER[no]->Stop();
				break;

			case SOUND_MODE_PLAY: //Play
				lpSECONDARYBUFFER[no]->Stop();
				lpSECONDARYBUFFER[no]->SetCurrentPosition(0);
				lpSECONDARYBUFFER[no]->Play(0, 0, 0);
				break;

			case SOUND_MODE_PLAY_LOOP: //Play looped
				lpSECONDARYBUFFER[no]->Play(0, 0, DSBPLAY_LOOPING);
				break;
		}
	}
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

void ChangeSoundFrequency(int no, unsigned long rate) //100 is MIN, 9999 is MAX, and 2195 is normal
{
#if 0
	if (lpSECONDARYBUFFER[no] != NULL)
		lpSECONDARYBUFFER[no]->SetFrequency((rate * 10) + 100);
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

void ChangeSoundVolume(int no, long volume) //300 is MAX and 300 is normal
{
#if 0
	if (lpSECONDARYBUFFER[no] != NULL)
		lpSECONDARYBUFFER[no]->SetVolume((volume - 300) * 8);
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

void ChangeSoundPan(int no, long pan) //512 is MAX and 256 is normal
{
#if 0
	if (lpSECONDARYBUFFER[no] != NULL)
		lpSECONDARYBUFFER[no]->SetPan((pan - 256) * 10);
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
#endif
}

//PiyoPiyo sound
// WAVEFORMATEX format_tbl2 = {WAVE_FORMAT_PCM, 1, 22050, 22050, 1, 8, 0};
int freq_tbl[12] = { 1551, 1652, 1747, 1848, 1955, 2074, 2205, 2324, 2461, 2616, 2770, 2938 };

bool MakePiyoPiyoSoundObject(char *wave, unsigned char *envelope, int octave, int data_size, int no)
{
#if 0
	bool result;
	int i;

	//Construct sound buffers
	DSBUFFERDESC dsbd;
	memset(&dsbd, 0, sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(dsbd);
	dsbd.dwBufferBytes = data_size;
	dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_STICKYFOCUS;
	dsbd.lpwfxFormat = &format_tbl2;
	
	for (i = 0; i < 24; i++)
	{
		if (lpDS->CreateSoundBuffer(&dsbd, &lpSECONDARYBUFFER[no + i], NULL) != DS_OK)
			return false;
	}
	
	//Write sound data
	unsigned char *wp = (BYTE*)malloc(data_size);
	
	for (i = 0; i < 24; i++)
	{
		//Construct waveform
		int wp_sub = 0;
		int envelope_i = 0;
		
		for (int j = 0; j < data_size; j++)
		{
			//Get sample
			int sample = wave[(BYTE)(wp_sub / 256)];
			envelope_i = (j << 6) / data_size;
			sample = sample * envelope[envelope_i] / 128;
			
			//Set sample
			wp[j] = sample + 0x80;
			
			//Increase sub-pos
			int freq;
			if (i < 12)
				freq = octave * freq_tbl[i] / 16;
			else
				freq = octave * freq_tbl[i - 12] / 8;
			wp_sub += freq;
		}
		
		//Lock sound buffer
		LPVOID lpbuf1, lpbuf2;
		unsigned long dwbuf1, dwbuf2 = 0;
		
		HRESULT hr = lpSECONDARYBUFFER[no + i]->Lock(0, data_size, &lpbuf1, &dwbuf1, &lpbuf2, &dwbuf2, 0);
		if (hr != DS_OK)
		{
			result = false;
			break;
		}
		
		//Copy waveform
		memset(lpbuf1, 0, data_size);
		memcpy(lpbuf1, wp, dwbuf1);
		if (dwbuf2 != 0)
			memcpy(lpbuf2, wp + dwbuf1, dwbuf2);
		
		//Unlock sound buffer
		lpSECONDARYBUFFER[no + i]->Unlock(lpbuf1, dwbuf1, lpbuf2, dwbuf2);
	}
	
	//Check if there was an error and free wave buffer
	if (i == 24)
		result = true;
	free(wp);
	return result;
#else
	fprintf(stderr, "stubbed function: %s\n", __PRETTY_FUNCTION__);
	return false;
#endif
}
