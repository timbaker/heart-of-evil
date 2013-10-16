//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#include "iloadingdisc.h"
#include "vgui_controls/Frame.h"
#include "vgui_controls/Label.h"
#include "hud_numericdisplay.h"
#include "vgui/ISurface.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#ifdef HOE_DLL

//-----------------------------------------------------------------------------
// Purpose: Displays the loading plaque
//-----------------------------------------------------------------------------
class CLoadingDiscPanel : public vgui::EditablePanel
{
	typedef vgui::EditablePanel BaseClass;
public:
	CLoadingDiscPanel( vgui::VPANEL parent );
	~CLoadingDiscPanel();

	virtual void ApplySchemeSettings( vgui::IScheme *pScheme )
	{
		BaseClass::ApplySchemeSettings( pScheme );

		int w, h;
		w = ScreenWidth();
		h = ScreenHeight();

		if ( w != m_ScreenSize[ 0 ] || 
			 h != m_ScreenSize[ 1 ] )
		{
			m_ScreenSize[ 0 ] = w;
			m_ScreenSize[ 1 ] = h;

			// Re-perform the layout if the screen size changed
			LoadControlSettings( "resource/LoadingDiscPanel.res" );
		}

		// center the dialog
		int wide, tall;
		GetSize( wide, tall );
		SetPos( ( w - wide ) / 2, ( h - tall ) / 2 );
	}

	virtual void PaintBackground()
	{
		SetBgColor( Color(0, 0, 0, 128) );
		SetPaintBackgroundType( 2 );
		BaseClass::PaintBackground();
	}
#if 0
	virtual void SetText( const char *text )
	{
	}
#endif
private:
//	vgui::ImagePanel *m_pLoadingImage;
	int			m_ScreenSize[ 2 ];
};

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CLoadingDiscPanel::CLoadingDiscPanel( vgui::VPANEL parent ) : BaseClass( NULL, "CLoadingDiscPanel" )
{
	int w, h;
	w = ScreenWidth();
	h = ScreenHeight();

	SetParent( parent );
	SetProportional( false /*true*/ );
	SetScheme( "ClientScheme" );
	SetVisible( false );
	SetCursor( NULL );
	SetPaintBackgroundEnabled( false );
#if 0
	m_pLoadingImage = vgui::SETUP_PANEL(new vgui::ImagePanel( this, "LoadingImage" ));
	m_pLoadingImage->SetPaintBackgroundEnabled( false );
#endif
	LoadControlSettings( "resource/LoadingDiscPanel.res" );

	// center the dialog
	int wide, tall;
	GetSize( wide, tall );
	SetPos( ( w - wide ) / 2, ( h - tall ) / 2 );

	m_ScreenSize[ 0 ] = w;
	m_ScreenSize[ 1 ] = h;
}

//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
CLoadingDiscPanel::~CLoadingDiscPanel()
{
}

//-----------------------------------------------------------------------------
// Purpose: Displays the loading plaque
//-----------------------------------------------------------------------------
class CPausedPanel : public vgui::EditablePanel
{
	typedef vgui::EditablePanel BaseClass;
public:
	CPausedPanel( vgui::VPANEL parent );
	~CPausedPanel();

	virtual void ApplySchemeSettings( vgui::IScheme *pScheme )
	{
		BaseClass::ApplySchemeSettings( pScheme );

		int w, h;
		w = ScreenWidth();
		h = ScreenHeight();

		// center the dialog
		int wide, tall;
		GetSize( wide, tall );
		SetPos( ( w - wide ) / 2, ( h - tall ) / 2 );
	}

	virtual void PaintBackground()
	{
		SetBgColor( Color(0, 0, 0, 128) );
		SetPaintBackgroundType( 2 );
		BaseClass::PaintBackground();
	}

	virtual void SetText( const char *text )
	{
		m_pPausedLabel->SetText( text );
	}

private:
	vgui::Label *m_pPausedLabel;
};

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CPausedPanel::CPausedPanel( vgui::VPANEL parent ) : BaseClass( NULL, "CPausedPanel" )
{
	int w, h;
	w = ScreenWidth();
	h = ScreenHeight();

	SetParent( parent );
	SetProportional( true );
	SetScheme( "ClientScheme" );
	SetVisible( false );
	SetCursor( NULL );

	m_pPausedLabel = vgui::SETUP_PANEL(new vgui::Label( this, "PausedLabel", "" ));
	m_pPausedLabel->SetPaintBackgroundEnabled( false );

	LoadControlSettings( "resource/PausedPanel.res" );

	// center the dialog
	int wide, tall;
	GetSize( wide, tall );
	SetPos( ( w - wide ) / 2, ( h - tall ) / 2 );
}

//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
CPausedPanel::~CPausedPanel()
{
}

class CLoadingDisc : public ILoadingDisc
{
private:
	CLoadingDiscPanel *loadingDiscPanel;
	CPausedPanel *m_pPauseDiscPanel;
	vgui::VPANEL m_hParent;

public:
	CLoadingDisc( void )
	{
		loadingDiscPanel = NULL;
	}

	void Create( vgui::VPANEL parent )
	{
		// don't create now, only when it's needed
		m_hParent = parent;
	}

	void Destroy( void )
	{
		if ( loadingDiscPanel )
		{
			loadingDiscPanel->SetParent( (vgui::Panel *)NULL );
			delete loadingDiscPanel;
		}

		if ( m_pPauseDiscPanel )
		{
			m_pPauseDiscPanel->SetParent( (vgui::Panel *)NULL );
			delete m_pPauseDiscPanel;
		}
	}

