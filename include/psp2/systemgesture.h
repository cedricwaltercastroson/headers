/**
 * \usergroup{SceSystemGesture}
 * \usage{psp2/systemgesture.h,SceSystemGesture_stub}
 */

#ifndef _PSP2_SYSTEMGESTURE_H_
#define _PSP2_SYSTEMGESTURE_H_

#include <psp2/types.h>
#include <psp2/touch.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Error number definition
 */

#define SCE_SYSTEM_GESTURE_ERROR_INVALID_ARGUMENT      ((int)0x80890001)
#define SCE_SYSTEM_GESTURE_ERROR_NOT_SUPPORTED_GESTURE ((int)0x80890002)
#define SCE_SYSTEM_GESTURE_ERROR_NOT_INITIALIZED       ((int)0x80890003)
#define SCE_SYSTEM_GESTURE_ERROR_INDEX_OUT_OF_ARRAY    ((int)0x80890004)
#define SCE_SYSTEM_GESTURE_ERROR_EVENT_DATA_NOT_FOUND  ((int)0x80890005)

/*
 * Constants definition
 */

typedef enum SceSystemGestureTouchState {
	SCE_SYSTEM_GESTURE_TOUCH_STATE_INACTIVE     = 0x00000000,
	SCE_SYSTEM_GESTURE_TOUCH_STATE_BEGIN        = 0x00000001,
	SCE_SYSTEM_GESTURE_TOUCH_STATE_ACTIVE       = 0x00000002,
	SCE_SYSTEM_GESTURE_TOUCH_STATE_END          = 0x00000003,
	SCE_SYSTEM_GESTURE_TOUCH_STATE_CANCELLED    = 0x00000004
} SceSystemGestureTouchState;

typedef enum SceSystemGestureType {
	SCE_SYSTEM_GESTURE_TYPE_TAP             = 0x00000001,
	SCE_SYSTEM_GESTURE_TYPE_DRAG            = 0x00000002,
	SCE_SYSTEM_GESTURE_TYPE_TAP_AND_HOLD    = 0x00000004,
	SCE_SYSTEM_GESTURE_TYPE_PINCH_OUT_IN    = 0x00000008,
	SCE_SYSTEM_GESTURE_TYPE_ROTATION        = 0x00000010
} SceSystemGestureType;

/*
 * Structure definition
 */

#pragma pack(push,8)

typedef struct SceSystemGestureVector2 {
	SceInt16 x;
	SceInt16 y;
} SceSystemGestureVector2;

typedef struct SceSystemGestureRectangle {
	SceInt16 x;
	SceInt16 y;
	SceInt16 width;
	SceInt16 height;
} SceSystemGestureRectangle;

typedef struct SceSystemGesturePrimitiveTouchEvent {
	SceSystemGestureTouchState eventState;
	SceUInt16 primitiveID;
	SceSystemGestureVector2 pressedPosition;
	SceInt16 pressedForce;
	SceSystemGestureVector2 currentPosition;
	SceInt16 currentForce;
	SceSystemGestureVector2 deltaVector;
	SceInt16 deltaForce;
	SceUInt64 deltaTime;
	SceUInt64 elapsedTime;
	SceUInt8 reserved[56];
} SceSystemGesturePrimitiveTouchEvent;

typedef struct SceSystemGesturePrimitiveTouchRecognizerParameter {
	SceUInt8 reserved[64];
} SceSystemGesturePrimitiveTouchRecognizerParameter;

typedef struct SceSystemGestureTouchRecognizer {
	SceUInt64 reserved[307];
} SceSystemGestureTouchRecognizer;

typedef struct SceSystemGestureTouchRecognizerInformation {
	SceSystemGestureType gestureType;
	SceUInt32 touchPanelPortID;
	SceSystemGestureRectangle rectangle;
	SceUInt64 updatedTime;
	SceUInt8 reserved[256];
} SceSystemGestureTouchRecognizerInformation;

typedef struct SceSystemGestureTapRecognizerParameter {
	SceUInt8 maxTapCount;
	SceUInt8 reserved[63];
} SceSystemGestureTapRecognizerParameter;

typedef struct SceSystemGestureDragRecognizerParameter {
	SceUInt8 reserved[64];
} SceSystemGestureDragRecognizerParameter;

typedef struct SceSystemGestureTapAndHoldRecognizerParameter {
	SceUInt64 timeToInvokeEvent;
	SceUInt8 reserved[56];
} SceSystemGestureTapAndHoldRecognizerParameter;

typedef struct SceSystemGesturePinchOutInRecognizerParameter {
	SceUInt8 reserved[64];
} SceSystemGesturePinchOutInRecognizerParameter;

typedef struct SceSystemGestureRotationRecognizerParameter {
	SceUInt8 reserved[64];
} SceSystemGestureRotationRecognizerParameter;

typedef union SceSystemGestureTouchRecognizerParameter {
	SceUInt8 parameterBuf[64];
	SceSystemGestureTapRecognizerParameter tap;
	SceSystemGestureDragRecognizerParameter drag;
	SceSystemGestureTapAndHoldRecognizerParameter tapAndHold;
	SceSystemGesturePinchOutInRecognizerParameter pinchOutIn;
	SceSystemGestureRotationRecognizerParameter rotation;
} SceSystemGestureTouchRecognizerParameter;

