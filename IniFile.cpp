#include <string.h>
#include <stdlib.h>
#include "IniFile.h"

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
//Implementation of CKeyWordItem
CKeyWordItem::CKeyWordItem()
{
	kwWord = NULL;
	kwComment = NULL;
	kwValue = NULL;
	kwBlank = 0;
	kwNextNode = NULL;
	kwType = 0;
}

CKeyWordItem::CKeyWordItem(char *key, char *val, int bcount)
{
	int l = strlen(key);
	kwWord = new char[l+1];
	if ( kwWord!=NULL ) strncpy(kwWord, key, l+1);

	l = strlen(val);
	kwValue = new char[l+1];
	if ( kwValue!=NULL ) strncpy(kwValue, val, l+1);

	kwComment = NULL;
	kwBlank = bcount;
	kwNextNode = NULL;
	kwType = 1;
}

CKeyWordItem::CKeyWordItem(char *line, int bcount)
{
	int l;
	unsigned char *p0, *p1, *p2, *p;
	p = (unsigned char*)strchr(line, '=');
	p0 = (unsigned char *)line;

	while ( (*p0<33)&&(*p0>0) ) p0 ++;
	if ( (p0[0]=='#')||(p==NULL)||(p==p0) )
	{
		l = strlen(line);
		kwValue = new char[l+1];
		if ( kwValue!=NULL ) strncpy(kwValue, line, l+1);
		kwBlank = bcount;

		kwType = 0;
		kwWord = NULL;
		kwComment = NULL;
		kwNextNode = NULL;
		return;
	}
	p1 = p - 1;
	p2 = p + 1;

	while ( *p1<33 ) p1 --;	
	p1++;
	while ( (*p2<33)&&(*p2>0) ) p2 ++;

	l = p1 - p0;
	kwWord = new char[l+1];
	strncpy(kwWord, (char*)p0, l);
	kwWord[l] = 0;

	l = p2 - p1;
	kwComment = new char [l+1];
	strncpy(kwComment, (char*)p1, l);
	kwComment[l] = 0;

	l = strlen((char*)p2);
	while ( (p2[l]>0)&&(p2[l]<33) ) l--;
	kwValue = new char [l+2];
	strncpy(kwValue, (char*)p2, l+1);
	kwValue[l+1] = 0;

	kwBlank = bcount;
	kwType = 1;
	kwNextNode = NULL;
}

CKeyWordItem::~CKeyWordItem()
{
	if ( kwWord!=NULL ) { delete [] kwWord; kwWord = NULL; }
	if ( kwComment!=NULL ) { delete [] kwComment; kwComment = NULL; }
	if ( kwValue!=NULL ) { delete []kwValue; kwValue = NULL; }
}

void CKeyWordItem::Print(FILE *fp)
{
	int i;
	for (i=0;i<kwBlank;i++) fprintf(fp, "\n");
	if ( kwValue==NULL ) return;

	if ( kwWord==NULL ) fprintf(fp, "%s\n", kwValue);
	else if ( kwComment==NULL ) fprintf(fp, "%s=%s\n", kwWord, kwValue);
	else fprintf(fp, "%s%s%s\n", kwWord, kwComment, kwValue);
}

int CKeyWordItem::GetProperty(char *val, int lSize)
{
	if ( kwValue==NULL )
	{
		strcpy(val, "");
	}
	if ( (int)strlen(kwValue)<lSize )
	{
		strcpy(val, kwValue);
	}
	else
	{
		strncpy(val, kwValue, lSize);
	}
	val[lSize-1] = 0;
	return ( strlen(val) );
}

int CKeyWordItem::SetProperty(char *val)
{
	if ( kwValue!=NULL ) delete [] kwValue;
	if ( (val==NULL)||(val[0]==0) )
	{
		kwValue = NULL;
		return 0;
	}

	int l = strlen(val);
	kwValue = new char [l+1];
	strncpy(kwValue, val, l+1);
	return l;
}

