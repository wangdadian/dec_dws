#ifndef GLOBAL_HEADER_PROPERTIES_INCLUDED
#define GLOBAL_HEADER_PROPERTIES_INCLUDED

#define     PROFILE_BUFSIZE         10240
#define		COMMENT_CHAR		'#'

#include <stdio.h>
#include <string.h>

extern	int	myatoi(char *val);
extern	int	getHexValue(char ch);

class CKeyWordItem
{
protected:
	CKeyWordItem();
	CKeyWordItem * & next() { return kwNextNode; }

public:
	CKeyWordItem(char *key, char *val, int bcount=0);
	CKeyWordItem(char *line, int bcount);
	virtual ~CKeyWordItem();

	int	kwType;
	void	Print(FILE *fp);
	int	GetProperty(char *val, int lSize);
	int	SetProperty(char *val);
	int	operator == (char *key);
private:
	char    *kwWord, *kwComment;
	char	*kwValue;
	int	kwBlank;
	CKeyWordItem * kwNextNode;

	friend class CProperties;
};

class CProperties
{
protected:
	CProperties * & next() { return NextNode; }
	CProperties(char *s);

	char	*load( FILE * fp );
	int	store( FILE *fp );
	void	free();
	void	SetName(int no);
	int	blank() { return m_blankCount; }

public:
	int	FirstKeyName(char *key, char *val);
	int	NextKeyName(char *key, char *val);
	int	load( char * fn );
	int	store( char * fn );

	int	GetProperty( char * key, char *val, int lSize, char *dft);
	int	GetProperty( char * key, int lDft);

	int	SetProperty( char * key, char *val);
	int	SetProperty( char * key, int val);
	int	IsEmpty() { return ( m_KeyWordsHead.next()==NULL); }

	int operator == ( char * pszName );
public:
	CProperties();
	virtual ~CProperties();

private:
	CProperties	*NextNode;
	CKeyWordItem	m_KeyWordsHead, *m_lpEnumKey;

	int	readline(char *line, int lSize, char*buf, int &i, int bSize);

	char	szName[41];
	char	nextName[41];
	int	keyCount, line_idx;
	int	m_blankCount;

	friend  class CProfile;
	
};

class CProfile
{
protected:

public:
	CProfile();
	CProfile(char *fn);
	virtual ~CProfile();

public:
	int	GetProperty(char *s, char *k, int dft);
	int	GetProperty(char *s, char *k, char *val, int lSize, char *dft);

	int	SetProperty(char *s, char *k, int val);
	int	SetProperty(char *s, char *k, char* val);

	int	load( char *fn );
	void	store( FILE *fp );

	char	*FirstSectionName();
	char	*NextSectionName();

	int	FirstKeyName(char *s, char *key, char *val);
	int	NextKeyName(char *s, char *key, char *val);

	void	RemoveSection(char *s);
	void	ReSortSection();
private:
	void	free();
	int	store( );
	CProperties	m_PropertiesHead, *m_lpEnumSect, *m_lpCurSect;
	char		pszFileName[129];

	int	m_bModified;
};

#endif

/*
 * $Log: properties.h,v $
 * Revision 1.1.1.1  2006/08/23 10:48:29  fish
 * no message
 *
 * Revision 1.1.1.1  2003/12/08 02:53:10  administrator
 * no message
 *
 * Revision 1.2  2003/11/26 02:33:28  administrator
 * backup 2003-11-26
 * In this version:
 * 1) NETAT200 Driver was modified by Fish, But It's Wrong!
 * 2) Philips Driver added!
 * 3) panasonis sx560 untested!
 *
 * Revision 1.3  2001/05/17 16:51:32  cvsroot
 * *** empty log message ***
 *
 * Revision 1.2  2001/01/23 22:00:46  cvsroot
 * Add Log Message in CVS
 *
 *
*/


