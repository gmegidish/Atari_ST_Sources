/************************************************************************/
/*									*/
/* LINK68 preprocessor module.						*/
/*									*/
/*	This module parses the command line and builds the 		*/
/*	tree that the other passes use for overlay and file 		*/
/*	information.							*/
/*									*/
/*	The main module, LINK68.C, does the rest of the initialization.	*/
/*									*/
/*	Error returns are through the errorx function in the main	*/
/*	module.								*/
/*									*/
/************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include "link68.h"

/* token values for scanner/parser */

#define JUNK  	-1			/* any illegal character	*/
#define NOMORE	0			/* end of line or file		*/
#define LPAREN	1			/* '('				*/
#define RPAREN	2			/* ')'				*/
#define LBRACK	3			/* '['				*/
#define RBRACK	4			/* ']'				*/
#define EQSIGN	5			/* '='				*/
#define COMMA 	6			/* ','				*/
#define NAMETK	7			/* file or option name		*/
#define NUMBTK	7			/* number -- hexadecimal	*/
					/* keep same so file names can	*/
					/* start with a digit		*/
#define DOT	9			/* '.', for control files	*/
#define BACKSL	10			/* '\\'				*/

/* token values for option names */

#define	JUNKOP		-1		/* unrecognized name		*/
#define	ABSOLUTE	1		/* rest of option strings same	*/
#define	BSSBASE		2		/* as name			*/
#define	DATABASE	3
#define	INCLUDE		4
#define	COMMAND		5
#define	ALLMODS		6
#define	LOCALS		7
#define	MAP		8
#define	NOLOCALS	9
#define	TEMPFILES	10
#define	TEXTBASE	11
#define SYMBOLS		12
#define IGNORE		13
#define UNDEFINED	14
#define CHAINED		15
#define DUMPSYMS	16

#define	TOKLEN	FNAMELEN		/* max len. file or option name */
#define	LINELEN	132			/* maximum length of input line */

#define MFLTYPE	".PRG"			/* default root filetype	*/
#define OFLTYPE	".O68"			/* default overlay filetype	*/

/* option string values -- change here for foreign language		*/

#define ABSSTR	"ABSOLUTE"
#define ALLSTR	"ALLMODS"
#define BSSSTR	"BSSBASE"
#define CHNSTR	"CHAINED"
#define COMSTR	"COMMAND"
#define DATSTR	"DATABASE"
#define IGNSTR	"IGNORE"
#define INCSTR	"INCLUDE"
#define LOCSTR	"LOCALS"
#define MAPSTR	"MAP"
#define NOLSTR	"NOLOCALS"
#define SYMSTR	"SYMBOLS"
#define TEMSTR	"TEMPFILES"
#define TEXSTR	"TEXTBASE"
#define UDFSTR	"UNDEFINED"
#define DMPSTR	"XXZZY"

/* syntax error submessages -- change for foreign language */

#define BRKNAM		"'[' <NAME>"
#define BRKNUM		"'[' <HEX NUMBER>"
#define COMORBRK	"',' OR ']'"
#define COMORPAR	"',' OR ')'"
#define NAMESTR 	"<NAME>"
#define NMORBRK 	"<NAME> OR '['"


/************************************************************************/
/*			GLOBAL DATA					*/
/************************************************************************/


int	numovls = 0;			/* number of overlays		*/
int	scanpos = 0;			/* read position for scanner	*/
int	lastpos = 0;			/* beginning of current token	*/
int	ovdepth = 0;			/* counts ovl nesting depth	*/
int	lastscan= NOMORE;		/* last token type scanned	*/
int	curovnum = ROOT;		/* current free overlay node	*/
char	tokenval[TOKLEN] = "";		/* last name/number scanned	*/
BOOLEAN cfileflg = FALSE;		/* set if commands from file	*/
BOOLEAN locsflg  = FALSE;		/* set if locals -> sym. table	*/
FILE	*cmdfpt = NULL;			/* command file			*/

