/* compile command line(example):

gcc sample_openal.c -osample_openal.exe \
 -lOpenAL32 \
 -I"D:/Program Files (x86)/OpenAL 1.1 SDK/include" \
 -L"D:/Program Files (x86)/OpenAL 1.1 SDK/libs/Win32"

 */

#include <stdio.h>
#include <al.h>
#include <alc.h>

int main()
{
    printf("OpenAL sample program: begin ----\n");

    // OpenAL コンテクストを用意
    ALCdevice *device = alcOpenDevice(NULL);
    if (device) {
        // コンテクストを作成
        ALCcontext *context = alcCreateContext(device, NULL);
        
        // 作成したコンテクストをカレントに設定
        alcMakeContextCurrent(context);
    }
    
    ALenum error;
    
    // buffer を準備
    ALuint buffer;
    // error をクリア
    alGetError();
    alGenBuffers(1, &buffer);
    if ((error = alGetError()) != AL_NO_ERROR) {
        printf("error! generate buffers");
        return 1;
    }
    
    // source を準備
    ALuint source;
    // error をクリア
    alGetError();
    alGenSources(1, &source);
    if ((error = alGetError()) != AL_NO_ERROR) {
        printf("error! generate sources");
        return 1;
    }
    
    // source のプロパティを設定
    alSourcei( source, AL_LOOPING,  AL_TRUE);    // 繰り返し
    alSourcei( source, AL_PITCH,    1.0f);       // ピッチ
    alSourcei( source, AL_GAIN,     0.45f);      // 音量
    alSource3f(source, AL_POSITION, 10, 20, 30); // 音源位置
    
    // source と buffer を接続
    alSourcei(source, AL_BUFFER, buffer);

    // listner の設定
    ALfloat listener_positions[]    = { 0.0, 0.0, 0.0 };
    ALfloat listener_velocities[]   = { 0.0, 0.0, 0.0 };
    ALfloat listener_orientations[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };
    
    alListenerfv(AL_POSITION, listener_positions);
    alListenerfv(AL_VELOCITY, listener_velocities);
    alListenerfv(AL_ORIENTATION, listener_orientations);
    
    // 再生
    alSourcePlay(source);
    
    printf("OpenAL sample program: end ------\n");
    return 0;
}
