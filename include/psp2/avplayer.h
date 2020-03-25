/**
 * \usergroup{SceAvPlayer}
 * \usage{psp2/avplayer.h,SceAvPlayer_stub}
 */

#ifndef _AVPLAYER_H_
#define _AVPLAYER_H_

#include <psp2/types.h>

/// The player handle definition.
///
	typedef void* SceAvPlayerHandle;

/// The stream types.
///
	typedef enum SceAvPlayerStreamType {
		SCE_AVPLAYER_VIDEO,			///< The video stream type.
		SCE_AVPLAYER_AUDIO,			///< The audio stream type.
		SCE_AVPLAYER_TIMEDTEXT,		///< The timed text stream type.
		SCE_AVPLAYER_UNKNOWN		///< An unknown stream type.
	} SceAvPlayerStreamType;

/// Contains representations of the player events, warnings and info.
///
	typedef enum SceAvPlayerEvents {
		SCE_AVPLAYER_STATE_STOP				= 0x01,	///< Stop state.
		SCE_AVPLAYER_STATE_READY			= 0x02,	///< Ready state.
		SCE_AVPLAYER_STATE_PLAY				= 0x03,	///< Play state.
		SCE_AVPLAYER_STATE_PAUSE			= 0x04,	///< Pause State.
		SCE_AVPLAYER_STATE_BUFFERING		= 0x05,	///< Buffering state.
		SCE_AVPLAYER_TIMED_TEXT_DELIVERY	= 0x10,	///< Timed text delivery event.
		SCE_AVPLAYER_WARNING_ID				= 0x20,	///< Warning ID returned.
		SCE_AVPLAYER_ENCRYPTION				= 0x30	///< Encryption information returned.
	} SceAvPlayerEvents;

/// Contains all the possible playback speeds.
///

	typedef enum SceAvPlayerTrickSpeeds {
		SCE_AVPLAYER_SPEED_NORMAL		= 100, ///< Normal playback speed.
		SCE_AVPLAYER_SPEED_FF_2X		= 200, ///< 2X fast forward. Because only key/"i" frames are displayed, 2X should only be used when the key frame interval is small.
		SCE_AVPLAYER_SPEED_FF_4X		= 400, ///< 4X fast forward. Because only key/"i" frames are displayed, 4X should only be used when the key frame interval is small.
		SCE_AVPLAYER_SPEED_FF_8X		= 800, ///< 8X fast forward. Above 8X is generally a good user experience.
		SCE_AVPLAYER_SPEED_FF_16X		= 1600, ///< 16X fast forward.
		SCE_AVPLAYER_SPEED_FF_MAX		= 3200, ///< 32X fast forward. Faster is possible. This is only a recommendation.
		SCE_AVPLAYER_SPEED_RW_8X		= -800, ///< 8X rewind. Because only Key/"i" frames are displayed, rewind speeds below 8X are not recommended.
		SCE_AVPLAYER_SPEED_RW_16X		= -1600, ///< 16X rewind.
		SCE_AVPLAYER_SPEED_RW_MAX		= -3200 ///< 32X rewind. Faster is possible. This is only a recommendation.
	} SceAvPlayerTrickSpeeds;