long	scannum();			/* convert hex-ascii to long	*/
BOOLEAN match();			/* compares option names	*/
extern long malloc();
extern char *strcat();
struct ovtrnode *newovnod();
struct filenode *newflnod();
extern char rootfile[FNAMELEN];
extern char ovlyfile[FNAMELEN];

/************************************************************************/
/*									*/
/* 	preproc() -- main function in this module			*/
/*									*/
/*		1)  Initialize local stuff				*/
/*		2)  Parse command line/file				*/
/*									*/
/*	Main module must assemble console command line in the global	*/
/*	variable cmdline.  This module does not know about the argv/	*/
/*	argc variables.							*/
/*									*/
/************************************************************************/


VOID preproc ()

{
	register int onum;

	ovtree[ROOT] = newovnod();		/* init. overlay tree	*/

	parsecmd();				/* parse command line	*/

	numovls = curovnum;
	ovflag = (numovls > 0);
	if (ovflag && (Dflag || Bflag))
		errorx(DISCONTIG);
}




/************************************************************************/
/*									*/
/* parsecmd() -- driver for command line parser.			*/
/*									*/
/*	Controls the two main phases of the parse:			*/
/*									*/
/*		1) global options					*/
/*		2) input files / overlay specifications			*/
/*									*/
/************************************************************************/


VOID parsecmd()

{
	register int toknum;

	toknum = scan();			/* get first cmd. token	*/

	if (toknum == LBRACK)			/* options specified?	*/
	{
		globops();			/* process global opts	*/
		toknum = scan();		/*  next after ']'	*/
	}

	if (toknum == NAMETK || toknum == BACKSL) /* looks o.k.?	*/
	{
    		strcpy(rootfile, tokenval);
    		addfltyp(rootfile, MFLTYPE, 0);
    		strcpy(ovlyfile, tokenval);
    		addfltyp(ovlyfile, OFLTYPE, 1);
		inparse(curovnum,NOPARENT);		/* parse inp. file list */
	}
	else					/* something wrong	*/
	{
		if (toknum == NOMORE)		/* early eof?		*/
			errorx(CMDTRUNC, "");	/*   yes, good bye	*/
		if (toknum == JUNK)		/* what kind of error	*/
			errorx(BADCHAR, tokenval);  /* illegal character*/
		else
			errorx(BADSYNT, NMORBRK);/* unexpected token	*/
	}

	if (cfileflg)				/* command file open?	*/
		fclose(cmdfpt);			/* close it		*/

	if (lastscan != NOMORE)			/* better be at end	*/
		errorx(MORECMD, tokenval);	/* could be bad parse	*/
}

/************************************************************************/
/*									*/
/* scan() -- scan for next command token.				*/
/*									*/
/*	Get the next token from the current command line.  Return 	*/
/*	the token number and put the string in the global variable	*/
/*	tokenval.  Lowercase is converted to uppercase.			*/
/*									*/
/*	If the commands are in a file, this function reads a new	*/
/*	line from the file when it needs to, and only returns the	*/
/*	value NOMORE when it is at the end of the file.			*/
/*									*/
/*	File-based command lines are printed on the standard output	*/
/*	device.								*/
/*									*/
/************************************************************************/

int
scan()


