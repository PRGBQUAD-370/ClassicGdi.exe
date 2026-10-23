#include <Windows.h>
#include <math.h>
#include <stdbool.h>
#define USE_MATH_DEFINES 1
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")

int red = 0, green = 0, blue = 0;
bool ifblue = false;

COLORREF Hue ( int length )
{
    if (red != length) {
        red++;
        if (ifblue)
            return RGB ( red, 0, length );
        else
            return RGB ( red, 0, 0 );
    }
    else if (green != length) {
        green++;
        return RGB ( length, green, 0 );
    }
    else if (blue != length) {
        blue++;
        return RGB ( 0, length, blue );
    }
    else {
        red = green = blue = 0;
        ifblue = true;
        return RGB ( 0, 0, 0 );
    }
}

VOID 
WINAPI 
squares 
( VOID ) 
{

	int w = GetSystemMetrics ( 0 ), h = GetSystemMetrics ( 1 );
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;

	for (;;) 
	{
		HDC hdc = GetDC ( 0 );
		x += incrementor * signX;
		y += incrementor * signY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		HBRUSH brush = CreateSolidBrush ( Hue ( 239 ) );
		SelectObject ( hdc, brush );
		Rectangle ( hdc, top_x, top_y, bottom_x, bottom_y );
		if (y == GetSystemMetrics ( SM_CYSCREEN ))
		{
			signY = -1;
		}

		if (x == GetSystemMetrics ( SM_CXSCREEN ))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}

		Sleep ( 5 );
		DeleteObject ( brush );
		ReleaseDC ( 0, hdc );

	}
}

VOID 
WINAPI 
textout 
( VOID ) 
{

	HDC hdc = GetDC ( 0 );
	int sx = GetSystemMetrics ( 0 );
	int sy = GetSystemMetrics ( 1 );
	LPCWSTR lpText = L"ClassicGdi.exe";

	for (;;)
	{

		hdc = GetDC ( 0 );
		SetBkColor ( hdc, RGB ( rand ( ) % 255, rand ( ) % 255, rand ( ) % 255 ) );
		SetTextColor ( hdc, RGB ( rand ( ) % 255, rand ( ) % 255, rand ( ) % 255 ) );

		TextOutW ( hdc, rand ( ) % sx, rand ( ) % sy, lpText, wcslen ( lpText ) );
		ReleaseDC ( GetDesktopWindow ( ), hdc );
		DeleteDC ( hdc );

	}
}

VOID 
WINAPI 
MoveDown
( VOID ) 
{

	HDC hdc = GetDC ( 0 );
	int w = GetSystemMetrics ( 0 );
	int h = GetSystemMetrics ( 1 );

	for (;;)
	{

		hdc = GetDC ( 0 );
		BitBlt ( hdc, 0, -30, w, h, hdc, 0, 0, SRCCOPY );
		BitBlt ( hdc, 0, h - 30, w, h, hdc, 0, 0, SRCCOPY );
		BitBlt ( hdc, -30, 0, w, h, hdc, 0, 0, SRCCOPY );
		BitBlt ( hdc, w - 30, 0, w, h, hdc, 0, 0, SRCCOPY );

		ReleaseDC ( GetDesktopWindow ( ), hdc );
		DeleteDC ( hdc );

	}
}

VOID 
WINAPI 
sinewave1 
( VOID ) 
{

	HDC hdc = GetDC ( 0 ); HWND wnd = GetDesktopWindow ( );
	int sw = GetSystemMetrics ( 0 ), sh = GetSystemMetrics ( 1 );
	double angle = 0;

	for (;;) 
	{

		hdc = GetDC ( 0 );
		for (float i = 0; i < sw + sh; i += 0.99f) {
			int a = sin ( angle ) * 60;
			BitBlt ( hdc, i, 0, 1, sh, hdc, i, a, SRCCOPY );
			angle += 100;
			DeleteObject ( &a ); DeleteObject ( &i );

		}

		ReleaseDC ( wnd, hdc );
		DeleteDC ( hdc ); DeleteObject ( wnd ); DeleteObject ( &sw ); DeleteObject ( &sh ); DeleteObject ( &angle );

	}
}