/// Contains AV Player synchronous and asynchronous errors as well as warning codes.
///
	typedef enum SceAvPlayerErrorCodes{
		SCE_AVPLAYER_NO_ERR						= 0x00,			///< No error occurred.
		SCE_AVPLAYER_ERR_INVALID_PARAMS			= 0x806A0001,	///< An error occurred because invalid parameters were passed via the API.
		SCE_AVPLAYER_ERR_OPERATION_FAILED		= 0x806A0002,	///< An error occurred because the desired operation failed.
		SCE_AVPLAYER_ERR_NO_MEMORY				= 0x806A0003,	///< An error occurred because there was not enough memory to continue.
		SCE_AVPLAYER_ERR_NOT_SUPPORTED			= 0x806A0004,	///< An error occurred because the content was unsupported.

		SCE_AVPLAYER_WAR_FILE_NONINTERLEAVED	= 0x806A00A0,	///< Warning: The file is non-interleaved.
		SCE_AVPLAYER_WAR_LOOPING_BACK			= 0x806A00A1,	///< Warning: The file got looped back.
		SCE_AVPLAYER_WAR_JUMP_COMPLETE			= 0x806A00A3,	///< Warning: The jump operation was completed.

		SCE_AVPLAYER_INFO_MARLIN_ENCRY			= 0x806A00B0,	///< Marlin Drm is required for this content.
		SCE_AVPLAYER_INFO_PLAYREADY_ENCRY		= 0x806A00B4,	///< Playready Drm is required for this content.
		SCE_AVPLAYER_INFO_AES_ENCRY				= 0x806A00B5,	///< AES-128 bit encryption is used for this content.
		SCE_AVPLAYER_INFO_OTHER_ENCRY			= 0x806A00BF	///< Other encryptions are used for this content.
	}SceAvPlayerErrorCodes;

/// @brief
/// Represents debug levels. Note that debug information is output to the console as text
/// and that error checking is always available through the return values of all video player library calls.
///
/// @ingroup libsceAvPlayer
	typedef enum SceAvPlayerDebuglevels {
		SCE_AVPLAYER_DBG_NONE,		///< No debug information output to the console.
		SCE_AVPLAYER_DBG_INFO,		///< Stream information output to the console. This is useful for discovering why streams are behaving differently.
		SCE_AVPLAYER_DBG_WARNINGS,	///< Warnings output to the console.
		SCE_AVPLAYER_DBG_ALL		///< All available information output to the console.
	} SceAvPlayerDebuglevels;

/// @brief Contains the details of an audio stream.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerAudio {
		uint16_t	channelCount;		///< The number of audio channels.
		uint8_t		reserved1[2];		///< A reserved value.
		uint32_t	sampleRate;			///< The audio sampling rate in Hz.
		uint32_t	size;				///< The size of the audio payload in bytes.  For calls to sceAvPlayerGetStreamInfo() only, the 'size' member will currently always be zero.
		uint8_t		languageCode[4];	///< The audio language code.
	} SceAvPlayerAudio;

/// @brief Contains the details of a video stream.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerVideo {
		uint32_t	width;				///< The default width of the video.
		uint32_t	height;				///< The default height of the video.
		float		aspectRatio;		///< The default aspect ratio of the video.
		uint8_t		languageCode[4];	///< The video language code.
	} SceAvPlayerVideo;

/// @brief Contains the positioning of some timed text.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerTextPosition{
		uint16_t	top;				///< The top of the rectangle containing the timed text.
		uint16_t	left;				///< The left of the rectangle containing the timed text.
		uint16_t	bottom;				///< The bottom of the rectangle containing the timed text.
		uint16_t	right;				///< The right of the rectangle containing the timed text.

	} SceAvPlayerTextPosition;

/// @brief Contains the details of a timed text stream.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerTimedText {
		uint8_t		languageCode[4];		///< The language code.
		uint16_t	textSize;				///< The size of the timed text.
		uint16_t	fontSize;				///< The size of the timed text font.
		SceAvPlayerTextPosition position;	///< The position of the timed text.
	} SceAvPlayerTimedText;					///< The stream details.

/// @brief
/// Contains the details (either audio, video or timed text) of a stream.
///
/// @ingroup libsceAvPlayer
	typedef union SceAvPlayerStreamDetails {
		uint8_t				reserved[16];	///< An array of reserved bytes.
		SceAvPlayerAudio	audio;			///< Audio details.
		SceAvPlayerVideo	video;			///< Video details.
		SceAvPlayerTimedText subs;			///< Timed text details.
	} SceAvPlayerStreamDetails;