{
	register char c;
	register int  i, j;	
	register int toktype;

	tokenval[0] = EOS;			/* zero it out		*/

	c = cmdline[i = scanpos];
	while (isspace(c))			/* skip white space	*/
		c = cmdline[++i];
	scanpos = i;				/* update scan position */
	lastpos = i;				/* beginning of token	*/

	toktype = lookahd();			/* get token number	*/
	lastscan = toktype;			/* might need it later	*/

	if (toktype == NOMORE)			/* eol or eof		*/
	{
		if (cfileflg)			/* reading from file?	*/
		{
			if (fgets(cmdline, LINELEN, cmdfpt) == NULL)
				return(NOMORE);
			else			/* got another line	*/
			{
				println(cmdline);
				scanpos = 0;	/* ready for new line	*/
				return(scan());	/* scan new line	*/
			}
		}
		else
			return(NOMORE);		/* end of console line	*/
	}

	else if ((toktype == NAMETK) || (toktype == NUMBTK)||(toktype==DOT)
    		 || (toktype == BACKSL))
	{
		j = 0;

		do				/* put name in tokenval	*/
		{
			if (j < TOKLEN -1)	/* don't overflow string,  */
			{			/* save room for null	*/
				tokenval[j++] = toupper(c);
			}
			c = cmdline[++i]; 
		}
		while (isalnum(c) || (c == ':') || (c == '.') || (c == '\\'));

					/* parser validifies number	*/
		tokenval[j] = EOS;		/* mark end of string	*/
		scanpos = i;			/* save scan position	*/
		return(toktype);
	}
	
	else					/* single character	*/
	{
		scanpos += 1;			/* next char in stream	*/
		tokenval[0] = c;		/* keep old character	*/
		tokenval[1] = EOS;		/* mark string end	*/
		return(toktype);		/* good or bad token	*/
	}
}

/************************************************************************/
/*									*/
/* lookahd() -- simple lookahead scan					*/
/*									*/
/*	Returns the token number for the next command token.  Does not	*/
/*	set any global values or read/write anything.  If the current	*/
/*	scan position is at the end of the line, this function does	*/
/*	does not read in a new command line.				*/
/*									*/
/*	The token number is only based on the next non-blank character	*/
/*	in the current command line.					*/
/*									*/
/************************************************************************/


int
lookahd()

{
	register char c;
	register int  i;

	i = scanpos;
	c = cmdline[i];

	while (isspace(c) && (c != EOS))	/* skip over white space */
		c = cmdline[++i];

	switch (c)				/* see if simple character */
	{
		case '='  : return(EQSIGN);
		case EOS : return(NOMORE);
		case '\#' : return(NOMORE);	/* comment delimiter	*/
		case '('  : return(LPAREN);
		case ')'  : return(RPAREN);
		case '['  : return(LBRACK);
		case ']'  : return(RBRACK);
		case ','  : return(COMMA);
		case '.'  : return(DOT);	/* nameless file	*/
    		case '\\' : return(BACKSL);
	}

	/* only get here if not a single-character token (or junk)	*/

	if (isalpha(c))				/* file or option name? */
		return(NAMETK);
	else if (isdigit(c))			/* number?		*/
		return(NUMBTK);
	else					/* who knows?		*/
		return(JUNK);
} 


/************************************************************************/
/*									*/
/* globops() -- process global options from command line/file		*/
/*									*/
/*	On entry to this function, the current token is a '['.		*/
/*	On normal exit, current token is a ']'.			 	*/
/*									*/
/*	Error exit taken through error function in main module.		*/
/*									*/
/************************************************************************/

VOID
globops()

{
	register int tokenum;			/* token number		*/
	register int opnum;			/* option number	*/

	tokenum = scan();			/* skip to next token	*/

	while ((tokenum != RBRACK) && (tokenum != NOMORE))
	{
		if (tokenum != NAMETK)		/* better be a name	*/
		{
			if (tokenum == JUNK)
				errorx(BADCHAR, tokenval);
			else		
				errorx(BADSYNT, NAMESTR);
		}
		/* only get here if it's a name				*/

		opnum = readop(tokenval);	/* which one is it?	*/
		
		if (opnum == ABSOLUTE)
			absflg = TRUE;		/* absolute load	*/
		else if (opnum == BSSBASE)
		{
			Bflag++;
			bssstart = scannum();
		}
		else if (opnum == DATABASE)
		{
			Dflag++;
			datastart = scannum();
		}
		else if (opnum == DUMPSYMS)
			dmpflg = TRUE;
		else if (opnum == COMMAND)
		{
			cmdfile();		/* set up command file	*/
			if (lookahd() == LBRACK) /* opt's in file?	*/
			{
				scan();		/* grab '['		*/
				globops();	/* process new options	*/
			}
			break;			/* leave loop -- return	*/
		}
		else if (opnum == CHAINED)
			chnflg = TRUE;
		else if (opnum == IGNORE)
			ignflg = TRUE;
		else if (opnum == LOCALS)
			locsflg = TRUE;
		else if (opnum == MAP)
			mapflg = TRUE;
		else if (opnum == NOLOCALS)
			locsflg = FALSE;
		else if (opnum == SYMBOLS)
			symflg = TRUE;
		else if (opnum == TEMPFILES)
			tdrvscan();		/* drive for temp files	*/ 
		else if (opnum == TEXTBASE)
		{
			Zflag++;
			textstart = scannum();
		}
		else if (opnum == UNDEFINED)
			udfflg = TRUE;		/* allow undefineds	*/
		else
			errorx(BADOPT, tokenval);	/* goodbye	*/

		if ((tokenum = scan()) == COMMA)
			tokenum = scan();	/* skip over comma	*/
		else if (tokenum != RBRACK)	/* better be a ']'	*/
			errorx(BADSYNT, COMORBRK);/* quit		*/

	}
}

