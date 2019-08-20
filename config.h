/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */


/* config.h.in --- xscreensaver, Copyright (c) 1991-2014 Jamie Zawinski.
 *
 *  The best way to set these parameters is by running the included `configure'
 *  script.  That examines your system, and generates `config.h' from 
 *  `config.h.in'.
 *
 *  If something goes very wrong, you can edit `config.h' directly, but beware
 *  that your changes will be lost if you ever run `configure' again.
 */


/* Define this to allow the root password to unlock the screen. */
#define ALLOW_ROOT_PASSWD 1

/* always defined to indicate that i18n is enabled */
#define ENABLE_NLS 1

/* Some screenhacks like to run an external program to generate random pieces
   of text; set this to the one you like. Note that this is just the default;
   X resources can be used to override it. */
/* #undef FORTUNE_PROGRAM */

/* This is the name of the gettext package to use. */
#define GETTEXT_PACKAGE "xscreensaver"

/* Define this if gettimeofday() takes two arguments. */
#define GETTIMEOFDAY_TWO_ARGS 1

/* Define this if your system is Solaris with ``adjunct'' passwords (this is
   the version where one gets at the passwords with getpwanam() instead of
   getpwnam().) I haven't tested this one, let me know if it works. */
/* #undef HAVE_ADJUNCT_PASSWD */

/* Define to 1 if you have the `bind_textdomain_codeset' function. */
#define HAVE_BIND_TEXTDOMAIN_CODESET 1

/* Define to 1 if you have the Mac OS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the Mac OS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define this if you have Gnome and want to build support for the
   xscreensaver control panel in the Gnome Control Center (gnomecc). (This is
   needed only with Gtk 1.x.) */
/* #undef HAVE_CRAPPLET */

/* Define this if HAVE_CRAPPLET is defined, and the function
   capplet_widget_changes_are_immediate() is available. */
/* #undef HAVE_CRAPPLET_IMMEDIATE */

/* Define to 1 if you have the <crypt.h> header file. */
#define HAVE_CRYPT_H 1

/* Define to 1 if you have the `dcgettext' function. */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define this if you have the X Double Buffer Extension. */
#define HAVE_DOUBLE_BUFFER_EXTENSION 1

/* Define this if you have the XDPMS extension. This is standard on
   sufficiently-recent XFree86 systems, and possibly elsewhere. (It's
   available if the file /usr/include/X11/extensions/dpms.h exists.) */
#define HAVE_DPMS_EXTENSION 1

/* Define this if your system is Digital or SCO Unix with so-called ``Enhanced
   Security'', that is, the passwords live in /tcb/files/auth/<x>/<xyz>
   instead of in /etc/passwd, and one reads them with getprpwnam() instead of
   getpwnam(). */
/* #undef HAVE_ENHANCED_PASSWD */

/* Define to 1 if you have the `fcntl' function. */
#define HAVE_FCNTL 1

/* Define this if you have the 'forkpty' function: This allows 'phosphor' and
   'apple2' to run curses-based programs, or be used as terminal windows. */
#define HAVE_FORKPTY 1

/* Define this if you have the GDK_Pixbuf library installed. Some of the demos
   can make use of this if it is available. */
#define HAVE_GDK_PIXBUF 1

/* Define this if you have the gdk_pixbuf_apply_embedded_orientation function
   (gdk-pixbuf 2.12). */
#define HAVE_GDK_PIXBUF_APPLY_EMBEDDED_ORIENTATION 1

/* Define to 1 if you have the `getaddrinfo' function. */
#define HAVE_GETADDRINFO 1

/* Define to 1 if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define this if you have the getifaddrs() function. */
#define HAVE_GETIFADDRS 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define this if you have the gettimeofday function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the `getwd' function. */
#define HAVE_GETWD 1

/* Define this if you have OpenGL. Some of the demos require it, so if you
   don't have it, then those particular demos won't be built. (This won't
   affect the screen saver as a whole.) */
#define HAVE_GL 1

/* Define this if your version of OpenGL has the glBindTexture() routine. This
   is the case for OpenGL 1.1, but not for OpenGL 1.0. */
#define HAVE_GLBINDTEXTURE 1

/* Define this if you have the -lgle and -lmatrix libraries (GL extrusion.) */
/* #undef HAVE_GLE */

/* Define this if you have the -lgle from GLE version 3 */
/* #undef HAVE_GLE3 */

/* Define this if you have Gtk (any version.) */
#define HAVE_GTK 1

/* Define this if you have Gtk 2.x. */
#define HAVE_GTK2 1

/* Define this if you are running HPUX with so-called ``Secure Passwords'' (if
   you have /usr/include/hpsecurity.h, you probably have this.) I haven't
   tested this one, let me know if it works. */
/* #undef HAVE_HPUX_PASSWD */