/// @brief
/// Contains information about a stream.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerStreamInfo {
		uint32_t		type;				///< The stream type.
		uint8_t			reserved[4];		///< A reserved value.
		SceAvPlayerStreamDetails details;	///< The details of the stream, which depend upon whether it is an audio or a video stream.
		uint64_t		duration;			///< The length of the stream in ms.
		uint64_t		startTime;			///< The start time of the stream in ms.
	} SceAvPlayerStreamInfo;

/// @brief
/// Contains frame information.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerFrameInfo {
		uint8_t*	pData;					///< A pointer to the payload data for the frame.
		uint8_t		reserved[4];			///< A reserved value.
		uint64_t	timeStamp;				///< The timestamp in ms.
		SceAvPlayerStreamDetails details;	///< The frame details.
	} SceAvPlayerFrameInfo;

/// @brief
/// A memory allocation function pointer.
///
/// @param argP				[O] Optional supplied pointer.
/// @param argAlignment		[I] The alignment of the memory to allocate.
/// @param argSize			[I] The size of the memory to allocate.
///
/// @retval
/// != NULL				The address of the memory allocated.
/// @retval
/// NULL				The operation failed.
///
/// @ingroup libsceAvPlayer
	typedef void* (*SceAvPlayerAllocate)(void* argP, uint32_t argAlignment, uint32_t argSize);

/// @brief
/// A memory deallocator function pointer.
///
/// @param argP				[O] Optional supplied pointer.
/// @param argMemory		[I] A pointer to the memory to deallocate.
///
/// @ingroup libsceAvPlayer
	typedef void (*SceAvPlayerDeallocate)(void* argP, void* argMemory);

/// @brief
/// A graphics memory allocation and mapping function pointer.
///
/// @param argP				[O] Optional supplied pointer.
/// @param argAlignment		[I] The alignment of the memory to allocate.
/// @param argSize			[I] The size of the memory to allocate.
///
/// @retval
/// != NULL				The address of the memory allocated.
/// @retval
/// NULL				The operation failed.
///
/// @ingroup libsceAvPlayer
	typedef void* (*SceAvPlayerAllocateTexture)(void* argP, uint32_t argAlignment, uint32_t argSize);

/// @brief
/// A graphics memory deallocation and unmapping function pointer.
///
/// @param		argP			[O] Optional supplied pointer.
/// @param		argMemory		[I] A pointer to the memory to deallocate and unmap.
///
/// @ingroup libsceAvPlayer
	typedef void (*SceAvPlayerDeallocateTexture)(void* argP, void* argMemory);

/// @brief
/// Contains the memory allocator function pointers for the <c>libsceAvPlayer</c> API.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerMemAllocator {
		void* objectPointer; ///< Optional pointer to a calling object. This pointer is returned with all of the below callback calls as <c>argP</c>. This helps with C++ integration.
		SceAvPlayerAllocate allocate; ///< The replacement general memory allocator.
		SceAvPlayerDeallocate deallocate; ///< The replacement general memory deallocator.
		SceAvPlayerAllocateTexture allocateTexture; ///< The replacement graphics memory allocator and map.
		SceAvPlayerDeallocateTexture deallocateTexture; ///<The replacement graphics memory deallocator and unmap.
	} SceAvPlayerMemAllocator;

/// @brief
/// A file open function pointer.
///
/// @param argP				[O] Optional supplied pointer.
/// @param argFilename		[I] The name of the file to open.
///
/// @retval
/// >=0						The operation was successful.
/// @retval
/// <0						The operation failed.
///
/// @ingroup libsceAvPlayer
	typedef int (*SceAvPlayerOpenFile)(void* argP, const char* argFilename);

/// @brief
/// A file close function pointer.
///
/// @param argP				[O] Optional supplied pointer.
///
/// @retval
/// >=0						The operation was successful.
/// @retval
/// <0						The operation failed.
///
/// @ingroup libsceAvPlayer
	typedef int (*SceAvPlayerCloseFile)(void* argP);