/************************************************************************/
/*									*/
/* inparse(ovnum) -- parses the input specs for an overlay		*/
/*									*/
/*	On entry to this function, the current token is a name.  On	*/
/*	normal exit, the current token is a delimiter.			*/
/*									*/
/*	The function fills in the overlay node and builds the file	*/
/*	list for the specified point in the overlay tree.  If part 	*/
/*	of the specification is a sub-overlay, the function calls	*/
/*	itself recursively.						*/
/*									*/
/*	Error exits are through the error processor.			*/
/*									*/
/************************************************************************/

VOID
inparse (ovnum,parent)

register int ovnum, parent;

{
	register int tknum;			/* token class number	*/
	int lastsib;				/* use for sib. lists	*/
	struct filenode *curfile;		/* use for file list	*/
	struct filenode **tfpt;			/* pointer to fnode ptr	*/

/*	strcpy(ovtree[ovnum]->ovfname, tokenval); */ /* get name	*/
	ovtree[ovnum]->ovparent = parent;	/* set parent link	*/

	if (lookahd() == EQSIGN)		/* out file?		*/
	{
		scan();				/* skip '='		*/
		tknum = scan();			/* should be inp. file	*/
		if (tknum != NAMETK && tknum != BACKSL)
			errorx(BADSYNT, NAMESTR);		/* quit	*/
	}
	else				/* insert default filetype	*/
	{
/*		addfltyp(ovtree[ovnum]->ovfname,
			  ovnum == ROOT ? MFLTYPE : OFLTYPE); 		*/
		tknum = NAMETK;		/* know it's a name		*/
	}

	while ((tknum == NAMETK) || (tknum == DOT) || (tknum == BACKSL))	
	{				/* process list of file names	*/
		if (tknum == DOT)	/* skip names starting with '.'	*/
		{
			tknum = scan();	/* discard dummy name		*/
			goto isdot;	/* don't allocate filenode	*/
		}
		curfile = newflnod();		/* get a new file node	*/
		strcpy(curfile->fnfname, tokenval);	/* file name	*/
						/* get the next token,	*/
		if ((tknum = scan()) == LBRACK)	/* local options?	*/
		{
			locops(curfile);	/* process options	*/
			tknum = scan();		/* discard ']'		*/
		}

		if (locsflg)			/* include locals?	*/
			curfile->fnflags |= FNLOCS;	/* set flag	*/

		tfpt = &(ovtree[ovnum]->ovflist);	/* insert filenode */
		while (*tfpt != NULL)			/* find end	*/
			tfpt = &((*tfpt)->fnnext);
		*tfpt = curfile;			/* update link	*/

isdot:		if (tknum == COMMA)
			tknum = scan();			/* skip ','	*/
		else if ((tknum != RPAREN) && (tknum != NOMORE))
			errorx(BADSYNT, COMORPAR);	/* quit		*/ 
	}

	lastsib = NULL;				/* mark for first use	*/

	while (tknum == LPAREN)			/* process overlay specs */
	{
		if ((tknum = scan()) != NAMETK && tknum != BACKSL)/* skip '('*/
			errorx(BADSYNT, NAMESTR);	/* quit		*/

		if (curovnum == MAXOVLS)		/* too many?	*/
			errorx(XESSOVLS, "");		/* quit		*/
		
		ovtree[++curovnum] = newovnod();	/* new overlay node */

		if (lastsib == NULL)		/* is this first child?	*/
			ovtree[ovnum]->ovfstkid = curovnum;
		else					/* no, it's a sib */
			ovtree[lastsib]->ovnxtsib = curovnum;

		lastsib = curovnum;			/* save index	*/

		if (((ovdepth += 1) > MAXOVDEP) ||
		    (chnflg && (ovdepth >1)))	 
			errorx(OVTODEEP, "");	/* overlays too deep	*/

		inparse(curovnum,ovnum);		/* parse ov spec*/

		ovdepth -= 1;			/* bump depth cntr. down */

		if ((tknum = scan()) == COMMA)		/* skip ')'	*/
			tknum = scan();			/* skip ',' too	*/
					/* end, better be ')' or nothing */
		else if ((tknum != RPAREN) && (tknum != NOMORE))
			errorx(BADSYNT, COMORPAR);	/* quit		*/
	}
}



