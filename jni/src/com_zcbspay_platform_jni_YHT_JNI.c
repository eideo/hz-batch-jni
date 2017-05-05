/*
 * com_zcbspay_platform_jni_YHT_JNI.c
 *
 *  Created on: 2017年5月1日
 *      Author: guojia
 */
#include "com_zcbspay_platform_jni_YHT_JNI.h"
#include <string.h>
#include <unistd.h>

void setYHTConnTOAddr( char *pszIPAddr, char *pszPort, char *pszPrepUsePath);
int sendYHTBWFile( char *pszIPAddr, char *pszPort, char *szSndFName);
int recvYHTBWFile( char *pszIPAddr, char *pszPort, char *szSndFName, int iTimeOut, char *szRcvedFName);
char *strupr(char *str)
{
   char *ptr = str;

   while (*ptr != '\0') {
       if (islower(*ptr)) 
            *ptr = toupper(*ptr);
       ptr++;
   }

   return str;
}
/*
 * Class:     com_zcbspay_platform_jni_YHT_JNI
 * Method:    sendYHTBWFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_zcbspay_platform_jni_YHT_1JNI_sendYHTBWFile
  (JNIEnv *env, jobject obj, jstring ip, jstring port, jstring sndFName,jstring prepUsePath)
{
	char *pszIPAddr = (*env)->GetStringUTFChars(env, ip, 0);
	char *pszPort = (*env)->GetStringUTFChars(env, port, 0);
	char *szSndFName = (*env)->GetStringUTFChars(env, sndFName, 0);
	char *pszPrepUsePath = (*env)->GetStringUTFChars(env, prepUsePath, 0);
	setYHTConnTOAddr(pszIPAddr,pszPort,pszPrepUsePath);
	return (jint)sendYHTBWFile(NULL,NULL,szSndFName);
}


/*
 * Class:     com_zcbspay_platform_jni_YHT_JNI
 * Method:    recvYHTBWFile
 * Signature: (Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;)I
 */
JNIEXPORT jstring JNICALL Java_com_zcbspay_platform_jni_YHT_1JNI_recvYHTBWFile
  (JNIEnv *env, jobject obj, jstring ip, jstring port, jstring sndFName,jstring prepUsePath)
{
	char rcvfile[82];
	char *pszIPAddr = (*env)->GetStringUTFChars(env, ip, 0);
	char *pszPort = (*env)->GetStringUTFChars(env, port, 0);
	char *szSndFName = (*env)->GetStringUTFChars(env, sndFName, 0);
	//char *szRcvedFName = (*env)->GetStringUTFChars(env, rcvedFName, 0);
	char *pszPrepUsePath = (*env)->GetStringUTFChars(env, prepUsePath, 0);
	setYHTConnTOAddr(pszIPAddr,pszPort,pszPrepUsePath);
	int i = recvYHTBWFile(NULL,NULL,szSndFName,30,rcvfile);
	if(i==-1){
		return (*env)->NewStringUTF(env, strupr("-1"));
	}else if(i==-2){
		return (*env)->NewStringUTF(env, strupr("-2"));
	}
	else if(i==-3){
		return (*env)->NewStringUTF(env, strupr("-3"));
	}
	return (*env)->NewStringUTF(env, strupr(rcvfile));
}