int CKeyWordItem::operator == (char *key)
{
	if ( kwWord==NULL ) return 0;
	return ( !strcasecmp(kwWord, key) );
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
CProperties::CProperties()
{
	m_blankCount = 0;
	szName[0] = 0;
	NextNode = NULL;
	m_KeyWordsHead.next() = NULL;
}

CProperties::CProperties(char *s)
{
	m_blankCount = 0;
	if ( s==NULL ) szName[0] = 0;
	else 
	{
		strncpy(szName, s, 40);
		szName[40] = 0;
	}
	strcpy(nextName, "");
	m_KeyWordsHead.next() = NULL;
	NextNode = NULL;
}

CProperties::~CProperties()
{
	free();
}

void CProperties::free()
{
	CKeyWordItem *pKey;
	pKey = m_KeyWordsHead.next();
	while ( pKey!=NULL )
	{
		m_KeyWordsHead.next() = pKey->next();
		delete pKey;
		pKey = m_KeyWordsHead.next();
	}
}

int CProperties::readline(char *line, int lSize, char *buf, int &i, int bSize)
{
	unsigned char b;
	int bytes;
	while ( i<bSize )
	{
		b = buf[i++];
		if ( b==10 )
		{
			if ( (line_idx>0)&&(line[line_idx-1]==13) ) line_idx--;
			line[line_idx] = 0;
			bytes = line_idx;
			line_idx = 0;
			return bytes;
		}
		else if ( (line_idx<lSize)&&((line_idx>0)||(b>33)) )
		{
			line[line_idx++] = b;
		}
	}
	return -1;
}

int CProperties::operator == ( char * pszName )
{
	return ( !strcasecmp(szName, pszName) );
}

char * CProperties::load( FILE * fp)
{
	int i = 0;
	int sectPos;
	CKeyWordItem *pKey, *pTail;
	if ( fp==NULL ) return NULL;
	line_idx = 0;

	char line[512], buffer[PROFILE_BUFSIZE];
	int bytes, blankCount = 0;
	int iSize = fread(buffer, 1, PROFILE_BUFSIZE, fp);
	pTail = &m_KeyWordsHead;
	while ( iSize>0 )
	{
		sectPos = i;
		bytes = readline(line, 512, buffer, i, iSize);
		if ( bytes<0 )
		{
			if ( feof(fp)||(iSize<PROFILE_BUFSIZE) )
			{
				m_blankCount = blankCount;
				return NULL;
			}
			if ( iSize>sectPos ) fseek(fp, -(iSize-sectPos), SEEK_CUR);
			iSize = fread(buffer, 1, PROFILE_BUFSIZE, fp);
			i = 0;
			continue;
		}
		if ( bytes==0 ) blankCount ++; //mean blank line 
		else if ( (line[0]=='[') )
		{
			m_blankCount = blankCount;
			fseek(fp, -(iSize-i), SEEK_CUR );
			char *p = strchr(line, ']');
			if (p!=NULL ) *p = 0;
			strncpy(nextName, line+1, 30);
			return nextName;
		}
		else
		{
			pKey = new CKeyWordItem(line, blankCount);
			blankCount = 0;
			pTail->next() = pKey;
			pTail = pKey;
		}
	}
	return 0;
}

int CProperties::load( char * fn)
{
	FILE * fp;
	fp = fopen( fn, "rt");
	if ( fp==NULL ) return -1;

	load( fp );

	fclose( fp );
	return 0;
}

int CProperties::store( char * fn)
{
	FILE *fp = fopen(fn, "wt");
	if ( fp==NULL ) return -1;
	store( fp );
	fclose(fp);
	return 0;
}

int CProperties::store( FILE * fp)
{
	CKeyWordItem * pKey;
	pKey = m_KeyWordsHead.next();

	if ((pKey!=NULL)&&(szName[0]!=0)) fprintf(fp, "[%s]\n", szName);

	while ( pKey!=NULL )
	{
		pKey->Print(fp);
		pKey = pKey->next();
	}

	for (int i=0;i<m_blankCount;i++) fprintf(fp, "\n");
	return 0;
}

void CProperties::SetName(int no)
{
	sprintf(szName, "%d", no);
}

int CProperties::GetProperty(char *key, char *val, int lSize, char *dft)
{
	CKeyWordItem *pKey;
	pKey = m_KeyWordsHead.next();
	while ( pKey!=NULL )
	{
		if ( *pKey==key ) return pKey->GetProperty(val, lSize);
		pKey = pKey->next();
	}
	if ( (int)strlen(dft)<lSize )
	{
		strcpy(val, dft);
	}
	else
	{
		strncpy(val, dft, lSize);
	}
	val[lSize-1] = 0;
	return ( strlen(val) );
}

int CProperties::GetProperty(char *key, int lDft)
{
	char def[20], val[20];
	sprintf(def, "%d", lDft);
	GetProperty(key, val, 20, def);

	if ( (val[0]=='"')&&(val[strlen(val)-1]=='"') )
	{
		val[strlen(val)-1] = 0;
		return myatoi( val+1 );
	}
	return myatoi( val );
}

int CProperties::SetProperty(char *key, char *val)
{
	CKeyWordItem *pKey, *pTail;
	pKey = m_KeyWordsHead.next();
	while ( pKey!=NULL )
	{
		if ( *pKey==key ) return pKey->SetProperty(val);
		pKey = pKey->next();
	}
	if ( (val==NULL)||(val[0]==0) ) return 0;

	pKey = new CKeyWordItem(key, val, 0);
	pTail =  &m_KeyWordsHead;
	while ( pTail->next()!=NULL )
	{
		if ( pTail->kwType==1 ) break;
		pTail = pTail->next();
	}
	pKey->next() = pTail->next();
	pTail->next() = pKey;
	return strlen(val);
}

int CProperties::SetProperty(char *key, int val)
{
	char value[20];
	sprintf(value, "%d", val);
	return SetProperty(key, value);
}

int CProperties::FirstKeyName(char *key, char *val)
{
	m_lpEnumKey = m_KeyWordsHead.next();
	return NextKeyName( key, val);
}

int CProperties::NextKeyName(char *key, char *val)
{
	if ( m_lpEnumKey==NULL ) return 0;

	strcpy(key, m_lpEnumKey->kwWord);
	strcpy(val, m_lpEnumKey->kwValue);
	m_lpEnumKey = m_lpEnumKey->next();
	return 1;
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
CProfile::CProfile()
{
	pszFileName[0] = 0;
	m_bModified = -1;
}

CProfile::CProfile(char *fn)
{
	m_bModified = -1;
	if ( fn!=NULL ) load( fn );
}

CProfile::~CProfile()
{
	if ( m_bModified>0 ) store();
	free();
}

void CProfile::free()
{
	CProperties *pSection, *lpCurSect;
	m_PropertiesHead.free();

	pSection = m_PropertiesHead.next();
	while ( pSection!=NULL )
	{
		lpCurSect = pSection->next();
		delete pSection;
		pSection = lpCurSect;
	}
	m_PropertiesHead.next() = NULL;
}

int CProfile::load(char *fn)
{
	FILE *fp;
	CProperties *pSection, *lpCurSect;

	if ( m_bModified>0 ) store();
	free();

	if ( fn==NULL ) return -1;

	strncpy( pszFileName, fn, 128);
	fp = fopen(pszFileName, "rt");

	if ( fp!=NULL )
	{
		char *NextSect = m_PropertiesHead.load( fp );
		lpCurSect = &m_PropertiesHead;
	
		while ( !feof(fp)&&(NextSect!=NULL) )
		{
			pSection = new CProperties(NextSect);
			NextSect = pSection->load( fp );
			lpCurSect->next() = pSection;
			lpCurSect = pSection;
		}
		lpCurSect->next() = NULL;
		fclose(fp);
	}
	m_bModified = 0;
	return 0;
}

int CProfile::store()
{
	FILE *fp;
	if ( pszFileName[0]==0 ) return -1;
	if ( m_bModified==0 ) return 0;

	fp = fopen(pszFileName, "wt");
	if ( fp==NULL ) return -1;

	store( fp );

	fclose( fp );
	return 0;
}

void CProfile::store(FILE *fp)
{
	CProperties *pSection;
	m_PropertiesHead.store(fp);

	pSection = m_PropertiesHead.next();
	while ( pSection!=NULL )
	{
		pSection->store(fp);
		pSection = pSection->next();
	}
	m_bModified = 0;
}

int CProfile::GetProperty(char *s, char *k, int dft)
{
	char val[256], pszdft[256];
	sprintf(pszdft, "%d", dft);
	if ( 0>=GetProperty(s, k, val, 255, pszdft) ) return 0;
	if ( (val[0]=='"')&&(val[strlen(val)-1]=='"') )
	{
		val[strlen(val)-1] = 0;
		return myatoi( val+1 );
	}
	return myatoi(val);
}

int CProfile::GetProperty(char *s, char *k, char *val, int lSize, char *dft)
{
	CProperties *pSect;

	if ( (s==NULL)||(s[0]==0) ) 
	{
		return m_PropertiesHead.GetProperty(k, val, lSize, dft);
	}

	pSect = m_PropertiesHead.next();
	while ( pSect!=NULL )
	{
		if ( *pSect==s ) return pSect->GetProperty(k,val,lSize,dft);
		pSect = pSect->next();
	}

	strncpy(val, dft, lSize);
	val[lSize-1] = 0;
	return ( strlen(val) );
}

int CProfile::SetProperty(char *s, char *k, int val)
{
	char value[256];
	sprintf(value, "%d", val);
	return SetProperty(s, k, value);
}

int CProfile::SetProperty(char *s, char *k, char *val)
{
	CProperties *pSect, *lpCurSect;

	m_bModified = 1;
	if ( (s==NULL)||(s[0]==0) ) 
	{
		return m_PropertiesHead.SetProperty(k, val);
	}

	lpCurSect = &m_PropertiesHead;
	pSect = m_PropertiesHead.next();
	while ( pSect!=NULL )
	{
		lpCurSect = pSect;
		if ( *pSect==s ) return pSect->SetProperty(k, val);
		pSect = pSect->next();
	}

	pSect = new CProperties(s);
	lpCurSect->next() = pSect;
	return pSect->SetProperty(k, val);
}

void CProfile::ReSortSection()
{
	int i = 0;
	m_bModified = 1;
	CProperties *lpCurSect = m_PropertiesHead.next();
	while ( lpCurSect!=NULL )
	{
		lpCurSect->SetName( i );
		lpCurSect = lpCurSect->next();
	}
}

void CProfile::RemoveSection(char *s)
{
	CProperties *pSect, *lpCurSect;

	if ( s==NULL ) return;
	m_bModified = 1;

	lpCurSect = &m_PropertiesHead;
	pSect = lpCurSect->next();
	while ( pSect!=NULL )
	{
		if ( *pSect==s )
		{
			lpCurSect->next() = pSect->next();
			delete pSect;
		}
		else
		{
			lpCurSect = pSect;
		}
		pSect = lpCurSect->next();
	}
}

char * CProfile::FirstSectionName()
{
	m_lpEnumSect = m_PropertiesHead.next();
	return NextSectionName();
}

char * CProfile::NextSectionName()
{
	if ( m_lpEnumSect==NULL ) return NULL;
	char *p = m_lpEnumSect->szName;
	m_lpEnumSect = m_lpEnumSect->next();
	return p;
}

int CProfile::FirstKeyName(char *s, char *key, char *val)
{
	if ( s==NULL ) return m_PropertiesHead.FirstKeyName(key, val);

	m_lpCurSect = m_PropertiesHead.next();
	while ( m_lpCurSect!=NULL )
	{
		if ( *m_lpCurSect==s ) return m_lpCurSect->FirstKeyName( key, val);
		m_lpCurSect = m_lpCurSect->next();
	}
	return 0;
}

int CProfile::NextKeyName(char *s, char *key, char *val)
{
	if ( (m_lpCurSect!=NULL)&&(*m_lpCurSect==s) )
	{
		return m_lpCurSect->NextKeyName( key, val);
	}
	return 0;
}


int	myatoi(char *val)
{
	int ret;
	if ( (val[0]=='0')&&(strlen(val)>=3) )
	{
		ret = 0;
		if ( (val[1]=='x')||(val[1]=='X') )
		{
			for ( unsigned long i=2;i<strlen(val);i++)
			{
				int j = getHexValue( val[i] );
				if ( j<0 ) break;
				ret = (ret<<4) + j;
			}
			return ret;
		}
	}
	return atoi(val);
}

int getHexValue(char ch)
{
	if ( (ch>='0')&&(ch<='9') ) return (ch-'0');
	if ( (ch>='A')&&(ch<='F') ) return (ch-'A'+10);
	if ( (ch>='a')&&(ch<='f') ) return (ch-'a'+10);
	return -1;
}


/* 
 * $Log: properties.cpp,v $
 * Revision 1.1.1.1  2006/08/23 10:48:29  fish
 * no message
 *
 * Revision 1.1.1.1  2003/12/08 02:53:12  administrator
 * no message
 *
 * Revision 1.1  2001/05/20 20:25:25  cvsroot
 * *** empty log message ***
 *
 * Revision 1.8  2001/05/17 16:51:32  cvsroot
 * *** empty log message ***
 *
 * Revision 1.7  2001/03/01 00:05:33  cvsroot
 * Fix bug in properties, where can result in loop when load file
 *
 * Revision 1.6  2001/01/23 21:51:40  cvsroot
 * add Log in CVS
 *
*/