/************************************************************************/
/*									*/
/* newovnod() -- allocate and initialize a new overlay tree node	*/
/*									*/
/*	Gets a new record from the heap and zeroes out the fields.	*/
/*	Returns a pointer to the new record.				*/
/*	Takes error exit through main module only if no room in heap.	*/
/*									*/
/************************************************************************/


struct ovtrnode *
newovnod()

{
	register struct ovtrnode *newnode;	/* temporary pointer	*/

	if ((newnode = malloc(sizeof(*newnode))) == NULL)  /* any space? */
		errorx(NOROOM, "");		/* heap full		*/
	newnode->ovoffset = 0;		/* zero all the fields	*/
	newnode->ovtxbase = 0;	
	newnode->ovdtbase = 0;
	newnode->ovbsbase = 0;
	newnode->ovcap    = 0;
	newnode->ovfsym   = NULL;
	newnode->ovnxtsib = NULL;
	newnode->ovfstkid = NULL;
	newnode->ovparent = NOPARENT;
	newnode->ovflist  = NULL;
	newnode->ovjblck  = NULL;
	
	return(newnode);			/* normal return	*/
}


/************************************************************************/
/*									*/
/* long scannum() -- convert hex to long value				*/
/*									*/
/*	Converts a null-terminated string to a long integer.  All 	*/
/*	letter digits must be uppercase.  Any spurious characters	*/
/*	result in an error exit through the main error function.	*/
/*									*/
/*	Entry token is a name, normal exit token is ']'			*/
/*									*/
/************************************************************************/

long
scannum ()

{
	register char *st;			/* working string	*/
	register char c;			/* current charater	*/
	register long val;			/* cumulative value	*/

	if ((scan() != LBRACK) || (scan() != NUMBTK)) /* get number	*/
		errorx(BADSYNT, BRKNUM);
 	
  
	st = tokenval;				/* get ptr. to string	*/
	val = 0;

	while ((c = *st++) != EOS)
	{
		if (isdigit(c))
			c -= '0';		/* ascii to int		*/
		else if ((c >= 'A') && (c <= 'F'))
			c = (c - 'A') + 10;	/* ascii to int		*/
		else				/* bad character	*/
			errorx(BADNUM, tokenval);/* so long for now...	*/ 
	
		val = (val << 4) + c;		/* val * 16 + c		*/
	}

	if (scan() != RBRACK)
		errorx(BADSYNT, "']'"); 

	return(val);				/* normal return	*/
}

/************************************************************************/
/*									*/
/* cmdfile() -- open the command file and set global variables		*/
/* 									*/
/*	This function is called during the option processing.  The	*/
/*	current token on entry is COMMAND.  On normal exit, the 	*/
/*	scanner is sitting at the first character in the first string	*/
/*	in the file.  If the file is empty, the line is a null string.	*/
/*									*/
/*	Error exits are through the main error processor.		*/
/*									*/
/************************************************************************/