/* Define this if you do pings with a `struct icmp' and an `icmp_id' slot. */
#define HAVE_ICMP 1

/* Define this if you do pings with a `struct icmphdr' and an `un.echo.id'
   slot. */
#define HAVE_ICMPHDR 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define this if you have the Independent JPEG Group's JPEG library
   installed. Some of the demos can make use of this if it is available. */
#define HAVE_JPEGLIB 1

/* Define this to target the OpenGL ES 1.x API instead of OpenGL 1.3. */
/* #undef HAVE_JWZGLES */

/* Define this if you want to use Kerberos authentication to lock/unlock the
   screen instead of your local password. This currently uses Kerberos V4, but
   a V5 server with V4 compatibility will work. WARNING: DO NOT USE AFS
   string-to-key passwords with this option. This option currently *only*
   works with standard Kerberos des_string_to_key. If your password is an AFS
   password and not a kerberos password, it will not authenticate properly.
   See the comments in driver/kpasswd.c for more information if you need it.
   */
/* #undef HAVE_KERBEROS */

/* Define this if you have Kerberos 5, meaning we need to use the Kerberos 4
   compatibility layer. */
/* #undef HAVE_KERBEROS5 */

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* Define this if your system has libcap. */
/* #undef HAVE_LIBCAP */

/* Define this if the Portable Network Graphics library is installed. It is
   basically required, but many things will more-or-less limp along without
   it. */
#define HAVE_LIBPNG 1

/* Define this if you have libsystemd. */
/* #undef HAVE_LIBSYSTEMD */

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define this if you have OpenGL, but it's the MesaGL variant. (The libraries
   have different names.) (HAVE_GL should be defined too.) */
#define HAVE_MESA_GL 1

/* Define this if you have Motif. */
/* #undef HAVE_MOTIF */

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the `nice' function. */
#define HAVE_NICE 1

/* Define this if you have the XML library headers in their old,
   non-namespaced location (you lack the gnome-xml/libxml symlink) */
/* #undef HAVE_OLD_XML_HEADERS */

/* Define this if you want to use PAM (Pluggable Authentication Modules) to
   lock/unlock the screen, instead of standard /etc/passwd authentication. */
/* #undef HAVE_PAM */

/* Define this if you have pam_fail_delay function. see driver/passwd-pam.c.
   */
/* #undef HAVE_PAM_FAIL_DELAY */

/* Define this if you have a Linux-like /proc/interrupts file which can be
   examined to determine when keyboard activity has occurred. */
/* #undef HAVE_PROC_INTERRUPTS */

/* Define this if you have a Linux-like /proc/.../oom_score_adj file which can
   be adjusted by root to exempt us from the out-of-memory . */
#define HAVE_PROC_OOM 1

/* Define this if your system supports POSIX threads. */
#define HAVE_PTHREAD 1

/* Have PTHREAD_PRIO_INHERIT. */
#define HAVE_PTHREAD_PRIO_INHERIT 1

/* Define to 1 if you have the <pty.h> header file. */
#define HAVE_PTY_H 1

/* Define to 1 if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define this if you have the Resize and Rotate extension. This is standard
   on sufficiently-recent XFree86 systems, and possibly elsewhere. (It's
   available if the file /usr/include/X11/extensions/Xrandr.h exists.) */
#define HAVE_RANDR 1

/* Define this if the RANDR library is version 1.2 or newer. */
#define HAVE_RANDR_12 1

/* Define this if you have the XReadDisplay extension (I think this is an
   SGI-only thing; it's in <X11/extensions/readdisplay.h>.) A few of the
   screenhacks will take advantage of this if it's available. */
/* #undef HAVE_READ_DISPLAY_EXTENSION */

/* Define to 1 if you have the `realpath' function. */
#define HAVE_REALPATH 1

/* Define this to enable recording of videos. */
/* #undef HAVE_RECORD_ANIM */

/* Define to 1 if you have the `sbrk' function. */
#define HAVE_SBRK 1

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if you have the `setpriority' function. */
#define HAVE_SETPRIORITY 1

/* Define to 1 if you have the `setrlimit' function. */
#define HAVE_SETRLIMIT 1

/* Define this if your system uses 'shadow' passwords, that is, the passwords
   live in /etc/shadow instead of /etc/passwd, and one reads them with
   getspnam() instead of getpwnam(). (Note that SCO systems do some random
   other thing; others might as well. See the ifdefs in driver/passwd-pwent.c
   if you're having trouble related to reading passwords.) */
#define HAVE_SHADOW_PASSWD 1

/* Define to 1 if you have the `sigaction' function. */
#define HAVE_SIGACTION 1

/* Define to 1 if you have the `sigtimedwait' function. */
/* #undef HAVE_SIGTIMEDWAIT */

