/*
 * NativeContoller.cpp
 *
 *  Created on: 2014/08/29
 *      Author: takyafumin
 */

#include <string>
#include "cocos2d.h"
#include "NativeContoller.h"
#include "platform/android/jni/JniHelper.h"

#define CLASS_NAME "org/cocos2dx/cpp/util/MessageUtils"

USING_NS_CC;


const char* NativeContoller::getMessage()
{
	std::string str;

	// JNI 呼出し
	JniMethodInfo methodInfo;
	if (!JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getMessage", "()Ljava/lang/String;"))
	{
		return nullptr;
	}

	// 戻り値取得
	jstring jstr = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

	const char* message = methodInfo.env->GetStringUTFChars(jstr, nullptr);


	// 後処理
	methodInfo.env->ReleaseStringUTFChars(jstr, message);
	methodInfo.env->DeleteLocalRef(jstr);

	CCLog("NativeController::getMessage, %s", message);

	return message;
}