VOID
cmdfile()

{
	int	toktype;

	if (cfileflg)				/* should not be set	*/
		errorx(XTRACFIL, "");		/* no nested cmd files	*/

	cfileflg = TRUE;			/* set it		*/

	if((scan()!=LBRACK) || (((toktype=scan())!=NAMETK)&&toktype != BACKSL))
		errorx(BADSYNT, BRKNAM);	/* syntax error		*/
 
	if ((cmdfpt = fopen(tokenval, "r")) == NULL)
		errorx(BADINFIL, tokenval);	/* can't open file	*/

	if (fgets(cmdline, LINELEN, cmdfpt) == NULL)  /* empty file?	*/
		cmdline[0] = EOS;		/* don't leave garbage	*/
	println(cmdline);			/* echo line		*/
	
	scanpos = 0;				/* reset scan position	*/
}


/************************************************************************/
/*									*/
/* addfltyp(name, type, change) -- put filetype into filespec		*/
/*									*/
/*	When the flag "change" is 1, change the file type to "type",	*/
/*	if the flag "change" is 0,  no replacement of file type will	*/
/*	be done, if there is already a file type;  "type" will be added */
/*	to the end of the file with a dot in front of it, if no file	*/
/*	type was in the name.						*/
/*									*/
/*	This function expects a normal CP/M filename with an optional	*/
/*	drive name.							*/
/*									*/
/************************************************************************/

VOID
addfltyp(flname, fltype, change)
char *flname, *fltype;
int	change;
{
	register int i;
	register char c;

	for (i = 0; ((c = flname[i]) != '.') && (c != EOS); i++)
	{					/* find end of name	*/
	}

	if (i > (FNAMELEN - (strlen(fltype) + 1)))
	{					/* room for type and null*/
		i = FNAMELEN - (strlen(fltype) + 1);
	}
    	if(change || (!change && c != '.')){
		flname[i] = EOS;		/* mark new end of string */
		flname = strcat(flname, fltype);
    	}
}		



/************************************************************************/
/*									*/
/* newflnod() -- make a new filenode and return pointer to it		*/
/*									*/
/*	Allocates space for a new file node and zeroes it out.		*/
/*									*/
/*	Returns a pointer to the new node if space available.		*/
/*	Otherwise exits through main error processor.			*/
/*									*/
/************************************************************************/

struct filenode *
newflnod()

{
	register struct filenode *newnode;	/* temporary pointer	*/

	if ((newnode = malloc(sizeof(*newnode))) == NULL) /* any space? */
		errorx(NOROOM, "");		/* heap full		*/
	newnode->fnfname[0] = EOS;		/* zero all the fields	*/
	newnode->fnflags = 0;
	newnode->fnnext  = NULL;

	return(newnode);
}




/************************************************************************/
/*									*/
/* locops(filenode) -- process the options for a specific file		*/
/*									*/
/*	On entry the current token is a '['.  On normal return, the	*/
/*	current token is a ']'.  					*/
/*									*/
/*	This function sets all the relevant filenode flags, except	*/
/*	the one for local symbols, which is set in the main parsing	*/
/*	routine.							*/
/*									*/
/************************************************************************/

VOID
locops(fnpt)

struct filenode *fnpt;

{
	register int toknum;			/* token class number	*/
	register int opnum;			/* specific option	*/

	toknum = scan();			/* get name, skip '['	*/
	if ((toknum != NAMETK) && (toknum != RBRACK))
		errorx(BADSYNT, NAMESTR);

