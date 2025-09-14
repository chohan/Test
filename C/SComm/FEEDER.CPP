#include "dartdbms.h"

/*STANDARD DBF FILE HEADER(PART 1)*/
typedef struct
	{char   filetype;
	 char   lastchange[3];
	 long   numrecs;
	 unsigned firstbyte;
	 unsigned reclength;
	 char   fill[20];
	}DBF_HEAD;
extern	 DBF_HEAD dbf_head;

/*STANDARD DBF FILE HEADER(PART 2)*/
typedef struct
	{char name[11];
	 char type;
	 long offset;
	 union
	 { unsigned char_len;
	   struct
	   { char nonchar_len;
	     char numeric_dec;
	   } number_type;
	 } length;
	 char fill2[14];
	}DBF_FIELDS;
extern   DBF_FIELDS dbf_fields[MAXFIELDS];
extern   int        dbf_hand;        		//DBF FILE HANDLE

/*INPUT FIELDS DATA*/
typedef struct
	{ char  szName[11];
	  char	cType;
	  int   nOffset;
	  int   nWidth;
        } INFIELDS;
extern	  INFIELDS infields[MAXFIELDS];    //REQUIRED FIELDS OF INPUT STRING
extern	  int      nInFields;              //NO OF INPUT FIELDS


void prt(char *string)
{
  HDC hDC = GetDC(hWnd);
  TextOut(hDC,10,10,string,lstrlen(string));
  ReleaseDC(hWnd,hDC);
}

BOOL Feeder(char *string)    //PARSE AND FEED STRING TO DBF FILE
{
  char   szDBF[80]="";
  int    newline = 0;
  int    i,j,k;

  //CONSTRUCTING DBF STRING
  szDBF[0] = '\x20';
  if(string[0] == '\n') newline = 1;   //CHECK PRESENCE OF NEW LINE CHARACTER
  k = 1;
  for(i=0; i<nInFields; i++)
  {
    for(j=infields[i].nOffset-1; j<infields[i].nOffset-1+infields[i].nWidth; j++)
    {
      szDBF[k++] = string[j+newline];
    }
//szDBF[k]='\0';
//MessageBox(hWnd,szDBF,"field string",MB_OK);
  }
  szDBF[k] = '\0';


  /*WRITE OUTPUT STRING TO DBF FILE*/
  _llseek(dbf_hand,0L,0);		//MOVE POINTER AT THE START
  _lread(dbf_hand,(char *)&dbf_head,sizeof(dbf_head));
//  _llseek(dbf_hand,0L,2);               //MOVE POINTER AT THE END
  _llseek(dbf_hand,dbf_head.firstbyte+dbf_head.numrecs*dbf_head.reclength,0);
  if(_lwrite(dbf_hand,&szDBF,dbf_head.reclength) != dbf_head.reclength)
  {
    MessageBox(hWnd,"ERROR in module Feeder","Write error",MB_OK);
    return(FALSE);
  }

  /*COUNTNG NO OF RECORDS*/
  ++dbf_head.numrecs;

  /*WIRITE END OF FILE
  char terminator = '\x1A';
  if(_lwrite(dbf_hand,&terminator,1) != 1)
  { MessageBox(hWnd,"Unable to write dbf END OF FILE marker to DBF file","Write error",MB_ICONSTOP | MB_OK);
    _lclose(dbf_hand);
    return;
  }
*/
  /*UPDATING FILE HEADER INFORMATION*/
  _llseek(dbf_hand,0L,0);
  _lwrite(dbf_hand,&dbf_head,sizeof(dbf_head));
  return(TRUE);
}

