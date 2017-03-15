# define the name of the installer
Outfile "LotsOfLines.exe"

# Set program files as install directory
InstallDir $PROGRAMFILES\LotsOfLines

# default section
Section
 
# define the output path for this file
SetOutPath $INSTDIR
 
# define what to install and place it in the output path
File bin\release\LotsOfLinesApp.exe
File 3rd-party\qt\Qt5Core.dll
File 3rd-party\qt\Qt5Gui.dll
File 3rd-party\qt\Qt5OpenGL.dll
File 3rd-party\qt\Qt5Widgets.dll
File 3rd-party\qt\Qt5WinExtras.dll
File /r data

# define uninstaller name
WriteUninstaller $INSTDIR\uninstaller.exe
 
# create shortcuts
CreateShortCut "$DESKTOP\Lots of Lines.lnk" "$INSTDIR\LotsOfLinesApp.exe"

CreateDirectory "$SMPROGRAMS\Lots of Lines"
CreateShortCut "$SMPROGRAMS\Lots of Lines\Lots of Lines.lnk" "$INSTDIR\LotsOfLinesApp.exe"

SectionEnd

Section "Uninstall"
 
# Always delete uninstaller first
Delete $INSTDIR\uninstaller.exe
 
# now delete installed files
Delete $INSTDIR\LotsOfLinesApp.exe
Delete $INSTDIR\Qt5Core.dll
Delete $INSTDIR\Qt5Gui.dll
Delete $INSTDIR\Qt5Widgets.dll
RMDir /r $INSTDIR\data
 
SectionEnd