	while (toknum == NAMETK)
	{
		opnum = readop(tokenval);	/* which option?	*/

		if (opnum == LOCALS)
			locsflg = TRUE;		/* include local syms.	*/
		else if (opnum == NOLOCALS)
			locsflg = FALSE;
		else if (opnum == ALLMODS)
			fnpt->fnflags |= FNALL;	/* don't search library	*/
		else if (opnum == INCLUDE)
			inclname(fnpt);		/* get the name		*/
		else if (opnum == COMMAND)
		{
			cmdfile();		/* set up command file	*/
			return;			/* leave loop -- return	*/
		}

		else				/* illegal name		*/
			errorx(BADOPT, tokenval);  /* quit		*/

		if ((toknum = scan()) == COMMA)
			toknum = scan();	/* skip ',' to name	*/
		else if ((toknum != RBRACK) && (toknum != NOMORE))
			errorx(BADSYNT,COMORBRK); /* quit		*/
	}
}


/************************************************************************/
/*									*/
/* readop(name) -- figure out which option the name represents		*/
/*									*/
/*	Name is a null-terminated string.  The returned value is an	*/
/*	integer that corresponds to the named option.  Only enough	*/
/*	characters to make the name unambiguous are needed, but all	*/
/*	included characters must match.					*/
/*									*/
/*	The matching process seems a bit inefficient, but it is		*/
/*	easy to convert to a foreign language by changing only		*/
/*	the string constants.						*/
/*									*/
/*	All the characters in the string must be uppercase.		*/
/*									*/
/************************************************************************/

int
readop(oname)

char *oname;

{
	int count, op;

	count = 0;				/* no matches yet	*/
	if (match(oname, ABSSTR))
		{op = ABSOLUTE; count++;} 
	if (match(oname, ALLSTR))
		{op = ALLMODS; count++;}
	if (match(oname, BSSSTR))
		{op = BSSBASE; count++;}
	if (match(oname, CHNSTR))
		{op = CHAINED; count++;}
	if (match(oname, COMSTR))
		{op = COMMAND; count++;}
	if (match(oname, DATSTR))
		{op = DATABASE; count++;}
	if (strcmp(oname, DMPSTR) == 0)
		{op = DUMPSYMS; count++;}
	if (match(oname, INCSTR))
		{op = INCLUDE; count++;}
	if (match(oname, IGNSTR))
		{op = IGNORE; count++;}
	if (match(oname, LOCSTR))
		{op = LOCALS; count++;}
	if (match(oname, MAPSTR))
		{op = MAP; count++;}
	if (match(oname, NOLSTR))
		{op = NOLOCALS; count++;}
	if (match(oname, SYMSTR))
		{op = SYMBOLS; count++;}
	if (match(oname, TEMSTR))
		{op = TEMPFILES; count++;}
	if (match(oname, TEXSTR))
		{op = TEXTBASE; count++;}
	if (match(oname, UDFSTR))
		{op = UNDEFINED; count++;}
	if (count == 1)				/* only found one match */
		return(op);
	else
		return(JUNKOP);			/* none or more than one */
}
	
/************************************************************************/
/*									*/
/* match(s1, s2) -- returns TRUE if s1 fits in s2			*/
/*									*/
/*	If the n characters in s1 match the first n characters in s2, 	*/
/*	return TRUE.							*/
/*									*/
/************************************************************************/

BOOLEAN
match(s1, s2)

char *s1, *s2;

{
	register int i;

	i = 0;
	while (s1[i] == s2[i])
		if (s1[i++] == EOS)		/* end of s1 & s2?	*/
			return(1);		/* they match 		*/
	if (s1[i] == EOS)
		return(1);			/* end of s1, it fits	*/
	else
		return(0);			/* doesn't match	*/
}


/************************************************************************/
/*									*/
/* tdrvscan() -- get the temp file drive from the command stream	*/
/*									*/
/*	On entry the current token is the TEMPFILES option.  On 	*/
/*	normal exit, the token is a ']'.  This function DOES NOT	*/
/*	check whether the drive spec is any good -- that is done	*/
/*	later when the tempfiles are set up.  This allows more		*/
/*	portability.							*/
/*									*/
/************************************************************************/

VOID
tdrvscan()

{
	register int toknum;

	if ((scan() != LBRACK) || ((toknum = scan()) != NAMETK))
		errorx(BADSYNT, BRKNAM);	/* must be '[' <drive>	*/

	strcpy(tdisk, tokenval);		/* set global variable	*/

	if (scan() != RBRACK)			/* better be a ']'	*/
		errorx(BADSYNT, "']'");
}