/// @brief
/// A file read with offset function pointer.
///
/// @param argP				[O] Optional supplied pointer.
/// @param argBuffer		[I/O] The target read buffer.
/// @param argPosition		[I] The offset position in the file.
/// @param argLength		[I] The length of the read.
///
/// @retval
/// >=0						The operation was successful (the number of bytes read).
/// @retval
/// <0						The operation failed.
///
/// @ingroup libsceAvPlayer
	typedef int (*SceAvPlayerReadOffsetFile)(void* argP, uint8_t* argBuffer, uint64_t argPosition, uint32_t argLength);

/// @brief
/// A file size retrieval function pointer.
///
/// @param argP				[O] Optional supplied pointer.
///
/// @retval
/// >0						The size of the file.
/// @retval
/// =0						The operation failed.
///
/// @ingroup libsceAvPlayer
	typedef uint64_t (*SceAvPlayerSizeFile)(void* argP);

/// @brief
/// Contains the file access function pointers for the <c>libsceAvPlayer</c> API.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerFileReplacement {
		void* objectPointer; ///< Optional pointer to a calling object. This pointer is returned with all of the below callback calls as <c>argP</c>. This helps with C++ integration.
		SceAvPlayerOpenFile open; ///< The replacement file open function.
		SceAvPlayerCloseFile close; ///< The replacement file close function.
		SceAvPlayerReadOffsetFile readOffset; ///< The replacement file read with offset function.
		SceAvPlayerSizeFile size; ///< The replacement file size retrieval function.
	} SceAvPlayerFileReplacement;

/// @brief
/// An event callback function pointer.
///
/// @param p				[O] Optional supplied pointer.
/// @param argEventId		[I] An event ID from #SceAvPlayerEvents.
/// @param argSourceId		[I] The source ID.
/// @param argEventData		[I] A reserved pointer to event data.
///
/// @ingroup libsceAvPlayer
	typedef void (*SceAvPlayerEventCallback)(void* p, int32_t argEventId, int32_t argSourceId, void* argEventData);

/// @brief
/// Contains the event callback function pointer for the <c>libsceAvPlayer</c> API.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerEventReplacement {
		void* objectPointer; ///< Optional pointer to a calling object. This pointer is returned with <c><i>eventCallback</i></c> calls as <c>p</c>. This helps with C++ integration.
		SceAvPlayerEventCallback eventCallback; ///< The event callback.
	} SceAvPlayerEventReplacement;

/// @brief
/// The initialization parameters. Note that additional parameters may be added in future releases of this library.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerInitData {
		SceAvPlayerMemAllocator		memoryReplacement; ///< The allocator instance for general allocations and, if they are not provided, backup for video and codec allocators.
		SceAvPlayerFileReplacement	fileReplacement; ///< The replacement file access calls. These are useful if your file is packed or encrypted and you want to handle the file IO yourself.
		SceAvPlayerEventReplacement		eventReplacement; ///< The event callback for state changes, warnings and errors.
		SceAvPlayerDebuglevels		debugLevel; ///< The debug level.
		uint32_t	basePriority;  ///< The base priority of the video player. Adjust this if the video player thread conflicts with a game thread. A default value of 160 is used if 0 is supplied.
		int32_t		numOutputVideoFrameBuffers; ///< Enables AV sync latency to be fine tuned to match complicated display lists. Values from 2 to 6 are valid; values outside of this range default to 2.
		SceBool        autoStart; ///< A flag that specifies whether to rely on the callback to start playback or not.
		uint8_t     reserved[3]; ///< A reserved value.
		const char* defaultLanguage; ///< The default language. If a default language is supplied, this will start automatically when <c><i>autostart</i></c> is set to true.
	} SceAvPlayerInitData;

