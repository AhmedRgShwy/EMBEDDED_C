/*
 * FunctionsTools.h
 *
 * Created: 11/16/2016 3:00:55 AM
 *  Author: AhmedShaarawy
 */ 


#ifndef FUNCTIONSTOOLS_H_
#define FUNCTIONSTOOLS_H_



typedef unsigned char STDreturn;
#define STD_R				unsigned char
#define StrartVerify()		unsigned char check=0x00
#define ReturnVerify()		return check
#define FalseVerify()		check=0x00
#define TrueVerify()		check=0x01
#define DoVerify			check
#define IsVerifyTrue		check==1
#define IsVerifyFalse		check==0


#define LOOP		while(1)



typedef struct
{
	unsigned char value;
	unsigned char key:1;
}sSyncU8;

typedef struct
{
	unsigned long value;
	unsigned char key:1;
}sSyncU32;

typedef struct
{
	unsigned short value;
	unsigned char key:1;
}sSyncU16;

#define HoldSource(src)			src.key=1
#define ReleaseSource(src)		src.key=0
#define AssignSource(src,val)	if(src.key==0)\
								src.value=val\
								else FalseVerify()

#endif /* FUNCTIONSTOOLS_H_ */