/************************************************************************/
/*									*/
/* inclname(fnode) -- set up filenode for include symbol name		*/
/*									*/
/*	Gets the symbol name out of the command stream and puts it	*/
/*	in the (node allocated in this routine).  The new node is 	*/
/*	linked after the main node (fnode).  If fnode already points	*/
/*	to something, the new node is linked in between.  All the 	*/
/*	appropriate filenode flags are set in both nodes.		*/
/*									*/
/*	Normal entry next token is '[', normal exit token is ']'.	*/
/*									*/
/************************************************************************/

VOID
inclname(fnode)

register struct filenode *fnode;

{
	register struct filenode *inode;

	if (scan() != LBRACK)			/* '[' <symbol>		*/
		errorx(BADSYNT, "'['");
	
	symscan();		/* get symbol -- may have funny chars.	*/

	inode = newflnod();			/* allocate new node	*/

	strcpy(inode->fnfname, tokenval);	/* put name in node	*/ 

	inode->fnflags |= FNSYM;		/* mark as symbol node	*/
	fnode->fnflags |= FNINCL;		/* mark for include	*/

	inode->fnnext = fnode->fnnext;		/* insert new node	*/
	fnode->fnnext = inode;

	scan();					/* skip to next token	*/
}

/************************************************************************/
/*									*/
/* symscan() -- scan for a symbol name					*/
/*									*/
/*	Grabs all characters up to a blank, ']', or null.  Does not	*/
/*	convert to upper case.  The regular name scanner chokes on	*/
/*	non-alphanumeric characters.					*/
/*									*/
/*	The symbol must be on the current line.  Only the first 	*/
/*	(TOKLEN -1) characters are kept.  Long symbols are truncated.	*/
/*									*/
/************************************************************************/

VOID
symscan()

{
	register int i;
	register char c;
	
	i = 0;
	tokenval[0] = EOS;			/* zap out string	*/

	while (((c = cmdline[scanpos]) != EOS) && (isspace(c))) 
		scanpos++;			/* find beginning of name */
	lastpos = scanpos;			/* save location	*/
	
	while (	((c = cmdline[scanpos]) != EOS) && 
		(!isspace(c)) && (c != ']') )
	{
		scanpos++;			/* move to next char	*/

		if (i < (TOKLEN -1))		/* don't overflow	*/
			tokenval[i++] = c;	/* build the string	*/
	}

	if (i == 0)
		errorx(BADSYNT, NAMESTR);	/* no symbol name	*/
	
	tokenval[i] = EOS;			/* null terminate	*/
}

/************************************************************************/
/*									*/
/* putarrow() -- print an arrow under offensive command token		*/
/*									*/
/*	For most syntax errors, the error processor calls this 		*/
/*	routine to point out the bad spot in the command stream.	*/
/*									*/
/*	The global variable lastpos marks the beginning of the 		*/
/*	current token.							*/
/*									*/
/************************************************************************/

VOID
putarrow()

{
	register int i;
	
	for (i=0; i < lastpos; i++)
		printf(".");			/* print a line of dots */

	printf("^");				/* print arrow under token */

	if (scanpos-1 > lastpos)		/* long token?		*/
	{
		for (i += 1; i < scanpos-1; i++)
			printf("-");
		printf("^");			/* mark other end of token */
	}

	printf("\n");
}


/************************************************************************/
/*									*/
/* println(string) -- prints string on standard output			*/  
/*									*/
/*	Converts all white characters to blanks.  String must be 	*/
/*	null terminated.						*/
/*									*/
/************************************************************************/

VOID
println(st)

char *st;

{
	register int i;
	register char c;

	i = 0;

	while ((c = st[i++]) != EOS)
		if (isspace(c))
			printf(" ");		/* convert whitespace	*/
		else
			printf("%c", c);

	printf("\n");				/* newline is whitespace */
}