typedef struct SceSystemGestureTapEventProperty {
	SceUInt16 primitiveID;
	SceSystemGestureVector2 position;
	SceUInt8 tappedCount;
	SceUInt8 reserved[57];
} SceSystemGestureTapEventProperty;

typedef struct SceSystemGestureDragEventProperty {
	SceUInt16 primitiveID;
	SceSystemGestureVector2 deltaVector;
	SceSystemGestureVector2 currentPosition;
	SceSystemGestureVector2 pressedPosition;
	SceUInt8 reserved[50];
} SceSystemGestureDragEventProperty;

typedef struct SceSystemGestureTapAndHoldEventProperty {
	SceUInt16 primitiveID;
	SceSystemGestureVector2 pressedPosition;
	SceUInt8 reserved[58];
} SceSystemGestureTapAndHoldEventProperty;

typedef struct SceSystemGesturePinchOutInEventProperty {
	float scale;
	struct {
		SceUInt16 primitiveID;
		SceSystemGestureVector2 currentPosition;
		SceSystemGestureVector2 deltaVector;
		SceSystemGestureVector2 pairedPosition;
	} primitive[2];
	SceUInt8 reserved[32];
} SceSystemGesturePinchOutInEventProperty;

typedef struct SceSystemGestureRotationEventProperty {
	float angle;
	struct {
		SceUInt16 primitiveID;
		SceSystemGestureVector2 currentPosition;
		SceSystemGestureVector2 deltaVector;
		SceSystemGestureVector2 pairedPosition;
	} primitive[2];
	SceUInt8 reserved[32];
} SceSystemGestureRotationEventProperty;

typedef struct SceSystemGestureTouchEvent {
	SceUInt32 eventID;
	SceSystemGestureTouchState eventState;
	SceSystemGestureType gestureType;
	SceUInt8 padding[4];
	SceUInt64 updatedTime;
	union {
		SceUInt8 propertyBuf[64];
		SceSystemGestureTapEventProperty tap;
		SceSystemGestureDragEventProperty drag;
		SceSystemGestureTapAndHoldEventProperty tapAndHold;
		SceSystemGesturePinchOutInEventProperty pinchOutIn;
		SceSystemGestureRotationEventProperty rotation;
	} property;
	SceUInt8 reserved[56];
} SceSystemGestureTouchEvent;

#pragma pack(pop)

/*
 * Function definition
 */

int sceSystemGestureInitializePrimitiveTouchRecognizer(SceSystemGesturePrimitiveTouchRecognizerParameter* parameter);

int sceSystemGestureFinalizePrimitiveTouchRecognizer(void);

int sceSystemGestureResetPrimitiveTouchRecognizer(void);

int sceSystemGestureUpdatePrimitiveTouchRecognizer(const SceTouchData* pFrontData, const SceTouchData* pBackData);

int sceSystemGestureGetPrimitiveTouchEvents(
	SceSystemGesturePrimitiveTouchEvent* primitiveEventBuffer,
	const SceUInt32 capacityOfBuffer,
	SceUInt32* numberOfEvent);

int sceSystemGestureGetPrimitiveTouchEventsCount(void);

int sceSystemGestureGetPrimitiveTouchEventByIndex(
	const SceUInt32 index,
	SceSystemGesturePrimitiveTouchEvent* primitiveTouchEvent);

int sceSystemGestureGetPrimitiveTouchEventByPrimitiveID(
	const SceUInt16 primitiveID,
	SceSystemGesturePrimitiveTouchEvent* primitiveTouchEvent);

int sceSystemGestureCreateTouchRecognizer(
	SceSystemGestureTouchRecognizer* touchRecognizer,
	const SceSystemGestureType gestureType,
	const SceUInt8 touchPanelPortID,
	const SceSystemGestureRectangle* rectangle,
	const SceSystemGestureTouchRecognizerParameter* touchRecognizerParameter);

int sceSystemGestureGetTouchRecognizerInformation(
	const SceSystemGestureTouchRecognizer* touchRecognizer,
	SceSystemGestureTouchRecognizerInformation* information);

int sceSystemGestureResetTouchRecognizer(SceSystemGestureTouchRecognizer* touchRecognizer);

int sceSystemGestureUpdateTouchRecognizer(SceSystemGestureTouchRecognizer* touchRecognizer);

int sceSystemGestureUpdateTouchRecognizerRectangle(
	SceSystemGestureTouchRecognizer* touchRecognizer,
	const SceSystemGestureRectangle* rectangle);

int sceSystemGestureGetTouchEvents(
	const SceSystemGestureTouchRecognizer* touchRecognizer,
	SceSystemGestureTouchEvent* eventBuffer,
	const SceUInt32 capacityOfBuffer,
	SceUInt32* numberOfEvent);

int sceSystemGestureGetTouchEventsCount(const SceSystemGestureTouchRecognizer* touchRecognizer);

int sceSystemGestureGetTouchEventByIndex(
	const SceSystemGestureTouchRecognizer* touchRecognizer,
	const SceUInt32 index,
	SceSystemGestureTouchEvent* touchEvent);

int sceSystemGestureGetTouchEventByEventID(
	const SceSystemGestureTouchRecognizer* touchRecognizer,
	const SceUInt32 eventID,
	SceSystemGestureTouchEvent* touchEvent);

#ifdef __cplusplus
}
#endif

#endif /* _PSP2_SYSTEMGESTURE_H_ */