	void SetLoadingVisible( bool bVisible )
	{
		// demand-create the dialog
		if ( bVisible && !loadingDiscPanel )
		{
			loadingDiscPanel = vgui::SETUP_PANEL(new CLoadingDiscPanel( m_hParent ) );
		}

		if ( loadingDiscPanel )
		{
			loadingDiscPanel->SetVisible( bVisible );
		}
	}


	void SetPausedVisible( bool bVisible )
	{
		if ( bVisible && !m_pPauseDiscPanel )
		{
			m_pPauseDiscPanel = vgui::SETUP_PANEL(new CPausedPanel( m_hParent ) );
		}

		if ( m_pPauseDiscPanel )
		{
			m_pPauseDiscPanel->SetVisible( bVisible );
		}
	}
};

static CLoadingDisc g_LoadingDisc;
ILoadingDisc *loadingdisc = ( ILoadingDisc * )&g_LoadingDisc;

#else // HOE_DLL

//-----------------------------------------------------------------------------
// Purpose: Displays the loading plaque
//-----------------------------------------------------------------------------
class CLoadingDiscPanel : public vgui::EditablePanel
{
	typedef vgui::EditablePanel BaseClass;
public:
	CLoadingDiscPanel( vgui::VPANEL parent );
	~CLoadingDiscPanel();

	virtual void ApplySchemeSettings( vgui::IScheme *pScheme )
	{
		BaseClass::ApplySchemeSettings( pScheme );

		int w, h;
		w = ScreenWidth();
		h = ScreenHeight();

		if ( w != m_ScreenSize[ 0 ] || 
			 h != m_ScreenSize[ 1 ] )
		{
			m_ScreenSize[ 0 ] = w;
			m_ScreenSize[ 1 ] = h;

			// Re-perform the layout if the screen size changed
			LoadControlSettings( "resource/LoadingDiscPanel.res" );
		}

		// center the dialog
		int wide, tall;
		GetSize( wide, tall );
		SetPos( ( w - wide ) / 2, ( h - tall ) / 2 );
	}

	virtual void PaintBackground()
	{
		SetBgColor( Color(0, 0, 0, 128) );
		SetPaintBackgroundType( 2 );
		BaseClass::PaintBackground();
	}

	virtual void SetText( const char *text )
	{
		m_pLoadingLabel->SetText( text );
	}

private:
	vgui::Label *m_pLoadingLabel;
	int			m_ScreenSize[ 2 ];
};

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CLoadingDiscPanel::CLoadingDiscPanel( vgui::VPANEL parent ) : BaseClass( NULL, "CLoadingDiscPanel" )
{
	int w, h;
	w = ScreenWidth();
	h = ScreenHeight();

	SetParent( parent );
	SetProportional( true );
	SetScheme( "ClientScheme" );
	SetVisible( false );
	SetCursor( NULL );

	m_pLoadingLabel = vgui::SETUP_PANEL(new vgui::Label( this, "LoadingLabel", "" ));
	m_pLoadingLabel->SetPaintBackgroundEnabled( false );

	LoadControlSettings( "resource/LoadingDiscPanel.res" );

	// center the dialog
	int wide, tall;
	GetSize( wide, tall );
	SetPos( ( w - wide ) / 2, ( h - tall ) / 2 );

	m_ScreenSize[ 0 ] = w;
	m_ScreenSize[ 1 ] = h;
}

//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
CLoadingDiscPanel::~CLoadingDiscPanel()
{
}

class CLoadingDisc : public ILoadingDisc
{
private:
	CLoadingDiscPanel *loadingDiscPanel;
	CLoadingDiscPanel *m_pPauseDiscPanel;
	vgui::VPANEL m_hParent;

public:
	CLoadingDisc( void )
	{
		loadingDiscPanel = NULL;
		m_pPauseDiscPanel = NULL;
	}

	void Create( vgui::VPANEL parent )
	{
		// don't create now, only when it's needed
		m_hParent = parent;
	}

	void Destroy( void )
	{
		if ( loadingDiscPanel )
		{
			loadingDiscPanel->SetParent( (vgui::Panel *)NULL );
			delete loadingDiscPanel;
			loadingDiscPanel = NULL;
		}

		if ( m_pPauseDiscPanel )
		{
			m_pPauseDiscPanel->SetParent( (vgui::Panel *)NULL );
			delete m_pPauseDiscPanel;
			m_pPauseDiscPanel = NULL;
		}

		m_hParent = NULL;
	}

	void SetLoadingVisible( bool bVisible )
	{
		// demand-create the dialog
		if ( bVisible && !loadingDiscPanel )
		{
			loadingDiscPanel = vgui::SETUP_PANEL(new CLoadingDiscPanel( m_hParent ) );
		}

		if ( loadingDiscPanel )
		{
			loadingDiscPanel->SetVisible( bVisible );
		}
	}


	void SetPausedVisible( bool bVisible )
	{
		if ( bVisible && !m_pPauseDiscPanel )
		{
			m_pPauseDiscPanel = vgui::SETUP_PANEL(new CLoadingDiscPanel( m_hParent ) );
			m_pPauseDiscPanel->SetText( "#gameui_paused" );
		}

		if ( m_pPauseDiscPanel )
		{
			m_pPauseDiscPanel->SetVisible( bVisible );
		}
	}
};

static CLoadingDisc g_LoadingDisc;
ILoadingDisc *loadingdisc = ( ILoadingDisc * )&g_LoadingDisc;

#endif // HOE_DLL