VOID 
WINAPI 
bltshake 
( LPVOID lpParam ) 
{

	HDC hdc = GetDC ( 0 );
	int w = GetSystemMetrics ( 0 );
	int h = GetSystemMetrics ( 1 );

	for (;;)
	{

		hdc = GetDC ( 0 );
		BitBlt ( hdc, 5, 5, w, h, hdc, 0, 0, SRCCOPY );
		BitBlt ( hdc, -5, -5, w, h, hdc, 0, 0, SRCCOPY );

		ReleaseDC ( GetDesktopWindow ( ), hdc );
		DeleteDC ( hdc );

	}
}

VOID
WINAPI
Redrawer
( VOID ) 
{

	for (;;) {

		RedrawWindow ( NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW );

		Sleep ( 2000 );

	}
}

VOID
WINAPI
sound1
( VOID ) 
{

	HWAVEOUT hwo = NULL;
	WAVEFORMATEX W = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen ( &hwo, WAVE_MAPPER, &W, 0, 0, CALLBACK_NULL );

	char buffer [ 8000 * 30 ];
	for ( DWORD t = 0; t < sizeof ( buffer ); ++t )

		buffer [ t ] = ( BYTE ) ( t % 25 - ( t >> 3 ) | 9 * t & t >> 4 | 5 * t & t >> 7 | 3 * t & t >> 10 );

	WAVEHDR hdr = { buffer, sizeof ( buffer ), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader ( hwo, &hdr, sizeof ( WAVEHDR ) );
	waveOutWrite ( hwo, &hdr, sizeof ( WAVEHDR ) );

	waveOutUnprepareHeader ( hwo, &hdr, sizeof ( WAVEHDR ) );
	waveOutClose ( hwo );

}

VOID
WINAPI
sound2
( VOID ) 
{

	HWAVEOUT hwo = NULL;
	WAVEFORMATEX W = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen ( &hwo, WAVE_MAPPER, &W, 0, 0, CALLBACK_NULL );

	char buffer [ 8000 * 30 ];
	for ( DWORD t = 0; t < sizeof ( buffer ); ++t )

		buffer [ t ] = ( BYTE ) ( t / 2 * ( 4 | 7 & t >> 13 ) >> ( ~t >> 11 & 1 ) & 127 ) + ( t * ( t >> 11 & t >> 13 ) * ( ~t >> 9 & 3 ) & 127 );

	WAVEHDR hdr = { buffer, sizeof ( buffer ), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader ( hwo, &hdr, sizeof ( WAVEHDR ) );
	waveOutWrite ( hwo, &hdr, sizeof ( WAVEHDR ) );

	waveOutUnprepareHeader ( hwo, &hdr, sizeof ( WAVEHDR ) );
	waveOutClose ( hwo );

}

VOID
WINAPI
sound3
( VOID ) 
{

	HWAVEOUT hwo = NULL;
	WAVEFORMATEX W = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen ( &hwo, WAVE_MAPPER, &W, 0, 0, CALLBACK_NULL );

	char buffer [ 8000 * 30 ];
	for ( DWORD t = 0; t < sizeof ( buffer ); ++t )

		buffer [ t ] = ( BYTE ) ( t * ( t & 8192 ? 7 : 5 ) * ( 6 - ( 3 & t >> 8 ) + ( 3 & t >> 9 ) ) >> ( 3 & t >> ( t & 2048 ? 2 : 11 ) ) | t >> 3 );

	WAVEHDR hdr = { buffer, sizeof ( buffer ), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader ( hwo, &hdr, sizeof ( WAVEHDR ) );
	waveOutWrite ( hwo, &hdr, sizeof ( WAVEHDR ) );

	waveOutUnprepareHeader ( hwo, &hdr, sizeof ( WAVEHDR ) );
	waveOutClose ( hwo );

}

VOID
WINAPI
sound4
( VOID ) 
{

	HWAVEOUT hwo = NULL;
	WAVEFORMATEX W = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen ( &hwo, WAVE_MAPPER, &W, 0, 0, CALLBACK_NULL );

	char buffer [ 8000 * 30 ];
	for ( DWORD t = 0; t < sizeof ( buffer ); ++t )

		buffer [ t ] = ( BYTE ) ( rand ( ) % 256 );

	WAVEHDR hdr = { buffer, sizeof ( buffer ), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader ( hwo, &hdr, sizeof ( WAVEHDR ) );
	waveOutWrite ( hwo, &hdr, sizeof ( WAVEHDR ) );

	waveOutUnprepareHeader ( hwo, &hdr, sizeof ( WAVEHDR ) );
	waveOutClose ( hwo );

}

VOID
WINAPI
sound5
( VOID ) 
{

	HWAVEOUT hwo = NULL;
	WAVEFORMATEX W = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen ( &hwo, WAVE_MAPPER, &W, 0, 0, CALLBACK_NULL );

	char buffer [ 8000 * 30 ];
	for ( DWORD t = 0; t < sizeof ( buffer ); ++t )

		buffer [ t ] = ( BYTE ) ( 9 * t & t >> 4 | 5 * t & t >> 7 | 3 * t & t >> 10 | t * ( t >> 8 ) & 64 );

	WAVEHDR hdr = { buffer, sizeof ( buffer ), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader ( hwo, &hdr, sizeof ( WAVEHDR ) );
	waveOutWrite ( hwo, &hdr, sizeof ( WAVEHDR ) );

	waveOutUnprepareHeader ( hwo, &hdr, sizeof ( WAVEHDR ) );
	waveOutClose ( hwo );

}

int main ( ) {

	if (MessageBoxA ( NULL, "Run ClassicGdi.exe?", "ClassicGdi.exe", MB_YESNO | MB_ICONWARNING ) == IDNO) {
		ExitProcess ( 0 );
	}
	else {

		if (MessageBoxA ( NULL, "You really want to?\r\nIf you do then press yes", "ClassicGdi.exe - Final Warning", MB_YESNO | MB_ICONWARNING ) == IDNO) {
			ExitProcess ( 0 );
		}
		else


		Sleep ( 1000 );

		HANDLE hThread1 = CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)squares, NULL, 0, NULL );
		sound1 ( );
		Sleep ( 30000 );
		TerminateThread ( hThread1, 0 );
		CloseHandle ( hThread1 );
		RedrawWindow ( NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW );
		Sleep ( 100 );
		HANDLE hThread2 = CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)textout, NULL, 0, NULL );
		HANDLE hRedrawThread = CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)Redrawer, NULL, 0, NULL );
		sound2 ( );
		Sleep ( 30000 );
		TerminateThread ( hThread2, 0 );
		CloseHandle ( hThread2 );
		TerminateThread ( hRedrawThread, 0 );
		CloseHandle ( hRedrawThread );
		RedrawWindow ( NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW );
		Sleep ( 100 );
		HANDLE hThread3 = CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)MoveDown, NULL, 0, NULL );
		sound3 ( );
		Sleep ( 30000 );
		TerminateThread ( hThread3, 0 );
		CloseHandle ( hThread3 );
		RedrawWindow ( NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW );
		Sleep ( 100 );
		HANDLE hThread4 = CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)sinewave1, NULL, 0, NULL );
		sound4 ( );
		Sleep ( 30000 );
		TerminateThread ( hThread4, 0 );
		CloseHandle ( hThread4 );
		RedrawWindow ( NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW );
		Sleep ( 100 );
		HANDLE hThread5 = CreateThread ( NULL, 0, (PTHREAD_START_ROUTINE)bltshake, NULL, 0, NULL );
		sound5 ( );
		Sleep ( 30000 );
		TerminateThread ( hThread5, 0 );
		CloseHandle ( hThread5 );
		RedrawWindow ( NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_UPDATENOW );
		Sleep ( 100 );

		return 0x00;

	}
}