/* Define to 1 if you have the `sqrtf' function. */
/* #undef HAVE_SQRTF */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if `sa_len' is a member of `struct sockaddr'. */
/* #undef HAVE_STRUCT_SOCKADDR_SA_LEN */

/* Define to 1 if you have the `syslog' function. */
#define HAVE_SYSLOG 1

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/select.h> header file. */
#define HAVE_SYS_SELECT_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/termios.h> header file. */
#define HAVE_SYS_TERMIOS_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the `uname' function. */
#define HAVE_UNAME 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <util.h> header file. */
/* #undef HAVE_UTIL_H */

/* Define this if you have the XF86MiscSetGrabKeysState function (which allows
   the Ctrl-Alt-KP_star and Ctrl-Alt-KP_slash key sequences to be temporarily
   disabled. Sadly, it doesn't affect Ctrl-Alt-BS or Ctrl-Alt-F1.) */
/* #undef HAVE_XF86MISCSETGRABKEYSSTATE */

/* Define this if you have the functions XF86VidModeGetModeLine() and
   XF86VidModeGetViewPort(), in support of virtual desktops where the X
   server's root window is bigger than the actual screen. This is an XFree86
   thing, and probably doesn't exist elsewhere. (It's available if the file
   /usr/include/X11/extensions/xf86vmode.h exists.) */
#define HAVE_XF86VMODE 1

/* Define this if you have the functions XF86VidModeGetGamma() and
   XF86VidModeSetGamma(), which allow clients to change the gamma response of
   the monitor. This is an XFree86 4.0.x thing, and probably doesn't exist
   elsewhere. (It's available if the file
   /usr/include/X11/extensions/xf86vmode.h exists and has stuff about gamma in
   it.) */
#define HAVE_XF86VMODE_GAMMA 1

/* Define this if you have the functions XF86VidModeGetGammaRamp() and
   XF86VidModeSetGammaRamp(), which provide finer-grained control than
   XF86VidMode[GS]etGamma(). These appeared in XFree86 4.1.0. */
#define HAVE_XF86VMODE_GAMMA_RAMP 1

/* Define this if you have libXft2. */
#define HAVE_XFT 1

/* Define this if you have the XHPDisableReset function (an HP only thing
   which allows the Ctrl-Sh-Reset key sequence to be temporarily disabled.) */
/* #undef HAVE_XHPDISABLERESET */

/* Define this if you have the Xinerama extension. This is standard on
   sufficiently-recent XFree86 systems, and possibly elsewhere. (It's
   available if the file /usr/include/X11/extensions/Xinerama.h exists.) */
#define HAVE_XINERAMA 1

/* Define this if you have the Xinput extension. This is standard since X11R5,
   and is thus almost everywhere. (It's available if the file
   /usr/include/X11/extensions/XInput.h exists.) */
#define HAVE_XINPUT 1

/* Define this if you have the XmComboBox Motif widget (Motif 2.0.) */
/* #undef HAVE_XMCOMBOBOX */

/* Define this if you have the XML library. */
#define HAVE_XML 1

/* Define this if you have the Xmu library. This is standard part of X, and if
   your vendor doesn't ship it, you should report that as a bug. */
#define HAVE_XMU 1

/* Define this if you have the X Shared Memory Extension. */
#define HAVE_XSHM_EXTENSION 1

/* Define this if you have the function Xutf8DrawString(). */
#define HAVE_XUTF8DRAWSTRING 1

/* Define this to remove the option of locking the screen at all. */
/* #undef NO_LOCKING */

/* This is the same as GETTEXT_PACKAGE, but for the glade generated code. */
#define PACKAGE "xscreensaver"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Whether PAM should check the result of account modules when authenticating.
   Only do this if you have account configured properly on your system. */
/* #undef PAM_CHECK_ACCOUNT_TYPE */

/* If PAM is being used, this is the name of the PAM service that xscreensaver
   will authenticate as. The default is "xscreensaver", which means that the
   PAM library will look for an "xscreensaver" line in /etc/pam.conf, or (on
   recent Linux systems) will look for a file called /etc/pam.d/xscreensaver.
   Some systems might already have a PAM installation that is configured for
   xlock, so setting this to "xlock" would also work in that case. */
/* #undef PAM_SERVICE_NAME */

/* Define if you have PAM and pam_strerror() requires two arguments. */
/* #undef PAM_STRERROR_TWO_ARGS */

/* Set the name of the password helper program, if any */
/* #undef PASSWD_HELPER_PROGRAM */

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Define this to void* if you're using X11R4 or earlier. */
/* #undef XPointer */

/* Define to 1 if the X Window System is missing or not being used. */
/* #undef X_DISPLAY_MISSING */

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
#define inline __inline__
#endif

/* Define to `int' if <sys/types.h> does not define. */
/* #undef mode_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to `int' if <sys/types.h> or <sys/socket.h> does not define. */
/* #undef socklen_t */