/// @brief
/// Initializes the <c>libsceAvPlayer</c> API and supplies it with initialization parameters.
///
/// @param[in]	pInit	A pointer to the initialization structure, which contains the function pointers required by the library.
///
/// @retval
/// SceAvPlayerHandle	The player handle. If the operation failed, a value of <c>NULL</c> is returned.
///
/// @ingroup libsceAvPlayer
	SceAvPlayerHandle sceAvPlayerInit(SceAvPlayerInitData* pInit);

/// @brief
/// The advanced initialization parameters. Note that additional parameters may be added in future releases of this library.
///
/// @ingroup libsceAvPlayer
	typedef struct SceAvPlayerPostInitData {
		uint32_t	demuxVideoBufferSize; ///< The size of the demux video buffer in bytes. This defaults to 512*1024. If audio/video playback is jittery, the size of the buffer should be increased beyond the default.
		uint8_t		reserved[128]; ///< A reserved value. Ensure this is filled with 0 to avoid conflict with future parameters.
	} SceAvPlayerPostInitData;

/// @brief
/// Allows advanced initialization of the <c>libsceAvPlayer</c> API. Use of this function is optional, and it should be used with caution.
///
/// @param[in]	h			The video player handle.
/// @param[in]	pPostInit	A pointer to the advanced initialization structure, which contains the size of the demux video buffer.
///
/// @retval
/// 0				The operation was successful.
/// @retval
/// <0				The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerPostInit(SceAvPlayerHandle h, SceAvPlayerPostInitData* pPostInit);

/// @brief
/// Closes the <c>libsceAvPlayer</c> API and frees any outstanding memory allocations.
///
/// @param[in]	h	The video player handle.
///
/// @retval
/// 0				The operation was successful.
/// @retval
/// <0				The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerClose(SceAvPlayerHandle h);

/// @brief
/// Adds a source file to the end of the video player playback queue.
///
/// @param[in]	h				The video player handle.
/// @param[in]	argFilename		A pointer to the source video filename, which should include the full path.
///
/// @retval
/// 0				The operation was successful.
/// @retval
/// <0				The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerAddSource(SceAvPlayerHandle h, const char* argFilename);

/// @brief
/// Retrieves how many valid streams are available.
///
/// @param[in]		h				The video player handle.
///
/// @retval
/// >=0				The number of streams available in the video at the top of the queue.
/// @retval
/// <0				The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerStreamCount(SceAvPlayerHandle h);

/// @brief
/// Retrieves detailed information on each stream.
///
/// @param[in]		h				The video player handle.
/// @param[in]		argStreamID		The stream ID.
/// @param[in,out]	argInfo			Receives information about the stream.
///
/// @retval
/// 0					The operation was successful.
/// @retval
/// <0					The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerGetStreamInfo(SceAvPlayerHandle h, uint32_t argStreamID, SceAvPlayerStreamInfo* argInfo);

/// @brief
/// Enables a stream.
///
/// @param[in]	h				The video player handle.
/// @param[in]	argStreamID		The stream ID.
///
/// @retval
/// 0					The operation was successful.
/// @retval
/// <0					The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerEnableStream(SceAvPlayerHandle h, uint32_t argStreamID);

/// @brief
/// Disables a stream.
///
/// @param[in]	h				The video player handle.
/// @param[in]	argStreamID		The stream ID.
///
/// @retval
/// 0					The operation was successful.
/// @retval
/// <0					The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerDisableStream(SceAvPlayerHandle h, uint32_t argStreamID);

/// @brief
///
/// Starts playback.
///
/// @param[in]	h		The video player handle.
///
/// @retval
/// 0					The operation was successful.
/// @retval
/// <0					The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerStart(SceAvPlayerHandle h);

/// @brief
/// Stops playback.
///
/// @param[in]	h	The video player handle.
///
/// @retval
/// 0				The operation was successful.
/// @retval
/// <0				The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerStop(SceAvPlayerHandle h);

