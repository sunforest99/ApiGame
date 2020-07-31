#pragma once

class cGdiImage
{
public:
	HDC		 m_memDC;
	HDC      m_hdcMem ;  ///< 메모리 DC
	HBITMAP  m_hbmNew ;  ///< 비트맵 이미지
	HBITMAP  m_hbmOld ;  ///< 복원용 이미지

	DWORD    m_Width ;   ///< 픽셀 폭
	DWORD    m_Height ;  ///< 픽셀 높이

	BLENDFUNCTION bf;


public:
	cGdiImage( void ) : m_hdcMem( NULL ), m_hbmNew( NULL ), m_hbmOld( NULL )
	{
		// nothing
		// 알파값. 투명도
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.SourceConstantAlpha = 0;
		bf.AlphaFormat = 0;
	}

	virtual ~cGdiImage( void )
	{
		this->Destroy() ;
	}

	void setDC( HDC memDC )
	{
		m_memDC				= memDC;
	}

	void Load( const char* fileName )
	{
		// 기존 리소스 해제
		this->Destroy() ;

		// 메모리 DC 생성
		m_hdcMem = ::CreateCompatibleDC( m_memDC ) ;

		// 이미지 로딩
		m_hbmNew = ( HBITMAP )::LoadImage( ::GetModuleHandle( NULL ) ,
			fileName ,
			IMAGE_BITMAP ,
			0 , 0 ,
			LR_CREATEDIBSECTION | LR_LOADFROMFILE ) ;

		m_hbmOld = ( HBITMAP )::SelectObject( m_hdcMem , m_hbmNew ) ;

		BITMAP bmp ;
		::GetObject( m_hbmNew , sizeof( BITMAP ) , (LPVOID)&bmp ) ;

		m_Width  = bmp.bmWidth ;
		m_Height = bmp.bmHeight ;
	}

	void Destroy()
	{
		if ( m_hbmNew ) // 비트맵 해제
		{
			::SelectObject( m_hdcMem , m_hbmOld ) ;
			::DeleteObject( m_hbmNew ) ; m_hbmNew = NULL ;
		}

		if ( m_hdcMem ) // 메모리 DC 해제
		{
			::DeleteDC( m_hdcMem ) ; m_hdcMem = NULL ;
		}
	}

	void Draw( int x , int y )
	{
		::BitBlt( m_memDC ,
			x , y , m_Width , m_Height ,
			m_hdcMem , 0 , 0 , SRCCOPY ) ;
	}

	void Draw( int dx , int dy , int sx , int sy )
	{
		::BitBlt( m_memDC ,
			dx , dy , m_Width , m_Height ,
			m_hdcMem , sx , sy , SRCCOPY ) ;
	}

	void Draw( int dx , int dy , int sx , int sy , int sw , int sh )
	{
		::BitBlt( m_memDC ,
			dx , dy , sw , sh ,
			m_hdcMem , sx , sy , SRCCOPY ) ;
	}

	void Draw( int dx , int dy , int sx , int sy , 
		int sw , int sh, int iw, int ih )
	{
		::StretchBlt( m_memDC ,	dx , dy , sw , sh ,
			m_hdcMem , sx , sy , iw, ih ,
			SRCCOPY ) ;
	}

	void Draw( int dx , int dy , int sx , int sy , 
		int sw , int sh, int iw, int ih, UINT uRGB )
	{
		::TransparentBlt( m_memDC ,	dx , dy , sw , sh ,
			m_hdcMem , sx , sy , iw, ih , uRGB );
	}

	void AlphaDraw( int dx , int dy , int sx , int sy , 
		int sw , int sh, int iw, int ih, int alphaValue)
	{
		bf.SourceConstantAlpha = alphaValue;
		::AlphaBlend( m_memDC ,	dx , dy , sw , sh ,
			m_hdcMem , sx , sy , iw, ih , bf) ;
	}


private:
	cGdiImage( const cGdiImage& rhs ) ;
	cGdiImage& operator = ( const cGdiImage& rhs ) ;

};
