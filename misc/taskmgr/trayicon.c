/*
 *  ReactOS Task Manager
 *
 *  trayicon.c
 *
 *  Copyright (C) 1999 - 2001  Brian Palmer  <brianp@reactos.org>
 *                2005         Klemens Friedl <frik85@reactos.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "taskmgr.h"

HICON TrayIcon_GetProcessorUsageIcon(void)
{
    HICON hTrayIcon = NULL;
    HDC hScreenDC = NULL;
    HDC hDC = NULL;
    HBITMAP hBitmap = NULL;
    HBITMAP hOldBitmap = NULL;
    HBITMAP hBitmapMask = NULL;
	ICONINFO iconInfo = { 0 };
    ULONG ProcessorUsage = 0;
    int nLinesToDraw  = 0;
    HBRUSH hBitmapBrush = NULL;
    RECT rc = { 0 };

    /*
     * Get a handle to the screen DC
     */
    hScreenDC = GetDC(NULL);
    if (!hScreenDC)
        goto done;

    /*
     * Create our own DC from it
     */
    hDC = CreateCompatibleDC(hScreenDC);
    if (!hDC)
        goto done;

    // Load the bitmaps.
    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_TRAYICON));
    hBitmapMask = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_TRAYMASK));
    if (!hBitmap || !hBitmapMask)
        goto done;

    hBitmapBrush = CreateSolidBrush(RGB(0, 255, 0));
    if (!hBitmapBrush)
        goto done;

    /*
     * Select the bitmap into our device context
     * so we can draw on it.
     */
    hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);

    // Get the cpu usage.
    ProcessorUsage = PerfDataGetProcessorUsage();

    /*
     * Calculate how many lines to draw
     * since we have 11 rows of space
     * to draw the cpu usage instead of
     * just having 10.
     */
    nLinesToDraw = (ProcessorUsage + (ProcessorUsage / 10)) / 11;
    rc.left = 3;
    rc.top = 12 - nLinesToDraw;
    rc.right = 13;
    rc.bottom = 13;

    // Now draw the cpu usage.
    if (nLinesToDraw)
        FillRect(hDC, &rc, hBitmapBrush);

    // Now that we are done drawing put the old bitmap back.
    hBitmap = SelectObject(hDC, hOldBitmap);
    hOldBitmap = NULL;

    iconInfo.fIcon = TRUE;
    iconInfo.hbmMask = hBitmapMask;
    iconInfo.hbmColor = hBitmap;

    hTrayIcon = CreateIconIndirect(&iconInfo);

done:
    // Cleanup.
    if (hScreenDC)
        ReleaseDC(NULL, hScreenDC);

    if (hDC)
        DeleteDC(hDC);

    if (hBitmapBrush)
        DeleteObject(hBitmapBrush);

    if (hBitmap)
        DeleteObject(hBitmap);

    if (hBitmapMask)
        DeleteObject(hBitmapMask);

    // Return the newly created tray icon (if successful)
    return hTrayIcon;
}

BOOL TrayIcon_ShellAddTrayIcon(void)
{
    NOTIFYICONDATA nid = { 0 };
    HICON hIcon = NULL;
    BOOL bRetVal = FALSE;
    WCHAR szMsg[64];

    memset(&nid, 0, sizeof(NOTIFYICONDATA));

    hIcon = TrayIcon_GetProcessorUsageIcon();

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_ONTRAYICON;
	nid.hWnd = hMainWnd;
    nid.hIcon = hIcon;

    LoadString(NULL, IDS_MSG_TRAYICONCPUUSAGE, szMsg, NUMBER_OF_ITEMS_IN_ARRAY(szMsg));
    
	wsprintf(nid.szTip, szMsg, PerfDataGetProcessorUsage());

    bRetVal = Shell_NotifyIcon(NIM_ADD, &nid);

    if (hIcon)
        DestroyIcon(hIcon);

    return bRetVal;
}

BOOL TrayIcon_ShellRemoveTrayIcon(void)
{
    NOTIFYICONDATA nid = { 0 };
    BOOL bRetVal = FALSE;

    memset(&nid, 0, sizeof(NOTIFYICONDATA));

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.uCallbackMessage = WM_ONTRAYICON;
	nid.hWnd = hMainWnd;
    
    bRetVal = Shell_NotifyIcon(NIM_DELETE, &nid);

    return bRetVal;
}

BOOL TrayIcon_ShellUpdateTrayIcon(void)
{
	NOTIFYICONDATA nid = { 0 };
    HICON hIcon = NULL;
    BOOL bRetVal = FALSE;
    WCHAR szTemp[64];

    memset(&nid, 0, sizeof(NOTIFYICONDATA));

    hIcon = TrayIcon_GetProcessorUsageIcon();

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_ONTRAYICON;
	nid.hWnd = hMainWnd; 
    nid.hIcon = hIcon;

    LoadString(hInst, IDS_MSG_TRAYICONCPUUSAGE, szTemp, NUMBER_OF_ITEMS_IN_ARRAY(szTemp));
   
	wsprintf(nid.szTip, szTemp, PerfDataGetProcessorUsage());

    bRetVal = Shell_NotifyIcon(NIM_MODIFY, &nid);

    if (hIcon)
        DestroyIcon(hIcon);

    return bRetVal;
}
