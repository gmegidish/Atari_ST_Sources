#ifndef	__MENU__
#define	__MENU__

#define	MENUE_KONTEXT_COPY			0x00000001L
#define	MENUE_KONTEXT_CUT				0x00000002L
#define	MENUE_KONTEXT_PASTE			0x00000004L
#define	MENUE_KONTEXT_MARK_ALL		0x00000008L
#define	MENUE_KONTEXT_KONTEXT		0x00000010L
#define	MENUE_KONTEXT_WINDOW_CYCLE	0x00010000L
#define	MENUE_KONTEXT_WINDOW_CLOSE	0x00020000L
#define	MENUE_KONTEXT_WINDOW_FULL	0x00040000L

void	KontextMenu( void );
WORD	HandleMenu( EVNT *Events );
WORD	KeyEvent( WORD	Key );
WORD	isMenuKey( WORD Key, WORD *Title, WORD *Entry );
void	InstallHtPopup( void );
#endif