/// @brief
/// Pauses playback.
///
/// @param[in]	h	The video player handle.
///
/// @retval
/// 0				The operation was successful.
/// @retval
/// <0				The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerPause(SceAvPlayerHandle h);

/// @brief
/// Resumes from pause.
///
/// @param[in]	h	The video player handle.
///
/// @retval
/// 0				The operation was successful.
/// @retval
/// <0				The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerResume(SceAvPlayerHandle h);

/// @brief
/// Turns seamless looping of a single file on or off. Looping is off by default.
///
/// @param[in]	h			The video player handle.
/// @param[in]	loopFlag	A flag that indicates whether the video player should loop the video.
///
/// @retval
/// 0					The operation was successful.
/// @retval
/// <0					The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerSetLooping(SceAvPlayerHandle h, SceBool loopFlag);

/// @brief
/// Checks the status of the video player.
///
/// @param[in]		h	The video player handle.
///
/// @retval
/// true				The operation was successful.
/// @retval
/// false				The operation failed.
///
/// @ingroup libsceAvPlayer
	SceBool sceAvPlayerIsActive(SceAvPlayerHandle h);

/// @brief
/// Retrieves the relevant audio frame.
///
/// @param[in]		h			The video player handle.
/// @param[in,out]	audioInfo	Receives information about the frame.
///
/// @retval
/// true				Valid data was delivered.
/// @retval
/// false				There was no data available.
///
/// @ingroup libsceAvPlayer
	SceBool sceAvPlayerGetAudioData(SceAvPlayerHandle h, SceAvPlayerFrameInfo* audioInfo);

/// @brief
/// Retrieves the relevant video frame.
///
/// @param[in]		h			The video player handle.
/// @param[in,out]	videoInfo	Receives information about the frame.
///
/// @retval
/// true				Valid data was delivered.
/// @retval
/// false				There was no data available.
///
/// @ingroup libsceAvPlayer
	SceBool sceAvPlayerGetVideoData(SceAvPlayerHandle h, SceAvPlayerFrameInfo* videoInfo);

/// @brief
/// Retrieves the current playback time. This value reflects the base clock time and not
/// just the previous audio or video frame timestamp. As a result it is very accurate. A/V sync uses this
/// same base clock.
///
/// @param[in]	h		The video player handle.
///
/// @retval
/// >0					The current 64-bit uint playback time in milliseconds.
/// @retval
/// =0					No current playback time is available.
///
/// @ingroup libsceAvPlayer
	uint64_t sceAvPlayerCurrentTime(SceAvPlayerHandle h);

/// @brief
/// Jumps to a time offset in ms.
///
/// @param[in]	h					The video player handle.
/// @param[in]	argJumpTimeMsec		The requested time offset.
///
/// @retval
/// 0						The operation was successful.
/// @retval
/// <0						The operation failed.
/// @note
/// This function actually jumps to the nearest random access point before or after the specified offset. This is an IDR picture in the case
///	of an AVC video, and in the case of an audio-only source, it will usually be the start of any audio frame. The accuracy of the jump depends
///	on the number of random access points in the media file, which is determined by the encoder settings.
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerJumpToTime(SceAvPlayerHandle h, uint64_t argJumpTimeMsec);

/// @brief
/// Sets the trickmode speed (see SceAvPlayerTrickSpeeds enumeration for valid values).
///
/// @note	Setting the trick speed back to SCE_AVPLAYER_SPEED_NORMAL is required to resume playback with audio. All other
///			speed variations will output without audio.
///
/// @param[in]	h				The video player handle.
/// @param[in]	argTrickSpeed	The requested trickmode speed.
///
/// @retval
/// 0						The operation was successful.
/// @retval
/// <0						The operation failed.
///
/// @ingroup libsceAvPlayer
	int32_t sceAvPlayerSetTrickSpeed(SceAvPlayerHandle h, int32_t argTrickSpeed);


#endif	/* _SCE_AVPLAYER_SCEAVPLAYER_H */

